#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "matrixabstype.h"
#include "../complex.h"

typedef MatrixAbsType<double> RealMatrixShape;
typedef MatrixAbsType<Complex> ComplexMatrixShape;
typedef MatrixXdType<double> RealMatrix;
typedef MatrixXdType<Complex> ComplexMatrix;
typedef VectorXdType<double> RealVector;
typedef VectorXdType<Complex> ComplexVector;

class VectorRow;
class VectorColumn;
class VectorRowI;
class VectorColumnI;
class Matrix;
class MatrixI;


/*实数列向量*/
class VectorRow : public VectorXdType<double> {
	friend Matrix;
public:
	VectorRow();
	VectorRow(size_t len);
	VectorRow(const Container1D<double>& list);
	VectorRow(const initializer_list<double>& list);
	VectorRow(const VectorRow& vec);
	VectorRow(const MatrixOperation<double>& tree);
	VectorRow(const MatrixXdType<double>& matxd);
	/*
	* @brief
	* 从表达式树创建实数行向量
	* @param
	* tree : 表达式树
	* @return
	* 实数行向量引用
	*/
	VectorRow& operator =(const MatrixOperation<double>& tree);
	/*
	* @brief
	* 从矩阵基类创建实数行向量
	* @param
	* matxd : 矩阵基类
	* @return
	* 实数行向量引用
	*/
	VectorRow& operator =(const MatrixXdType<double>& matxd);
	/*
	* @brief
	* 从实数行向量拷贝构造
	* @param
	* vec : 向量
	* @return
	* 实数行向量引用
	*/
	VectorRow& operator =(const VectorRow& vec);
public:
	/*
	* @brief
	* 填充向量
	* @param
	* size : 向量长度
	* @param
	* var : 填充元素
	* @return
	* 向量
	*/
	static VectorRow fill(size_t size, double var);
	/*
	* @brief
	* 生成全1向量
	* @param
	* size : 向量长度
	* @return
	* 向量
	*/
	static VectorRow ones(size_t size);
	/*
	* @brief
	* 实数向量转换为复数向量
	* @param
	* vec : 向量对象
	* @return
	* 复数向量
	*/
	static VectorRowI toComplex(const VectorRow& vec);
	/*
	* @brief
	* 生成随机数行向量
	* @param
	* size : 向量长度
	* @return
	* 行向量
	*/
	static VectorRow random(size_t size);
};


/*实数列向量*/
class VectorColumn : public VectorXdType<double> {
	friend Matrix;
public:
	VectorColumn();
	VectorColumn(size_t len);
	VectorColumn(const Container1D<double>& list);
	VectorColumn(const initializer_list<double>& list);
	VectorColumn(const VectorColumn& vec);
	VectorColumn(const MatrixOperation<double>& tree);
	VectorColumn(const MatrixXdType<double>& matxd);
	/*
	* @brief
	* 从表达式树创建实数列向量
	* @param
	* tree : 表达式树
	* @return
	* 实数列向量引用
	*/
	VectorColumn& operator =(const MatrixOperation<double>& tree);
	/*
	* @brief
	* 从矩阵基类创建实数列向量
	* @param
	* matxd : 矩阵基类
	* @return
	* 实数列向量引用
	*/
	VectorColumn& operator =(const MatrixXdType<double>& matxd);
	/*
	* @brief
	* 从实数列向量拷贝构造
	* @param
	* vec : 向量
	* @return
	* 实数列向量引用
	*/
	VectorColumn& operator=(const VectorColumn& vec);
public:
	/*
	* @brief
	* 填充向量
	* @param
	* size : 向量长度
	* @param
	* var : 填充元素
	* @return
	* 向量
	*/
	static VectorColumn fill(size_t size, double var);
	/*
	* @brief
	* 生成全1向量
	* @param
	* size : 向量长度
	* @return
	* 向量
	*/
	static VectorColumn ones(size_t size);
	/*
	* @brief
	* 实数向量转换为复数向量
	* @param
	* vec : 向量对象
	* @return
	* 复数向量
	*/
	static VectorColumnI toComplex(const VectorColumn& vec);
	/*
	* @brief
	* 生成随机数列向量
	* @param
	* size : 向量长度
	* @return
	* 列向量
	*/
	static VectorColumn random(size_t size);
};


/*复数行向量*/
class VectorRowI : public VectorXdType<Complex> {
	friend VectorColumnI;
	friend VectorRow;
	friend MatrixI;
public:
	VectorRowI();
	VectorRowI(size_t len);
	VectorRowI(const Container1D<Complex>& list);
	VectorRowI(const initializer_list<Complex>& list);
	VectorRowI(const VectorRowI& vec);
	VectorRowI(const MatrixOperation<Complex>& tree);
	VectorRowI(const MatrixXdType<Complex>& matxd);
	/*
	* @brief
	* 从表达式树创建复数行向量
	* @param
	* tree : 表达式树
	* @return
	* 复数行向量引用
	*/
	VectorRowI& operator =(const MatrixOperation<Complex>& tree);
	/*
	* @brief
	* 从矩阵基类创建复数行向量
	* @param
	* matxd : 矩阵基类
	* @return
	* 复数行向量引用
	*/
	VectorRowI& operator =(const MatrixXdType<Complex>& matxd);
	/*
	* @brief
	* 从复数行向量拷贝
	* @param
	* vec : 向量
	* @return
	* 复数行向量引用
	*/
	VectorRowI& operator=(const VectorRowI& vec);
public:
	/*
	* @brief
	* 填充向量
	* @param
	* size : 向量长度
	* @param
	* var : 填充元素
	* @return
	* 向量
	*/
	static VectorRowI fill(size_t size, const Complex& var);
	/*
	* @brief
	* 生成全1向量
	* @param
	* size : 向量长度
	* @return
	* 向量
	*/
	static VectorRowI ones(size_t size);
	/*
	* @brief
	* 生成复随机数行向量
	* @param
	* size : 向量长度
	* @return
	* 行向量
	*/
	static VectorRowI random(size_t size);
};


/*复数列向量*/
class VectorColumnI : public VectorXdType<Complex> {
	friend VectorRowI;
	friend VectorColumn;
	friend MatrixI;
public:
	VectorColumnI();
	VectorColumnI(size_t len);
	VectorColumnI(const Container1D<Complex>& list);
	VectorColumnI(const initializer_list<Complex>& list);
	VectorColumnI(const VectorColumnI& vec);
	VectorColumnI(const MatrixOperation<Complex>& tree);
	VectorColumnI(const MatrixXdType<Complex>& matxd);
	/*
	* @brief
	* 从表达式树创建复数列向量
	* @param
	* tree : 表达式树
	* @return
	* 复数列向量引用
	*/
	 VectorColumnI& operator =(const MatrixOperation<Complex>& tree);
	/*
	* @brief
	* 从矩阵基类创建复数列向量
	* @param
	* matxd : 矩阵基类
	* @return
	* 复数列向量引用
	*/
	VectorColumnI& operator =(const MatrixXdType<Complex>& matxd);
	/*
	* @brief
	* 从列向量拷贝构造
	* @param
	* vec : 列向量
	* @return
	* 复数列向量引用
	*/
	VectorColumnI& operator =(const VectorColumnI& vec);
public:
	/*
	* @brief
	* 填充向量
	* @param
	* size : 向量长度
	* @param
	* var : 填充元素
	* @return
	* 向量
	*/
	static VectorColumnI fill(size_t size, const Complex& var);
	/*
	* @brief
	* 生成全1向量
	* @param
	* size : 向量长度
	* @return
	* 向量
	*/
	static VectorColumnI ones(size_t size);
	/*
	* @brief
	* 生成复随机数列向量
	* @param
	* size : 向量长度
	* @return
	* 列向量
	*/
	static VectorColumnI random(size_t size);
};

/*实数矩阵*/
class Matrix : public MatrixXdType<double> {
	friend MatrixI;
public:
	Matrix();
	Matrix(size_t r, size_t c);
	Matrix(size_t r, size_t c, const initializer_list<double>& list);
	Matrix(const Matrix& mat);
	Matrix(const MatrixOperation<double>& tree);
	Matrix(const MatrixXdType<double>& matxd);
	/*
	* @brief
	* 获取矩阵一行
	* @param
	* r_index : 行索引
	* @return
	* 一行的元素
	*/
	virtual VectorRow& getRow(const size_t r_index);
	/*
	* @brief
	* 获取矩阵一列
	* @param
	* c_index : 列索引
	* @return
	* 一列的元素
	*/
	virtual VectorColumn& getColumn(const size_t c_index);
	/*
	* @brief
	* 行替换
	* @param
	* vec : 替换的向量
	* @param
	* index : 替换的行索引
	* @return
	* 无
	*/
	void replace(const VectorRow& vec, size_t index);
	/*
	* @brief
	* 列替换
	* @param
	* vec : 替换的向量
	* @param
	* index : 替换的列索引
	* @return
	* 无
	*/
	void replace(const VectorColumn& vec, size_t index);
	/*
	* @brief
	* 实数矩阵求逆
	* @param
	* 无
	* @return
	* 逆矩阵
	*/
	Matrix I() const;
	/*
	* @brief
	* 获取矩阵实数部分
	* @param
	* 无
	* @return
	* 矩阵实数部分
	*/
	virtual Matrix real() const;
	/*
	* @brief
	* 获取矩阵虚数部分
	* @param
	* 无
	* @return
	* 矩阵虚数部分
	*/
	virtual Matrix imag() const;
	/*
	* @brief
	* 保存矩阵
	* @param
	* path: 文件路径
	* @return
	* 是否保存成功，1表示成功，0表示失败
	*/
	bool save(const char* path) const;
	/*
	* @brief
	* 从表达式创建实数矩阵
	* @param
	* tree : 表达式树
	* @return
	* 无
	*/
	void operator=(const MatrixOperation<double>& tree);
	/*
	* @brief
	* 从矩阵基类创建实数矩阵
	* @param
	* matxd : 矩阵基类
	* @return
	* 无
	*/
	void operator=(const MatrixXdType<double>& matxd);
private:
	/*@brief
	* 内部方法，不公开。辅助矩阵求逆，按照矩阵每行0的个数给矩阵进行阶梯型排序
	* @param
	* mat : Matrix对象
	* @param
	* newmat : 矩阵求逆过程中位于原矩阵后方的新矩阵
	* @return
	* 无
	*/
	void sort(Matrix& mat, Matrix& newmat) const;
	/*@brief
	* 内部方法，不公开。辅助矩阵求逆的函数，用于寻找矩阵每行非0元素的起始位置
	* @param
	* mat : Matrix对象
	* @param
	* row : 需要查找的行索引
	* @return
	* 非0元素起始索引
	*/
	size_t seek(const Matrix& mat, size_t row) const;
public:
	/*
	* @brief
	* 从文件读取矩阵
	* @param
	* path: 路径
	* @param
	* ok: 是否读取成功
	* @return
	* 矩阵对象
	*/
	static Matrix read(const char* path, bool* ok = nullptr);
	/*
	* @brief
	* 创建对角阵
	* @param
	* r : 阶数
	* @param
	* var : 对角线元素
	* @return
	* 对角矩阵
	*/
	static Matrix identity(size_t r, double var);
	/*
	* @brief
	* 创建单位矩阵
	* @param
	* r : 阶数
	* @return
	* 单位矩阵
	*/
	static Matrix eye(size_t r);
	/*
	* @brief
	* 矩阵所有位置填充相同元素
	* @param
	* r : 行数
	* @param
	* c : 列数
	* @param
	* var : 填充元素
	* @return
	* 填充矩阵
	*/
	static Matrix fill(size_t r, size_t c, double var);
	/*
	* @brief
	* 指定对角线元素生成矩阵
	* @param
	* list : 对角线元素列表
	* @return
	* 对角线矩阵
	*/
	static Matrix diag(const Container1D<double>& list);
	/*
	* @brief
	* 实数矩阵转换为复数矩阵
	* @param
	* matrix : 矩阵对象
	* @return
	* 复数矩阵
	*/
	static MatrixI toComplex(const Matrix& matrix);
	/*
	* @brief
	* 生成随机数矩阵
	* @param
	* row : 行数
	* @param
	* column : 列数
	* @return
	* 随机数矩阵
	*/
	static Matrix random(size_t row, size_t column);
	/*
	* @brief
	* 生成列随机矩阵
	* @param
	* row : 行数
	* @param
	* column : 列数
	* @return
	* 列随机矩阵
	*/
	static Matrix stochastic(size_t row, size_t column);
};


/*复数矩阵*/
class MatrixI : public MatrixXdType<Complex> {
	friend Matrix;
public:
	MatrixI();
	MatrixI(size_t r, size_t c);
	MatrixI(size_t r, size_t c, const initializer_list<Complex>& list);
	MatrixI(const Matrix& realMat, const Matrix& imagMat);
	MatrixI(const MatrixI& mat);
	MatrixI(const MatrixOperation<Complex>& tree);
	MatrixI(const MatrixXdType<Complex>& matxd);
	/*
	* @brief
	* 获取矩阵一行
	* @param
	* r_index : 行索引
	* @return
	* 一行的元素
	*/
	virtual VectorRowI& getRow(const size_t r_index);
	/*
	* @brief
	* 获取矩阵一列
	* @param
	* c_index : 列索引
	* @return
	* 一列的元素
	*/
	virtual VectorColumnI& getColumn(const size_t c_index);
	/*
	* @brief
	* 行替换
	* @param
	* vec : 替换的向量
	* @param
	* index : 替换的行索引
	* @return
	* 无
	*/
	void replace(const VectorRowI& vec, size_t index);
	/*
	* @brief
	* 列替换
	* @param
	* vec : 替换的向量
	* @param
	* index : 替换的列索引
	* @return
	* 无
	*/
	void replace(const VectorColumnI& vec, size_t index);
	/*
	* @brief
	* 复数矩阵求逆
	* @param
	* 无
	* @return
	* 逆矩阵
	*/
	MatrixI I() const;
	/*
	* @brief
	* 获取矩阵实数部分
	* @param
	* 无
	* @return
	* 矩阵实数部分
	*/
	virtual Matrix real() const;
	/*
	* @brief
	* 获取矩阵虚数部分
	* @param
	* 无
	* @return
	* 矩阵虚数部分
	*/
	virtual Matrix imag() const;
	/*
	* @brief
	* 保存矩阵
	* @param
	* path: 文件路径
	* @return
	* 是否保存成功，1表示成功，0表示失败
	*/
	bool save(const char* path) const;
	/*
	* @brief
	* 从表达式创建复数矩阵
	* @param
	* tree : 表达式树
	* @return
	* 无
	*/
	void operator=(const MatrixOperation<Complex>& tree);
	/*
	* @brief
	* 从矩阵基类创建复数矩阵
	* @param
	* matxd : 矩阵基类
	* @return
	* 无
	*/
	void operator=(const MatrixXdType<Complex>& matxd);
public:
	/*
	* @brief
	* 从文件读取矩阵
	* @param
	* path: 路径
	* @param
	* ok: 是否读取成功
	* @return
	* 矩阵对象
	*/
	static MatrixI read(const char* path, bool* ok = nullptr);
	/*
	* @brief
	* 创建对角阵
	* @param
	* r : 阶数
	* @param
	* var : 对角线元素
	* @return
	* 对角矩阵
	*/
	static MatrixI identity(size_t r, const Complex& var);
	/*
	* @brief
	* 创建单位矩阵
	* @param
	* r : 阶数
	* @return
	* 单位矩阵
	*/
	static MatrixI eye(size_t r);
	/*
	* @brief
	* 矩阵所有位置填充相同元素
	* @param
	* r : 行数
	* @param
	* c : 列数
	* @param
	* var : 填充元素
	* @return
	* 填充矩阵
	*/
	static MatrixI fill(size_t r, size_t c, const Complex& var);
	/*
	* @brief
	* 指定对角线元素生成矩阵
	* @param
	* list : 对角线元素列表
	* @return
	* 对角线矩阵
	*/
	static MatrixI diag(const Container1D<Complex>& list);
	/*
	* @brief
	* 生成复随机数矩阵
	* @param
	* row : 行数
	* @param
	* column : 列数
	* @return
	* 随机数矩阵
	*/
	static MatrixI random(size_t row, size_t column);
};

#endif // !MATRIX_H
