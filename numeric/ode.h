#pragma once

#ifndef ODE_H
#define ODE_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "../matrix/matrix.h"
#include "../array/array.h"
#include "../list.h"

/*����΢�ַ��̸�ʽ*/
template<typename argTy, typename diffTy, typename reTy>
struct ODETypeDef {
	typedef reTy(*odety_ptr)(argTy t, diffTy y);
};

/*����΢�ַ��̽�ĸ�ʽ*/
template<typename _T, typename _Y>
struct ODEResultTypeDef {
	_T t;
	_Y y;
};

/*һԪ΢�ַ���*/
typedef ODETypeDef<double, double, double>::odety_ptr odety;

/*һԪ΢�ַ�����*/
typedef ODETypeDef<double, const Array&, Array>::odety_ptr odetys;

/*һԪ΢�ַ��̵Ľ�*/
typedef ODEResultTypeDef<Array, Array> odere;

/*һԪ΢�ַ�����Ľ�*/
typedef ODEResultTypeDef<Array, List<Array>> oderes;


ostream& operator<<(ostream& out, const odere& result);

ostream& operator<<(ostream& out, const oderes& result);

/*
* @brief
* ��ʽŷ������
* @param
* f: б�ʺ���
* @param
* y0: ��ʼֵ
* @param
* range: �������
* @param
* h: ����
* @return
* ΢�ַ�����ָ�������ϵĽ�
*/
odere ode1(odety f, double y0, const initializer_list<double>& range, double h);

/*
* @brief
* ��ʽŷ������
* @param
* f: б�ʺ���
* @param
* y0: ��ʼֵ
* @param
* range: �������
* @param
* h: ����
* @return
* ΢�ַ�����ָ�������ϵĽ�
*/
oderes ode1(odetys f, Array y0, const initializer_list<double>& range, double h);

/*
* @brief
* ��ʽ���η���
* @param
* f: б�ʺ���
* @param
* y0: ��ʼֵ
* @param
* range: �������
* @param
* h: ����
* @return
* ΢�ַ�����ָ�������ϵĽ�
*/
odere ode2(odety f, double y0, const initializer_list<double>& range, double h);

/*
* @brief
* ��ʽ���η���
* @param
* f: б�ʺ���
* @param
* y0: ��ʼֵ
* @param
* range: �������
* @param
* h: ����
* @return
* ΢�ַ�����ָ�������ϵĽ�
*/
oderes ode2(odetys f, Array y0, const initializer_list<double>& range, double h);

/*
* @brief
* ���������������
* @param
* f: б�ʺ���
* @param
* y0: ��ʼֵ
* @param
* range: �������
* @param
* h: ����
* @return
* ΢�ַ�����ָ�������ϵĽ�
*/
odere ode3(odety f, double y0, const initializer_list<double>& range, double h);

/*
* @brief
* ���������������
* @param
* f: б�ʺ���
* @param
* y0: ��ʼֵ
* @param
* range: �������
* @param
* h: ����
* @return
* ΢�ַ�����ָ�������ϵĽ�
*/
oderes ode3(odetys f, Array y0, const initializer_list<double>& range, double h);

/*
* @brief
* �Ľ������������
* @param
* f: б�ʺ���
* @param
* y0: ��ʼֵ
* @param
* range: �������
* @param
* h: ����
* @return
* ΢�ַ�����ָ�������ϵĽ�
*/
odere ode4(odety f, double y0, const initializer_list<double>& range, double h);

/*
* @brief
* �Ľ������������
* @param
* f: б�ʺ���
* @param
* y0: ��ʼֵ
* @param
* range: �������
* @param
* h: ����
* @return
* ΢�ַ�����ָ�������ϵĽ�
*/
oderes ode4(odetys f, Array y0, const initializer_list<double>& range, double h);

/*
* @brief
* Bogacki-Shampine 2/3��Ƕ���
* @param
* f: б�ʺ���
* @param
* y0: ��ʼֵ
* @param
* range: �������
* @param
* h0: ��ʼ����
* @param
* T: ���
* @return
* ΢�ַ�����ָ�������ϵĽ�
*/
odere ode23(odety f, double y0, const initializer_list<double>& range, double h0 = 0.05, double T = 0.001);

/*
* @brief
* Bogacki-Shampine 2/3��Ƕ���
* @param
* f: б�ʺ���
* @param
* y0: ��ʼֵ
* @param
* range: �������
* @param
* h0: ��ʼ����
* @param
* T: ���
* @return
* ΢�ַ�����ָ�������ϵĽ�
*/
oderes ode23(odetys f, Array y0, const initializer_list<double>& range, double h0 = 0.05, double T = 0.001);

/*
* @brief
* Dormand-Prince 4/5��Ƕ���
* @param
* f: б�ʺ���
* @param
* y0: ��ʼֵ
* @param
* range: �������
* @param
* h0: ��ʼ����
* @param
* T: ���
* @return
* ΢�ַ�����ָ�������ϵĽ�
*/
odere ode45(odety f, double y0, const initializer_list<double>& range, double h0 = 0.05, double T = 0.001);

/*
* @brief
* Dormand-Prince 4/5��Ƕ���
* @param
* f: б�ʺ���
* @param
* y0: ��ʼֵ
* @param
* range: �������
* @param
* h0: ��ʼ����
* @param
* T: ���
* @return
* ΢�ַ�����ָ�������ϵĽ�
*/
oderes ode45(odetys f, Array y0, const initializer_list<double>& range, double h0 = 0.05, double T = 0.001);

/*
* @brief
* Adams-Bashforth-Moulton 3��Ԥ��-У������
* @param
* f: б�ʺ���
* @param
* y0: ��ʼֵ
* @param
* range: �������
* @param
* h: ����
* @return
* ΢�ַ�����ָ�������ϵĽ�
*/
odere ode3s(odety f, double y0, const initializer_list<double>& range, double h);

/*
* @brief
* Adams-Bashforth-Moulton 3��Ԥ��-У������
* @param
* f: б�ʺ���
* @param
* y0: ��ʼֵ
* @param
* range: �������
* @param
* h: ����
* @return
* ΢�ַ�����ָ�������ϵĽ�
*/
oderes ode3s(odetys f, Array y0, const initializer_list<double>& range, double h);

/*
* @brief
* Adams-Bashforth-Moulton 4��Ԥ��-У������
* @param
* f: б�ʺ���
* @param
* y0: ��ʼֵ
* @param
* range: �������
* @param
* h: ����
* @return
* ΢�ַ�����ָ�������ϵĽ�
*/
odere ode4s(odety f, double y0, const initializer_list<double>& range, double h);

/*
* @brief
* Adams-Bashforth-Moulton 4��Ԥ��-У������
* @param
* f: б�ʺ���
* @param
* y0: ��ʼֵ
* @param
* range: �������
* @param
* h: ����
* @return
* ΢�ַ�����ָ�������ϵĽ�
*/
oderes ode4s(odetys f, Array y0, const initializer_list<double>& range, double h);

#endif // !ODE_H
