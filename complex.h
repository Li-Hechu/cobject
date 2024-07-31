#pragma once
#pragma warning(disable:4455)

#ifndef COMPLEX_H
#define COMPLEX_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "cobject.h"

/*����*/
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
	/*Ĭ�Ϲ��캯��*/
	Complex();
	/*����ʵ����������*/
	Complex(double x);
	/*����ʵ�����鲿��������*/
	Complex(double x, double y);
	/*�������캯��*/
	Complex(const Complex& complex);
	/*
	* @brief
	* ��ȡʵ��
	* @param
	* ��
	* @return
	* ʵ��
	*/
	double real() const;
	/*
	* @brief
	* ��ȡ�鲿
	* @param
	* ��
	* @return
	* �鲿
	*/
	double imag() const;
	/*
	* @brief
	* �ж��Ƿ�Ϊʵ��
	* @param
	* ��
	* @return
	* 1��ʾʵ����0��ʾ����
	*/
	bool isReal() const;
	/*
	* @brief
	* �ж��Ƿ�Ϊ������
	* @param
	* ��
	* @return
	* 1��ʾ��������0��ʾ����
	*/
	bool isImag() const;
	/*
	* @brief
	* ��ȡ�����Ĺ����
	* @param
	* ��
	* @return
	* �����
	*/
	Complex conj() const;
	/*
	* @brief
	* �����ֵ
	*/
	void operator =(const Complex& var);
	/*
	* @brief
	* ��������
	*/
	Complex operator- ();
	/*
	* @brief
	* ��������������С��1e-15�Ĳ�����Ϊ0
	* @param
	* comp : ����
	* @return
	* ���������������
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
* ������ģ��
* @param
* z : ����
* @return
* ģ��
*/
double abs(const Complex& z);

/*
* @brief
* ������������
* @param
* z : ����
* @return
* �Ƕȣ��Ի��ȼ��㣩
*/
double arg(const Complex& z);

/*
* @brief
* ���Ը���Ϊָ���Ľ��
* @param
* z : ����
* @return
* ����ָ��������
*/
Complex exp(const Complex& z);

/*
* @brief
* ��������Ȼ����������ֻȡ������
* @param
* z : ����
* @return
* ������Ȼ����������
*/
Complex log(const Complex& z);

/*
* @brief
* ����������
* @param
* z : ����
* @return
* ��������������
*/
Complex sin(const Complex& z);

/*
* @brief
* ����������
* @param
* z : ����
* @return
* ��������������
*/
Complex cos(const Complex& z);

/*
* @brief
* ��������
* @param
* z: ����
* @return
* ��������������
*/
Complex tan(const Complex& z);

/*
* @brief
* ������˫������
* @param
* z : ����
* @return
* ����˫������������
*/
Complex sinh(const Complex& z);

/*
* @brief
* ������˫������
* @param
* z : ����
* @return
* ����˫������������
*/
Complex cosh(const Complex& z);

/*
* @brief
* �����Ĺ����
* @param
* z : ����
* @return
* ��������
*/
Complex conj(const Complex& z);

/*
* @brief
* �������ݴΣ�ֻȡ������
* @param
* z : ����
* index : ָ��
* @return
* ����������
*/
Complex pow(const Complex& z, double index);

/*
* @brief
* �������ݴΣ�ֻȡ������
* @param
* base : ����
* z : ָ��
* @return
* ����������
*/
Complex pow(double base, const Complex& z);

/*
* @brief
* �������ݴΣ�ֻȡ������
* @param
* z : ����
* z1 : ��ָ��
* @return
* ����������
*/
Complex pow(const Complex& z, const Complex& z1);

/*
* @brief
* ��ȫ������ר����Ը��������������鲿�Ƿ�Ϊ0��һ�ɰ��ո�������ֻȡ������
* @param
* base : �ݺ����ĵ�
* index : �ݺ�����ָ��
* @return
* ����������
*/
Complex pow_s(double base, double index);



#endif // ! COMPLEX_H