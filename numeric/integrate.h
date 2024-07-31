#pragma once

#ifndef INTEGRATE_H
#define INTEGRATE_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "function.h"
#include "../vector.h"
#include <iomanip>

static const char IntegrateErrorHeader[ERROR_HEADER_MAXLEN] = "IntegrateError";
/*���ִ���*/
class IntegrateError : public Error<IntegrateErrorHeader> {
public:
	inline IntegrateError(const char* info) : Error(info) {

	}
};

/*���ֽ��*/
typedef struct InteRe {
	size_t time;				//�������ô���
	bool ok;					//�Ƿ����ɹ�
	const char* discription;	//��������� 
	double inte_value;			//����ֵ

	inline friend ostream& operator<<(ostream& out, const InteRe& re) {
		out << "���ô�����" << re.time << endl;
		out << "״    ̬��" << re.ok << endl;
		out << "��    ����" << re.discription << endl;
		out << "���ֽ����" << fixed << setprecision(10) << re.inte_value << endl;
		return out;
	}
}InteRe;


/*
* @brief
* ��ɢ���λ���
* @param
* y: �����y��ֵ
* @param
* x: �Ա���x��ֵ
* @return
* ���ֽ��
*/
double trapezoid(const Container1D<double>& y, const Container1D<double>& x);

/*
* @brief
* ��ɢ���λ���
* @param
* y: �����y��ֵ
* @param
* dx: ����
* @return
* ���ֽ��
*/
double trapezoid(const Container1D<double>& y, const double dx);

/*
* @brief
* ��ɢ����ɭ����
* @param
* y: �����y��ֵ
* @param
* x: �Ա���x��ֵ
* @return
* ���ֽ��
*/
double simpson(const Container1D<double>& y, const Container1D<double>& x);

/*
* @brief
* ��ɢ����ɭ����
* @param
* y: �����y��ֵ
* @param
* dx: ����
* @return
* ���ֽ��
*/
double simpson(const Container1D<double>& y, const double dx);

/*
* @brief
* ����Ӧ����ɭ����
* @param
* f: ��������
* @param
* low: �����½�
* @param
* up: �����Ͻ�
* @param
* err: ����������
* @return
* ����������ָ�������ϵĻ��ֽ��
*/
InteRe quad(func1d f, const double low, const double up, double err = precision10);

/*
* @brief
* ��覵������Ӧ����ɭ����
* @attention
* ǿ�ҽ���覵�Ϊ0����߻��־��ȣ���覵㲻Ϊ0�������������ֵ������ɻ���ʧ��
* ��覵㲻Ϊ0�����齵�ͻ��־���
* @param
* f: ��������
* @param
* range: ��������
* @param
* point: 覵��б�
* @param
* err: ���־���
* @return
* ����������ָ�������ϵĻ��ֽ��
*/
InteRe quad(func1d f, const double low, const double up, const Vector<double>& point, const double err = precision10);

/*
* @brief
* ����Ӧ���ػ���
* @param
* f: ��������
* @param
* low1: �������½�
* @param
* up1: �������Ͻ�
* @param
* low2: �ڲ�����½�
* @param
* up2: �ڲ�����Ͻ�
* @param
* err: ���־���
* @return
* ���ֽ��
*/
InteRe dblquad(func2d f, const double low1, const double up1, const double low2, const double up2, const double err = precision10);

/*
* @brief
* ����Ӧ���ػ���
* @param
* f: ��������
* @param
* low1: �������½�
* @param
* up1: �������Ͻ�
* @param
* low2: �ڲ�����½�
* @param
* up2: �ڲ�����Ͻ�
* @param
* err: ���־���
* @return
* ���ֽ��
*/
InteRe dblquad(func2d f, const double low1, const double up1, const func1d low2, const func1d up2, const double err = precision10);

/*
* @brief
* ���������
* @param
* f: ��������
* @param
* range: ��������
* @param
* err: ����������
* @return
* ����������ָ�������ϵĻ��ֽ��
*/
double romberg(func1d f, const LimitedF& range, double err = precision10);

/*
* @brief
* ��˹-���õ»���
* @param
* f: ��������
* @param
* range: ��������
* @param
* N: ���ֽ���
* @return
* ����������ָ�������ϵĻ��ֽ��
*/
double gaussquad(func1d f, const LimitedF& range, const size_t N = 4);

#endif // !INTEGRATE_H
