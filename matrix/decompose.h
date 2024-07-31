#pragma once

#ifndef DECOMPOSE_H
#define DECOMPOSE_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "matrix.h"

//����PLU�ֽ�ṹ��
template<typename MatType>
struct matPLU {
	//�û�����
	MatType P;
	//�����Ǿ���
	MatType L;
	//�����Ǿ���
	MatType U;
};

//ʵ������PLU�ֽ�
typedef matPLU<Matrix> PLU;
//��������PLU�ֽ�
typedef matPLU<MatrixI> PLUI;


//����QR�ֽ�ṹ��
template<typename MatType>
struct matQR {
	//��������
	MatType Q;
	//�����Ǿ���
	MatType R;
};

//ʵ������QR�ֽ�
typedef matQR<Matrix> QR;
//��������QR�ֽ�
typedef matQR<MatrixI> QRI;

//��������ֵ�ֽ�ṹ��
template<typename MatType>
struct matEIG {
	//����ֵ����
	MatType E;
	//������������
	MatType F;
};

//ʵ�������ֽ�
typedef matEIG<Matrix> EIG;
//���������ֽ�
typedef matEIG<MatrixI> EIGI;


//����SVD�ֽ�ṹ��
template<typename MatType>
struct matSVD {
	//���������
	MatType U;
	//����ֵ����
	MatType S;
	//���������
	MatType V;
	///�������A������ֵ�ֽ����� A = U*S*V.H()
};

//ʵ������SVD�ֽ�
typedef matSVD<Matrix> SVD;
//����SVD�ֽ�
typedef matSVD<MatrixI> SVDI;


//�Ϻ�ɭ�������Ʊ任
template<typename MatType>
struct matHessen {
	//�Ϻ�ɭ������ʽ
	MatType H;
	//��������
	MatType Q;
	/// �������A�ĺ�ɭ������ʽH���� H = Q*A*Q.H
};

//ʵ������ɭ����任�ṹ��
typedef matHessen<Matrix> Hessen;
//��������ɭ����任�ṹ��
typedef matHessen<MatrixI> HessenI;


/*
* @brief
* ʵ������PLU�ֽ�
* @param
* mat : ����
* @return
* �ֽ�ṹ��
*/
PLU plu(const Matrix& mat);

/*
* @brief
* ��������PLU�ֽ�
* @param
* mat : ����
* @return
* �ֽ�ṹ��
*/
PLUI plu(const MatrixI& mat);

/*
* @brief
* ʵ����������
* @param
* mat : ʵ������
* @return
* �����
*/
Matrix inv(const Matrix& mat);

/*
* @brief
* ������������
* @param
* mat : ��������
* @return
* �������
*/
MatrixI inv(const MatrixI& mat);

/*
* @brief
* ʵ��������˹�����·���
* @param
* x : ����1
* @param
* w : ����2
* @param
* check : �Ƿ��鼸�γ���һ�£�Ĭ�ϲ����
* @return
* ��˹�����·������
*/
Matrix householder(const VectorColumn& x, const VectorColumn& w, bool check = false);

/*
* @brief
* ����������˹�����·���
* @param
* x : ����1
* @param
* w : ����2
* @param
* check : �Ƿ��鼸�γ���һ�£�Ĭ�ϲ����
* @return
* ��˹�����·������
*/
MatrixI householder(const VectorColumnI& x, const VectorColumnI& w, bool check = false);

/*
* @brief
* ʵ������QR�ֽ�
* @param
* mat : ����
* @return
* QR�ֽ�ṹ��
*/
QR qr(const Matrix& mat);

/*
* @brief
* ��������QR�ֽ�
* @param
* mat : ����
* @return
* QR�ֽ�ṹ��
*/
QRI qr(const MatrixI& mat);

/*
* @brief
* ʵ��������Ϻ�ɭ�������Ʊ任
* @param
* mat : ����
* @return
* Hessen�ֽ�ṹ��
*/
Hessen hessenburge(const Matrix& mat);

/*
* @brief
* ����������Ϻ�ɭ�������Ʊ任
* @param
* mat : ����
* @return
* Hessen�ֽ�ṹ��
*/
HessenI hessenburge(const MatrixI& mat);

/*
* @brief
* �ݷ�
* @param
* mat : ʵ������
* @param
* flag : �����Ƿ�ɹ�
* @return
* ʵ������ֵ�������ֵ
*/
double powerit(const Matrix& mat, bool* flag = nullptr);

/*
* @brief
* �ݷ�
* @param
* mat : ��������
* @param
* flag : �����Ƿ�ɹ�
* @return
* ��������ֵ�������ֵ
*/
Complex powerit(const MatrixI& mat, bool* flag = nullptr);

/*
* @brief
* �����̵���
* @param
* mat : ʵ������
* @param
* flag : �����Ƿ�ɹ�
* @return
* ʵ������ֵ�������ֵ
*/

double rayleigh(const Matrix& mat, bool* flag = nullptr);

/*
* @brief
* �����̵���
* @param
* mat : ʵ������
* @param
* flag : �����Ƿ�ɹ�
* @return
* ��������ֵ�������ֵ
*/

Complex rayleigh(const MatrixI& mat, bool* flag = nullptr);

/*
* @brief
* ��ƽ�Ƶķ��ݷ�
* @param
* mat : ʵ������
* @param
* s0 : ����ֵ�Ľ���
* @param
* init_var : ��ʼ�����������ֵ������Ϊ0
* @return
* ��s0���������ֵ������������
*/
Match<double,VectorColumn> invpowerit(const Matrix& mat, double s0 = 0, double init_var = 1);

/*
* @brief
* ��ƽ�Ƶķ��ݷ�
* @param
* mat : ��������
* @param
* s0 : ����ֵ�Ľ���
* @param
* init_var : ��ʼ�����������ֵ������Ϊ0
* @return
* ��s0���������ֵ������������
*/
Match<Complex, VectorColumnI> invpowerit(const MatrixI& mat, const Complex& s0 = 0, const Complex& init_var = 1 + 1j);

/*
* @brief
* ���һ����������ֵ����������
* @param
* mat : ����
* @return
* �����ֽ�ṹ��
*/
EIGI eigen(const MatrixI& mat);

/*
* @brief
* ʵ�Գƾ��������ֽ�
* @param
* mat : ʵ�Գƾ���
* @param
* �����ֽ�ṹ��
*/
EIG eigen_s(const Matrix& mat);

/*
* @brief
* ���Գƣ������أ����������ֽ�
* @param
* mat : ���Գƾ���
* @return
* �����ֽ�ṹ��
*/
EIGI eigen_s(const MatrixI& mat);

/*
* @brief
* ʵ������SVD�ֽ�
* @param
* mat : ����
* @return
* SVD�ֽ�ṹ��
*/
SVD svd(const Matrix& mat);

/*
* @brief
* ��������SVD�ֽ�
* @param
* mat : ����
* @return
* SVD�ֽ�ṹ��
*/
SVDI svd(const MatrixI& mat);

/*
* @brief
* Moore-Penrose���������
* @param
* mat: ʵ������
* @return
* ���������
*/
Matrix pinv(const Matrix& mat);

/*
* @brief
* Moore-Penrose���������
* @param
* mat: ��������
* @return
* ���������
*/
MatrixI pinv(const MatrixI& mat);

#endif // !DECOMPOSE_H
