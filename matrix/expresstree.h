#pragma once

#ifndef EXPRESSTREE
#define EXPRESSTREE

#pragma comment(lib,"lib/cobjectLib.lib")
#include "../cobject.h"
#include "../complex.h"
#include "assert.h"

template<typename _data, typename _left, typename _right>
class MatrixAddOperation;

template<typename _data, typename _left, typename _right>
class MatrixSubOperation;

template<typename _data, typename _left, typename _right>
class MatrixMultiOperation;

template<typename _data, typename _left, typename _right>
class MatrixMultiNumberOperation;

template<typename _data, typename _mat>
class MatrixTransposeOperation;

template<typename _data, typename _mat>
class MatrixConjugateOperation;

template<typename _data, typename _mat>
class MatrixHermitianOperation;

template<typename _data, typename _mat>
class MatrixContraryOperation;

/*矩阵输出*/
template<typename op>
ostream& MatrixOut(ostream& out, const op& matrixlike) {
	out << '[';
	for (int i = 0; i < matrixlike.row(); i++) {
		//不是第一行，输出一个空格
		if (i != 0) out << ' ';
		for (int j = 0; j < matrixlike.column(); j++) {
			//在输出每行第一个数字前输出左括号
			if (j == 0) out << '[';
			out << std::scientific << matrixlike.at(i, j);
			if (j < matrixlike.column() - 1) out << "  ";
			else out << ']';
		}
		if (i < matrixlike.row() - 1) out << endl;
	}
	out << ']' << endl;
	return out;
}


/*矩阵运算基类*/
template<typename _data>
class MatrixOperation {
	inline friend MatrixAddOperation<_data, MatrixOperation<_data>, MatrixOperation<_data>> operator +(const MatrixOperation<_data>& left, const MatrixOperation<_data>& right) {
		return MatrixAddOperation< _data, MatrixOperation<_data>, MatrixOperation<_data>>(left, right);
	}
	inline friend MatrixSubOperation< _data, MatrixOperation<_data>, MatrixOperation<_data>> operator -(const MatrixOperation<_data>& left, const MatrixOperation<_data>& right) {
		return MatrixSubOperation<_data, MatrixOperation<_data>, MatrixOperation<_data>>(left, right);
	}
	inline friend MatrixMultiOperation< _data, MatrixOperation<_data>, MatrixOperation<_data>> operator *(const MatrixOperation<_data>& left, const MatrixOperation<_data>& right) {
		return MatrixMultiOperation<_data, MatrixOperation<_data>, MatrixOperation<_data>>(left, right);
	}
	inline friend MatrixMultiNumberOperation<_data, MatrixOperation<_data>, MatrixOperation<_data>> operator *(const MatrixOperation<_data>& mat, _data var) {
		return MatrixMultiNumberOperation<_data, MatrixOperation<_data>, MatrixOperation<_data>>(var, mat);
	}
	inline friend MatrixMultiNumberOperation<_data, MatrixOperation<_data>, MatrixOperation<_data>> operator *(_data var, const MatrixOperation<_data>& mat) {
		return MatrixMultiNumberOperation<_data, MatrixOperation<_data>, MatrixOperation<_data>>(var, mat);
	}
	inline friend MatrixMultiNumberOperation<_data, MatrixOperation<_data>, MatrixOperation<_data>> operator /(const MatrixOperation<_data>& mat, _data var) {
		return MatrixMultiNumberOperation<_data, MatrixOperation<_data>, MatrixOperation<_data>>(1.0 / var, mat);
	}
public:
	MatrixOperation() {

	}
	MatrixOperation(const size_t& row, const size_t& column) : matrow(row), matcolumn(column) {

	}
	//子类重载此方法
	virtual _data at(const size_t r_index, const size_t c_index) const {
		return _data();
	}
	virtual size_t row() const {
		return this->matrow;
	}
	virtual size_t column() const {
		return this->matcolumn;
	}
	/*转置*/
	inline MatrixTransposeOperation<_data, MatrixOperation<_data>> T() const {
		return MatrixTransposeOperation<_data, MatrixOperation<_data>>(*this);
	}
	/*共轭*/
	inline MatrixConjugateOperation<_data, MatrixOperation<_data>> conj() const {
		return MatrixConjugateOperation<_data, MatrixOperation<_data>>(*this);
	}
	/*共轭转置*/
	inline MatrixHermitianOperation<_data, MatrixOperation<_data>> H() const {
		return MatrixHermitianOperation<_data, MatrixOperation<_data>>(*this);
	}
	/*取负数运算*/
	inline MatrixContraryOperation<_data, MatrixOperation<_data>> operator- () {
		return MatrixContraryOperation<_data, MatrixOperation<_data>>(*this);
	}
protected:
	const size_t matrow;
	const size_t matcolumn;
};


/*矩阵加法表达式*/
template<typename _data, typename _left, typename _right>
class MatrixAddOperation : public MatrixOperation<_data> {
	inline friend ostream& operator <<(ostream& out, const MatrixAddOperation<_data, _left, _right> tree) {
		return MatrixOut< const MatrixAddOperation<_data, _left, _right>>(out, tree);
	}
public:
	//获取相加的两个矩阵
	explicit MatrixAddOperation(const _left& l, const _right& r) : left(l), right(r), MatrixOperation<_data>(l.row(), r.column()) {
		_assert_matrix_add_(l, r)
	}
	_data at(const size_t r_index, const size_t c_index) const {
		return this->left.at(r_index, c_index) + this->right.at(r_index, c_index);
	}
protected:
	const _left& left;
	const _right& right;
};


/*矩阵减法表达式*/
template<typename _data, typename _left, typename _right>
class MatrixSubOperation : public MatrixOperation<_data> {
	inline friend ostream& operator <<(ostream& out, const MatrixSubOperation<_data, _left, _right> tree) {
		return MatrixOut< const MatrixSubOperation<_data, _left, _right>>(out, tree);
	}
public:
	//获取相减的两个矩阵
	explicit MatrixSubOperation(const _left& l, const _right& r) : left(l), right(r), MatrixOperation<_data>(l.row(), r.column()) {
		_assert_matrix_sub_(l, r)
	}
	virtual _data at(const size_t r_index, const size_t c_index) const {
		return this->left.at(r_index, c_index) - this->right.at(r_index, c_index);
	}
public:
	const _left& left;
	const _right& right;
};


/*矩阵乘法表达式*/
template<typename _data, typename _left, typename _right>
class MatrixMultiOperation : public MatrixOperation<_data> {
	inline friend ostream& operator <<(ostream& out, const MatrixMultiOperation<_data, _left, _right> tree) {
		return MatrixOut< const MatrixMultiOperation<_data, _left, _right>>(out, tree);
	}
public:
	//获取相乘的两个矩阵
	explicit MatrixMultiOperation(const _left& l, const _right& r) : left(l), right(r), common(l.column()), MatrixOperation<_data>(l.row(), r.column()) {
		_assert_matrix_multi_(l, r)
	}
	inline virtual _data at(const size_t r_index, const size_t c_index) const {
		_data re = _data();
		for (int i = 0; i < this->common; i++) {
			re += this->left.at(r_index, i) * this->right.at(i, c_index);
		}
		return re;
	}
public:
	const _left& left;
	const _right& right;
	const size_t common;	//不可为引用
};


/*数字和矩阵相乘表达式，默认数字在左边*/
template<typename _data, typename _left, typename _right>
class MatrixMultiNumberOperation : public MatrixOperation<_data> {
	inline friend ostream& operator <<(ostream& out, const MatrixMultiNumberOperation<_data, _left, _right> tree) {
		return MatrixOut< const MatrixMultiNumberOperation<_data, _left, _right>>(out, tree);
	}
public:
	/*获取矩阵和数字*/
	explicit MatrixMultiNumberOperation(const _data& data, const _right& mat) : number(data), matrix(mat), MatrixOperation<_data>(mat.row(), mat.column()) {

	}
	virtual _data at(const size_t r_index, const size_t c_index) const {
		return this->number * this->matrix.at(r_index, c_index);
	}
public:
	const _data number;		//不可为引用
	const _right& matrix;
};

/*实数共轭*/
static double adjoint(double var) {
	return var;
}

/*复数共轭*/
static Complex adjoint(const Complex& var) {
	return var.conj();
}


/*矩阵转置表达式*/
template<typename _data, typename _mat>
class MatrixTransposeOperation : public MatrixOperation<_data> {
	friend ostream& operator<<(ostream& out, const MatrixTransposeOperation<_data, _mat>& tree) {
		return MatrixOut<const MatrixTransposeOperation<_data, _mat>>(out, tree);
	}
public:
	inline MatrixTransposeOperation(const _mat& mat) : MatrixOperation<_data>(mat.column(), mat.row()), matrix(mat) {

	}
	virtual _data at(const size_t r_index, const size_t c_index) const {
		return this->matrix.at(c_index, r_index);
	}
protected:
	const _mat& matrix;
};

/*矩阵共轭表达式*/
template<typename _data, typename _mat>
class MatrixConjugateOperation : public MatrixOperation<_data> {
	friend ostream& operator<<(ostream& out, const MatrixConjugateOperation<_data, _mat>& tree) {
		return MatrixOut<const MatrixConjugateOperation<_data, _mat>>(out, tree);
	}
public:
	inline MatrixConjugateOperation(const _mat& mat) : MatrixOperation<_data>(mat.row(), mat.column()), matrix(mat) {

	}
	virtual _data at(const size_t r_index, const size_t c_index) const {
		return adjoint(this->matrix.at(r_index, c_index));
	}
protected:
	const _mat& matrix;
};

/*矩阵共轭转置表达式*/
template<typename _data, typename _mat>
class MatrixHermitianOperation : public MatrixOperation<_data> {
	friend ostream& operator<<(ostream& out, const MatrixHermitianOperation<_data, _mat>& tree) {
		return MatrixOut<const MatrixHermitianOperation<_data, _mat>>(out, tree);
	}
public:
	inline MatrixHermitianOperation(const _mat& mat) : MatrixOperation<_data>(mat.column(), mat.row()), matrix(mat) {

	}
	virtual _data at(const size_t r_index, const size_t c_index) const {
		return adjoint(this->matrix.at(c_index, r_index));
	}
protected:
	const _mat& matrix;
};

/*矩阵取负数运算*/
template<typename _data, typename _mat>
class MatrixContraryOperation : public MatrixOperation<_data> {
	friend ostream& operator<<(ostream& out, const MatrixContraryOperation<_data, _mat>& tree) {
		return MatrixOut<const MatrixContraryOperation<_data, _mat>>(out, tree);
	}
public:
	inline MatrixContraryOperation(const _mat& mat) : MatrixOperation<_data>(mat.row(), mat.column()), matrix(mat) {

	}
	inline virtual _data at(const size_t r_index, const size_t c_index) const {
		return -this->matrix.at(r_index, c_index);
	}
protected:
	const _mat& matrix;
};


#endif // !EXPRESSTREE