#pragma once

#ifndef LIST_H
#define LIST_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "cobject.h"

static const char ListErrorHeader[ERROR_HEADER_MAXLEN] = "ListError";
/*�������*/
class ListError : public Error<ListErrorHeader> {
public:
	inline ListError(const char* info) : Error(info) {

	}
};

/*������*/
template<typename _Ty>
class List : public Container1D<_Ty>
{
	template<typename _key, typename _value>
	friend class Dict;
public:
	/*
	* @brief
	* ����б�Ԫ��
	*/
	inline friend ostream& operator << (ostream& out, const List<_Ty>& list) {
		ListNode* tmp = list.head;
		while (tmp->next != nullptr) {
			tmp = tmp->next;
			out << tmp->Data << " ";
		}
		return out;
	}
	inline friend CommaInitializer<_Ty>& operator << (List<_Ty>& list, _Ty&& ele) {
		list.append(ele);
		delete list.commainitializer;
		list.commainitializer = new CommaInitializer<_Ty>(&list);
		return *list.commainitializer;
	}
	inline friend CommaInitializer<_Ty>& operator << (List<_Ty>& list, _Ty& ele) {
		list.append(ele);
		delete list.commainitializer;
		list.commainitializer = new CommaInitializer<_Ty>(&list);
		return *list.commainitializer;
	}
protected:
	/*����ڵ�*/
	typedef struct ListNode {
		ListNode* pre = nullptr;
		_Ty Data;
		ListNode* next = nullptr;
	}ListNode;
public:
	/*Ĭ�Ϲ��캯��*/
	inline List() : Container1D<_Ty>() {
		//������ͷ����ͷ���������
		this->head = new ListNode{};
		//��β�ͱ�ͷ�غϣ���β��Ҫ�������
		this->tail = this->head;
		//��ǰλ���ڱ�ͷ
		this->current = this->head;
		//����
		this->length = 0;
		//���ų�ʼ��
		this->commainitializer = nullptr;
	}
	/*�ӳ��ȴ����б�*/
	inline List(size_t len) : Container1D<_Ty>() {
		//������ͷ����ͷ���������
		this->head = new ListNode{};
		//��β�ͱ�ͷ�غϣ���β��Ҫ�������
		this->tail = this->head;
		//��ǰλ���ڱ�ͷ
		this->current = this->head;
		for (size_t i = 0; i < len; i++) {
			//������ֵ
			ListNode* cur = new ListNode{};
			//����
			this->tail->next = cur;
			cur->pre = this->tail;
			//��β�ƶ�
			this->tail = cur;
		}
		//����
		this->length = len;
		//���ų�ʼ��
		this->commainitializer = nullptr;
	}
	/*���б����б�*/
	inline List(const initializer_list<_Ty>& list) : Container1D<_Ty>() {
		//������ͷ����ͷ���������
		this->head = new ListNode{};
		//��β�ͱ�ͷ�غϣ���β��Ҫ�������
		this->tail = this->head;
		//��ǰλ���ڱ�ͷ
		this->current = this->head;
		for (auto i = list.begin(); i != list.end(); i++) {
			this->append(*i);
		}
		this->length = list.size();
		//���ų�ʼ��
		this->commainitializer = nullptr;
	}
	/*�������캯��*/
	inline List(const List<_Ty>& list) {
		//������ͷ����ͷ���������
		this->head = new ListNode{};
		//��β�ͱ�ͷ�غϣ���β��Ҫ�������
		this->tail = this->head;
		//��ǰλ���ڱ�ͷ
		this->current = this->head;
		//���ų�ʼ��
		this->commainitializer = nullptr;

		ListNode* cur = list.head;	//�׵�ַ
		for (size_t i = 0; i < list.length; i++) {
			cur = cur->next;
			this->append(cur->Data);
		}
	}
	/*��������*/
	~List() {
		this->clear();
		delete this->tail;
		delete this->commainitializer;
	}
	/*@brief
	* ��ĩβ׷��Ԫ��
	* @param
	* ele : Ԫ��
	* @return
	* ��
	*/
	inline void append(const _Ty& ele) {
		//������ֵ
		ListNode* cur = new ListNode{ NULL,ele,NULL };
		//����
		this->tail->next = cur;
		cur->pre = this->tail;
		//��β�ƶ�
		this->tail = cur;
		//��������
		this->length++;
	}
	/*@brief
	* ��ĩβ׷��Ԫ��
	* @param
	* ele : Ԫ��
	* @return
	* ��
	*/
	inline void append(_Ty&& ele) {
		//������ֵ
		ListNode* cur = new ListNode{ NULL,ele,NULL };
		//����
		this->tail->next = cur;
		cur->pre = this->tail;
		//��β�ƶ�
		this->tail = cur;
		//��������
		this->length++;
	}
	/*
	* @brief
	* �޸�ĳ��ֵ
	* @param
	* index : ��Ҫ�޸ĵ�ֵ������
	* ele : �޸ĺ��ֵ
	* @return
	* ��
	*/
	inline void replace(const size_t index, _Ty& ele) {
		this->check_index(index);
		this->search(index)->Data = ele;
	}
	/*
	* @brief
	* �޸�ĳ��ֵ
	* @param
	* index : ��Ҫ�޸ĵ�ֵ������
	* ele : �޸ĺ��ֵ
	* @return
	* ��
	*/
	inline void replace(int index, _Ty&& ele) {
		this->check_index(index);
		this->search(index)->Data = ele;
	}
	/*@brief
	* �ϲ������б�
	* @param
	* list : �б�
	* @return
	* ��
	*/
	inline void concat(const List<_Ty>& list) {
		ListNode* cur = list.head;	//�׵�ַ
		for (size_t i = 0; i < list.length; i++) {
			cur = cur->next;
			this->append(cur->Data);
		}
		this->length += list.length;
	}
	/*@brief
	* ����Ԫ��
	* @param
	* index : ����λ������
	* ele : �����Ԫ��
	* @return
	* ��
	*/
	inline void insert(const size_t index, _Ty& ele) {
		this->check_index(index);
		//�ҵ���ǰλ�õĽڵ�
		ListNode* cur = this->search(index);
		//�����½ڵ�
		ListNode* node = new ListNode{ cur->pre,ele,cur };
		cur->pre->next = node;
		cur->pre = node;
		//��������
		this->length++;
	}
	/*@brief
	* ����Ԫ��
	* @param
	* index : ����λ������
	* ele : �����Ԫ��
	* @return
	* ��
	*/
	inline void insert(const size_t index, _Ty&& ele) {
		this->check_index(index);
		//�ҵ���ǰλ�õĽڵ�
		ListNode* cur = this->search(index);
		//�����½ڵ�
		ListNode* node = new ListNode{ cur->pre,ele,cur };
		cur->pre->next = node;
		cur->pre = node;
		//��������
		this->length++;
	}
	/*
	* @brief
	* ������ָ���ƶ�����һ��λ�ã���������һ��λ�õ�Ԫ��
	* @param
	* ��
	* @return
	* ��һ��λ��Ԫ��
	*/
	inline _Ty& next() {
		this->current = this->current->next;
		//���Ϊ�գ�˵������β��
		if (this->current == nullptr) {
			emit(ListError("������ָ�뵽���β\n"));
		}
		return this->current->Data;
	}
	/*
	* @brief
	* ��ȡ������ָ��ĵ�ǰλ��
	* @param
	* ��
	* @return
	* ��ǰλ��
	*/
	inline _Ty& location() const {
		return this->current->Data;
	}
	/*
	* @brief
	* ������ָ��ص���ͷ
	* @param
	* ��
	* @return
	* ��
	*/
	inline void iterreset() {
		this->current = this->head;
	}
	/*@brief
	* ɾ��ָ��Ԫ��
	* @param
	* index : ��Ҫɾ����Ԫ������
	* @return
	* ��
	*/
	inline void remove(const size_t index) {
		this->check_index(index);
		ListNode* node = this->search(index);
		//����ǰλ�ýڵ�ǰ�������ڵ����
		node->pre->next = node->next;
		//����������һ��
		if (node->next != nullptr) {
			node->next->pre = node->pre;
		}
		else {
			//β����ǰ�ƶ�һ��λ��
			this->tail = node->pre;
		}
		//ɾ����ǰ�ڵ�
		delete node;
		//���ȼ���
		this->length--;
	}
	/*@brief
	* ��ȡָ��Ԫ��
	* @param
	* index : ����ֵ
	* @return
	* ������λ���ϵ�Ԫ��
	*/
	inline _Ty& at(const size_t index) const {
		this->check_index(index);
		return this->search(index)->Data;
	}
	/*@brief
	* ����б�
	* @param
	* ��
	* @return
	* ��
	*/
	inline void clear() {
		ListNode* cur = this->head->next;
		ListNode* cur_next = nullptr;
		for (size_t i = 0; i < this->length; i++) {
			cur_next = cur->next;	//������һ���ڵ�
			delete cur;				//ɾ����ǰֵ
			cur = cur_next;			//�ƶ�����һ���ڵ�
		}
		this->length = 0;
		this->tail = this->head;
	}
	/*
	* @brief
	* �Ⱥ���������
	* @param
	* list: ��һ���б�
	* @return
	* ��
	*/
	inline void operator = (const List<_Ty>& list) {
		this->clear();
		ListNode* ptr = list.head;
		for (size_t i = 0; i < list.length; i++) {
			ptr = ptr->next;
			this->append(ptr->Data);
		}
	}
protected:
	/*��������Ƿ�Խ��*/
	virtual inline void check_index(const size_t index) const {
		//�Ⱥŷǳ���Ҫ
		if (index >= this->length) {
			emit(IndexError("����������Χ"));
		}
	}
	/*
	* @brief
	* ��ȡ��ǰ����λ�õĽڵ�
	* @param
	* index : ����ֵ
	* @return
	* �ڵ�
	*/
	ListNode* search(const size_t index) const {
		ListNode* cur = this->head->next;
		for (size_t i = 0; i < index; i++) {
			cur = cur->next;
		}
		return cur;
	}
protected:
	/*�洢���ŷָ���*/
	CommaInitializer<_Ty>* commainitializer;
	/*��ͷ*/
	ListNode* head;
	/*��β*/
	ListNode* tail;
	/*������ָ��*/
	ListNode* current;
};


#endif // !LIST_H