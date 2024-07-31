#pragma once
#pragma warning(disable:4455)

#ifndef COMPLEX_H
#define COMPLEX_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "cobject.h"

/*复数*/
class Complex : public CObject
{
public:
	friend Complex operator + (const Complex& complex, double x);
	friend void operator += (Complex& complex, double x);
	friend Complex operator + (double x, const Complex& complex);
	friend Complex operator + (const Complex& complex1, const Complex& complex2);
	friend void operator += (Complex& complex1, const Complex& complex2);
	friend Complex operator - (const Complex& complex, double x);
	friend void operator -= (Complex& complex, double x);
	friend Complex operator - (double x, const Complex& complex);
	friend void operator -= (Complex& complex1, const Complex& complex2);
	friend Complex operator - (const Complex& complex1, const Complex& complex2);
	friend Complex operator * (const Complex& complex, double x);
	friend void operator *= (Complex& complex, double x);
	friend Complex operator * (double x, const Complex& complex);
	friend Complex operator * (const Complex& complex1, const Complex& complex2);
	friend void operator *= (Complex& complex1, const Complex& complex2);
	friend Complex operator / (const Complex& complex, double x);
	friend void operator /= (Complex& complex, double x);
	friend Complex operator / (double x, const Complex& complex);
	friend Complex operator / (const Complex& complex1, const Complex& complex2);
	friend void operator /= (Complex& complex1, const Complex& complex2);
	friend ostream& operator << (ostream& out, const Complex& complex);
	friend bool operator <(const Complex& complex1, const Complex& complex2);
	friend bool operator >(const Complex& complex1, const Complex& complex2);
	friend bool operator ==(const Complex& complex1, const Complex& complex2);
	friend bool operator <=(const Complex& complex1, const Complex& complex2);
	friend bool operator >=(const Complex& complex1, const Complex& complex2);
	bool operator == (const Complex& other) const;
public:
	/*默认构造函数*/
	Complex();
	/*给定实部创建复数*/
	Complex(double x);
	/*给定实部和虚部创建复数*/
	Complex(double x, double y);
	/*拷贝构造函数*/
	Complex(const Complex& complex);
	/*
	* @brief
	* 获取实部
	* @param
	* 无
	* @return
	* 实部
	*/
	double real() const;
	/*
	* @brief
	* 获取虚部
	* @param
	* 无
	* @return
	* 虚部
	*/
	double imag() const;
	/*
	* @brief
	* 判断是否为实数
	* @param
	* 无
	* @return
	* 1表示实数，0表示复数
	*/
	bool isReal() const;
	/*
	* @brief
	* 判断是否为纯虚数
	* @param
	* 无
	* @return
	* 1表示纯虚数，0表示复数
	*/
	bool isImag() const;
	/*
	* @brief
	* 获取复数的共轭复数
	* @param
	* 无
	* @return
	* 共轭复数
	*/
	Complex conj() const;
	/*
	* @brief
	* 深拷贝赋值
	*/
	void operator =(const Complex& var);
	/*
	* @brief
	* 负号重载
	*/
	Complex operator- ();
	/*
	* @brief
	* 规整化复数，把小于1e-15的部分视为0
	* @param
	* comp : 复数
	* @return
	* 规整后自身的引用
	*/
	static Complex& regular(Complex& comp);
protected:
	double _real;
	double _img;
};

Complex operator ""j(unsigned long long  y);
Complex operator ""j(long double y);


/*
* @brief
* 求复数的模长
* @param
* z : 复数
* @return
* 模长
*/
double abs(const Complex& z);

/*
* @brief
* 求复数的主辐角
* @param
* z : 复数
* @return
* 角度（以弧度计算）
*/
double arg(const Complex& z);

/*
* @brief
* 求以复数为指数的结果
* @param
* z : 复数
* @return
* 复数指数运算结果
*/
Complex exp(const Complex& z);

/*
* @brief
* 求复数的自然对数，这里只取主辐角
* @param
* z : 复数
* @return
* 复数自然对数运算结果
*/
Complex log(const Complex& z);

/*
* @brief
* 求复数的正弦
* @param
* z : 复数
* @return
* 复数正弦运算结果
*/
Complex sin(const Complex& z);

/*
* @brief
* 求复数的余弦
* @param
* z : 复数
* @return
* 复数余弦运算结果
*/
Complex cos(const Complex& z);

/*
* @brief
* 求复数正切
* @param
* z: 复数
* @return
* 复数正切运算结果
*/
Complex tan(const Complex& z);

/*
* @brief
* 求复数的双曲正弦
* @param
* z : 复数
* @return
* 复数双曲正切运算结果
*/
Complex sinh(const Complex& z);

/*
* @brief
* 求复数的双曲余弦
* @param
* z : 复数
* @return
* 复数双曲余弦运算结果
*/
Complex cosh(const Complex& z);

/*
* @brief
* 求复数的共轭复数
* @param
* z : 复数
* @return
* 复数共轭
*/
Complex conj(const Complex& z);

/*
* @brief
* 求复数的幂次，只取主辐角
* @param
* z : 复数
* index : 指数
* @return
* 复数幂运算
*/
Complex pow(const Complex& z, double index);

/*
* @brief
* 求复数的幂次，只取主辐角
* @param
* base : 底数
* z : 指数
* @return
* 复数幂运算
*/
Complex pow(double base, const Complex& z);

/*
* @brief
* 求复数的幂次，只取主辐角
* @param
* z : 复数
* z1 : 复指数
* @return
* 复数幂运算
*/
Complex pow(const Complex& z, const Complex& z1);

/*
* @brief
* 安全函数，专门针对负数开方，无论虚部是否为0，一律按照复数处理，只取主辐角
* @param
* base : 幂函数的底
* index : 幂函数的指数
* @return
* 复数幂运算
*/
Complex pow_s(double base, double index);



#endif // ! COMPLEX_H