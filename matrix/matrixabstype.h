#pragma once

#ifndef MATRIXABSTYPE
#define MATRIXABSTYPE

#pragma comment(lib,"lib/cobjectLib.lib")
#include "../cobject.h"
#include "expresstree.h"

/*矩阵类型基类*/
template<typename _Ele>
class MatrixAbsType : public Container2D<_Ele> {
	/*矩阵输入*/
	inline friend CommaInitializer<_Ele>& operator << (MatrixAbsType<_Ele>& mat, _Ele& ele) {
		mat.append(ele);
		delete mat.commainitializer;
		mat.commainitializer = new CommaInitializer<_Ele>(&mat);
		return *mat.commainitializer;
	}
	inline friend CommaInitializer<_Ele>& operator << (MatrixAbsType<_Ele>& mat, _Ele&& ele) {
		mat.append(ele);
		delete mat.commainitializer;
		mat.commainitializer = new CommaInitializer<_Ele>(&mat);
		return *mat.commainitializer;
	}
	/*矩阵输出*/
	inline friend ostream& operator << (ostream& out, const MatrixAbsType<_Ele>& mat) {
		//输出左括号
		out << '[';
		for (size_t i = 0; i < mat.rowCount; i++) {
			//不是第一行，输出一个空格
			if (i != 0) out << ' ';
			for (size_t j = 0; j < mat.colCount; j++) {
				//在输出每行第一个数字前输出左括号
				if (j == 0) out << '[';
				out << std::scientific << mat.container[i * mat.colCount + j];
				if (j < mat.colCount - 1) out << "  ";
				else out << ']';
			}
			if (i < mat.rowCount - 1) out << endl;
		}
		//输出右括号
		out << ']' << endl;
		return out;
	}
public:
	//矩阵形状
	typedef Match<size_t, size_t> matShape;
	/*矩阵行指针*/
	class matRowPtr : public Container2D<_Ele>::Container2D_Ptr {
	public:
		/*给定指针及其长度构造*/
		inline matRowPtr(_Ele* pointer, size_t length) : Container2D<_Ele>::Container2D_Ptr(length) {
			this->ptr = pointer;
		}
		inline _Ele& operator[](const size_t index) const {
			if (index >= this->ptr_length) {
				emit(IndexError("索引越界"));
			}
			return this->ptr[index];
		}
		inline void operator=(const MatrixAbsType<_Ele>::matRowPtr& rowptr) {
			//指针赋值
			this->ptr = rowptr.ptr;
		}
	protected:
		/*行指针*/
		_Ele* ptr;
	};
public:
	/*默认构造函数*/
	inline MatrixAbsType() : Container2D<_Ele>() {
		this->cur = 0;
		this->container = nullptr;
		this->commainitializer = nullptr;
	}
	/*指定形状构造*/
	inline MatrixAbsType(size_t row, size_t col) : Container2D<_Ele>(row, col) {
		this->cur = 0;
		this->container = new _Ele[row * col]{};
		this->commainitializer = nullptr;
	}
	/*指定形状和元素构造*/
	inline MatrixAbsType(size_t row, size_t col, std::initializer_list<_Ele> data) : Container2D<_Ele>(row, col) {
		this->cur = 0;
		this->container = new _Ele[row * col]{};
		this->commainitializer = nullptr;
		for (auto ele = data.begin(); ele != data.end(); ele++) {
			if (this->cur >= row * col) {
				return;
			}
			this->container[this->cur++] = *ele;
		}
	}
	/*深拷贝构造*/
	inline MatrixAbsType(const MatrixAbsType<_Ele>& matrixtype) {
		this->rowCount = matrixtype.rowCount;
		this->colCount = matrixtype.colCount;
		this->cur = matrixtype.cur;
		this->commainitializer = nullptr;
		size_t len = this->rowCount * this->colCount;
		this->container = new _Ele[len]{};
		//元素拷贝
		memcpy_s(this->container, sizeof(_Ele) * len, matrixtype.container, sizeof(_Ele) * len);
	}
	/*析构函数*/
	inline ~MatrixAbsType() {
		delete[] this->container;
		delete this->commainitializer;
	}
	/*
	* @brief
	* 顺序初始化
	* @param
	* var : 填入的元素
	* @return
	* 无
	*/
	inline virtual void append(const _Ele& var) {
		//如果元素全部初始化完毕
		if (this->cur >= this->rowCount * this->colCount) {
			return;
		}
		//如果元素没有初始化完毕
		this->container[this->cur++] = var;
	}
	/*
	* @brief
	* 顺序初始化
	* @param
	* var : 填入的元素
	* @return
	* 无
	*/
	inline virtual void append(_Ele&& var) {
		//如果元素全部初始化完毕
		if (this->cur >= this->rowCount * this->colCount) {
			return;
		}
		//如果元素没有初始化完毕
		this->container[this->cur++] = var;
	}
	/*
	* @brief
	* 通过索引获取元素
	* @param
	* r_index : 行索引
	* @param
	* c_index : 列索引
	* @return
	* 该位置上的元素
	*/
	inline virtual _Ele& at(const size_t r_index, const size_t c_index) const {
		//判断索引
		if (r_index >= this->rowCount || c_index >= this->colCount) {
			emit(MatrixError("矩阵索引超出范围"));
		}
		return this->container[r_index * this->colCount + c_index];
	}
	/*
	* @brief
	* 获取矩阵一行
	* @param
	* r_index : 行索引
	* @return
	* 一行的元素
	*/
	virtual MatrixAbsType<_Ele>& getRow(const size_t r_index) {
		//判断索引
		if (r_index >= this->rowCount) {
			emit(MatrixError("矩阵行索引超出范围"));
		}
		//创建新矩阵
		MatrixAbsType<_Ele> *mat = new MatrixAbsType<_Ele>(1, this->colCount);
		//复制元素
		memcpy_s(mat->container, this->colCount * sizeof(_Ele), \
			this->container + (r_index * this->colCount), this->colCount * sizeof(_Ele));
		return *mat;
	}
	/*
	* @brief
	* 获取矩阵一列
	* @param
	* c_index : 列索引
	* @return
	* 一列的元素
	*/
	inline virtual MatrixAbsType<_Ele>& getColumn(const size_t c_index) {
		//判断索引
		if (c_index >= this->colCount) {
			emit(MatrixError("矩阵列索引超出范围"));
		}
		//创建新矩阵
		MatrixAbsType<_Ele> *mat = new MatrixAbsType<_Ele>(this->rowCount, 1);
		//赋值
		for (size_t i = 0; i < this->rowCount; i++) {
			mat->container[i] = this->container[i * this->colCount + c_index];
		}
		//返回
		return *mat;
	}
	/*
	* @brief
	* 获取矩阵形状
	* @param
	* 无
	* @return
	* 矩阵形状
	*/
	inline matShape shape() const {
		return matShape(this->rowCount, this->colCount);
	}
	/*
	* @brief
	* 获取矩阵行指针
	* @param
	* index : 行索引
	* @return
	* 行指针类型
	*/
	inline MatrixAbsType<_Ele>::matRowPtr operator[](const size_t index) const {
		return MatrixAbsType<_Ele>::matRowPtr(this->container + index * this->colCount, this->colCount);
	}
	/*
	* @brief
	* 深拷贝赋值
	* @param
	* matobj : 矩阵对象
	* @return
	* 无
	*/
	inline virtual void deepcopy(const MatrixAbsType<_Ele>& matobj) {
		delete[] this->container;
		delete this->commainitializer;
		this->container = new _Ele[matobj.rowCount * matobj.colCount];
		this->rowCount = matobj.rowCount;
		this->colCount = matobj.colCount;
		delete this->commainitializer;
		this->commainitializer = nullptr;
		this->cur = matobj.cur;
		size_t size = this->rowCount * this->colCount * sizeof(_Ele);
		memcpy_s(this->container, size, matobj.container, size);
	}
	/*
	* @brief
	* 行交换
	* @param
	* mat : 矩阵
	* @param
	* h1 : 行1
	* @param
	* h2 : 行2
	* @return
	* 无
	*/
	static void rowSwap(MatrixAbsType<_Ele>& mat, size_t h1, size_t h2) {
		if (h1 >= mat.rowCount || h2 >= mat.rowCount) {
			emit(MatrixError("行索引越界"));
		}
		//缓冲区
		_Ele* buffer = new _Ele[mat.colCount]{};
		//缓冲区大小
		size_t buffersize = sizeof(_Ele) * mat.colCount;
		//交换
		memcpy_s(buffer, buffersize, mat.container + h1 * mat.colCount, buffersize);
		memcpy_s(mat.container + h1 * mat.colCount, buffersize, mat.container + h2 * mat.colCount, buffersize);
		memcpy_s(mat.container + h2 * mat.colCount, buffersize, buffer, buffersize);
		//内存删除
		delete[] buffer;
	}
protected:
	/*元素容器，连续内存存储*/
	_Ele* container;
	/*当前初始化的元素个数*/
	size_t cur;
	/*逗号分隔符*/
	CommaInitializer<_Ele>* commainitializer;
};


template <typename _Ele>
class MatrixXdType;

template<typename _Ele>
class VectorXdType;

template <typename _Ele>
class VectorRowType;

template <typename _Ele>
class VectorColumnType;


/*可运算矩阵基类*/
template<typename _Ele>
class MatrixXdType : public MatrixAbsType<_Ele> {
	friend class VectorRow;
	friend class VectorColumn;
	friend class VectorRowI;
	friend class VectorColumnI;
	friend class Matrix;
	friend class MatrixI;
	template<typename _Ele>
	friend size_t _seek(const MatrixXdType<_Ele>& mat, size_t row);
	template<typename ty>
	friend void _sort(MatrixXdType<ty>& matrix, VectorXdType<ty>& vector);
	template<typename ty>
	friend VectorXdType<ty> _gauss(const MatrixXdType<ty>& matrix, const VectorXdType<ty>& vector);
	template<typename MatType, typename _Ele>
	friend MatType matrixConcat(const Container1D<MatrixXdType<_Ele>>& matlist, bool direct);
public:
	inline friend MatrixAddOperation< _Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>> operator +(const MatrixXdType<_Ele>& left, const MatrixXdType<_Ele>& right) {
		return MatrixAddOperation<_Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>>(left, right);
	}
	inline friend MatrixAddOperation< _Ele, MatrixOperation<_Ele>, MatrixXdType<_Ele>> operator +(const MatrixOperation<_Ele>& left, const MatrixXdType<_Ele>& right) {
		return MatrixAddOperation<_Ele, MatrixOperation<_Ele>, MatrixXdType<_Ele>>(left, right);
	}
	inline friend MatrixAddOperation< _Ele, MatrixXdType<_Ele>, MatrixOperation<_Ele>> operator +(const MatrixXdType<_Ele>& left, const MatrixOperation<_Ele>& right) {
		return MatrixAddOperation<_Ele, MatrixXdType<_Ele>, MatrixOperation<_Ele>>(left, right);
	}
	inline friend MatrixSubOperation< _Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>> operator -(const MatrixXdType<_Ele>& left, const MatrixXdType<_Ele>& right) {
		return MatrixSubOperation<_Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>>(left, right);
	}
	inline friend MatrixSubOperation< _Ele, MatrixOperation<_Ele>, MatrixXdType<_Ele>> operator -(const MatrixOperation<_Ele>& left, const MatrixXdType<_Ele>& right) {
		return MatrixSubOperation<_Ele, MatrixOperation<_Ele>, MatrixXdType<_Ele>>(left, right);
	}
	inline friend MatrixSubOperation< _Ele, MatrixXdType<_Ele>, MatrixOperation<_Ele>> operator -(const MatrixXdType<_Ele>& left, const MatrixOperation<_Ele>& right) {
		return MatrixSubOperation<_Ele, MatrixXdType<_Ele>, MatrixOperation<_Ele>>(left, right);
	}
	inline friend MatrixMultiOperation< _Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>> operator *(const MatrixXdType<_Ele>& left, const MatrixXdType<_Ele>& right) {
		return MatrixMultiOperation<_Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>>(left, right);
	}
	inline friend MatrixMultiOperation< _Ele, MatrixOperation<_Ele>, MatrixXdType<_Ele>> operator *(const MatrixOperation<_Ele>& left, const MatrixXdType<_Ele>& right) {
		return MatrixMultiOperation<_Ele, MatrixOperation<_Ele>, MatrixXdType<_Ele>>(left, right);
	}
	inline friend MatrixMultiOperation< _Ele, MatrixXdType<_Ele>, MatrixOperation<_Ele>> operator *(const MatrixXdType<_Ele>& left, const MatrixOperation<_Ele>& right) {
		return MatrixMultiOperation<_Ele, MatrixXdType<_Ele>, MatrixOperation<_Ele>>(left, right);
	}
	inline friend MatrixMultiNumberOperation<_Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>> operator *(const MatrixXdType<_Ele>& mat, _Ele var) {
		return MatrixMultiNumberOperation<_Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>>(var, mat);
	}
	inline friend MatrixMultiNumberOperation<_Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>> operator *(_Ele var, const MatrixXdType<_Ele>& mat) {
		return MatrixMultiNumberOperation<_Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>>(var, mat);
	}
	inline friend MatrixMultiNumberOperation<_Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>> operator /(const MatrixXdType<_Ele>& mat, _Ele var) {
		return MatrixMultiNumberOperation<_Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>>(1.0 / var, mat);
	}
	inline friend void operator *=(MatrixXdType<_Ele>& mat, _Ele var) {
		for (size_t i = 0; i < mat.rowCount * mat.colCount; i++) {
			mat.container[i] *= var;
		}
	}
	inline friend void operator /= (MatrixXdType<_Ele>& mat, _Ele var) {
		for (size_t i = 0; i < mat.rowCount * mat.colCount; i++) {
			mat.container[i] /= var;
		}
	}
	inline friend void operator +=(MatrixXdType<_Ele>& mat, const MatrixXdType<_Ele>& mat1) {
		_assert_matrix_add_(mat, mat1);
		for (size_t i = 0; i < mat.rowCount * mat.colCount; i++) {
			mat.container[i] += mat1.container[i];
		}
	}
	inline friend void operator +=(MatrixXdType<_Ele>& mat, const MatrixOperation<_Ele>& mat1) {
		_assert_matrix_add_(mat, mat1);
		for (size_t i = 0; i < mat.rowCount; i++) {
			for (size_t j = 0; j < mat.colCount; j++) {
				mat.container[i * mat.colCount + j] += mat1.at(i, j);
			}
		}
	}
	inline friend void operator -=(MatrixXdType<_Ele>& mat, const MatrixXdType<_Ele>& mat1) {
		_assert_matrix_sub_(mat, mat1);
		for (size_t i = 0; i < mat.rowCount * mat.colCount; i++) {
			mat.container[i] -= mat1.container[i];
		}
	}
	inline friend void operator -=(MatrixXdType<_Ele>& mat, const MatrixOperation<_Ele>& mat1) {
		_assert_matrix_sub_(mat, mat1);
		for (size_t i = 0; i < mat.rowCount; i++) {
			for (size_t j = 0; j < mat.colCount; j++) {
				mat.container[i * mat.colCount + j] -= mat1.at(i, j);
			}
		}
	}
	inline void operator =(const MatrixOperation<_Ele>& tree) {
		this->rowCount = tree.row();
		this->colCount = tree.column();
		this->container = new _Ele[this->rowCount * this->colCount];	//不用初始化
		for (size_t i = 0; i < this->rowCount; i++) {
			for (size_t j = 0; j < this->colCount; j++) {
				this->container[i * this->colCount + j] = tree.at(i, j);
			}
		}
		this->cur = this->rowCount * this->colCount;
	}
	inline MatrixXdType<_Ele>& operator=(const MatrixXdType<_Ele>& matobj) {
		this->deepcopy(matobj);
		return *this;
	}
public:
	inline MatrixXdType() : MatrixAbsType<_Ele>() {

	}
	inline MatrixXdType(size_t row, size_t col) : MatrixAbsType<_Ele>(row, col) {

	}
	inline MatrixXdType(size_t row, size_t col, const initializer_list<_Ele>& list) : MatrixAbsType<_Ele>(row, col, list) {

	}
	inline MatrixXdType(const MatrixXdType<_Ele>& mat) : MatrixAbsType<_Ele>(mat) {

	}
	/*
	* @brief
	* 获取矩阵一行
	* @param
	* r_index : 行索引
	* @return
	* 一行的元素
	*/
	inline virtual MatrixXdType<_Ele>& getRow(const size_t r_index) {
		//判断索引
		if (r_index >= this->rowCount) {
			emit(MatrixError("矩阵行索引超出范围"));
		}
		//创建新矩阵
		MatrixXdType<_Ele> *mat = new MatrixXdType<_Ele>(1, this->colCount);
		//复制元素
		memcpy_s(mat->container, this->colCount * sizeof(_Ele), \
			this->container + (r_index * this->colCount), this->colCount * sizeof(_Ele));
		return *mat;
	}
	/*
	* @brief
	* 获取矩阵一列
	* @param
	* c_index : 列索引
	* @return
	* 一列的元素
	*/
	inline virtual MatrixXdType<_Ele>& getColumn(const size_t c_index) {
		//判断索引
		if (c_index >= this->colCount) {
			emit(MatrixError("矩阵列索引超出范围"));
		}
		//创建新矩阵
		MatrixXdType<_Ele>* mat = new MatrixXdType<_Ele>(this->rowCount, 1);
		//赋值
		for (int i = 0; i < this->rowCount; i++) {
			mat->container[i] = this->container[i * this->colCount + c_index];
		}
		//返回
		return *mat;
	}
	/*
	* @brief
	* 转置
	* @param
	* 无
	* @return
	* 转置表达式
	*/
	inline virtual MatrixTransposeOperation<_Ele, MatrixXdType<_Ele>> T() const {
		return MatrixTransposeOperation<_Ele, MatrixXdType<_Ele>>(*this);
	}
	/*
	* @brief
	* 复共轭转置
	* @param
	* 无
	* @return
	* 转置后的矩阵
	*/
	inline virtual MatrixHermitianOperation<_Ele, MatrixXdType<_Ele>> H() const {
		return MatrixHermitianOperation<_Ele, MatrixXdType<_Ele>>(*this);
	}
	/*
	* @brief
	* 复共轭矩阵
	* @param
	* 无
	* @return
	* 返回该矩阵的复共轭矩阵，对实数矩阵无效
	*/
	inline virtual MatrixConjugateOperation<_Ele, MatrixXdType<_Ele>> conj() const {
		return MatrixConjugateOperation<_Ele, MatrixXdType<_Ele>>(*this);
	}
	/*
	* @brief
	* 矩阵取相反数
	* @param
	* 无
	* @return
	* 对矩阵每一个元素均取其相反数
	*/
	inline virtual MatrixContraryOperation<_Ele, MatrixXdType<_Ele>> operator- () {
		return MatrixContraryOperation<_Ele, MatrixXdType<_Ele>>(*this);
	}
	/*
	* @brief
	* 矩阵的迹
	* @param
	* 无
	* @return
	* 迹
	*/
	inline _Ele trace() const {
		_assert_matrix_square_ptr_(this)
		_Ele re = _Ele();
		for (size_t i = 0; i < this->rowCount; i++) {
			re += this->at(i, i);
		}
		return re;
	}
};

/*向量基类*/
template<typename _Ele>
class VectorXdType : public MatrixXdType<_Ele> {
public:
	typedef enum class VectorShape {
		vectorShapeRow,
		vectorShapeColumn
	}VectorShape;
public:
	/*默认构造*/
	inline VectorXdType() : MatrixXdType<_Ele>() {
		this->length = 0;
	}
	/*指定长度和形状构造*/
	inline VectorXdType(size_t len, VectorXdType<_Ele>::VectorShape shape = VectorShape::vectorShapeColumn) : \
		MatrixXdType<_Ele>(shape == VectorShape::vectorShapeRow ? 1 : len, shape == VectorShape::vectorShapeRow ? len : 1) {
		this->length = len;
	}
	/*从列表创建*/
	inline VectorXdType(const Container1D<_Ele>& list, VectorXdType<_Ele>::VectorShape shape = VectorShape::vectorShapeColumn) : \
		MatrixXdType<_Ele>(shape == VectorShape::vectorShapeRow ? 1 : list.len(), shape == VectorShape::vectorShapeRow ? list.len() : 1) {
		this->length = list.len();
		this->cur = this->length;
		for (size_t i = 0; i < this->length; i++) {
			this->container[i] = list.at(i);
		}
	}
	/*从初始化列表创建*/
	inline VectorXdType(const initializer_list<_Ele>& list, VectorXdType<_Ele>::VectorShape shape = VectorShape::vectorShapeColumn) : \
		MatrixXdType<_Ele>(shape == VectorShape::vectorShapeRow ? 1 : list.size(), shape == VectorShape::vectorShapeRow ? list.size() : 1) {
		this->length = list.size();
		for (auto start = list.begin(); start != list.end(); start++) {
			this->container[this->cur++] = *start;
		}
	}
	/*拷贝构造*/
	inline VectorXdType(const VectorXdType<_Ele>& vec) : MatrixXdType<_Ele>(vec) {
		this->length = vec.length;
	}
	/*
	* @brief
	* 获取向量元素
	* @param
	* index : 元素索引
	* @return
	* 该位置上的元素
	*/
	inline virtual _Ele& at(const size_t index) const {
		if (index >= this->length) {
			emit(MatrixError("索引越界"));
		}
		return this->container[index];
	}
	/*
	* @brief
	* 获取向量长度
	* @param
	* 无
	* @return
	* 向量长度
	*/
	inline size_t size() const {
		return this->length;
	}
	/*
	* @brief
	* 获取向量元素
	* @param
	* index: 索引
	* @return
	* 向量元素
	*/
	inline _Ele& operator[] (const size_t index) const {
		if (index >= this->length) {
			emit(MatrixError("索引越界"));
		}
		return this->container[index];
	}
	/*
	* @brief
	* 深拷贝赋值
	* @param
	* vecobj : 向量对象
	* @return
	* 无
	*/
	inline virtual void deepcopy(const VectorXdType<_Ele>& vecobj) {
		delete[] this->container;
		delete this->commainitializer;
		this->container = new _Ele[vecobj.rowCount * vecobj.colCount];
		this->rowCount = vecobj.rowCount;
		this->colCount = vecobj.colCount;
		this->commainitializer = nullptr;
		this->cur = vecobj.cur;
		this->length = vecobj.length;
		size_t size = this->rowCount * this->colCount * sizeof(_Ele);
		memcpy_s(this->container, size, vecobj.container, size);
	}
protected:
	size_t length;
};

#endif // !MATRIXABSTYPE
