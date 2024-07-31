#pragma once

#ifndef ARRAYABSTYPE_H
#define ARRAYABSTYPE_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "../vector.h"

static const char ArrayErrorHeader[ERROR_HEADER_MAXLEN] = "ArrayError";
/*序列错误*/
class ArrayError : public Error<ArrayErrorHeader> {
public:
	inline ArrayError(const char* info) : Error(info) {

	}
};

template<typename _ty>
class ArrayOperation;

template<typename _left, typename _right, typename _ty>
class ArrayAddOperation;

template<typename _left, typename _right, typename _ty>
class ArraySubOperation;

template<typename _left, typename _right, typename _ty>
class ArrayMultiOperation;

template<typename _left, typename _right, typename _ty>
class ArrayDivOperation;

template<typename _arr, typename _ty>
class ArrayAddNumberOperation;

template<typename _arr, typename _ty>
class ArrayMultiNumberOperation;

template<typename _arr, typename _ty>
class ArraySubNumberLOperation;

template<typename _arr, typename _ty>
class ArraySubNumberROperation;

template<typename _arr, typename _ty>
class ArrayDivNumberLOperation;

template<typename _arr, typename _ty>
class ArrayDivNumberROperation;

template<typename _ty>
class ArrayXdType;


/*序列运算基类*/
template<typename _ty>
class ArrayOperation {
	friend ArrayAddOperation<ArrayOperation, ArrayOperation, _ty> operator+(const ArrayOperation<_ty>& left, const ArrayOperation<_ty>& right) {
		return ArrayAddOperation<ArrayOperation, ArrayOperation, _ty>(left, right);
	}
	friend ArraySubOperation<ArrayOperation, ArrayOperation, _ty> operator-(const ArrayOperation<_ty>& left, const ArrayOperation<_ty>& right) {
		return ArraySubOperation<ArrayOperation, ArrayOperation, _ty>(left, right);
	}
	friend ArrayMultiOperation<ArrayOperation, ArrayOperation, _ty> operator*(const ArrayOperation<_ty>& left, const ArrayOperation<_ty>& right) {
		return ArrayMultiOperation<ArrayOperation, ArrayOperation, _ty>(left, right);
	}
	friend ArrayDivOperation<ArrayOperation, ArrayOperation, _ty> operator/(const ArrayOperation<_ty>& left, const ArrayOperation<_ty>& right) {
		return ArrayDivOperation<ArrayOperation, ArrayOperation, _ty>(left, right);
	}
	friend ArrayAddOperation<ArrayXdType<_ty>, ArrayOperation<_ty>, _ty> operator+(const ArrayXdType<_ty>& arr, const ArrayOperation<_ty>& op) {
		return ArrayAddOperation<ArrayXdType<_ty>, ArrayOperation<_ty>, _ty>(arr, op);
	}
	friend ArrayAddOperation<ArrayOperation<_ty>, ArrayXdType<_ty>, _ty> operator+(const ArrayOperation<_ty>& op, const ArrayXdType<_ty>& arr) {
		return ArrayAddOperation<ArrayOperation<_ty>, ArrayXdType<_ty>, _ty>(op, arr);
	}
	friend ArrayAddNumberOperation<ArrayOperation<_ty>, _ty> operator+(const _ty& var, const ArrayOperation<_ty>& op) {
		return ArrayAddNumberOperation<ArrayOperation<_ty>, _ty>(var, op);
	}
	friend ArrayAddNumberOperation<ArrayOperation<_ty>, _ty> operator+(const ArrayOperation<_ty>& op, const _ty& var) {
		return ArrayAddNumberOperation<ArrayOperation<_ty>, _ty>(var, op);
	}
	friend ArraySubOperation<ArrayXdType<_ty>, ArrayOperation<_ty>, _ty> operator-(const ArrayXdType<_ty>& arr, const ArrayOperation<_ty>& op) {
		return ArraySubOperation<ArrayXdType<_ty>, ArrayOperation<_ty>, _ty>(arr, op);
	}
	friend ArraySubOperation<ArrayOperation<_ty>, ArrayXdType<_ty>, _ty> operator-(const ArrayOperation<_ty>& op, const ArrayXdType<_ty>& arr) {
		return ArraySubOperation<ArrayOperation<_ty>, ArrayXdType<_ty>, _ty>(op, arr);
	}
	friend ArraySubNumberLOperation<ArrayOperation<_ty>, _ty> operator-(const ArrayOperation<_ty>& op, const _ty& var) {
		return ArraySubNumberLOperation<ArrayOperation<_ty>, _ty>(op, var);
	}
	friend ArraySubNumberROperation<ArrayOperation<_ty>, _ty> operator-(const _ty& var, const ArrayOperation& op) {
		return ArraySubNumberROperation<ArrayOperation<_ty>, _ty>(var, op);
	}
	friend ArrayMultiOperation<ArrayXdType<_ty>, ArrayOperation<_ty>, _ty> operator*(const ArrayXdType<_ty>& arr, const ArrayOperation<_ty>& op) {
		return ArrayMultiOperation<ArrayXdType<_ty>, ArrayOperation<_ty>, _ty>(arr, op);
	}
	friend ArrayMultiOperation<ArrayOperation<_ty>, ArrayXdType<_ty>, _ty> operator*(const ArrayOperation<_ty>& op, const ArrayXdType<_ty>& arr) {
		return ArrayMultiOperation<ArrayOperation<_ty>, ArrayXdType<_ty>, _ty>(op, arr);
	}
	friend ArrayMultiNumberOperation<ArrayOperation<_ty>, _ty> operator *(const _ty& var, const ArrayOperation<_ty>& op) {
		return ArrayMultiNumberOperation<ArrayOperation<_ty>, _ty>(var, op);
	}
	friend ArrayMultiNumberOperation<ArrayOperation<_ty>, _ty> operator *(const ArrayOperation<_ty>& op, const _ty& var) {
		return ArrayMultiNumberOperation<ArrayOperation<_ty>, _ty>(var, op);
	}
	friend ArrayDivOperation<ArrayXdType<_ty>, ArrayOperation<_ty>, _ty> operator/(const ArrayXdType<_ty>& arr, const ArrayOperation<_ty>& op) {
		return ArrayDivOperation<ArrayXdType<_ty>, ArrayOperation<_ty>, _ty>(arr, op);
	}
	friend ArrayDivOperation<ArrayOperation<_ty>, ArrayXdType<_ty>, _ty> operator/(const ArrayOperation<_ty>& op, const ArrayXdType<_ty>& arr) {
		return ArrayDivOperation<ArrayOperation<_ty>, ArrayXdType<_ty>, _ty>(op, arr);
	}
	friend ArrayDivNumberLOperation<ArrayOperation<_ty>, _ty> operator/(const ArrayOperation<_ty>& op, const _ty& var) {
		return ArrayDivNumberLOperation<ArrayOperation<_ty>, _ty>(op, var);
	}
	friend ArrayDivNumberROperation<ArrayOperation<_ty>, _ty> operator/(const _ty& var, const ArrayOperation<_ty>& op) {
		return ArrayDivNumberROperation<ArrayOperation<_ty>, _ty>(var, op);
	}
	friend bool operator <(const ArrayOperation<_ty>& op, const _ty& val) {
		for (size_t i = 0; i < op.length; i++) {
			if (op.at(i) >= val) {
				return false;
			}
		}
		return true;
	}
	friend bool operator >(const ArrayOperation<_ty>& op, const _ty& val) {
		for (size_t i = 0; i < op.length; i++) {
			if (op.at(i) <= val) {
				return false;
			}
		}
		return true;
	}
	friend bool operator <=(const ArrayOperation<_ty>& op, const _ty& val) {
		for (size_t i = 0; i < op.length; i++) {
			if (op.at(i) > val) {
				return false;
			}
		}
		return true;
	}
	friend bool operator >=(const ArrayOperation<_ty>& op, const _ty& val) {
		for (size_t i = 0; i < op.length; i++) {
			if (op.at(i) < val) {
				return false;
			}
		}
		return true;
	}
	friend bool operator ==(const ArrayOperation<_ty>& op, const _ty& val) {
		for (size_t i = 0; i < op.length; i++) {
			if (op.at(i) != val) {
				return false;
			}
		}
		return true;
	}
public:
	inline ArrayOperation() : length(0) {

	}
	/*获取当前值*/
	inline virtual _ty at(const size_t index) const = 0;
	/*获取长度*/
	inline size_t len() const {
		return this->length;
	}
	/*判断长度是否一致*/
	template<typename _left, typename _right>
	inline void check_length(const _left& l, const _right& r) {
		if (l.len() != r.len()) {
			char info[100]{};
			sprintf_s(info, "序列长度分别为 %zu,%zu，不符合广播规则\n", l.len(), r.len());
			emit(ArrayError(info));
		}
	}
	/*
	* @brief
	* 查找最大值
	* @param
	* _abs: bool变量，1表示查找绝对值最大
	* @return
	* double类型数据
	*/
	_ty max(bool _abs = 0) const {
		//目标索引
		size_t target = 0;
		if (!_abs) {
			for (size_t j = 0; j < this->length; j++) {
				//找到了更大的数
				if (this->at(target) < this->at(j)) {
					target = j;
				}
			}
		}
		else {
			for (size_t j = 0; j < this->length; j++) {
				//找到了更大的数
				if (abs(this->at(target)) < abs(this->at(j))) {
					target = j;
				}
			}
		}
		return this->at(target);
	}
	/*
	* @brief
	* 查找最小值
	* @param
	* _abs: bool变量，1表示查找绝对值最小
	* @return
	* double类型数据
	*/
	_ty min(bool _abs = 0) const {
		//目标索引
		size_t target = 0;
		if (!_abs) {
			for (size_t j = 0; j < this->length; j++) {
				//找到了更小的数
				if (this->at(target) > this->at(j)) {
					target = j;
				}
			}
		}
		else {
			for (size_t j = 0; j < this->length; j++) {
				//找到了更小的数
				if (abs(this->at(target)) > abs(this->at(j))) {
					target = j;
				}
			}
		}
		return this->at(target);
	}
	/*
	* @brief
	* 对序列求和
	* @param
	* 无
	* @return
	* double类型数据
	*/
	_ty sum() const {
		_ty result = 0;
		for (size_t i = 0; i < this->length; i++) {
			result += this->at(i);
		}
		return result;
	}
	/*输出*/
	inline friend ostream& operator<<(ostream& out, const ArrayOperation& expr) {
		out << "[";
		for (int i = 0; i < expr.length; i++) {
			if (i != 0) {
				out << " ";
			}
			out << expr.at(i);
		}
		out << "]" << endl;
		return out;
	}
protected:
	size_t length;
};

/*序列与序列运算*/
template<typename _left, typename _right>
class ArrayOperationElement {
public:
	inline ArrayOperationElement() {

	}
	inline ArrayOperationElement(const _left& l, const _right& r) : left(l), right(r) {

	}
protected:
	const _left& left;
	const _right& right;
};

/*序列和数字运算*/
template<typename _op, typename _ty>
class ArrayOperationEleNumber {
public:
	inline ArrayOperationEleNumber() {

	}
	inline ArrayOperationEleNumber(const _ty& value, const _op& operation) : var(value), op(operation) {

	}
protected:
	const _ty& var;
	const _op& op;
};

/*序列单运算*/
template<typename _op>
class ArrayFunctionOperation {
public:
	inline ArrayFunctionOperation() {

	}
	inline ArrayFunctionOperation(const _op& _arr) : op(_arr) {

	}
protected:
	const _op& op;
};

/*序列加法运算*/
template<typename _left, typename _right, typename _ty>
class ArrayAddOperation : public ArrayOperation<_ty>, public ArrayOperationElement<_left, _right> {
public:
	ArrayAddOperation(const _left& l, const _right& r) : ArrayOperation<_ty>(), ArrayOperationElement<_left, _right>(l, r) {
		this->check_length<_left, _right>(l, r);
		this->length = l.len();
	}
	inline virtual _ty at(const size_t index) const {
		return this->left.at(index) + this->right.at(index);
	}
};

/*序列减法运算*/
template<typename _left, typename _right, typename _ty>
class ArraySubOperation : public ArrayOperation<_ty>, public ArrayOperationElement<_left, _right> {
public:
	ArraySubOperation(const _left& l, const _right& r) : ArrayOperation<_ty>(), ArrayOperationElement<_left, _right>(l, r) {
		this->check_length<_left, _right>(l, r);
		this->length = l.len();
	}
	inline virtual _ty at(const size_t index) const {
		return this->left.at(index) - this->right.at(index);
	}
};

/*序列乘法运算*/
template<typename _left, typename _right, typename _ty>
class ArrayMultiOperation : public ArrayOperation<_ty>, public ArrayOperationElement<_left, _right> {
public:
	ArrayMultiOperation(const _left& l, const _right& r) : ArrayOperation<_ty>(), ArrayOperationElement<_left, _right>(l, r) {
		this->check_length<_left, _right>(l, r);
		this->length = l.len();
	}
	inline virtual _ty at(const size_t index) const {
		return this->left.at(index) * this->right.at(index);
	}
};

/*序列除法运算*/
template<typename _left, typename _right, typename _ty>
class ArrayDivOperation : public ArrayOperation<_ty>, public ArrayOperationElement<_left, _right> {
public:
	ArrayDivOperation(const _left& l, const _right& r) : ArrayOperation<_ty>(), ArrayOperationElement<_left, _right>(l, r) {
		this->check_length<_left, _right>(l, r);
		this->length = l.len();
	}
	inline virtual _ty at(const size_t index) const {
		return this->left.at(index) / this->right.at(index);
	}
};

/*序列和数字相加运算，默认左侧为数字*/
template<typename _arr, typename _ty>
class ArrayAddNumberOperation : public ArrayOperation<_ty>, public ArrayOperationEleNumber< _arr, _ty> {
public:
	ArrayAddNumberOperation(const _ty& l, const _arr& r) : ArrayOperation<_ty>(), ArrayOperationEleNumber<_arr, _ty>(l, r) {
		this->length = r.len();
	}
	inline virtual _ty at(const size_t index) const {
		return this->var + this->op.at(index);
	}
};

/*序列和数字相乘运算，默认左侧为数字*/
template<typename _arr, typename _ty>
class ArrayMultiNumberOperation : public ArrayOperation<_ty>, public ArrayOperationEleNumber<_arr, _ty> {
public:
	ArrayMultiNumberOperation(const _ty& l, const _arr& r) : ArrayOperation<_ty>(), ArrayOperationEleNumber<_arr, _ty>(l, r) {
		this->length = r.len();
	}
	inline virtual _ty at(const size_t index) const {
		return this->var * this->op.at(index);
	}
};

/*序列减数字*/
template<typename _arr, typename _ty>
class ArraySubNumberLOperation : public ArrayOperation<_ty>, public ArrayOperationEleNumber<_arr, _ty> {
public:
	ArraySubNumberLOperation(const _arr& l, const _ty& r) : ArrayOperation<_ty>(), ArrayOperationEleNumber<_arr, _ty>(r, l) {
		this->length = l.len();
	}
	inline virtual _ty at(const size_t index) const {
		return this->op.at(index) - this->var;
	}
};

/*数字减序列*/
template<typename _arr, typename _ty>
class ArraySubNumberROperation : public ArrayOperation<_ty>, public ArrayOperationEleNumber<_arr, _ty> {
public:
	ArraySubNumberROperation(const _ty& l, const _arr& r) : ArrayOperation<_ty>(), ArrayOperationEleNumber<_arr, _ty>(l, r) {
		this->length = r.len();
	}
	inline virtual _ty at(const size_t index) const {
		return this->var - this->op.at(index);
	}
};

/*序列除以数字*/
template<typename _arr, typename _ty>
class ArrayDivNumberLOperation : public ArrayOperation<_ty>, public ArrayOperationEleNumber<_arr, _ty> {
public:
	ArrayDivNumberLOperation(const _arr& l, const _ty& r) : ArrayOperation<_ty>(), ArrayOperationEleNumber<_arr, _ty>(r, l) {
		this->length = l.len();
	}
	inline virtual _ty at(const size_t index) const {
		return this->op.at(index) / this->var;
	}
};

/*数字除以序列*/
template<typename _arr, typename _ty>
class ArrayDivNumberROperation : public ArrayOperation<_ty>, public ArrayOperationEleNumber<_arr, _ty> {
public:
	ArrayDivNumberROperation(const _ty& l, const _arr& r) : ArrayOperation<_ty>(), ArrayOperationEleNumber<_arr, _ty>(l, r) {
		this->length = r.len();
	}
	inline virtual _ty at(const size_t index) const {
		return this->var / this->op.at(index);
	}
};

/*
* @brief
* 判断两个序列长度是否一致，不一致则终止程序
*/
template<typename _ty>
static void check_array_length(const ArrayXdType<_ty>& arr1, const ArrayXdType<_ty>& arr2) {
	if (arr1.len() != arr2.len()) {
		char info[100]{};
		sprintf_s(info, "序列长度分别为 %zu,%zu，不符合广播规则\n", arr1.len(), arr2.len());
		emit(ArrayError(info));
	}
}


template<typename _ty>
class ArrayXdType : public Vector<_ty> {
	friend ArrayAddOperation<ArrayXdType<_ty>, ArrayXdType<_ty>, _ty> operator + (const ArrayXdType<_ty>& arr1, const ArrayXdType<_ty>& arr2) {
		return ArrayAddOperation<ArrayXdType<_ty>, ArrayXdType<_ty>, _ty>(arr1, arr2);
	}
	friend ArrayAddNumberOperation<ArrayXdType<_ty>, _ty> operator + (const ArrayXdType<_ty>& arr, const _ty& element) {
		return ArrayAddNumberOperation<ArrayXdType<_ty>, _ty>(element, arr);
	}
	friend ArrayAddNumberOperation<ArrayXdType<_ty>, _ty> operator + (const _ty& element, const ArrayXdType<_ty>& arr) {
		return ArrayAddNumberOperation<ArrayXdType<_ty>, _ty>(element, arr);
	}
	friend ArraySubOperation<ArrayXdType<_ty>, ArrayXdType<_ty>, _ty> operator - (const ArrayXdType<_ty>& arr1, const ArrayXdType<_ty>& arr2) {
		return ArraySubOperation<ArrayXdType<_ty>, ArrayXdType<_ty>, _ty>(arr1, arr2);
	}
	friend ArraySubNumberLOperation<ArrayXdType<_ty>, _ty> operator - (const ArrayXdType<_ty>& arr, const _ty& element) {
		return ArraySubNumberLOperation<ArrayXdType<_ty>, _ty>(arr, element);
	}
	friend ArraySubNumberROperation<ArrayXdType<_ty>, _ty> operator - (const _ty& element, const ArrayXdType<_ty>& arr) {
		return ArraySubNumberROperation<ArrayXdType<_ty>, _ty>(element, arr);
	}
	friend ArrayMultiOperation<ArrayXdType<_ty>, ArrayXdType<_ty>, _ty> operator * (const ArrayXdType<_ty>& arr1, const ArrayXdType<_ty>& arr2) {
		return ArrayMultiOperation<ArrayXdType<_ty>, ArrayXdType<_ty>, _ty>(arr1, arr2);
	}
	friend ArrayMultiNumberOperation<ArrayXdType<_ty>, _ty> operator * (const ArrayXdType<_ty>& arr, const _ty& element) {
		return ArrayMultiNumberOperation<ArrayXdType<_ty>, _ty>(element, arr);
	}
	friend ArrayMultiNumberOperation<ArrayXdType<_ty>, _ty> operator * (const _ty& element, const ArrayXdType<_ty>& arr) {
		return ArrayMultiNumberOperation<ArrayXdType<_ty>, _ty>(element, arr);
	}
	friend ArrayDivOperation<ArrayXdType<_ty>, ArrayXdType<_ty>, _ty> operator / (const ArrayXdType<_ty>& arr1, const ArrayXdType<_ty>& arr2) {
		return ArrayDivOperation<ArrayXdType<_ty>, ArrayXdType<_ty>, _ty>(arr1, arr2);
	}
	friend ArrayDivNumberLOperation<ArrayXdType<_ty>, _ty> operator / (const ArrayXdType<_ty>& arr, const _ty& element) {
		return ArrayDivNumberLOperation<ArrayXdType<_ty>, _ty>(arr, element);
	}
	friend ArrayDivNumberROperation<ArrayXdType<_ty>, _ty> operator / (const _ty& element, const ArrayXdType<_ty>& arr) {
		return ArrayDivNumberROperation<ArrayXdType<_ty>, _ty>(element, arr);
	}
	friend void operator += (ArrayXdType<_ty>& arr1, const ArrayXdType<_ty>& arr2) {
		check_array_length<_ty>(arr1, arr2);
		//相加
		for (size_t i = 0; i < arr1.length; i++) {
			arr1.container[i] += arr2.container[i];
		}
	}
	friend void operator += (ArrayXdType<_ty>& arr, const _ty& element) {
		for (size_t i = 0; i < arr.length; i++) {
			arr.container[i] += element;
		}
	}
	friend void operator -= (ArrayXdType<_ty>& arr1, const ArrayXdType<_ty>& arr2) {
		check_array_length<_ty>(arr1, arr2);
		//相减
		for (size_t i = 0; i < arr1.length; i++) {
			arr1.container[i] -= arr2.container[i];
		}
	}
	friend void operator -= (ArrayXdType<_ty>& arr, const _ty& element) {
		for (size_t i = 0; i < arr.length; i++) {
			arr.container[i] -= element;
		}
	}
	friend void operator *= (ArrayXdType<_ty>& arr1, const ArrayXdType<_ty>& arr2) {
		check_array_length<_ty>(arr1, arr2);
		//相乘
		for (size_t i = 0; i < arr1.length; i++) {
			arr1.container[i] *= arr2.container[i];
		}
		return;
	}
	friend void operator *= (ArrayXdType<_ty>& arr, const _ty& element) {
		for (size_t i = 0; i < arr.length; i++) {
			arr.container[i] *= element;
		}
	}
	friend void operator /= (ArrayXdType<_ty>& arr1, const ArrayXdType<_ty>& arr2) {
		check_array_length<_ty>(arr1, arr2);
		//相乘
		for (size_t i = 0; i < arr1.length; i++) {
			arr1.container[i] /= arr2.container[i];
		}
	}
	friend void operator /= (ArrayXdType<_ty>& arr, const _ty& element) {
		for (size_t i = 0; i < arr.length; i++) {
			arr.container[i] /= element;
		}
	}
	friend bool operator < (const ArrayXdType<_ty>& arr, const _ty& f) {
		for (size_t i = 0; i < arr.length; i++) {
			if (arr.container[i] >= f) {
				return false;
			}
		}
		return true;
	}
	friend bool operator > (const ArrayXdType<_ty>& arr, const _ty& f) {
		for (size_t i = 0; i < arr.length; i++) {
			if (arr.container[i] <= f) {
				return false;
			}
		}
		return true;
	}
	friend bool operator <= (const ArrayXdType<_ty>& arr, const _ty& f) {
		for (size_t i = 0; i < arr.length; i++) {
			if (arr.container[i] > f) {
				return false;
			}
		}
		return true;
	}
	friend bool operator >= (const ArrayXdType<_ty>& arr, const _ty& f) {
		for (size_t i = 0; i < arr.length; i++) {
			if (arr.container[i] < f) {
				return false;
			}
		}
		return true;
	}
	friend bool operator == (const ArrayXdType<_ty>& arr, const _ty& f) {
		for (size_t i = 0; i < arr.length; i++) {
			if (arr.container[i] != f) {
				return false;
			}
		}
		return true;
	}
	friend ostream& operator << (ostream& out, const ArrayXdType<_ty>& arr) {
		out << "[";
		for (size_t i = 0; i < arr.length; i++) {
			if (i != 0) {
				out << " ";
			}
			out << arr.container[i];
		}
		out << "]" << endl;
		return out;
	}
public:
	/*
	* @brief
	* 无参构造
	* @param
	* 无
	* @return
	* 无
	*/
	inline ArrayXdType() : Vector<_ty>() {

	}
	/*
	* @brief
	* 从一维数组构造
	* @param
	* 一维数组
	* @return
	* 无
	*/
	ArrayXdType(const initializer_list<_ty>& list) : Vector<_ty>(list) {

	}
	/*
	* @brief
	* 指定生成序列的长度
	* @param
	* n : 序列长度
	* @return
	* 无
	*/
	ArrayXdType(size_t length) : Vector<_ty>(length) {

	}
	/*
	* @brief
	* 从表达式构造序列
	* @param
	* expr : 序列表达式
	* @return
	* 无
	*/
	ArrayXdType(const ArrayOperation<_ty>& expr) {
		this->length = expr.len();
		this->size = this->length;
		delete[] this->container;
		this->container = new _ty[this->length] {};
		for (size_t i = 0; i < this->length; i++) {
			this->container[i] = expr.at(i);
		}
	}
	/*
	* @brief
	* 拷贝构造函数,默认深拷贝
	* @param
	* arr : Array对象
	* ctrl : Array控制器
	* @return
	* 无
	*/
	ArrayXdType(const ArrayXdType<_ty>& arr) {
		this->length = arr.length;
		this->size = arr.size;
		this->container = new _ty[this->size] {};
		deepcopy<_ty>(this->container, this->length, arr.container, arr.length);
	}
	/*
	* @brief
	* 移除序列中的连续存储的数据，不包含右侧数据
	* @param
	* start : 开始位置索引
	* @param
	* end : 结束位置索引
	* @return
	* 无
	*/
	void removes(size_t start, size_t end) {
		if (start >= this->length || end >= this->length) {
			emit(IndexError("索引超出序列范围"));
		}
		if (start > end) {
			emit(IndexError("索引范围不合法"));
		}
		size_t range = end - start;
		for (size_t i = start; i < this->length; i++) {
			if (i + range < this->length) {
				this->container[i] = this->container[i + range];
			}
			else {
				break;
			}
		}
		this->length -= range;
	}
	/*
	* @brief
	* 截取给定长度的序列
	* @param
	* start : 起始索引
	* @param
	* end : 结束索引
	* @return
	* Array类型对象
	* @note
	* 对返回对象进行操作不会影响原序列
	*/
	virtual ArrayXdType<_ty> slice(size_t start, size_t end) const {
		//由于不取end位置的值，因此判断和长度的关系的时候不加等号
		if (end > this->length || start > end) {
			emit(IndexError("切片条件不存在"));
		}
		ArrayXdType<_ty> new_arr(end - start);
		//内存拷贝
		deepcopy<_ty>(new_arr.container, (end - start), this->container + start, (end - start));
		return new_arr;
	}
	/*
	* @brief
	* 查找最大值
	* @param
	* _abs: bool变量，1表示查找绝对值最大
	* @return
	* double类型数据
	*/
	_ty max(bool _abs = 0) const {
		//目标索引
		size_t target = 0;
		if (!_abs) {
			for (size_t j = 0; j < this->length; j++) {
				//找到了更大的数
				if (this->container[target] < this->container[j]) {
					target = j;
				}
			}
		}
		else {
			for (size_t j = 0; j < this->length; j++) {
				//找到了更大的数
				if (abs(this->container[target]) < abs(this->container[j])) {
					target = j;
				}
			}
		}
		return this->container[target];
	}
	/*
	* @brief
	* 查找最小值
	* @param
	* _abs: bool变量，1表示查找绝对值最小
	* @return
	* double类型数据
	*/
	_ty min(bool _abs = 0) const {
		//目标索引
		size_t target = 0;
		if (!_abs) {
			for (size_t j = 0; j < this->length; j++) {
				//找到了更小的数
				if (this->container[target] > this->container[j]) {
					target = j;
				}
			}
		}
		else {
			for (size_t j = 0; j < this->length; j++) {
				//找到了更小的数
				if (abs(this->container[target]) > abs(this->container[j])) {
					target = j;
				}
			}
		}
		return this->container[target];
	}
	/*
	* @brief
	* 对序列求和
	* @param
	* 无
	* @return
	* double类型数据
	*/
	_ty sum() const {
		_ty result = 0;
		for (size_t i = 0; i < this->length; i++) {
			result += this->container[i];
		}
		return result;
	}
	/*
	* @brief
	* 从序列表达式创建序列
	* @param
	* expr : 序列表达式
	* @return
	* 无
	*/
	virtual void operator=(const ArrayOperation<_ty>& expr) {
		this->length = expr.len();
		this->size = this->length;
		delete[] this->container;
		this->container = new _ty[this->length] {};
		for (size_t i = 0; i < this->length; i++) {
			this->container[i] = expr.at(i);
		}
	}
	/*
	* @brief
	* 深拷贝构造
	* @param
	* arr : 序列
	* @return
	* 无
	*/
	virtual void operator=(const ArrayXdType<_ty>& arr) {
		this->length = arr.length;
		this->size = arr.size;
		this->container = new _ty[this->size] {};
		deepcopy<_ty>(this->container, this->length, arr.container, this->length);
	}
};


#endif // !ARRAYABSTYPE_H
