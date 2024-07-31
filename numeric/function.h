#pragma once

#ifndef FUNCTION_H
#define FUNCTION_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "../matrix/matrix.h"
#include <functional>

/*һԪ��ֵ����*/
typedef std::function<double(double)> func1d;

/*��Ԫ��ֵ����*/
typedef std::function<double(double, double)> func2d;

/*��Ԫ��ֵ����*/
typedef std::function<double(const VectorColumn&)> funcnd;

/*һԪ����ֵ����*/
typedef std::function<VectorColumn(double)> func1dn;

/*��Ԫ����ֵ����*/
typedef std::function<VectorColumn(const VectorColumn&)> funcndn;

/*������*/
typedef std::function<Matrix(const VectorColumn&)> funcmat;

/*һԪ��������ϵ����ʽ*/
typedef std::function<double(double, const VectorColumn&)> unco1d;

/*��Ԫ��������ϵ����ʽ*/
typedef std::function<double(double, double, const VectorColumn&)> unco2d;

/*��Ԫ��ֵ��������ʽ*/
typedef Point<VectorColumn, double> PointU;

/*��Ԫ����ֵ��������ʽ*/
typedef Point<VectorColumn, VectorColumn> PointV;

//����������
#define COUNTER_MAX_TIME	150

#define SET_OK(ok_ptr, state) if(ok_ptr != nullptr) *ok_ptr = state;
#define SET_OK_T(ok_ptr) SET_OK(ok_ptr,true)
#define SET_OK_F(ok_ptr) SET_OK(ok_ptr,false)

#define SUCCESSFUL		"successful"
#define NUM_DISCRIPTION_LEN		100

/*6λ����*/
constexpr double precision6 = 1e-6;

/*7λ����*/
constexpr double precision7 = 1e-7;

/*8λ����*/
constexpr double precision8 = 1e-8;

/*9λ����*/
constexpr double precision9 = 1e-9;

/*10λ����*/
constexpr double precision10 = 1e-10;

/*11λ����*/
constexpr double precision11 = 1e-11;

/*12λ����*/
constexpr double precision12 = 1e-12;

/*13λ����*/
constexpr double precision13 = 1e-13;

/*14λ����*/
constexpr double precision14 = 1e-14;

/*15λ����*/
constexpr double precision15 = 1e-15;

/*16λ����*/
constexpr double precision16 = 1e-16;

/*
* @brief
* ��ȡ�����ڵ�����
* @param
* f: ����ָ��
* @param
* x0: ��ʼ��
* @param
* h: ��������
* @param
* ok: �Ƿ��ҵ�����
* @param
* counter: �����������
* @return
* �����ڵ�����
*/
LimitedF rootInterval(func1d f, double x0, double h, bool* ok = nullptr, const size_t counter = COUNTER_MAX_TIME);

/*
* @brief
* ���ַ���һԪ�����ĸ�
* @param
* f: ����ָ��
* @param
* range: ��ʼ��������
* @param
* ok: bool�ͱ���ָ�룬�����Ƿ�����ɹ�
* @param
* precision: ��ľ���
* @param
* counter: ����������
* @return
* ���Ľ��ƽ����������ʧ�ܣ��򷵻�0
*/
double bisection(func1d f, const LimitedF& range, bool* ok = nullptr, const double precision = precision14, const size_t counter = COUNTER_MAX_TIME);

/*
* @brief
* �����������һԪ�����ĸ�
* @param
* f: ����ָ��
* @param
* x0: ��ʼ������
* @param
* ok: bool�ͱ���ָ�룬�����Ƿ�����ɹ�
* @param
* precision: ��ľ���
* @param
* counter: ����������
* @return
* ���Ľ��ƽ����������ʧ�ܣ��򷵻�0
*/
double fpi(func1d f, double x0, bool* ok = nullptr, const double precision = precision14, const size_t counter = COUNTER_MAX_TIME);

/*
* @brief
* ���߷�����һԪ�����ĸ�
* @param
* f: ����ָ��
* @param
* init: ������ʼ��
* @param
* ok: bool�ͱ���ָ�룬�����Ƿ�����ɹ�
* @param
* precision: ��ľ���
* @param
* counter: ����������
* @return
* ���Ľ��ƽ����������ʧ�ܣ��򷵻�0
*/
double secant(func1d f, const initializer_list<double>& init, bool* ok = nullptr, const double precision = precision14, const size_t counter = COUNTER_MAX_TIME);

/*
* @brief
* ����β�ֵ����һԪ�����ĸ�
* @param
* f: ����ָ��
* @param
* init: ������ʼ��
* @param
* ok: bool�ͱ���ָ�룬�����Ƿ�����ɹ�
* @param
* precision: ��ľ���
* @param
* counter: ����������
* @return
* ���Ľ��ƽ����������ʧ�ܣ��򷵻�0
*/
double iqi(func1d f, const initializer_list<double>& init, bool* ok = nullptr, const double precision = precision14, const size_t counter = COUNTER_MAX_TIME);

/*
* @brief
* ţ��-����ѷ��
* @param
* f: һԪ����ָ��
* @param
* df: ������һ�׵���
* @param
* x0: ��ʼ������
* @param
* ok: bool�ͱ���ָ�룬�����Ƿ�����ɹ�
* @param
* m: ��������
* @param
* precision: ��ľ���
* @param
* counter: ����������
* @return
* ���Ľ��ƽ����������ʧ�ܣ��򷵻�0
*/
double newraph(func1d f, func1d df, double x0, bool* ok = nullptr, const int m = 1, const double precision = precision14, const size_t counter = COUNTER_MAX_TIME);

/*
* @brief
* ����ֵ΢�ֵ�ţ��-����ѷ����
* @param
* f: һԪ����ָ��
* @param
* x0: ��ʼ������
* @param
* ok: bool�ͱ���ָ�룬�����Ƿ�����ɹ�
* @param
* m: ��������
* @param
* precision: ��ľ���
* @param
* counter: ����������
* @return
* ���Ľ��ƽ����������ʧ�ܣ��򷵻�0
*/
double newraph(func1d f, double x0, bool* ok = nullptr, const int m = 1, const double precision = precision14, const size_t counter = COUNTER_MAX_TIME);

/*
* @brief
* ţ��-����ѷ���������Է�����
* @param
* f: ��Ԫ����ֵ����ָ��
* @param
* df: ������һ�׵������ſɱȾ���
* @param
* x0: ��ʼ������
* @param
* ok: bool�ͱ���ָ�룬�����Ƿ�����ɹ�
* @param
* precision: ��ľ���
* @param
* counter: ����������
* @return
* ���Ľ��ƽ����������ʧ�ܣ��򷵻�0
*/
VectorColumn newraph(funcndn f, funcmat df, VectorColumn x0, bool* ok, const double precision = precision14, const size_t counter = COUNTER_MAX_TIME);

/*
* @brief
* BroydenII�����������Է�����
* @param
* f: ��Ԫ����ֵ����ָ��
* @param
* x0: ��ʼ������
* @param
* ok: bool�ͱ���ָ�룬�����Ƿ�����ɹ�
* @param
* precision: ��ľ���
* @param
* counter: ����������
* @return
* ���Ľ��ƽ����������ʧ�ܣ��򷵻�0
*/
VectorColumn broyden(funcndn f, VectorColumn x0, bool* ok, const double precision = precision14, const size_t counter = COUNTER_MAX_TIME);

/*
* @brief
* һԪ����һ�׵���
* @param
* f: һԪ����
* @param
* x: ΢�ֵ�
* @return
* ������ָ���㴦��һ�׵���
*/
double diff1(func1d f, double x);

/*
* @brief
* ��Ԫ����һ�׵������ݶȣ�
* @param
* f: һԪ����
* @param
* point: ΢�ֵ�
* @return
* ������ָ���㴦��һ�׵���
*/
PointF diff1(func2d f, const PointF& point);

/*
* @brief
* ��Ԫ����һ�׵������ݶȣ�
* @param
* f: һԪ����
* @param
* point: ΢�ֵ�
* @return
* ������ָ���㴦��һ�׵���
*/
VectorColumn diff1(funcnd f, const VectorColumn& point);

/*
* @brief
* һԪ�������׵���
* @param
* f: һԪ����
* @param
* x: ΢�ֵ�
* @return
* ������ָ���㴦�Ķ��׵���
*/
double diff2(func1d f, double x);

#endif // FUNCTION_H
