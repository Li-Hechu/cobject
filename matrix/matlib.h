#pragma once

#ifndef MATLIB_H
#define MATLIB_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "matrix.h"

/*
* @brief
* 向量第一范数
* @param
* vec : 向量
* @return
* 第一范数
*/
double normal1(const VectorXdType<double>& vec);

/*
* @brief
* 向量第一范数
* @param
* vec : 向量
* @return
* 第一范数
*/
double normal1(const VectorXdType<Complex>& vec);

/*
* @brief
* 向量第二范数
* @param
* vec : 向量
* @return
* 第二范数
*/
double normal2(const VectorXdType<double>& vec);

/*
* @brief
* 向量第二范数
* @param
* vec : 向量
* @return
* 第二范数
*/
double normal2(const VectorXdType<Complex>& vec);

/*
* @brief
* 向量最大范数（无穷范数）
* @param
* vec : 向量
* @return
* 向量的最大范数
*/
double normalN(const VectorXdType<double>& vec);

/*
* @brief
* 向量最大范数（无穷范数）
* @param
* vec : 向量
* @return
* 向量的最大范数
*/
double normalN(const VectorXdType<Complex>& vec);

/*
* @brief
* 求解矩阵第一范数
* @param
* mat : 矩阵
* @return
* 矩阵第一范数
*/
double normal1(const MatrixXdType<double>& mat);

/*
* @brief
* 求解矩阵第一范数
* @param
* mat : 矩阵
* @return
* 矩阵第一范数
*/
double normal1(const MatrixXdType<Complex>& mat);

/*
* @brief
* 求解矩阵最大范数（无穷范数）
* @param
* mat : 矩阵
* @return
* 矩阵最大范数
*/
double normalN(const MatrixXdType<double>& mat);

/*
* @brief
* 求解矩阵最大范数（无穷范数）
* @param
* mat : 矩阵
* @return
* 矩阵最大范数
*/
double normalN(const MatrixXdType<Complex>& mat);

/*
* @brief
* 方阵的条件数
* @param
* mat : 矩阵（方阵）
* @return
* 条件数
*/
double cond(const Matrix& mat);

/*
* @brief
* 方阵的条件数
* @param
* mat : 矩阵（方阵）
* @return
* 条件数
*/
double cond(const MatrixI& mat);

/*
* @brief
* 判断实数向量是否为0向量
* @param
* vec : 向量对象
* @return
* 1表示0向量，0表示存在不为0的元素
*/
bool vectorIsZero(const VectorXdType<double>& vec);

/*
* @brief
* 判断复数向量是否为0向量
* @param
* vec : 向量对象
* @return
* 1表示0向量，0表示存在不为0的元素
*/
bool vectorIsZero(const VectorXdType<Complex>& vec);

/*
* @brief
* 检查向量元素绝对值是否均小于某一个数字
* @param
* vec: 向量
* @param
* val: 数字
* @return
* 1表示均小于该数字，0表示不满足此条件
*/
bool vectorMinus(const VectorXdType<double>& vec, const double val);

/*
* @brief
* 检查向量元素绝对值是否均小于某一个数字
* @param
* vec: 向量
* @param
* val: 数字
* @return
* 1表示均小于该数字，0表示不满足此条件
*/
bool vectorMinus(const VectorXdType<Complex>& vec, const double val);

/*
* @brief
* 检查向量中是否存在inf
* @param
* vec: 向量
* @return
* 1表示存在inf，0表示不存在
*/
bool vectorHasInf(const VectorXdType<double>& vec);

/*
* @brief
* 检查向量中是否存在inf
* @param
* vec: 向量
* @return
* 1表示存在inf，0表示不存在
*/
bool vectorHasInf(const VectorXdType<Complex>& vec);

/*
* @brief
* 单位化一个实数向量
* @param
* vec : 向量
* @return
* 无
*/
void unitization(VectorXdType<double>& vec);

/*
* @brief
* 单位化一个复数向量
* @param
* vec : 向量
* @return
* 无
*/
void unitization(VectorXdType<Complex>& vec);

/*
* @brief
* 矩阵拼接
* @param
* matlist : 矩阵列表
* @param
* direct : 拼接方向，1表示横向，0表示纵向
* @return
* 拼接后的矩阵
*/
Matrix matrixConcat(const Container1D<MatrixXdType<double>>& matlist, bool direct = true);

/*
* @brief
* 矩阵拼接
* @param
* matlist : 矩阵列表
* @param
* direct : 拼接方向，1表示横向，0表示纵向
* @return
* 拼接后的矩阵
*/
MatrixI matrixConcat(const Container1D<MatrixXdType<Complex>>& matlist, bool direct = true);

/*
* @brief
* 高斯消元求解实数方程组
* @param
* mat : 系数矩阵
* @param
* vec : 结果向量
* @return
* 方程组的解
*/
VectorColumn gauss(const Matrix& mat, const VectorColumn& vec);

/*
* @brief
* 高斯消元求解复数方程组
* @param
* mat : 系数矩阵
* @param
* vec : 结果向量
* @return
* 方程组的解
*/
VectorColumnI gauss(const MatrixI& mat, const VectorColumnI& vec);

/*
* @brief
* 最小二乘法求解无解（不一致）方程组
* @param
* A: 列满秩矩阵
* @param
* b: 结果向量
* @param
* _qr: 是否使用QR分解获取高精度结果，适用于矩阵A条件数较大的情况。1表示使用，0表示不使用
* @return
* 最小二乘解
*/
VectorColumn ls(const Matrix& A, const VectorColumn& b, bool _qr = false);

/*
* @brief
* 最小二乘法求解无解（不一致）方程组
* @param
* A: 列满秩矩阵
* @param
* b: 结果向量
* @param
* _qr: 是否使用QR分解获取高精度结果，适用于矩阵A条件数较大的情况。1表示使用，0表示不使用
* @return
* 最小二乘解
*/
VectorColumnI ls(const MatrixI& A, const VectorColumnI& b, bool _qr = false);

/*
* @brief
* 对无解或者无数组解的方程组求近似解
* @param
* A: 系数矩阵
* @param
* b: 结果向量
* @return
* 方程组的解
*/
VectorColumn eqs(const Matrix& A, const VectorColumn& b);

/*
* @brief
* 对无解或者无数组解的方程组求近似解
* @param
* A: 系数矩阵
* @param
* b: 结果向量
* @return
* 方程组的解
*/
VectorColumnI eqs(const MatrixI& A, const VectorColumnI& b);

#endif // !MATLIB_H
