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
	* ����������
	*/
	inline Vector() : Container1D<_Ty>() {
		this->container = nullptr;
		this->commainitializer = nullptr;
	}
	/*
	* @brief
	* ����ָ�����ȵ�����
	* @param
	* n �����г���
	*/
	inline Vector(const size_t n) : Container1D<_Ty>() {
		this->container = new _Ty[n]{};
		this->length = n;
		this->size = n;
		this->commainitializer = nullptr;
	}
	/*
	* @brief
	* ��һά���鴴������
	* @param
	* list ��һά����
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
	* �������
	* @param
	* vec ����һ������ʵ��
	*/
	inline Vector(const Vector<_Ty>& vec) {
		this->size = vec.size;
		this->length = vec.length;
		this->container = new _Ty[this->size]{};
		this->commainitializer = nullptr;
		deepcopy<_Ty>(this->container, this->size, vec.container, vec.size);
	}
	/*��������*/
	virtual ~Vector() {
		delete[] this->container;
		delete this->commainitializer;
	}
	/*
	* @brief
	* ��ȡ��ʼ��ַ
	* @param
	* ��
	* @return
	* ��ʼ��ַ
	*/
	inline const _Ty* begin() const {
		return this->container;
	}
	/*
	* @brief
	* ��ȡ������ַ��������
	* @param
	* ��
	* @return
	* ������ַ
	*/
	inline const _Ty* end() const {
		return this->container + this->length;
	}
	/*
	* @brief
	* ��ĩβ׷��Ԫ�أ���ֵ����
	* @param
	* ele ��׷�ӵ�Ԫ��
	* @return
	* ��
	*/
	inline virtual void append(const _Ty& ele) {
		//������Ȳ���������
		if (this->length >= this->size) {
			//��ȡ���䳤��
			size_t expand = this->expand_length(this->length);
			//��������
			this->memory_expand(expand);
		}
		//��ֵ
		this->container[this->length] = ele;
		//���ȼ�1
		this->length++;
	}
	/*
	* @brief
	* ��ĩβ׷��Ԫ�أ���ֵ����
	* @param
	* ele ��׷�ӵ�Ԫ��
	* @return
	* ��
	*/
	inline virtual void append(_Ty&& ele) {
		//������Ȳ���������
		if (this->length >= this->size) {
			//��ȡ���䳤��
			size_t expand = this->expand_length(this->length);
			//��������
			this->memory_expand(expand);
		}
		//��ֵ
		this->container[this->length] = ele;
		//���ȼ�1
		this->length++;
	}
	/*
	* @brief
	* ��ȡָ��������ֵ
	* @param
	* index ������ֵ
	* @return
	* ��������Ӧ������
	*/
	inline virtual _Ty& at(const size_t index) const {
		this->check_index(index);
		return this->container[index];
	}
	/*
	* @brief
	* ����Ԫ�أ���ֵ����
	* @param
	* index �����������λ��
	* ele �������Ԫ��
	* @return
	* ��
	*/
	inline void insert(const size_t index, _Ty& ele) {
		this->check_index(index);
		//׷��
		this->append(ele);
		//����
		for (size_t i = this->length - 1; i > index; i--) {
			this->container[i] = this->container[i - 1];
		}
		this->container[index] = ele;
	}
	/*
	* @brief
	* ����Ԫ�أ���ֵ����
	* @param
	* index �����������λ��
	* ele �������Ԫ��
	* @return
	* ��
	*/
	inline void insert(const size_t index, _Ty&& ele) {
		this->check_index(index);
		//׷��
		this->append(ele);
		//����
		for (size_t i = this->length - 1; i > index; i--) {
			this->container[i] = this->container[i - 1];
		}
		this->container[index] = ele;
	}
	/*
	* @brief
	* �滻Ԫ�أ���ֵ����
	* @param
	* index ����Ҫ�滻��Ԫ������
	* ele ���滻Ԫ��
	* @return
	* ��
	*/
	inline void replace(const size_t index, _Ty& ele) {
		this->check_index(index);
		//�滻
		this->container[index] = ele;
	}
	/*
	* @brief
	* �滻Ԫ�أ���ֵ����
	* @param
	* index ����Ҫ�滻��Ԫ������
	* ele ���滻Ԫ��
	* @return
	* ��
	*/
	inline void replace(const size_t index, _Ty&& ele) {
		this->check_index(index);
		//�滻
		this->container[index] = ele;
	}
	/*
	* @brief
	* �Ƴ�Ԫ��
	* @param
	* index ����Ҫ�Ƴ���Ԫ�ص�����
	* @return
	* ��
	*/
	inline void remove(const size_t index) {
		this->check_index(index);
		//����Ԫ����ǰ
		for (size_t i = index; i < this->length - 1; i++) {
			this->container[i] = this->container[i + 1];
		}
		//���ȼ�1
		this->length--;
	}
	/*
	* @brief
	* ���ڶ����б�ϲ��ڱ��б���
	* @param
	* arr : �ϲ����б�
	* @return
	* ��
	*/
	inline void concat(const Vector<_Ty>& vec) {
		if (vec.length == 0) {
			return;
		}
		//���ʣ��ռ䲻��
		if (this->length + vec.length >= this->size) {
			//����
			this->memory_expand(vec.length);
		}
		//����
		deepcopy<_Ty>(this->container + this->length, this->size, vec.container, vec.length);
		//���ȸ���
		this->length += vec.length;
	}
	/*
	* @brief
	* �������Ԫ��
	* @param
	* ��
	* @return
	* ��
	*/
	inline void clear() {
		delete[] this->container;
		this->container = nullptr;
		this->length = 0;
		this->size = 0;
	}
	/*
	* @brief
	* �����ֵ
	* @param
	* vec: vector����
	* @return
	* ��
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
	/*��������Ƿ�Խ��*/
	virtual inline void check_index(const size_t index) const {
		//�Ⱥŷǳ���Ҫ
		if (index >= this->length) {
			emit(IndexError("����������Χ"));
		}
	}
	/*
	* @brief
	* �ڴ������ֲ�������������
	* @param
	* expand_len : ��Ҫ����ĳ���
	* @return
	* ��
	*/
	virtual inline void memory_expand(const size_t expand_len) {
		//������ĳ���
		size_t length = this->size + expand_len;
		//�µ��ڴ�ռ�
		_Ty* ptr = new _Ty[length]{};
		//���ݿ���
		deepcopy(ptr, length, this->container, this->size);
		//��ֵ
		delete[] this->container;
		this->container = ptr;
		//��������
		this->size += expand_len;
	}
	/*
	* @brief
	* �����ڴ�ֲ��������������������
	* @param
	* current_length : ��ǰ����
	* @return
	* ��Ҫ����ĳ���
	*/
	virtual size_t expand_length(const size_t current_size) const {
		//���������<=60,ÿ������10�����������ÿ������ԭ�����ȵ�0.5��
		return current_size <= 60 ? 10 : current_size / 2;
	}
protected:
	/*����ָ��*/
	_Ty* container;
	/*���ŷָ���*/
	CommaInitializer<_Ty>* commainitializer;
};


#endif // !VECTOR_H