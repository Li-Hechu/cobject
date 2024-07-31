#pragma once

#ifndef ITERPFIT
#define INTERPFIT

#pragma comment(lib,"lib/cobjectLib.lib")
#include "poly.h"
#include "function.h"

/*
* @brief
* ����ʽ������ݵ�
* @param
* x �����е��xֵ
* @param
* y �����е��yֵ
* @param
* r ����϶���ʽ����
* @return
* ����ʽ
*/
Poly polyfit(const Array& x, const Array& y, size_t r);

/*
* @brief
* ��������С�������
* @param
* x �����е��xֵ
* @param
* y �����е��yֵ
* @param
* f: ��Ϻ���
* @param
* dr: ��Ϻ����Ը�������ϵ����ƫ�����б�
* @param
* c: ������ʼ����
* @param
* ok: �����Ƿ�ɹ�
* @param
* lambda: ��������
* @param
* precision: ��ľ���
* @param
* counter: ����������
* @return
* ����ϵ����ֵ
*/
VectorColumn nonlinearfit(const Array& x, const Array& y, unco1d f, const initializer_list<unco1d>& dr, VectorColumn c, bool* ok, double lambda = 50, const double precision = precision14, const size_t counter = COUNTER_MAX_TIME);

/*
* @brief
* ����ɢ�ĵ�����������ղ�ֵ
* @param
* x: ��xֵ����
* @param
* y: ��yֵ����
* @return
* �������е�Ĳ�ֵ����ʽ
*/
Poly lagrange(const Array& x, const Array& y);

/*
* @brief
* �Ժ��������������ղ�ֵ
* @param
* f: һԪ����ָ��
* @param
* range: ��ֵ����
* @param
* count: ��ֵ�����,Ӧ����2
* @return
* ����ʽ
*/
Poly lagrange(func1d f, const LimitedF& range, const size_t count);

/*
* @brief
* �Ժ��������б�ѩ���ֵ
* @param
* f: һԪ����ָ��
* @param
* range: ��ֵ����
* @param
* count: ��ֵ�������Ӧ����2
* @return
* ����ʽ
*/
Poly chebyinterp(func1d f, const LimitedF& range, const size_t count);

/*
* @brief
* �Ժ����������õ¶���ʽ��ֵ
*  @param
* f: һԪ����ָ��
* @param
* range: ��ֵ����
* @param
* count: ��ֵ�������Ӧ����2
* @return
* ����ʽ
*/
Poly legendreinterp(func1d f, const LimitedF& range, const size_t count);


/*һԪ������ֵ*/
class SplineInterp : public CObject {
public:
	friend ostream& operator<<(ostream& out, const SplineInterp& spline);
public:
	/*
	* @brief
	* �����ֵ����
	* @param
	* rank: ����
	* @param
	* x: ��ʼ��
	* @param
	* count: ��������
	*/
	SplineInterp(size_t rank, double x, size_t count);
	/*��������*/
	~SplineInterp();
	/*
	* @brief
	* �����������ߣ�Ӧ��������������˳������
	* @param
	* poly: ��������ʽ
	* @param
	* end: ����ʽ����������ֵ
	* @return
	* ��
	*/
	void fillin(const Poly& poly, double end);
	/*
	* @brief
	* �����ֵ���
	* @param
	* x: �Ա���
	* @return
	* ����ֵ
	*/
	double val(double x) const;
	/*
	* @brief
	* �����ֵ���
	* @param
	* x: �Ա���
	* @return
	* ����ֵ
	*/
	Array val(const Container1D<double>& x) const;
private:
	Vector<Poly> expr;
	double* node;
	const size_t rank;		//��������
	const size_t count;		//��������
	size_t cur;				//��ǰ����Ķ���ʽ����
};

/*
* @brief
* һ��������ֵ
* @param
* x: ���е�xֵ
* @param
* y: ���е�yֵ
* @return
* ������ֵ����
*/
SplineInterp interp1(const Array& x, const Array& y);

/*
* @brief
* ����������ֵ
* @param
* x: ���е�xֵ
* @param
* y: ���е�yֵ
* @return
* ������ֵ����
*/
SplineInterp interp2(const Array& x, const Array& y);

/*
* @brief
* ����������ֵ
* @param
* x: ���е�xֵ
* @param
* y: ���е�yֵ
* @return
* ������ֵ����
*/
SplineInterp interp3(const Array& x, const Array& y);


/*һά���ǲ�ֵ*/
class DFTInterp : public CObject {
public:
	friend ostream& operator <<(ostream& out, const DFTInterp& interp);
public:
	/*Ĭ�Ϲ��캯��*/
	DFTInterp();
	/*��ֵ���캯��*/
	DFTInterp(const size_t _N, const size_t _R, double* _A, double* _B, double _const, double _single, const LimitedF& range);
	/*��������*/
	~DFTInterp();
	/*
	* @brief
	* ��ȡֵ
	* @param
	* t: �Ա���
	* @return
	* ����ֵ
	*/
	double val(const double& t) const;
	/*
	* @brief
	* ��ȡֵ
	* @param
	* t: �Ա����б�
	* @return
	* ����ֵ
	*/
	Array val(const Container1D<double>& t) const;
private:
	//�ܳ�
	const size_t N;
	//����
	const size_t rank;
	//���������ϵ��
	double* A;
	//���������ϵ��
	double* B;
	//������
	double constant;
	//����������ϵ��
	double single;
	//������ֵ
	double c;
	//������ֵ
	double d;
};

/*һά���Ҳ�ֵ*/
class DCTInterp : public CObject {
public:
	friend ostream& operator <<(ostream& out, const DCTInterp& interp);
public:
	/*Ĭ�Ϲ��캯��*/
	DCTInterp();
	/*��ֵ���캯��*/
	DCTInterp(const size_t _N, const size_t _R, double* _A, double _const, const LimitedF& range);
	/*��������*/
	~DCTInterp();
	/*
	* @brief
	* ��ȡֵ
	* @param
	* t: �Ա���
	* @return
	* ����ֵ
	*/
	double val(const double& t) const;
	/*
	* @brief
	* ��ȡֵ
	* @param
	* t: �Ա����б�
	* @return
	* ����ֵ
	*/
	Array val(const Container1D<double>& t) const;
private:
	//�ܳ�
	const size_t N;
	//����
	const size_t rank;
	//���������ϵ��
	double* A;
	//������
	double constant;
	//������ֵ
	double c;
	//������ֵ
	double d;
};


/*
* @brief
* һά���Ƕ���ʽ���
* @param
* y: ���ݵ�
* @param
* range: ��ֵ����
* @param
* rank: ����ʽ������Ϊ0��ʾ��ֵ����ʽ�������е�
* @return
* ��ֵ���Ƕ���ʽ
*/
DFTInterp dftfit(const Container1D<double>& y, const LimitedF& range, size_t rank = 0);

/*
* @brief
* һά���Ƕ���ʽ���
* @param
* y: ���ݵ�
* @param
* range: ��ֵ����
* @param
* rank: ����ʽ������Ϊ0��ʾ��ֵ����ʽ�������е�
* @return
* ��ֵ���Ƕ���ʽ
*/
DCTInterp dctfit(const Container1D<double>& y, const LimitedF& range, size_t rank = 0);

#endif // !ITERPFIT
