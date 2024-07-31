#pragma once

#ifndef POLY_H
#define POLY_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "../array/array.h"
#include "../vector.h"
#include "../complex.h"
#include "../cobject.h"

#define POLYDIV_D
struct PolyDiv;

/*实系数多项式*/
class Poly : public CObject
{
public:
	friend Poly operator + (const Poly& poly_l, const Poly& poly_r);
	friend Poly operator + (const Poly& poly, double con);
	friend Poly operator + (double con, const Poly& poly);
	friend void operator += (Poly& poly, double con);
	friend void operator += (Poly& poly_l, const Poly& poly_r);
	friend Poly operator - (const Poly& poly_l, const Poly& poly_r);
	friend Poly operator - (const Poly& poly, double con);
	friend Poly operator - (double con, const Poly& poly);
	friend void operator -= (Poly& poly, double con);
	friend void operator -= (Poly& poly_l, const Poly& poly_r);
	friend Poly operator * (const Poly& poly_l, const Poly& poly_r);
	friend Poly operator * (const Poly& poly, double con);
	friend Poly operator * (double con, const Poly& poly);
	friend void operator *= (Poly& poly, double con);
	friend void operator *= (Poly& poly_l, const Poly& poly_r);
	friend PolyDiv operator / (const Poly& poly_l, const Poly& poly_r);
	friend Poly operator / (const Poly& poly, double con);
	friend ostream& operator << (ostream& out, const Poly& poly);
	friend Poly polyones(size_t r);
	friend Poly polyrandn(size_t r);
	friend Poly polyfromroots(const Vector<double>& roots);
	friend Poly polyfromroots(const Vector<Complex>& roots);
	friend Vector<Complex> polyroots(const Poly& poly, const double precision);
	friend Poly polyinteg(const Poly& poly, const Array& cof);
	friend Poly polyinteg(const Poly& poly, const size_t r);
	friend Poly polyderiv(const Poly& poly, size_t r);
	friend Poly polyfit(const Array& x, const Array& y, size_t r);
public:
	/*
	* @brief
	* 创建空多项式，默认为0
	*/
	Poly();
	/*
	* @brief
	* 从系数创建多项式，输入系数从高阶到低阶排列
	*/
	Poly(initializer_list<double> cof);
	/*
	* @brief
	* 从系数创建多项式，输入系数从高阶到低阶排列
	*/
	Poly(const Array& cof);
	/*
	* @brief
	* 拷贝构造函数，深拷贝
	*/
	Poly(const Poly& poly);
	/*
	* @brief
	* 析构函数
	*/
	~Poly();
	/*
	* @brief
	* 通过给定输入值获取输出值
	* @param
	* x : 输入值
	* @return
	* 输出值
	*/
	double val(double x) const;
	/*
	* @brief
	* 输入列表，获取列表中每一个元素在多项式中的值
	* @param
	* x : 自变量列表
	* @return
	* 输出Array类对象
	*/
	Array val(const Array& x) const;
	/*
	* @brief
	* 给定输入获取输出
	* @param
	* x : 输入值
	* @return
	* 输出值
	*/
	Complex val(const Complex& x) const;
	/*
	* @brief
	* 输入列表，获取列表中每一个元素在多项式中的值
	* @param
	* x : 自变量列表
	* @return
	* 输出Array类对象
	*/
	Vector<Complex> val(const Vector<Complex>& x) const;
	/*
	* @biref
	* 获取多项式系数
	* @param
	* 无
	* @return
	* 系数
	*/
	Array cof() const;
	/*
	* @brief
	* 获取多项式的阶
	* @param
	* 无
	* @return
	* 阶数
	*/
	size_t order() const;
	/*
	* @brief
	* 深拷贝构造
	*/
	virtual void operator=(const Poly& poly);
private:
	//多项式的阶
	size_t rank;
	//长度，为阶数加1
	size_t length;
	//多项式的系数
	double* coeff;
};

/*
* @brief
* 多项式除法结果
*/
typedef struct PolyDiv{
	//商
	Poly quotient;
	//余数
	Poly remainder;
}PolyDiv;

/*
* @brief
* 生成勒让德多项式
* @param
* n: 阶数
* @return
* n阶勒让德多项式
*/
Poly Legendre(size_t n);

/*
* @brief
* 多项式求根
* 阶数越高，数值精度也应当随之下降，否则会由于精度问题找不到符合要求的解
* @param
* poly : 需要求根的多项式
* @param
* precision: 精度
* @return
* 多项式的根
*/
Vector<Complex> polyroots(const Poly& poly, const double precision = 1e-14);

/*
* @brief
* 多项式求积分
* @param
* poly ： 需要求积分的多项式
* @param
* cof : 每次积分增加的常数项
* @return
* 求完积分后的多项式
*/
Poly polyinteg(const Poly& poly, const Array& cof);

/*
* @brief
* 多项式求积分
* @param
* poly ： 需要求积分的多项式
* @param
* r: 积分次数
* @return
* 求完积分后的多项式
*/
Poly polyinteg(const Poly& poly, const size_t r);

/*
* @brief
* 多项式求微分
* @param
* poly ： 需要求微分的多项式
* @param
* r ： 微分阶数
* @return
* 求完微分后的多项式
*/
Poly polyderiv(const Poly& poly, size_t r);

/*
* @brief
* 创建系数全部是1的多项式
* @param
* r : 多项式的阶数
* @return
* 多项式
*/
Poly polyones(size_t r);

/*
* @brief
* 创建随机系数多项式
* @param
* r: 多项式阶数
* @return
* 多项式
*/
Poly polyrandn(size_t r);


/*
* @brief
* 从实数根创建多项式
* @param
* roots : 多项式的根
* @return
* 多项式
*/
Poly polyfromroots(const Vector<double>& roots);

/*
* @brief
* 从复数根创建多项式
* @param
* roots : 多项式的根
* @return
* 多项式
*/
Poly polyfromroots(const Vector<Complex>& roots);


#endif // !POLY_H