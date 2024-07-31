#pragma once

#ifndef ODE_H
#define ODE_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "../matrix/matrix.h"
#include "../array/array.h"
#include "../list.h"

/*定义微分方程格式*/
template<typename argTy, typename diffTy, typename reTy>
struct ODETypeDef {
	typedef reTy(*odety_ptr)(argTy t, diffTy y);
};

/*定义微分方程解的格式*/
template<typename _T, typename _Y>
struct ODEResultTypeDef {
	_T t;
	_Y y;
};

/*一元微分方程*/
typedef ODETypeDef<double, double, double>::odety_ptr odety;

/*一元微分方程组*/
typedef ODETypeDef<double, const Array&, Array>::odety_ptr odetys;

/*一元微分方程的解*/
typedef ODEResultTypeDef<Array, Array> odere;

/*一元微分方程组的解*/
typedef ODEResultTypeDef<Array, List<Array>> oderes;


ostream& operator<<(ostream& out, const odere& result);

ostream& operator<<(ostream& out, const oderes& result);

/*
* @brief
* 显式欧拉方法
* @param
* f: 斜率函数
* @param
* y0: 初始值
* @param
* range: 求解区间
* @param
* h: 步长
* @return
* 微分方程在指定区间上的解
*/
odere ode1(odety f, double y0, const initializer_list<double>& range, double h);

/*
* @brief
* 显式欧拉方法
* @param
* f: 斜率函数
* @param
* y0: 初始值
* @param
* range: 求解区间
* @param
* h: 步长
* @return
* 微分方程在指定区间上的解
*/
oderes ode1(odetys f, Array y0, const initializer_list<double>& range, double h);

/*
* @brief
* 显式梯形方法
* @param
* f: 斜率函数
* @param
* y0: 初始值
* @param
* range: 求解区间
* @param
* h: 步长
* @return
* 微分方程在指定区间上的解
*/
odere ode2(odety f, double y0, const initializer_list<double>& range, double h);

/*
* @brief
* 显式梯形方法
* @param
* f: 斜率函数
* @param
* y0: 初始值
* @param
* range: 求解区间
* @param
* h: 步长
* @return
* 微分方程在指定区间上的解
*/
oderes ode2(odetys f, Array y0, const initializer_list<double>& range, double h);

/*
* @brief
* 三阶龙格库塔方法
* @param
* f: 斜率函数
* @param
* y0: 初始值
* @param
* range: 求解区间
* @param
* h: 步长
* @return
* 微分方程在指定区间上的解
*/
odere ode3(odety f, double y0, const initializer_list<double>& range, double h);

/*
* @brief
* 三阶龙格库塔方法
* @param
* f: 斜率函数
* @param
* y0: 初始值
* @param
* range: 求解区间
* @param
* h: 步长
* @return
* 微分方程在指定区间上的解
*/
oderes ode3(odetys f, Array y0, const initializer_list<double>& range, double h);

/*
* @brief
* 四阶龙格库塔方法
* @param
* f: 斜率函数
* @param
* y0: 初始值
* @param
* range: 求解区间
* @param
* h: 步长
* @return
* 微分方程在指定区间上的解
*/
odere ode4(odety f, double y0, const initializer_list<double>& range, double h);

/*
* @brief
* 四阶龙格库塔方法
* @param
* f: 斜率函数
* @param
* y0: 初始值
* @param
* range: 求解区间
* @param
* h: 步长
* @return
* 微分方程在指定区间上的解
*/
oderes ode4(odetys f, Array y0, const initializer_list<double>& range, double h);

/*
* @brief
* Bogacki-Shampine 2/3阶嵌入对
* @param
* f: 斜率函数
* @param
* y0: 初始值
* @param
* range: 求解区间
* @param
* h0: 初始步长
* @param
* T: 误差
* @return
* 微分方程在指定区间上的解
*/
odere ode23(odety f, double y0, const initializer_list<double>& range, double h0 = 0.05, double T = 0.001);

/*
* @brief
* Bogacki-Shampine 2/3阶嵌入对
* @param
* f: 斜率函数
* @param
* y0: 初始值
* @param
* range: 求解区间
* @param
* h0: 初始步长
* @param
* T: 误差
* @return
* 微分方程在指定区间上的解
*/
oderes ode23(odetys f, Array y0, const initializer_list<double>& range, double h0 = 0.05, double T = 0.001);

/*
* @brief
* Dormand-Prince 4/5阶嵌入对
* @param
* f: 斜率函数
* @param
* y0: 初始值
* @param
* range: 求解区间
* @param
* h0: 初始步长
* @param
* T: 误差
* @return
* 微分方程在指定区间上的解
*/
odere ode45(odety f, double y0, const initializer_list<double>& range, double h0 = 0.05, double T = 0.001);

/*
* @brief
* Dormand-Prince 4/5阶嵌入对
* @param
* f: 斜率函数
* @param
* y0: 初始值
* @param
* range: 求解区间
* @param
* h0: 初始步长
* @param
* T: 误差
* @return
* 微分方程在指定区间上的解
*/
oderes ode45(odetys f, Array y0, const initializer_list<double>& range, double h0 = 0.05, double T = 0.001);

/*
* @brief
* Adams-Bashforth-Moulton 3阶预测-校正方法
* @param
* f: 斜率函数
* @param
* y0: 初始值
* @param
* range: 求解区间
* @param
* h: 步长
* @return
* 微分方程在指定区间上的解
*/
odere ode3s(odety f, double y0, const initializer_list<double>& range, double h);

/*
* @brief
* Adams-Bashforth-Moulton 3阶预测-校正方法
* @param
* f: 斜率函数
* @param
* y0: 初始值
* @param
* range: 求解区间
* @param
* h: 步长
* @return
* 微分方程在指定区间上的解
*/
oderes ode3s(odetys f, Array y0, const initializer_list<double>& range, double h);

/*
* @brief
* Adams-Bashforth-Moulton 4阶预测-校正方法
* @param
* f: 斜率函数
* @param
* y0: 初始值
* @param
* range: 求解区间
* @param
* h: 步长
* @return
* 微分方程在指定区间上的解
*/
odere ode4s(odety f, double y0, const initializer_list<double>& range, double h);

/*
* @brief
* Adams-Bashforth-Moulton 4阶预测-校正方法
* @param
* f: 斜率函数
* @param
* y0: 初始值
* @param
* range: 求解区间
* @param
* h: 步长
* @return
* 微分方程在指定区间上的解
*/
oderes ode4s(odetys f, Array y0, const initializer_list<double>& range, double h);

#endif // !ODE_H
