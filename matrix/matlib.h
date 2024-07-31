#pragma once

#ifndef MATLIB_H
#define MATLIB_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "matrix.h"

/*
* @brief
* ������һ����
* @param
* vec : ����
* @return
* ��һ����
*/
double normal1(const VectorXdType<double>& vec);

/*
* @brief
* ������һ����
* @param
* vec : ����
* @return
* ��һ����
*/
double normal1(const VectorXdType<Complex>& vec);

/*
* @brief
* �����ڶ�����
* @param
* vec : ����
* @return
* �ڶ�����
*/
double normal2(const VectorXdType<double>& vec);

/*
* @brief
* �����ڶ�����
* @param
* vec : ����
* @return
* �ڶ�����
*/
double normal2(const VectorXdType<Complex>& vec);

/*
* @brief
* ������������������
* @param
* vec : ����
* @return
* �����������
*/
double normalN(const VectorXdType<double>& vec);

/*
* @brief
* ������������������
* @param
* vec : ����
* @return
* �����������
*/
double normalN(const VectorXdType<Complex>& vec);

/*
* @brief
* �������һ����
* @param
* mat : ����
* @return
* �����һ����
*/
double normal1(const MatrixXdType<double>& mat);

/*
* @brief
* �������һ����
* @param
* mat : ����
* @return
* �����һ����
*/
double normal1(const MatrixXdType<Complex>& mat);

/*
* @brief
* ��������������������
* @param
* mat : ����
* @return
* ���������
*/
double normalN(const MatrixXdType<double>& mat);

/*
* @brief
* ��������������������
* @param
* mat : ����
* @return
* ���������
*/
double normalN(const MatrixXdType<Complex>& mat);

/*
* @brief
* �����������
* @param
* mat : ���󣨷���
* @return
* ������
*/
double cond(const Matrix& mat);

/*
* @brief
* �����������
* @param
* mat : ���󣨷���
* @return
* ������
*/
double cond(const MatrixI& mat);

/*
* @brief
* �ж�ʵ�������Ƿ�Ϊ0����
* @param
* vec : ��������
* @return
* 1��ʾ0������0��ʾ���ڲ�Ϊ0��Ԫ��
*/
bool vectorIsZero(const VectorXdType<double>& vec);

/*
* @brief
* �жϸ��������Ƿ�Ϊ0����
* @param
* vec : ��������
* @return
* 1��ʾ0������0��ʾ���ڲ�Ϊ0��Ԫ��
*/
bool vectorIsZero(const VectorXdType<Complex>& vec);

/*
* @brief
* �������Ԫ�ؾ���ֵ�Ƿ��С��ĳһ������
* @param
* vec: ����
* @param
* val: ����
* @return
* 1��ʾ��С�ڸ����֣�0��ʾ�����������
*/
bool vectorMinus(const VectorXdType<double>& vec, const double val);

/*
* @brief
* �������Ԫ�ؾ���ֵ�Ƿ��С��ĳһ������
* @param
* vec: ����
* @param
* val: ����
* @return
* 1��ʾ��С�ڸ����֣�0��ʾ�����������
*/
bool vectorMinus(const VectorXdType<Complex>& vec, const double val);

/*
* @brief
* ����������Ƿ����inf
* @param
* vec: ����
* @return
* 1��ʾ����inf��0��ʾ������
*/
bool vectorHasInf(const VectorXdType<double>& vec);

/*
* @brief
* ����������Ƿ����inf
* @param
* vec: ����
* @return
* 1��ʾ����inf��0��ʾ������
*/
bool vectorHasInf(const VectorXdType<Complex>& vec);

/*
* @brief
* ��λ��һ��ʵ������
* @param
* vec : ����
* @return
* ��
*/
void unitization(VectorXdType<double>& vec);

/*
* @brief
* ��λ��һ����������
* @param
* vec : ����
* @return
* ��
*/
void unitization(VectorXdType<Complex>& vec);

/*
* @brief
* ����ƴ��
* @param
* matlist : �����б�
* @param
* direct : ƴ�ӷ���1��ʾ����0��ʾ����
* @return
* ƴ�Ӻ�ľ���
*/
Matrix matrixConcat(const Container1D<MatrixXdType<double>>& matlist, bool direct = true);

/*
* @brief
* ����ƴ��
* @param
* matlist : �����б�
* @param
* direct : ƴ�ӷ���1��ʾ����0��ʾ����
* @return
* ƴ�Ӻ�ľ���
*/
MatrixI matrixConcat(const Container1D<MatrixXdType<Complex>>& matlist, bool direct = true);

/*
* @brief
* ��˹��Ԫ���ʵ��������
* @param
* mat : ϵ������
* @param
* vec : �������
* @return
* ������Ľ�
*/
VectorColumn gauss(const Matrix& mat, const VectorColumn& vec);

/*
* @brief
* ��˹��Ԫ��⸴��������
* @param
* mat : ϵ������
* @param
* vec : �������
* @return
* ������Ľ�
*/
VectorColumnI gauss(const MatrixI& mat, const VectorColumnI& vec);

/*
* @brief
* ��С���˷�����޽⣨��һ�£�������
* @param
* A: �����Ⱦ���
* @param
* b: �������
* @param
* _qr: �Ƿ�ʹ��QR�ֽ��ȡ�߾��Ƚ���������ھ���A�������ϴ�������1��ʾʹ�ã�0��ʾ��ʹ��
* @return
* ��С���˽�
*/
VectorColumn ls(const Matrix& A, const VectorColumn& b, bool _qr = false);

/*
* @brief
* ��С���˷�����޽⣨��һ�£�������
* @param
* A: �����Ⱦ���
* @param
* b: �������
* @param
* _qr: �Ƿ�ʹ��QR�ֽ��ȡ�߾��Ƚ���������ھ���A�������ϴ�������1��ʾʹ�ã�0��ʾ��ʹ��
* @return
* ��С���˽�
*/
VectorColumnI ls(const MatrixI& A, const VectorColumnI& b, bool _qr = false);

/*
* @brief
* ���޽�����������ķ���������ƽ�
* @param
* A: ϵ������
* @param
* b: �������
* @return
* ������Ľ�
*/
VectorColumn eqs(const Matrix& A, const VectorColumn& b);

/*
* @brief
* ���޽�����������ķ���������ƽ�
* @param
* A: ϵ������
* @param
* b: �������
* @return
* ������Ľ�
*/
VectorColumnI eqs(const MatrixI& A, const VectorColumnI& b);

#endif // !MATLIB_H
