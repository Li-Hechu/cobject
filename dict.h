#pragma once
#pragma warning(disable:6011)

#ifndef DICT_H
#define DICT_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "vector.h"
#include "list.h"

static const char DictErrorHeader[ERROR_HEADER_MAXLEN] = "DictError";
/*�ֵ����*/
class DictError : public Error<DictErrorHeader> {
public:
	inline DictError(const char* info) : Error(info) {

	}
};


/*�ֵ���*/
template<typename _key, typename _value>
class Dict : public CObject {
public:
	/*�ֵ�ʵ��*/
	typedef struct DictEntry {
		unsigned long long hash;	//��ϣֵ
		_key key;					//��
		_value value;				//ֵ
	}DictEntry;
	/*����Ӧ�����ݰ�*/
	typedef struct KeyDataeWrap {
		unsigned long long hashvalue;	//��ϣֵ
		List<size_t>* list;				//����Ӧ������
		_value* value;					//����Ӧ��ֵ������������Ϊ��
		size_t rank;					//��ǰ�����е�����
		size_t index;					//�ֵ�����ʵ���б��е�����
	}KeyDataWrap;
public:
	inline friend ostream& operator << (ostream& out, const Dict& dict) {
		Dict::DictEntry* entry = nullptr;
		out << "{";
		for (size_t i = 0; i < dict.entries->len(); i++) {
			entry = dict.entries->at(i);
			out << entry->key << ":" << entry->value << ",";
		}
		out << "}";
		return out;
	}
public:
	/*Ĭ�Ϲ��캯��*/
	inline Dict() : CObject() {
		//�жϼ��Ƿ����ת��Ϊ��ϣֵ
		if (!this->keyhashable()) {
			emit(DictError("�����Ͳ��ɹ�ϣ��"));
		}
		//��ʼ��
		this->entries = new Vector<Dict::DictEntry*>();
		this->indices = new Vector<List<size_t>*>(this->_Eve_Con_Length);
		for (size_t i = 0; i < this->_Eve_Con_Length; i++) {
			this->indices->at(i) = new List<size_t>();
		}
		this->ptr = nullptr;
	}
	/*��������*/
	inline ~Dict() {
		delete this->entries;
		delete this->indices;
		this->ptr = nullptr;
	}
	/*
	* @brief
	* ���ü�-ֵ�ԣ������������޸ģ������������
	* @param
	* key : ��
	* @param
	* value : ֵ
	* @return
	* ��
	*/
	inline void set(const _key& key, const _value& value) {
		//Ѱ��
		Dict::KeyDataWrap* wrap = this->search(key);
		if (wrap->value != nullptr) {
			//�ҵ�����Ӧ��ֵ�������޸�
			*wrap->value = *new _value(value);	//ֵ����
			delete wrap;
			//�˳�����
			return;
		}
		//�ڹ�ϣ���д洢�ֵ�ʵ������ʵ���б��е�����
		wrap->list->append(this->entries->len());	//Ϊ�˱�֤ʵ���б�������0��ʼ����仰Ӧ����ִ��
		this->entries->append(new Dict::DictEntry{ wrap->hashvalue,key,value });	//�����ֵ�ʵ����
		delete wrap;	//�ڴ����
	}
	/*
	* @brief
	* ���ݼ���ȡֵ
	* @param
	* key : ��
	* @return
	* ����Ӧ��ֵ
	*/
	inline _value& get(const _key& key) {
		Dict::KeyDataWrap* wrap = this->search(key);
		if (wrap->value == nullptr) {
			emit(DictError("��������"));
		}
		_value& var = *wrap->value;
		delete wrap;
		return var;
	}
	/*
	* @brief
	* ɾ���ֵ�Ԫ�أ�����������ִ�в���
	* @param
	* key : ��
	* @return
	* ��
	*/
	inline void remove(const _key& key) {
		Dict::KeyDataWrap* wrap = this->search(key);
		//���û���ҵ���ֱ�ӷ���
		if (wrap->value == nullptr) {
			delete wrap;
			return;
		}
		//�Ƴ�Ԫ��
		wrap->list->remove(wrap->rank);
		this->entries->remove(wrap->index);
		delete wrap;
	}
	/*
	* @brief
	* ��ȡ�ֵ�Ԫ�ظ���
	* @param
	* ��
	* @return
	* ��
	*/
	inline size_t size() const {
		return this->entries->len();
	}
	/*
	* @brief
	* ��ȡ���м�
	* @param
	* ��
	* @return
	* ���м����б�
	*/
	inline Vector<_key>& keys() {
		Vector<_key>* keylist = new Vector<_key>(this->entries->len());
		for (size_t i = 0; i < this->entries->len(); i++) {
			keylist->at(i) = this->entries->at(i)->key;
		}
		return *keylist;
	}
	/*
	* @brief
	* ��ȡ����ֵ
	* @param
	* ��
	* @return
	* ����ֵ���б�
	*/
	inline Vector<_value>& values() {
		Vector<_value>* keylist = new Vector<_value>(this->entries->len());
		for (size_t i = 0; i < this->entries->len(); i++) {
			keylist->at(i) = this->entries->at(i)->value;
		}
		return *keylist;
	}
protected:
	/*
	* @brief
	* ��ȡ���Ĺ�ϣֵ
	* @param
	* obj : Ԫ��
	* @return
	* Ԫ�ع�ϣֵ
	*/
	virtual inline const unsigned long long hashvalue(const unsigned long long& obj) {
		///������������ͣ�����ת��Ϊunsigned long long��Ϊ��ϣֵ
		return obj;
	}
	virtual inline const unsigned long long hashvalue(const char* obj) {
		///���Ϊ�ַ����ͣ����������㷨��Ϊ��ϣֵ
		unsigned long long charhashvalue = 0;
		const unsigned long long base = 13;		//���������
		for (size_t i = 0; i < strlen(obj); i++) {
			charhashvalue += charhashvalue * base + obj[i] - 31;	//��ȥ����ʾ�ַ������ASCII��
		}
		return charhashvalue;
	}
	/*
	* @brief
	* ����ϣֵת��Ϊ��ϣ������
	* @param
	* hash : ��ϣֵ
	* @return
	* ��ϣ������
	*/
	inline unsigned char hashindex(const unsigned long long hash) {
		///�ñ�����ַ�������������ȵ�������Ϊ��ϣ����
		return hash % this->_Eve_Con_Length;
	}
	/*
	* @brief
	* �жϼ������Ƿ����ת��Ϊ��ϣֵ
	* @param
	* ��
	* @return
	* boolֵ��1��ʾ���ԣ�0��ʾ������
	*/
	inline bool keyhashable() {
		///ֻ��c++ԭ���������͡��ַ����Ϳ�����Ϊ��������
		if (is_same<_key, short>::value || is_same<_key, unsigned short>::value || \
			is_same<_key, int>::value || is_same<_key, unsigned int>::value || \
			is_same<_key, long>::value || is_same<_key, unsigned long>::value || \
			is_same<_key, long long>::value || is_same<_key, unsigned long long>::value || \
			is_same<_key, float>::value || is_same<_key, double>::value || \
			is_same<_key, char>::value || is_same<_key, unsigned char>::value || \
			is_same<_key, char*>::value || is_same<_key, const char*>::value) {
			return true;
		}
		return false;
	}
	/*
	* @brief
	* ���ݼ�Ѱ��ֵ
	* @param
	* key : ��
	* @return
	* ����Ӧ�����ݰ�
	*/
	inline Dict::KeyDataWrap* search(const _key& key) {
		//��ϣֵ
		unsigned long long hvalue = this->hashvalue(key);
		//��ϣ������
		unsigned char hindex = this->hashindex(hvalue);
		//��ǰλ�ö�Ӧ������
		List<size_t>* list = this->indices->at(hindex);
		this->ptr = list->head;				//����ͷ���洢Ԫ��
		//�ֵ�ʵ��ָ��
		Dict::DictEntry* entry = nullptr;
		size_t rank = 0;	//��ǰ��������
		//�Ե�ǰλ�õ�Ԫ�ؽ��б�������
		while (this->ptr->next != nullptr) {
			this->ptr = this->ptr->next;
			//��ȡ��ǰ��ϣ��λ�ö�Ӧ��Ԫ��
			entry = this->entries->at(this->ptr->Data);
			//�������ͬ��Ԫ�أ�Ҳ����ϣֵһ��
			if (hvalue == entry->hash) {
				return new KeyDataWrap{ hvalue, list, &entry->value, rank, this->ptr->Data };
			}
			rank++;
		}
		return new KeyDataWrap{ hvalue, list, nullptr, rank, 0 };
	}
protected:
	/*ÿ���������ĳ���*/
	static const size_t _Eve_Con_Length = 16;
	/*�ֵ�ʵ���б�*/
	Vector<Dict::DictEntry*>* entries;
	/*�ֵ�������ϣ��*/
	Vector<List<size_t>*>* indices;
	/*����ͷ�ڵ�*/
	List<size_t>::ListNode* ptr;
};

#endif