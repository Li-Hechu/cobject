#pragma once

#ifndef LIST_H
#define LIST_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "cobject.h"

static const char ListErrorHeader[ERROR_HEADER_MAXLEN] = "ListError";
/*链表错误*/
class ListError : public Error<ListErrorHeader> {
public:
	inline ListError(const char* info) : Error(info) {

	}
};

/*链表类*/
template<typename _Ty>
class List : public Container1D<_Ty>
{
	template<typename _key, typename _value>
	friend class Dict;
public:
	/*
	* @brief
	* 输出列表元素
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
	/*链表节点*/
	typedef struct ListNode {
		ListNode* pre = nullptr;
		_Ty Data;
		ListNode* next = nullptr;
	}ListNode;
public:
	/*默认构造函数*/
	inline List() : Container1D<_Ty>() {
		//创建表头，表头不存放数据
		this->head = new ListNode{};
		//表尾和表头重合，表尾需要存放数据
		this->tail = this->head;
		//当前位置在表头
		this->current = this->head;
		//长度
		this->length = 0;
		//逗号初始化
		this->commainitializer = nullptr;
	}
	/*从长度创建列表*/
	inline List(size_t len) : Container1D<_Ty>() {
		//创建表头，表头不存放数据
		this->head = new ListNode{};
		//表尾和表头重合，表尾需要存放数据
		this->tail = this->head;
		//当前位置在表头
		this->current = this->head;
		for (size_t i = 0; i < len; i++) {
			//创建新值
			ListNode* cur = new ListNode{};
			//连接
			this->tail->next = cur;
			cur->pre = this->tail;
			//表尾移动
			this->tail = cur;
		}
		//长度
		this->length = len;
		//逗号初始化
		this->commainitializer = nullptr;
	}
	/*从列表创建列表*/
	inline List(const initializer_list<_Ty>& list) : Container1D<_Ty>() {
		//创建表头，表头不存放数据
		this->head = new ListNode{};
		//表尾和表头重合，表尾需要存放数据
		this->tail = this->head;
		//当前位置在表头
		this->current = this->head;
		for (auto i = list.begin(); i != list.end(); i++) {
			this->append(*i);
		}
		this->length = list.size();
		//逗号初始化
		this->commainitializer = nullptr;
	}
	/*拷贝构造函数*/
	inline List(const List<_Ty>& list) {
		//创建表头，表头不存放数据
		this->head = new ListNode{};
		//表尾和表头重合，表尾需要存放数据
		this->tail = this->head;
		//当前位置在表头
		this->current = this->head;
		//逗号初始化
		this->commainitializer = nullptr;

		ListNode* cur = list.head;	//首地址
		for (size_t i = 0; i < list.length; i++) {
			cur = cur->next;
			this->append(cur->Data);
		}
	}
	/*析构函数*/
	~List() {
		this->clear();
		delete this->tail;
		delete this->commainitializer;
	}
	/*@brief
	* 在末尾追加元素
	* @param
	* ele : 元素
	* @return
	* 无
	*/
	inline void append(const _Ty& ele) {
		//创建新值
		ListNode* cur = new ListNode{ NULL,ele,NULL };
		//连接
		this->tail->next = cur;
		cur->pre = this->tail;
		//表尾移动
		this->tail = cur;
		//长度增加
		this->length++;
	}
	/*@brief
	* 在末尾追加元素
	* @param
	* ele : 元素
	* @return
	* 无
	*/
	inline void append(_Ty&& ele) {
		//创建新值
		ListNode* cur = new ListNode{ NULL,ele,NULL };
		//连接
		this->tail->next = cur;
		cur->pre = this->tail;
		//表尾移动
		this->tail = cur;
		//长度增加
		this->length++;
	}
	/*
	* @brief
	* 修改某个值
	* @param
	* index : 需要修改的值的索引
	* ele : 修改后的值
	* @return
	* 无
	*/
	inline void replace(const size_t index, _Ty& ele) {
		this->check_index(index);
		this->search(index)->Data = ele;
	}
	/*
	* @brief
	* 修改某个值
	* @param
	* index : 需要修改的值的索引
	* ele : 修改后的值
	* @return
	* 无
	*/
	inline void replace(int index, _Ty&& ele) {
		this->check_index(index);
		this->search(index)->Data = ele;
	}
	/*@brief
	* 合并两个列表
	* @param
	* list : 列表
	* @return
	* 无
	*/
	inline void concat(const List<_Ty>& list) {
		ListNode* cur = list.head;	//首地址
		for (size_t i = 0; i < list.length; i++) {
			cur = cur->next;
			this->append(cur->Data);
		}
		this->length += list.length;
	}
	/*@brief
	* 插入元素
	* @param
	* index : 插入位置索引
	* ele : 插入的元素
	* @return
	* 无
	*/
	inline void insert(const size_t index, _Ty& ele) {
		this->check_index(index);
		//找到当前位置的节点
		ListNode* cur = this->search(index);
		//创建新节点
		ListNode* node = new ListNode{ cur->pre,ele,cur };
		cur->pre->next = node;
		cur->pre = node;
		//长度增加
		this->length++;
	}
	/*@brief
	* 插入元素
	* @param
	* index : 插入位置索引
	* ele : 插入的元素
	* @return
	* 无
	*/
	inline void insert(const size_t index, _Ty&& ele) {
		this->check_index(index);
		//找到当前位置的节点
		ListNode* cur = this->search(index);
		//创建新节点
		ListNode* node = new ListNode{ cur->pre,ele,cur };
		cur->pre->next = node;
		cur->pre = node;
		//长度增加
		this->length++;
	}
	/*
	* @brief
	* 迭代器指针移动到下一个位置，并返回下一个位置的元素
	* @param
	* 无
	* @return
	* 下一个位置元素
	*/
	inline _Ty& next() {
		this->current = this->current->next;
		//如果为空，说明到结尾了
		if (this->current == nullptr) {
			emit(ListError("迭代器指针到达结尾\n"));
		}
		return this->current->Data;
	}
	/*
	* @brief
	* 获取迭代器指针的当前位置
	* @param
	* 无
	* @return
	* 当前位置
	*/
	inline _Ty& location() const {
		return this->current->Data;
	}
	/*
	* @brief
	* 迭代器指针回到开头
	* @param
	* 无
	* @return
	* 无
	*/
	inline void iterreset() {
		this->current = this->head;
	}
	/*@brief
	* 删除指定元素
	* @param
	* index : 需要删除的元素索引
	* @return
	* 无
	*/
	inline void remove(const size_t index) {
		this->check_index(index);
		ListNode* node = this->search(index);
		//将当前位置节点前后两个节点相接
		node->pre->next = node->next;
		//如果不是最后一个
		if (node->next != nullptr) {
			node->next->pre = node->pre;
		}
		else {
			//尾部往前移动一个位置
			this->tail = node->pre;
		}
		//删除当前节点
		delete node;
		//长度减少
		this->length--;
	}
	/*@brief
	* 获取指定元素
	* @param
	* index : 索引值
	* @return
	* 该索引位置上的元素
	*/
	inline _Ty& at(const size_t index) const {
		this->check_index(index);
		return this->search(index)->Data;
	}
	/*@brief
	* 清空列表
	* @param
	* 无
	* @return
	* 无
	*/
	inline void clear() {
		ListNode* cur = this->head->next;
		ListNode* cur_next = nullptr;
		for (size_t i = 0; i < this->length; i++) {
			cur_next = cur->next;	//保存下一个节点
			delete cur;				//删除当前值
			cur = cur_next;			//移动到下一个节点
		}
		this->length = 0;
		this->tail = this->head;
	}
	/*
	* @brief
	* 等号运算重载
	* @param
	* list: 另一个列表
	* @return
	* 无
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
	/*检查索引是否越界*/
	virtual inline void check_index(const size_t index) const {
		//等号非常重要
		if (index >= this->length) {
			emit(IndexError("索引超出范围"));
		}
	}
	/*
	* @brief
	* 获取当前索引位置的节点
	* @param
	* index : 索引值
	* @return
	* 节点
	*/
	ListNode* search(const size_t index) const {
		ListNode* cur = this->head->next;
		for (size_t i = 0; i < index; i++) {
			cur = cur->next;
		}
		return cur;
	}
protected:
	/*存储逗号分隔符*/
	CommaInitializer<_Ty>* commainitializer;
	/*表头*/
	ListNode* head;
	/*表尾*/
	ListNode* tail;
	/*迭代器指针*/
	ListNode* current;
};


#endif // !LIST_H