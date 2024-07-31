#pragma once
#pragma warning(disable:6011)

#ifndef DICT_H
#define DICT_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "vector.h"
#include "list.h"

static const char DictErrorHeader[ERROR_HEADER_MAXLEN] = "DictError";
/*字典错误*/
class DictError : public Error<DictErrorHeader> {
public:
	inline DictError(const char* info) : Error(info) {

	}
};


/*字典类*/
template<typename _key, typename _value>
class Dict : public CObject {
public:
	/*字典实体*/
	typedef struct DictEntry {
		unsigned long long hash;	//哈希值
		_key key;					//键
		_value value;				//值
	}DictEntry;
	/*键对应的数据包*/
	typedef struct KeyDataeWrap {
		unsigned long long hashvalue;	//哈希值
		List<size_t>* list;				//键对应的链表
		_value* value;					//键对应的值，若不存在则为空
		size_t rank;					//当前链表中的索引
		size_t index;					//字典项在实体列表中的索引
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
	/*默认构造函数*/
	inline Dict() : CObject() {
		//判断键是否可以转换为哈希值
		if (!this->keyhashable()) {
			emit(DictError("键类型不可哈希化"));
		}
		//初始化
		this->entries = new Vector<Dict::DictEntry*>();
		this->indices = new Vector<List<size_t>*>(this->_Eve_Con_Length);
		for (size_t i = 0; i < this->_Eve_Con_Length; i++) {
			this->indices->at(i) = new List<size_t>();
		}
		this->ptr = nullptr;
	}
	/*析构函数*/
	inline ~Dict() {
		delete this->entries;
		delete this->indices;
		this->ptr = nullptr;
	}
	/*
	* @brief
	* 设置键-值对，若键存在在修改，不存在则添加
	* @param
	* key : 键
	* @param
	* value : 值
	* @return
	* 无
	*/
	inline void set(const _key& key, const _value& value) {
		//寻找
		Dict::KeyDataWrap* wrap = this->search(key);
		if (wrap->value != nullptr) {
			//找到键对应的值，进行修改
			*wrap->value = *new _value(value);	//值拷贝
			delete wrap;
			//退出函数
			return;
		}
		//在哈希表中存储字典实体项在实体列表中的索引
		wrap->list->append(this->entries->len());	//为了保证实体列表索引从0开始，这句话应该先执行
		this->entries->append(new Dict::DictEntry{ wrap->hashvalue,key,value });	//创建字典实体项
		delete wrap;	//内存控制
	}
	/*
	* @brief
	* 根据键获取值
	* @param
	* key : 键
	* @return
	* 键对应的值
	*/
	inline _value& get(const _key& key) {
		Dict::KeyDataWrap* wrap = this->search(key);
		if (wrap->value == nullptr) {
			emit(DictError("键不存在"));
		}
		_value& var = *wrap->value;
		delete wrap;
		return var;
	}
	/*
	* @brief
	* 删除字典元素，若不存在则不执行操作
	* @param
	* key : 键
	* @return
	* 无
	*/
	inline void remove(const _key& key) {
		Dict::KeyDataWrap* wrap = this->search(key);
		//如果没有找到，直接返回
		if (wrap->value == nullptr) {
			delete wrap;
			return;
		}
		//移除元素
		wrap->list->remove(wrap->rank);
		this->entries->remove(wrap->index);
		delete wrap;
	}
	/*
	* @brief
	* 获取字典元素个数
	* @param
	* 无
	* @return
	* 无
	*/
	inline size_t size() const {
		return this->entries->len();
	}
	/*
	* @brief
	* 获取所有键
	* @param
	* 无
	* @return
	* 所有键的列表
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
	* 获取所有值
	* @param
	* 无
	* @return
	* 所有值的列表
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
	* 获取键的哈希值
	* @param
	* obj : 元素
	* @return
	* 元素哈希值
	*/
	virtual inline const unsigned long long hashvalue(const unsigned long long& obj) {
		///如果是数字类型，则将其转换为unsigned long long作为哈希值
		return obj;
	}
	virtual inline const unsigned long long hashvalue(const char* obj) {
		///如果为字符类型，采用以下算法作为哈希值
		unsigned long long charhashvalue = 0;
		const unsigned long long base = 13;		//最好是质数
		for (size_t i = 0; i < strlen(obj); i++) {
			charhashvalue += charhashvalue * base + obj[i] - 31;	//减去非显示字符的最大ASCII码
		}
		return charhashvalue;
	}
	/*
	* @brief
	* 将哈希值转换为哈希表索引
	* @param
	* hash : 哈希值
	* @return
	* 哈希表索引
	*/
	inline unsigned char hashindex(const unsigned long long hash) {
		///用变量地址除以子容器长度的余数作为哈希索引
		return hash % this->_Eve_Con_Length;
	}
	/*
	* @brief
	* 判断键类型是否可以转换为哈希值
	* @param
	* 无
	* @return
	* bool值，1表示可以，0表示不可以
	*/
	inline bool keyhashable() {
		///只有c++原生数字类型、字符类型可以作为键的类型
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
	* 根据键寻找值
	* @param
	* key : 键
	* @return
	* 键对应的数据包
	*/
	inline Dict::KeyDataWrap* search(const _key& key) {
		//哈希值
		unsigned long long hvalue = this->hashvalue(key);
		//哈希表索引
		unsigned char hindex = this->hashindex(hvalue);
		//当前位置对应的链表
		List<size_t>* list = this->indices->at(hindex);
		this->ptr = list->head;				//链表头不存储元素
		//字典实体指针
		Dict::DictEntry* entry = nullptr;
		size_t rank = 0;	//当前链表索引
		//对当前位置的元素进行遍历查找
		while (this->ptr->next != nullptr) {
			this->ptr = this->ptr->next;
			//获取当前哈希表位置对应的元素
			entry = this->entries->at(this->ptr->Data);
			//如果有相同的元素，也即哈希值一致
			if (hvalue == entry->hash) {
				return new KeyDataWrap{ hvalue, list, &entry->value, rank, this->ptr->Data };
			}
			rank++;
		}
		return new KeyDataWrap{ hvalue, list, nullptr, rank, 0 };
	}
protected:
	/*每个子容器的长度*/
	static const size_t _Eve_Con_Length = 16;
	/*字典实体列表*/
	Vector<Dict::DictEntry*>* entries;
	/*字典索引哈希表*/
	Vector<List<size_t>*>* indices;
	/*链表头节点*/
	List<size_t>::ListNode* ptr;
};

#endif