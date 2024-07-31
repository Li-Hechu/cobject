#pragma once

#ifndef FUNCTION_H
#define FUNCTION_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "../matrix/matrix.h"
#include <functional>

/*一元单值函数*/
typedef std::function<double(double)> func1d;

/*二元单值函数*/
typedef std::function<double(double, double)> func2d;

/*多元单值函数*/
typedef std::function<double(const VectorColumn&)> funcnd;

/*一元向量值函数*/
typedef std::function<VectorColumn(double)> func1dn;

/*多元向量值函数*/
typedef std::function<VectorColumn(const VectorColumn&)> funcndn;

/*矩阵函数*/
typedef std::function<Matrix(const VectorColumn&)> funcmat;

/*一元函数待定系数格式*/
typedef std::function<double(double, const VectorColumn&)> unco1d;

/*二元函数待定系数格式*/
typedef std::function<double(double, double, const VectorColumn&)> unco2d;

/*多元单值函数点形式*/
typedef Point<VectorColumn, double> PointU;

/*多元向量值函数点形式*/
typedef Point<VectorColumn, VectorColumn> PointV;

//最大迭代次数
#define COUNTER_MAX_TIME	150

#define SET_OK(ok_ptr, state) if(ok_ptr != nullptr) *ok_ptr = state;
#define SET_OK_T(ok_ptr) SET_OK(ok_ptr,true)
#define SET_OK_F(ok_ptr) SET_OK(ok_ptr,false)

#define SUCCESSFUL		"successful"
#define NUM_DISCRIPTION_LEN		100

/*6位精度*/
constexpr double precision6 = 1e-6;

/*7位精度*/
constexpr double precision7 = 1e-7;

/*8位精度*/
constexpr double precision8 = 1e-8;

/*9位精度*/
constexpr double precision9 = 1e-9;

/*10位精度*/
constexpr double precision10 = 1e-10;

/*11位精度*/
constexpr double precision11 = 1e-11;

/*12位精度*/
constexpr double precision12 = 1e-12;

/*13位精度*/
constexpr double precision13 = 1e-13;

/*14位精度*/
constexpr double precision14 = 1e-14;

/*15位精度*/
constexpr double precision15 = 1e-15;

/*16位精度*/
constexpr double precision16 = 1e-16;

/*
* @brief
* 获取根所在的区间
* @param
* f: 函数指针
* @param
* x0: 初始点
* @param
* h: 搜索步长
* @param
* ok: 是否找到区间
* @param
* counter: 最大搜索次数
* @return
* 根所在的区间
*/
LimitedF rootInterval(func1d f, double x0, double h, bool* ok = nullptr, const size_t counter = COUNTER_MAX_TIME);

/*
* @brief
* 二分法求一元函数的根
* @param
* f: 函数指针
* @param
* range: 初始迭代区间
* @param
* ok: bool型变量指针，表征是否迭代成功
* @param
* precision: 解的精度
* @param
* counter: 最大迭代次数
* @return
* 根的近似结果，若迭代失败，则返回0
*/
double bisection(func1d f, const LimitedF& range, bool* ok = nullptr, const double precision = precision14, const size_t counter = COUNTER_MAX_TIME);

/*
* @brief
* 不动点迭代求一元函数的根
* @param
* f: 函数指针
* @param
* x0: 初始迭代点
* @param
* ok: bool型变量指针，表征是否迭代成功
* @param
* precision: 解的精度
* @param
* counter: 最大迭代次数
* @return
* 根的近似结果，若迭代失败，则返回0
*/
double fpi(func1d f, double x0, bool* ok = nullptr, const double precision = precision14, const size_t counter = COUNTER_MAX_TIME);

/*
* @brief
* 割线方法求一元函数的根
* @param
* f: 函数指针
* @param
* init: 两个初始点
* @param
* ok: bool型变量指针，表征是否迭代成功
* @param
* precision: 解的精度
* @param
* counter: 最大迭代次数
* @return
* 根的近似结果，若迭代失败，则返回0
*/
double secant(func1d f, const initializer_list<double>& init, bool* ok = nullptr, const double precision = precision14, const size_t counter = COUNTER_MAX_TIME);

/*
* @brief
* 逆二次插值法求一元函数的根
* @param
* f: 函数指针
* @param
* init: 三个初始点
* @param
* ok: bool型变量指针，表征是否迭代成功
* @param
* precision: 解的精度
* @param
* counter: 最大迭代次数
* @return
* 根的近似结果，若迭代失败，则返回0
*/
double iqi(func1d f, const initializer_list<double>& init, bool* ok = nullptr, const double precision = precision14, const size_t counter = COUNTER_MAX_TIME);

/*
* @brief
* 牛顿-拉夫逊法
* @param
* f: 一元函数指针
* @param
* df: 函数的一阶导数
* @param
* x0: 初始迭代点
* @param
* ok: bool型变量指针，表征是否迭代成功
* @param
* m: 根的重数
* @param
* precision: 解的精度
* @param
* counter: 最大迭代次数
* @return
* 根的近似结果，若迭代失败，则返回0
*/
double newraph(func1d f, func1d df, double x0, bool* ok = nullptr, const int m = 1, const double precision = precision14, const size_t counter = COUNTER_MAX_TIME);

/*
* @brief
* 带数值微分的牛顿-拉夫逊方法
* @param
* f: 一元函数指针
* @param
* x0: 初始迭代点
* @param
* ok: bool型变量指针，表征是否迭代成功
* @param
* m: 根的重数
* @param
* precision: 解的精度
* @param
* counter: 最大迭代次数
* @return
* 根的近似结果，若迭代失败，则返回0
*/
double newraph(func1d f, double x0, bool* ok = nullptr, const int m = 1, const double precision = precision14, const size_t counter = COUNTER_MAX_TIME);

/*
* @brief
* 牛顿-拉夫逊法求解非线性方程组
* @param
* f: 多元向量值函数指针
* @param
* df: 函数的一阶导数（雅可比矩阵）
* @param
* x0: 初始迭代点
* @param
* ok: bool型变量指针，表征是否迭代成功
* @param
* precision: 解的精度
* @param
* counter: 最大迭代次数
* @return
* 根的近似结果，若迭代失败，则返回0
*/
VectorColumn newraph(funcndn f, funcmat df, VectorColumn x0, bool* ok, const double precision = precision14, const size_t counter = COUNTER_MAX_TIME);

/*
* @brief
* BroydenII方法求解非线性方程组
* @param
* f: 多元向量值函数指针
* @param
* x0: 初始迭代点
* @param
* ok: bool型变量指针，表征是否迭代成功
* @param
* precision: 解的精度
* @param
* counter: 最大迭代次数
* @return
* 根的近似结果，若迭代失败，则返回0
*/
VectorColumn broyden(funcndn f, VectorColumn x0, bool* ok, const double precision = precision14, const size_t counter = COUNTER_MAX_TIME);

/*
* @brief
* 一元函数一阶导数
* @param
* f: 一元函数
* @param
* x: 微分点
* @return
* 函数在指定点处的一阶导数
*/
double diff1(func1d f, double x);

/*
* @brief
* 二元函数一阶导数（梯度）
* @param
* f: 一元函数
* @param
* point: 微分点
* @return
* 函数在指定点处的一阶导数
*/
PointF diff1(func2d f, const PointF& point);

/*
* @brief
* 多元函数一阶导数（梯度）
* @param
* f: 一元函数
* @param
* point: 微分点
* @return
* 函数在指定点处的一阶导数
*/
VectorColumn diff1(funcnd f, const VectorColumn& point);

/*
* @brief
* 一元函数二阶导数
* @param
* f: 一元函数
* @param
* x: 微分点
* @return
* 函数在指定点处的二阶导数
*/
double diff2(func1d f, double x);

#endif // FUNCTION_H
