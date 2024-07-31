#pragma once

#ifndef VECTOR_H
#define VECTOR_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "cobject.h"

template<typename _Ty>
class Vector : public Container1D<_Ty>
{
public:
	inline friend CommaInitializer<_Ty>& operator << (Vector<_Ty>& vec, _Ty& ele) {
		vec.append(ele);
		delete vec.commainitializer;
		vec.commainitializer = new CommaInitializer<_Ty>(&vec);
		return *vec.commainitializer;
	}
	inline friend CommaInitializer<_Ty>& operator << (Vector<_Ty>& vec, _Ty&& ele) {
		vec.append(ele);
		delete vec.commainitializer;
		vec.commainitializer = new CommaInitializer<_Ty>(&vec);
		return *vec.commainitializer;
	}
	inline friend ostream& operator << (ostream& out, const Vector<_Ty>& vec) {
		for (int i = 0; i < vec.length; i++) {
			out << vec.container[i] << " ";
		}
		return out;
	}
public:
	/*
	* @brief
	* 创建空序列
	*/
	inline Vector() : Container1D<_Ty>() {
		this->container = nullptr;
		this->commainitializer = nullptr;
	}
	/*
	* @brief
	* 创建指定长度的序列
	* @param
	* n ：序列长度
	*/
	inline Vector(const size_t n) : Container1D<_Ty>() {
		this->container = new _Ty[n]{};
		this->length = n;
		this->size = n;
		this->commainitializer = nullptr;
	}
	/*
	* @brief
	* 从一维数组创建序列
	* @param
	* list ：一维数组
	*/
	inline Vector(initializer_list<_Ty> list) {
		this->length = list.size();
		this->size = this->length;
		this->container = new _Ty[this->length]{};
		this->commainitializer = nullptr;
		size_t i = 0;
		for (auto start = list.begin(); start != list.end(); start++) {
			*(this->container + i++) = *start;
		}
	}
	/*
	* @brief
	* 深拷贝构造
	* @param
	* vec ：另一个序列实例
	*/
	inline Vector(const Vector<_Ty>& vec) {
		this->size = vec.size;
		this->length = vec.length;
		this->container = new _Ty[this->size]{};
		this->commainitializer = nullptr;
		deepcopy<_Ty>(this->container, this->size, vec.container, vec.size);
	}
	/*析构函数*/
	virtual ~Vector() {
		delete[] this->container;
		delete this->commainitializer;
	}
	/*
	* @brief
	* 获取起始地址
	* @param
	* 无
	* @return
	* 起始地址
	*/
	inline const _Ty* begin() const {
		return this->container;
	}
	/*
	* @brief
	* 获取结束地址，不包含
	* @param
	* 无
	* @return
	* 结束地址
	*/
	inline const _Ty* end() const {
		return this->container + this->length;
	}
	/*
	* @brief
	* 在末尾追加元素，左值引用
	* @param
	* ele ：追加的元素
	* @return
	* 无
	*/
	inline virtual void append(const _Ty& ele) {
		//如果长度不在容量内
		if (this->length >= this->size) {
			//获取扩充长度
			size_t expand = this->expand_length(this->length);
			//扩充序列
			this->memory_expand(expand);
		}
		//赋值
		this->container[this->length] = ele;
		//长度加1
		this->length++;
	}
	/*
	* @brief
	* 在末尾追加元素，右值引用
	* @param
	* ele ：追加的元素
	* @return
	* 无
	*/
	inline virtual void append(_Ty&& ele) {
		//如果长度不在容量内
		if (this->length >= this->size) {
			//获取扩充长度
			size_t expand = this->expand_length(this->length);
			//扩充序列
			this->memory_expand(expand);
		}
		//赋值
		this->container[this->length] = ele;
		//长度加1
		this->length++;
	}
	/*
	* @brief
	* 获取指定索引的值
	* @param
	* index ：索引值
	* @return
	* 该索引对应的数据
	*/
	inline virtual _Ty& at(const size_t index) const {
		this->check_index(index);
		return this->container[index];
	}
	/*
	* @brief
	* 插入元素，左值引用
	* @param
	* index ：插入的索引位置
	* ele ：插入的元素
	* @return
	* 无
	*/
	inline void insert(const size_t index, _Ty& ele) {
		this->check_index(index);
		//追加
		this->append(ele);
		//交换
		for (size_t i = this->length - 1; i > index; i--) {
			this->container[i] = this->container[i - 1];
		}
		this->container[index] = ele;
	}
	/*
	* @brief
	* 插入元素，右值引用
	* @param
	* index ：插入的索引位置
	* ele ：插入的元素
	* @return
	* 无
	*/
	inline void insert(const size_t index, _Ty&& ele) {
		this->check_index(index);
		//追加
		this->append(ele);
		//交换
		for (size_t i = this->length - 1; i > index; i--) {
			this->container[i] = this->container[i - 1];
		}
		this->container[index] = ele;
	}
	/*
	* @brief
	* 替换元素，左值引用
	* @param
	* index ：需要替换的元素索引
	* ele ：替换元素
	* @return
	* 无
	*/
	inline void replace(const size_t index, _Ty& ele) {
		this->check_index(index);
		//替换
		this->container[index] = ele;
	}
	/*
	* @brief
	* 替换元素，右值引用
	* @param
	* index ：需要替换的元素索引
	* ele ：替换元素
	* @return
	* 无
	*/
	inline void replace(const size_t index, _Ty&& ele) {
		this->check_index(index);
		//替换
		this->container[index] = ele;
	}
	/*
	* @brief
	* 移除元素
	* @param
	* index ：需要移除的元素的索引
	* @return
	* 无
	*/
	inline void remove(const size_t index) {
		this->check_index(index);
		//后面元素往前
		for (size_t i = index; i < this->length - 1; i++) {
			this->container[i] = this->container[i + 1];
		}
		//长度减1
		this->length--;
	}
	/*
	* @brief
	* 将第二个列表合并在本列表中
	* @param
	* arr : 合并的列表
	* @return
	* 无
	*/
	inline void concat(const Vector<_Ty>& vec) {
		if (vec.length == 0) {
			return;
		}
		//如果剩余空间不够
		if (this->length + vec.length >= this->size) {
			//扩容
			this->memory_expand(vec.length);
		}
		//复制
		deepcopy<_Ty>(this->container + this->length, this->size, vec.container, vec.length);
		//长度更新
		this->length += vec.length;
	}
	/*
	* @brief
	* 清空所有元素
	* @param
	* 无
	* @return
	* 无
	*/
	inline void clear() {
		delete[] this->container;
		this->container = nullptr;
		this->length = 0;
		this->size = 0;
	}
	/*
	* @brief
	* 深拷贝赋值
	* @param
	* vec: vector对象
	* @return
	* 无
	*/
	inline virtual void operator=(const Vector<_Ty>& vec) {
		delete[] this->container;
		delete this->commainitializer;
		this->size = vec.size;
		this->length = vec.length;
		this->container = new _Ty[this->size]{};
		this->commainitializer = nullptr;
		deepcopy<_Ty>(this->container, this->size, vec.container, vec.size);
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
	* 内存连续分布容器扩充容量
	* @param
	* expand_len : 需要扩充的长度
	* @return
	* 无
	*/
	virtual inline void memory_expand(const size_t expand_len) {
		//拷贝后的长度
		size_t length = this->size + expand_len;
		//新的内存空间
		_Ty* ptr = new _Ty[length]{};
		//数据拷贝
		deepcopy(ptr, length, this->container, this->size);
		//赋值
		delete[] this->container;
		this->container = ptr;
		//更新容量
		this->size += expand_len;
	}
	/*
	* @brief
	* 连续内存分布容器扩充容量计算规则
	* @param
	* current_length : 当前容量
	* @return
	* 需要扩充的长度
	*/
	virtual size_t expand_length(const size_t current_size) const {
		//如果在容量<=60,每次增加10，如果超出，每次增加原来长度的0.5倍
		return current_size <= 60 ? 10 : current_size / 2;
	}
protected:
	/*容器指针*/
	_Ty* container;
	/*逗号分隔符*/
	CommaInitializer<_Ty>* commainitializer;
};


#endif // !VECTOR_H