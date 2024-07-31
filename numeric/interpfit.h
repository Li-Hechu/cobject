#pragma once

#ifndef ITERPFIT
#define INTERPFIT

#pragma comment(lib,"lib/cobjectLib.lib")
#include "poly.h"
#include "function.h"

/*
* @brief
* 多项式拟合数据点
* @param
* x ：所有点的x值
* @param
* y ：所有点的y值
* @param
* r ：拟合多项式阶数
* @return
* 多项式
*/
Poly polyfit(const Array& x, const Array& y, size_t r);

/*
* @brief
* 非线性最小二乘拟合
* @param
* x ：所有点的x值
* @param
* y ：所有点的y值
* @param
* f: 拟合函数
* @param
* dr: 拟合函数对各个待定系数的偏导数列表
* @param
* c: 迭代初始向量
* @param
* ok: 迭代是否成功
* @param
* lambda: 阻尼因子
* @param
* precision: 解的精度
* @param
* counter: 迭代最大次数
* @return
* 待定系数的值
*/
VectorColumn nonlinearfit(const Array& x, const Array& y, unco1d f, const initializer_list<unco1d>& dr, VectorColumn c, bool* ok, double lambda = 50, const double precision = precision14, const size_t counter = COUNTER_MAX_TIME);

/*
* @brief
* 对离散的点进行拉格朗日插值
* @param
* x: 点x值序列
* @param
* y: 点y值序列
* @return
* 经过所有点的插值多项式
*/
Poly lagrange(const Array& x, const Array& y);

/*
* @brief
* 对函数进行拉格朗日插值
* @param
* f: 一元函数指针
* @param
* range: 插值区间
* @param
* count: 插值点个数,应大于2
* @return
* 多项式
*/
Poly lagrange(func1d f, const LimitedF& range, const size_t count);

/*
* @brief
* 对函数进行切比雪夫插值
* @param
* f: 一元函数指针
* @param
* range: 插值区间
* @param
* count: 插值点个数，应大于2
* @return
* 多项式
*/
Poly chebyinterp(func1d f, const LimitedF& range, const size_t count);

/*
* @brief
* 对函数进行勒让德多项式插值
*  @param
* f: 一元函数指针
* @param
* range: 插值区间
* @param
* count: 插值点个数，应大于2
* @return
* 多项式
*/
Poly legendreinterp(func1d f, const LimitedF& range, const size_t count);


/*一元样条插值*/
class SplineInterp : public CObject {
public:
	friend ostream& operator<<(ostream& out, const SplineInterp& spline);
public:
	/*
	* @brief
	* 构造插值序列
	* @param
	* rank: 阶数
	* @param
	* x: 起始点
	* @param
	* count: 样条个数
	*/
	SplineInterp(size_t rank, double x, size_t count);
	/*析构函数*/
	~SplineInterp();
	/*
	* @brief
	* 填入样条曲线，应当按照作用区间顺序填入
	* @param
	* poly: 样条多项式
	* @param
	* end: 多项式作用区间右值
	* @return
	* 无
	*/
	void fillin(const Poly& poly, double end);
	/*
	* @brief
	* 计算插值结果
	* @param
	* x: 自变量
	* @return
	* 函数值
	*/
	double val(double x) const;
	/*
	* @brief
	* 计算插值结果
	* @param
	* x: 自变量
	* @return
	* 函数值
	*/
	Array val(const Container1D<double>& x) const;
private:
	Vector<Poly> expr;
	double* node;
	const size_t rank;		//样条阶数
	const size_t count;		//样条个数
	size_t cur;				//当前填入的多项式个数
};

/*
* @brief
* 一次样条插值
* @param
* x: 所有点x值
* @param
* y: 所有点y值
* @return
* 样条插值序列
*/
SplineInterp interp1(const Array& x, const Array& y);

/*
* @brief
* 二次样条插值
* @param
* x: 所有点x值
* @param
* y: 所有点y值
* @return
* 样条插值序列
*/
SplineInterp interp2(const Array& x, const Array& y);

/*
* @brief
* 三次样条插值
* @param
* x: 所有点x值
* @param
* y: 所有点y值
* @return
* 样条插值序列
*/
SplineInterp interp3(const Array& x, const Array& y);


/*一维三角插值*/
class DFTInterp : public CObject {
public:
	friend ostream& operator <<(ostream& out, const DFTInterp& interp);
public:
	/*默认构造函数*/
	DFTInterp();
	/*赋值构造函数*/
	DFTInterp(const size_t _N, const size_t _R, double* _A, double* _B, double _const, double _single, const LimitedF& range);
	/*析构函数*/
	~DFTInterp();
	/*
	* @brief
	* 获取值
	* @param
	* t: 自变量
	* @return
	* 函数值
	*/
	double val(const double& t) const;
	/*
	* @brief
	* 获取值
	* @param
	* t: 自变量列表
	* @return
	* 函数值
	*/
	Array val(const Container1D<double>& t) const;
private:
	//总长
	const size_t N;
	//阶数
	const size_t rank;
	//余弦求和项系数
	double* A;
	//正弦求和项系数
	double* B;
	//常数项
	double constant;
	//单独余弦项系数
	double single;
	//区间左值
	double c;
	//区间右值
	double d;
};

/*一维余弦插值*/
class DCTInterp : public CObject {
public:
	friend ostream& operator <<(ostream& out, const DCTInterp& interp);
public:
	/*默认构造函数*/
	DCTInterp();
	/*赋值构造函数*/
	DCTInterp(const size_t _N, const size_t _R, double* _A, double _const, const LimitedF& range);
	/*析构函数*/
	~DCTInterp();
	/*
	* @brief
	* 获取值
	* @param
	* t: 自变量
	* @return
	* 函数值
	*/
	double val(const double& t) const;
	/*
	* @brief
	* 获取值
	* @param
	* t: 自变量列表
	* @return
	* 函数值
	*/
	Array val(const Container1D<double>& t) const;
private:
	//总长
	const size_t N;
	//阶数
	const size_t rank;
	//余弦求和项系数
	double* A;
	//常数项
	double constant;
	//区间左值
	double c;
	//区间右值
	double d;
};


/*
* @brief
* 一维三角多项式拟合
* @param
* y: 数据点
* @param
* range: 插值区间
* @param
* rank: 多项式阶数，为0表示插值多项式经过所有点
* @return
* 插值三角多项式
*/
DFTInterp dftfit(const Container1D<double>& y, const LimitedF& range, size_t rank = 0);

/*
* @brief
* 一维三角多项式拟合
* @param
* y: 数据点
* @param
* range: 插值区间
* @param
* rank: 多项式阶数，为0表示插值多项式经过所有点
* @return
* 插值三角多项式
*/
DCTInterp dctfit(const Container1D<double>& y, const LimitedF& range, size_t rank = 0);

#endif // !ITERPFIT
