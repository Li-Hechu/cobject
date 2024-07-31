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

/*ʵϵ������ʽ*/
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
	* �����ն���ʽ��Ĭ��Ϊ0
	*/
	Poly();
	/*
	* @brief
	* ��ϵ����������ʽ������ϵ���Ӹ߽׵��ͽ�����
	*/
	Poly(initializer_list<double> cof);
	/*
	* @brief
	* ��ϵ����������ʽ������ϵ���Ӹ߽׵��ͽ�����
	*/
	Poly(const Array& cof);
	/*
	* @brief
	* �������캯�������
	*/
	Poly(const Poly& poly);
	/*
	* @brief
	* ��������
	*/
	~Poly();
	/*
	* @brief
	* ͨ����������ֵ��ȡ���ֵ
	* @param
	* x : ����ֵ
	* @return
	* ���ֵ
	*/
	double val(double x) const;
	/*
	* @brief
	* �����б���ȡ�б���ÿһ��Ԫ���ڶ���ʽ�е�ֵ
	* @param
	* x : �Ա����б�
	* @return
	* ���Array�����
	*/
	Array val(const Array& x) const;
	/*
	* @brief
	* ���������ȡ���
	* @param
	* x : ����ֵ
	* @return
	* ���ֵ
	*/
	Complex val(const Complex& x) const;
	/*
	* @brief
	* �����б���ȡ�б���ÿһ��Ԫ���ڶ���ʽ�е�ֵ
	* @param
	* x : �Ա����б�
	* @return
	* ���Array�����
	*/
	Vector<Complex> val(const Vector<Complex>& x) const;
	/*
	* @biref
	* ��ȡ����ʽϵ��
	* @param
	* ��
	* @return
	* ϵ��
	*/
	Array cof() const;
	/*
	* @brief
	* ��ȡ����ʽ�Ľ�
	* @param
	* ��
	* @return
	* ����
	*/
	size_t order() const;
	/*
	* @brief
	* �������
	*/
	virtual void operator=(const Poly& poly);
private:
	//����ʽ�Ľ�
	size_t rank;
	//���ȣ�Ϊ������1
	size_t length;
	//����ʽ��ϵ��
	double* coeff;
};

/*
* @brief
* ����ʽ�������
*/
typedef struct PolyDiv{
	//��
	Poly quotient;
	//����
	Poly remainder;
}PolyDiv;

/*
* @brief
* �������õ¶���ʽ
* @param
* n: ����
* @return
* n�����õ¶���ʽ
*/
Poly Legendre(size_t n);

/*
* @brief
* ����ʽ���
* ����Խ�ߣ���ֵ����ҲӦ����֮�½�����������ھ��������Ҳ�������Ҫ��Ľ�
* @param
* poly : ��Ҫ����Ķ���ʽ
* @param
* precision: ����
* @return
* ����ʽ�ĸ�
*/
Vector<Complex> polyroots(const Poly& poly, const double precision = 1e-14);

/*
* @brief
* ����ʽ�����
* @param
* poly �� ��Ҫ����ֵĶ���ʽ
* @param
* cof : ÿ�λ������ӵĳ�����
* @return
* ������ֺ�Ķ���ʽ
*/
Poly polyinteg(const Poly& poly, const Array& cof);

/*
* @brief
* ����ʽ�����
* @param
* poly �� ��Ҫ����ֵĶ���ʽ
* @param
* r: ���ִ���
* @return
* ������ֺ�Ķ���ʽ
*/
Poly polyinteg(const Poly& poly, const size_t r);

/*
* @brief
* ����ʽ��΢��
* @param
* poly �� ��Ҫ��΢�ֵĶ���ʽ
* @param
* r �� ΢�ֽ���
* @return
* ����΢�ֺ�Ķ���ʽ
*/
Poly polyderiv(const Poly& poly, size_t r);

/*
* @brief
* ����ϵ��ȫ����1�Ķ���ʽ
* @param
* r : ����ʽ�Ľ���
* @return
* ����ʽ
*/
Poly polyones(size_t r);

/*
* @brief
* �������ϵ������ʽ
* @param
* r: ����ʽ����
* @return
* ����ʽ
*/
Poly polyrandn(size_t r);


/*
* @brief
* ��ʵ������������ʽ
* @param
* roots : ����ʽ�ĸ�
* @return
* ����ʽ
*/
Poly polyfromroots(const Vector<double>& roots);

/*
* @brief
* �Ӹ�������������ʽ
* @param
* roots : ����ʽ�ĸ�
* @return
* ����ʽ
*/
Poly polyfromroots(const Vector<Complex>& roots);


#endif // !POLY_H