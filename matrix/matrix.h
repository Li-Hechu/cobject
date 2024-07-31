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


/*ʵ��������*/
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
	* �ӱ��ʽ������ʵ��������
	* @param
	* tree : ���ʽ��
	* @return
	* ʵ������������
	*/
	VectorRow& operator =(const MatrixOperation<double>& tree);
	/*
	* @brief
	* �Ӿ�����ഴ��ʵ��������
	* @param
	* matxd : �������
	* @return
	* ʵ������������
	*/
	VectorRow& operator =(const MatrixXdType<double>& matxd);
	/*
	* @brief
	* ��ʵ����������������
	* @param
	* vec : ����
	* @return
	* ʵ������������
	*/
	VectorRow& operator =(const VectorRow& vec);
public:
	/*
	* @brief
	* �������
	* @param
	* size : ��������
	* @param
	* var : ���Ԫ��
	* @return
	* ����
	*/
	static VectorRow fill(size_t size, double var);
	/*
	* @brief
	* ����ȫ1����
	* @param
	* size : ��������
	* @return
	* ����
	*/
	static VectorRow ones(size_t size);
	/*
	* @brief
	* ʵ������ת��Ϊ��������
	* @param
	* vec : ��������
	* @return
	* ��������
	*/
	static VectorRowI toComplex(const VectorRow& vec);
	/*
	* @brief
	* ���������������
	* @param
	* size : ��������
	* @return
	* ������
	*/
	static VectorRow random(size_t size);
};


/*ʵ��������*/
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
	* �ӱ��ʽ������ʵ��������
	* @param
	* tree : ���ʽ��
	* @return
	* ʵ������������
	*/
	VectorColumn& operator =(const MatrixOperation<double>& tree);
	/*
	* @brief
	* �Ӿ�����ഴ��ʵ��������
	* @param
	* matxd : �������
	* @return
	* ʵ������������
	*/
	VectorColumn& operator =(const MatrixXdType<double>& matxd);
	/*
	* @brief
	* ��ʵ����������������
	* @param
	* vec : ����
	* @return
	* ʵ������������
	*/
	VectorColumn& operator=(const VectorColumn& vec);
public:
	/*
	* @brief
	* �������
	* @param
	* size : ��������
	* @param
	* var : ���Ԫ��
	* @return
	* ����
	*/
	static VectorColumn fill(size_t size, double var);
	/*
	* @brief
	* ����ȫ1����
	* @param
	* size : ��������
	* @return
	* ����
	*/
	static VectorColumn ones(size_t size);
	/*
	* @brief
	* ʵ������ת��Ϊ��������
	* @param
	* vec : ��������
	* @return
	* ��������
	*/
	static VectorColumnI toComplex(const VectorColumn& vec);
	/*
	* @brief
	* ���������������
	* @param
	* size : ��������
	* @return
	* ������
	*/
	static VectorColumn random(size_t size);
};


/*����������*/
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
	* �ӱ��ʽ����������������
	* @param
	* tree : ���ʽ��
	* @return
	* ��������������
	*/
	VectorRowI& operator =(const MatrixOperation<Complex>& tree);
	/*
	* @brief
	* �Ӿ�����ഴ������������
	* @param
	* matxd : �������
	* @return
	* ��������������
	*/
	VectorRowI& operator =(const MatrixXdType<Complex>& matxd);
	/*
	* @brief
	* �Ӹ�������������
	* @param
	* vec : ����
	* @return
	* ��������������
	*/
	VectorRowI& operator=(const VectorRowI& vec);
public:
	/*
	* @brief
	* �������
	* @param
	* size : ��������
	* @param
	* var : ���Ԫ��
	* @return
	* ����
	*/
	static VectorRowI fill(size_t size, const Complex& var);
	/*
	* @brief
	* ����ȫ1����
	* @param
	* size : ��������
	* @return
	* ����
	*/
	static VectorRowI ones(size_t size);
	/*
	* @brief
	* ���ɸ������������
	* @param
	* size : ��������
	* @return
	* ������
	*/
	static VectorRowI random(size_t size);
};


/*����������*/
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
	* �ӱ��ʽ����������������
	* @param
	* tree : ���ʽ��
	* @return
	* ��������������
	*/
	 VectorColumnI& operator =(const MatrixOperation<Complex>& tree);
	/*
	* @brief
	* �Ӿ�����ഴ������������
	* @param
	* matxd : �������
	* @return
	* ��������������
	*/
	VectorColumnI& operator =(const MatrixXdType<Complex>& matxd);
	/*
	* @brief
	* ����������������
	* @param
	* vec : ������
	* @return
	* ��������������
	*/
	VectorColumnI& operator =(const VectorColumnI& vec);
public:
	/*
	* @brief
	* �������
	* @param
	* size : ��������
	* @param
	* var : ���Ԫ��
	* @return
	* ����
	*/
	static VectorColumnI fill(size_t size, const Complex& var);
	/*
	* @brief
	* ����ȫ1����
	* @param
	* size : ��������
	* @return
	* ����
	*/
	static VectorColumnI ones(size_t size);
	/*
	* @brief
	* ���ɸ������������
	* @param
	* size : ��������
	* @return
	* ������
	*/
	static VectorColumnI random(size_t size);
};

/*ʵ������*/
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
	* ��ȡ����һ��
	* @param
	* r_index : ������
	* @return
	* һ�е�Ԫ��
	*/
	virtual VectorRow& getRow(const size_t r_index);
	/*
	* @brief
	* ��ȡ����һ��
	* @param
	* c_index : ������
	* @return
	* һ�е�Ԫ��
	*/
	virtual VectorColumn& getColumn(const size_t c_index);
	/*
	* @brief
	* ���滻
	* @param
	* vec : �滻������
	* @param
	* index : �滻��������
	* @return
	* ��
	*/
	void replace(const VectorRow& vec, size_t index);
	/*
	* @brief
	* ���滻
	* @param
	* vec : �滻������
	* @param
	* index : �滻��������
	* @return
	* ��
	*/
	void replace(const VectorColumn& vec, size_t index);
	/*
	* @brief
	* ʵ����������
	* @param
	* ��
	* @return
	* �����
	*/
	Matrix I() const;
	/*
	* @brief
	* ��ȡ����ʵ������
	* @param
	* ��
	* @return
	* ����ʵ������
	*/
	virtual Matrix real() const;
	/*
	* @brief
	* ��ȡ������������
	* @param
	* ��
	* @return
	* ������������
	*/
	virtual Matrix imag() const;
	/*
	* @brief
	* �������
	* @param
	* path: �ļ�·��
	* @return
	* �Ƿ񱣴�ɹ���1��ʾ�ɹ���0��ʾʧ��
	*/
	bool save(const char* path) const;
	/*
	* @brief
	* �ӱ��ʽ����ʵ������
	* @param
	* tree : ���ʽ��
	* @return
	* ��
	*/
	void operator=(const MatrixOperation<double>& tree);
	/*
	* @brief
	* �Ӿ�����ഴ��ʵ������
	* @param
	* matxd : �������
	* @return
	* ��
	*/
	void operator=(const MatrixXdType<double>& matxd);
private:
	/*@brief
	* �ڲ��������������������������棬���վ���ÿ��0�ĸ�����������н���������
	* @param
	* mat : Matrix����
	* @param
	* newmat : �������������λ��ԭ����󷽵��¾���
	* @return
	* ��
	*/
	void sort(Matrix& mat, Matrix& newmat) const;
	/*@brief
	* �ڲ���������������������������ĺ���������Ѱ�Ҿ���ÿ�з�0Ԫ�ص���ʼλ��
	* @param
	* mat : Matrix����
	* @param
	* row : ��Ҫ���ҵ�������
	* @return
	* ��0Ԫ����ʼ����
	*/
	size_t seek(const Matrix& mat, size_t row) const;
public:
	/*
	* @brief
	* ���ļ���ȡ����
	* @param
	* path: ·��
	* @param
	* ok: �Ƿ��ȡ�ɹ�
	* @return
	* �������
	*/
	static Matrix read(const char* path, bool* ok = nullptr);
	/*
	* @brief
	* �����Խ���
	* @param
	* r : ����
	* @param
	* var : �Խ���Ԫ��
	* @return
	* �ԽǾ���
	*/
	static Matrix identity(size_t r, double var);
	/*
	* @brief
	* ������λ����
	* @param
	* r : ����
	* @return
	* ��λ����
	*/
	static Matrix eye(size_t r);
	/*
	* @brief
	* ��������λ�������ͬԪ��
	* @param
	* r : ����
	* @param
	* c : ����
	* @param
	* var : ���Ԫ��
	* @return
	* ������
	*/
	static Matrix fill(size_t r, size_t c, double var);
	/*
	* @brief
	* ָ���Խ���Ԫ�����ɾ���
	* @param
	* list : �Խ���Ԫ���б�
	* @return
	* �Խ��߾���
	*/
	static Matrix diag(const Container1D<double>& list);
	/*
	* @brief
	* ʵ������ת��Ϊ��������
	* @param
	* matrix : �������
	* @return
	* ��������
	*/
	static MatrixI toComplex(const Matrix& matrix);
	/*
	* @brief
	* �������������
	* @param
	* row : ����
	* @param
	* column : ����
	* @return
	* ���������
	*/
	static Matrix random(size_t row, size_t column);
	/*
	* @brief
	* �������������
	* @param
	* row : ����
	* @param
	* column : ����
	* @return
	* ���������
	*/
	static Matrix stochastic(size_t row, size_t column);
};


/*��������*/
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
	* ��ȡ����һ��
	* @param
	* r_index : ������
	* @return
	* һ�е�Ԫ��
	*/
	virtual VectorRowI& getRow(const size_t r_index);
	/*
	* @brief
	* ��ȡ����һ��
	* @param
	* c_index : ������
	* @return
	* һ�е�Ԫ��
	*/
	virtual VectorColumnI& getColumn(const size_t c_index);
	/*
	* @brief
	* ���滻
	* @param
	* vec : �滻������
	* @param
	* index : �滻��������
	* @return
	* ��
	*/
	void replace(const VectorRowI& vec, size_t index);
	/*
	* @brief
	* ���滻
	* @param
	* vec : �滻������
	* @param
	* index : �滻��������
	* @return
	* ��
	*/
	void replace(const VectorColumnI& vec, size_t index);
	/*
	* @brief
	* ������������
	* @param
	* ��
	* @return
	* �����
	*/
	MatrixI I() const;
	/*
	* @brief
	* ��ȡ����ʵ������
	* @param
	* ��
	* @return
	* ����ʵ������
	*/
	virtual Matrix real() const;
	/*
	* @brief
	* ��ȡ������������
	* @param
	* ��
	* @return
	* ������������
	*/
	virtual Matrix imag() const;
	/*
	* @brief
	* �������
	* @param
	* path: �ļ�·��
	* @return
	* �Ƿ񱣴�ɹ���1��ʾ�ɹ���0��ʾʧ��
	*/
	bool save(const char* path) const;
	/*
	* @brief
	* �ӱ��ʽ������������
	* @param
	* tree : ���ʽ��
	* @return
	* ��
	*/
	void operator=(const MatrixOperation<Complex>& tree);
	/*
	* @brief
	* �Ӿ�����ഴ����������
	* @param
	* matxd : �������
	* @return
	* ��
	*/
	void operator=(const MatrixXdType<Complex>& matxd);
public:
	/*
	* @brief
	* ���ļ���ȡ����
	* @param
	* path: ·��
	* @param
	* ok: �Ƿ��ȡ�ɹ�
	* @return
	* �������
	*/
	static MatrixI read(const char* path, bool* ok = nullptr);
	/*
	* @brief
	* �����Խ���
	* @param
	* r : ����
	* @param
	* var : �Խ���Ԫ��
	* @return
	* �ԽǾ���
	*/
	static MatrixI identity(size_t r, const Complex& var);
	/*
	* @brief
	* ������λ����
	* @param
	* r : ����
	* @return
	* ��λ����
	*/
	static MatrixI eye(size_t r);
	/*
	* @brief
	* ��������λ�������ͬԪ��
	* @param
	* r : ����
	* @param
	* c : ����
	* @param
	* var : ���Ԫ��
	* @return
	* ������
	*/
	static MatrixI fill(size_t r, size_t c, const Complex& var);
	/*
	* @brief
	* ָ���Խ���Ԫ�����ɾ���
	* @param
	* list : �Խ���Ԫ���б�
	* @return
	* �Խ��߾���
	*/
	static MatrixI diag(const Container1D<Complex>& list);
	/*
	* @brief
	* ���ɸ����������
	* @param
	* row : ����
	* @param
	* column : ����
	* @return
	* ���������
	*/
	static MatrixI random(size_t row, size_t column);
};

#endif // !MATRIX_H
