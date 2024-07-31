#pragma once

#ifndef DECOMPOSE_H
#define DECOMPOSE_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "matrix.h"

//矩阵PLU分解结构体
template<typename MatType>
struct matPLU {
	//置换矩阵
	MatType P;
	//下三角矩阵
	MatType L;
	//上三角矩阵
	MatType U;
};

//实数矩阵PLU分解
typedef matPLU<Matrix> PLU;
//复数矩阵PLU分解
typedef matPLU<MatrixI> PLUI;


//矩阵QR分解结构体
template<typename MatType>
struct matQR {
	//正交矩阵
	MatType Q;
	//上三角矩阵
	MatType R;
};

//实数矩阵QR分解
typedef matQR<Matrix> QR;
//复数矩阵QR分解
typedef matQR<MatrixI> QRI;

//矩阵特征值分解结构体
template<typename MatType>
struct matEIG {
	//特征值矩阵
	MatType E;
	//特征向量矩阵
	MatType F;
};

//实数特征分解
typedef matEIG<Matrix> EIG;
//复数特征分解
typedef matEIG<MatrixI> EIGI;


//矩阵SVD分解结构体
template<typename MatType>
struct matSVD {
	//左奇异矩阵
	MatType U;
	//奇异值矩阵
	MatType S;
	//右奇异矩阵
	MatType V;
	///任意矩阵A的奇异值分解满足 A = U*S*V.H()
};

//实数矩阵SVD分解
typedef matSVD<Matrix> SVD;
//复数SVD分解
typedef matSVD<MatrixI> SVDI;


//上海森伯格相似变换
template<typename MatType>
struct matHessen {
	//上海森伯格形式
	MatType H;
	//正交矩阵
	MatType Q;
	/// 任意矩阵A的海森伯格形式H满足 H = Q*A*Q.H
};

//实数矩阵海森伯格变换结构体
typedef matHessen<Matrix> Hessen;
//复数矩阵海森伯格变换结构体
typedef matHessen<MatrixI> HessenI;


/*
* @brief
* 实数矩阵PLU分解
* @param
* mat : 矩阵
* @return
* 分解结构体
*/
PLU plu(const Matrix& mat);

/*
* @brief
* 复数矩阵PLU分解
* @param
* mat : 矩阵
* @return
* 分解结构体
*/
PLUI plu(const MatrixI& mat);

/*
* @brief
* 实数矩阵求逆
* @param
* mat : 实数方阵
* @return
* 逆矩阵
*/
Matrix inv(const Matrix& mat);

/*
* @brief
* 复数矩阵求逆
* @param
* mat : 复数方阵
* @return
* 矩阵的逆
*/
MatrixI inv(const MatrixI& mat);

/*
* @brief
* 实数向量豪斯霍尔德反射
* @param
* x : 向量1
* @param
* w : 向量2
* @param
* check : 是否检查几何长度一致，默认不检查
* @return
* 豪斯霍尔德反射矩阵
*/
Matrix householder(const VectorColumn& x, const VectorColumn& w, bool check = false);

/*
* @brief
* 复数向量豪斯霍尔德反射
* @param
* x : 向量1
* @param
* w : 向量2
* @param
* check : 是否检查几何长度一致，默认不检查
* @return
* 豪斯霍尔德反射矩阵
*/
MatrixI householder(const VectorColumnI& x, const VectorColumnI& w, bool check = false);

/*
* @brief
* 实数矩阵QR分解
* @param
* mat : 矩阵
* @return
* QR分解结构体
*/
QR qr(const Matrix& mat);

/*
* @brief
* 复数矩阵QR分解
* @param
* mat : 矩阵
* @return
* QR分解结构体
*/
QRI qr(const MatrixI& mat);

/*
* @brief
* 实数方阵的上海森伯格相似变换
* @param
* mat : 方阵
* @return
* Hessen分解结构体
*/
Hessen hessenburge(const Matrix& mat);

/*
* @brief
* 复数方阵的上海森伯格相似变换
* @param
* mat : 方阵
* @return
* Hessen分解结构体
*/
HessenI hessenburge(const MatrixI& mat);

/*
* @brief
* 幂法
* @param
* mat : 实数方阵
* @param
* flag : 迭代是否成功
* @return
* 实数绝对值最大特征值
*/
double powerit(const Matrix& mat, bool* flag = nullptr);

/*
* @brief
* 幂法
* @param
* mat : 复数方阵
* @param
* flag : 迭代是否成功
* @return
* 复数绝对值最大特征值
*/
Complex powerit(const MatrixI& mat, bool* flag = nullptr);

/*
* @brief
* 瑞利商迭代
* @param
* mat : 实数矩阵
* @param
* flag : 迭代是否成功
* @return
* 实数绝对值最大特征值
*/

double rayleigh(const Matrix& mat, bool* flag = nullptr);

/*
* @brief
* 瑞利商迭代
* @param
* mat : 实数矩阵
* @param
* flag : 迭代是否成功
* @return
* 复数绝对值最大特征值
*/

Complex rayleigh(const MatrixI& mat, bool* flag = nullptr);

/*
* @brief
* 带平移的反幂法
* @param
* mat : 实数矩阵
* @param
* s0 : 特征值的近似
* @param
* init_var : 初始迭代向量填充值，不可为0
* @return
* 距s0最近的特征值及其特征向量
*/
Match<double,VectorColumn> invpowerit(const Matrix& mat, double s0 = 0, double init_var = 1);

/*
* @brief
* 带平移的反幂法
* @param
* mat : 复数矩阵
* @param
* s0 : 特征值的近似
* @param
* init_var : 初始迭代向量填充值，不可为0
* @return
* 距s0最近的特征值及其特征向量
*/
Match<Complex, VectorColumnI> invpowerit(const MatrixI& mat, const Complex& s0 = 0, const Complex& init_var = 1 + 1j);

/*
* @brief
* 求解一般矩阵的特征值和特征向量
* @param
* mat : 方阵
* @return
* 特征分解结构体
*/
EIGI eigen(const MatrixI& mat);

/*
* @brief
* 实对称矩阵特征分解
* @param
* mat : 实对称矩阵
* @param
* 特征分解结构体
*/
EIG eigen_s(const Matrix& mat);

/*
* @brief
* 复对称（厄米特）矩阵特征分解
* @param
* mat : 复对称矩阵
* @return
* 特征分解结构体
*/
EIGI eigen_s(const MatrixI& mat);

/*
* @brief
* 实数矩阵SVD分解
* @param
* mat : 矩阵
* @return
* SVD分解结构体
*/
SVD svd(const Matrix& mat);

/*
* @brief
* 复数矩阵SVD分解
* @param
* mat : 矩阵
* @return
* SVD分解结构体
*/
SVDI svd(const MatrixI& mat);

/*
* @brief
* Moore-Penrose广义逆矩阵
* @param
* mat: 实数矩阵
* @return
* 广义逆矩阵
*/
Matrix pinv(const Matrix& mat);

/*
* @brief
* Moore-Penrose广义逆矩阵
* @param
* mat: 复数矩阵
* @return
* 广义逆矩阵
*/
MatrixI pinv(const MatrixI& mat);

#endif // !DECOMPOSE_H
