#pragma once

#ifndef ARRAY_H
#define ARRAY_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "arrayabstype.h"
#include "../complex.h"

class Array;
class ArrayI;

/*ʵ������*/
class Array : public ArrayXdType<double> {
	friend class ArrayI;
public:
	/*
	* @brief
	* �޲ι���
	* @param
	* ��
	* @return
	* ��
	*/
	Array();
	/*
	* @brief
	* ��һά���鹹��
	* @param
	* һά����
	* @return
	* ��
	*/
	Array(const initializer_list<double>& list);
	/*
	* @brief
	* ָ���������еĳ���
	* @param
	* n : ���г���
	* @return
	* ��
	*/
	Array(size_t length);
	/*
	* @brief
	* �ӱ��ʽ��������
	* @param
	* expr : ���б��ʽ
	* @return
	* ��
	*/
	Array(const ArrayOperation<double>& expr);
	/*
	* @brief
	* �������캯��
	* @param
	* arr : Array����
	* ctrl : Array������
	* @return
	* ��
	*/
	Array(const Array& arr);
	/*
	* @brief
	* ת��Ϊ��������
	* @param
	* ��
	* @return
	* ��������
	*/
	ArrayI toComplex() const;
	/*
	* @brief
	* ��������
	* @param
	* path: �ļ�·��
	* @return
	* bool�ͱ�����1��ʾ�ɹ���0��ʾʧ��
	*/
	bool save(const char* path);
	/*
	* @brief
	* ���ļ���ȡ����
	* @param
	* path: �ļ�·��
	* @param
	* ok: �Ƿ��ȡ�ɹ�
	* @return
	* ����
	*/
	static Array read(const char* path, bool* ok = nullptr);
	/*
	* @brief
	* �������������
	* @param
	* size: ���г���
	* @return
	* ����
	*/
	static Array random(const size_t size);
	/*
	* @brief
	* �������
	* @param
	* length: ����
	* @param
	* value: ���ֵ
	* @return
	* ���������
	*/
	static Array fill(const size_t length, double value);
};

/*��������*/
class ArrayI : public ArrayXdType<Complex> {
	friend class Array;
public:
	/*
	* @brief
	* �޲ι���
	* @param
	* ��
	* @return
	* ��
	*/
	ArrayI();
	/*
	* @brief
	* ��һά���鹹��
	* @param
	* һά����
	* @return
	* ��
	*/
	ArrayI(const initializer_list<Complex>& list);
	/*
	* @brief
	* ָ���������еĳ���
	* @param
	* n : ���г���
	* @return
	* ��
	*/
	ArrayI(size_t length);
	/*
	* @brief
	* �ӱ��ʽ��������
	* @param
	* expr : ���б��ʽ
	* @return
	* ��
	*/
	ArrayI(const ArrayOperation<Complex>& expr);
	/*
	* @brief
	* �������캯��
	* @param
	* arr : Array����
	* ctrl : Array������
	* @return
	* ��
	*/
	ArrayI(const ArrayI& arr);
	/*
	* @brief
	* ȡʵ��
	* @param
	* ��
	* @return
	* ʵ������
	*/
	Array real() const;
	/*
	* @brief
	* ȡ�鲿
	* @param
	* ��
	* @return
	* ��������
	*/
	ArrayI imag() const;
	/*
	* @brief
	* ��������
	* @param
	* path: �ļ�·��
	* @return
	* bool�ͱ�����1��ʾ�ɹ���0��ʾʧ��
	*/
	bool save(const char* path);
	/*
	* @brief
	* ���ļ���ȡ����
	* @param
	* path: �ļ�·��
	* @param
	* ok: �Ƿ��ȡ�ɹ�
	* @return
	* ����
	*/
	static ArrayI read(const char* path, bool* ok);
	/*
	* @brief
	* �������������
	* @param
	* size: ���г���
	* @return
	* ����
	*/
	static ArrayI random(const size_t size);
	/*
	* @brief
	* �������
	* @param
	* length: ����
	* @param
	* value: ���ֵ
	* @return
	* ���������
	*/
	static ArrayI fill(const size_t length, const Complex& value);
};



/*������������*/
template<typename _arr, typename _ty>
class ArraySinOperation : public ArrayOperation<_ty>, public ArrayFunctionOperation<_arr> {
public:
	ArraySinOperation(const _arr& arr) : ArrayOperation<_ty>(), ArrayFunctionOperation<_arr>(arr) {
		this->length = arr.len();
	}
	inline virtual _ty at(const size_t index) const {
		return sin(this->op.at(index));
	}
};

/*������������*/
template<typename _arr, typename _ty>
class ArrayCosOperation : public ArrayOperation<_ty>, public ArrayFunctionOperation<_arr> {
public:
	ArrayCosOperation(const _arr& arr) : ArrayOperation<_ty>(), ArrayFunctionOperation<_arr>(arr) {
		this->length = arr.len();
	}
	inline virtual _ty at(const size_t index) const {
		return cos(this->op.at(index));
	}
};

/*������������*/
template<typename _arr, typename _ty>
class ArrayTanOperation : public ArrayOperation<_ty>, public ArrayFunctionOperation<_arr> {
public:
	ArrayTanOperation(const _arr& arr) : ArrayOperation<_ty>(), ArrayFunctionOperation<_arr>(arr) {
		this->length = arr.len();
	}
	inline virtual _ty at(const size_t index) const {
		return tan(this->op.at(index));
	}
};

/*��������ֵ*/
template<typename _arr, typename _ty>
class ArraySecOperation : public ArrayOperation<_ty>, public ArrayFunctionOperation<_arr> {
public:
	ArraySecOperation(const _arr& arr) : ArrayOperation<_ty>(), ArrayFunctionOperation<_arr>(arr) {
		this->length = arr.len();
	}
	inline virtual _ty at(const size_t index) const {
		return 1 / sin(this->op.at(index));
	}
};

/*�����������*/
template<typename _arr, typename _ty>
class ArrayCesOperation : public ArrayOperation<_ty>, public ArrayFunctionOperation<_arr> {
public:
	ArrayCesOperation(const _arr& arr) : ArrayOperation<_ty>(), ArrayFunctionOperation<_arr>(arr) {
		this->length = arr.len();
	}
	inline virtual _ty at(const size_t index) const {
		return 1 / cos(this->op.at(index));
	}
};

/*������������*/
template<typename _arr, typename _ty>
class ArrayCotOperation : public ArrayOperation<_ty>, public ArrayFunctionOperation<_arr> {
public:
	ArrayCotOperation(const _arr& arr) : ArrayOperation<_ty>(), ArrayFunctionOperation<_arr>(arr) {
		this->length = arr.len();
	}
	inline virtual _ty at(const size_t index) const {
		return 1 / tan(this->op.at(index));
	}
};

/*����ָ������*/
template<typename _arr, typename _ty>
class ArrayExpOperation : public ArrayOperation<_ty>, public ArrayFunctionOperation<_arr> {
public:
	ArrayExpOperation(const _arr& arr) : ArrayOperation<_ty>(), ArrayFunctionOperation<_arr>(arr) {
		this->length = arr.len();
	}
	inline virtual _ty at(const size_t index) const {
		return exp(this->op.at(index));
	}
};


/*������Ȼ��������*/
template<typename _arr, typename _ty>
class ArrayLnOperation : public ArrayOperation<_ty>, public ArrayFunctionOperation<_arr> {
public:
	ArrayLnOperation(const _arr& arr) : ArrayOperation<_ty>(), ArrayFunctionOperation<_arr>(arr) {
		this->length = arr.len();
	}
	inline virtual _ty at(const size_t index) const {
		return log(this->op.at(index));
	}
};

static double ln_10 = log(10);

/*������10Ϊ�׵Ķ�������*/
template<typename _arr, typename _ty>
class ArrayLogOperation : public ArrayOperation<_ty>, public ArrayFunctionOperation<_arr> {
public:
	ArrayLogOperation(const _arr& arr) : ArrayOperation<_ty>(), ArrayFunctionOperation<_arr>(arr) {
		this->length = arr.len();
	}
	inline virtual _ty at(const size_t index) const {
		return log(this->op.at(index)) / ln_10;
	}
};

/*���о���ֵ����*/
template<typename _arr>
class ArrayAbsOperation : public ArrayOperation<double>, public ArrayFunctionOperation<_arr> {
public:
	ArrayAbsOperation(const _arr& arr) : ArrayOperation<double>(), ArrayFunctionOperation<_arr>(arr) {
		this->length = arr.len();
	}
	inline virtual double at(const size_t index) const {
		return abs(this->op.at(index));
	}
};


/*
* @brief
* ������ÿ������������ֵ
* @param
* arr : ����
* @return
* �������ұ��ʽ
*/
ArraySinOperation<Array, double> sin(const Array& arr);

/*
* @brief
* ��������ÿ������������ֵ
* @param
* arr : ����
* @return
* �������ұ��ʽ
*/
ArraySinOperation<ArrayOperation<double>, double> sin(const ArrayOperation<double>& arr);

/*
* @brief
* ��������ÿ������������ֵ
* @param
* arr : ����
* @return
* �������ұ��ʽ
*/
ArraySinOperation<ArrayI, Complex> sin(const ArrayI& arr);

/*
* @brief
* ��������ÿ������������ֵ
* @param
* arr : ����
* @return
* �������ұ��ʽ
*/
ArraySinOperation<ArrayOperation<Complex>, Complex> sin(const ArrayOperation<Complex>& arr);

/*
* @brief
* ��������ÿ����������ֵ
* @param
* arr : ����
* @return
* �������ұ��ʽ
*/
ArrayCosOperation<Array, double> cos(const Array& arr);

/*
* @brief
* ��������ÿ����������ֵ
* @param
* arr : ����
* @return
* �������ұ��ʽ
*/
ArrayCosOperation<ArrayOperation<double>, double> cos(const ArrayOperation<double>& arr);

/*
* @brief
* ��������ÿ����������ֵ
* @param
* arr : ����
* @return
* �������ұ��ʽ
*/
ArrayCosOperation<ArrayI, Complex> cos(const ArrayI& arr);

/*
* @brief
* ��������ÿ����������ֵ
* @param
* arr : ����
* @return
* �������ұ��ʽ
*/
ArrayCosOperation<ArrayOperation<Complex>, Complex> cos(const ArrayOperation<Complex>& arr);

/*
* @brief
* ��������ÿ����������ֵ
* @param
* arr : ����
* @return
* �������б��ʽ
*/
ArrayTanOperation<Array, double> tan(const Array& arr);

/*
* @brief
* ��������ÿ����������ֵ
* @param
* arr : ����
* @return
* �������б��ʽ
*/
ArrayTanOperation<ArrayOperation<double>, double> tan(const ArrayOperation<double>& arr);

/*
* @brief
* ��������ÿ����������ֵ
* @param
* arr : ����
* @return
* �������б��ʽ
*/
ArrayTanOperation<ArrayI, Complex> tan(const ArrayI& arr);

/*
* @brief
* ��������ÿ����������ֵ
* @param
* arr : ����
* @return
* �������б��ʽ
*/
ArrayTanOperation<ArrayOperation<Complex>, Complex> tan(const ArrayOperation<Complex>& arr);

/*
* @brief
* ��������ÿ����������ֵ
* @param
* arr : ����
* @return
* ����������ʽ
*/
ArraySecOperation<Array, double> sec(const Array& arr);

/*
* @brief
* ��������ÿ����������ֵ
* @param
* arr : ����
* @return
* ����������ʽ
*/
ArraySecOperation<ArrayOperation<double>, double> sec(const ArrayOperation<double>& arr);

/*
* @brief
* ��������ÿ����������ֵ
* @param
* arr : ����
* @return
* ����������ʽ
*/
ArraySecOperation<ArrayI, Complex> sec(const ArrayI& arr);

/*
* @brief
* ��������ÿ����������ֵ
* @param
* arr : ����
* @return
* ����������ʽ
*/
ArraySecOperation<ArrayOperation<Complex>, Complex> sec(const ArrayOperation<Complex>& arr);

/*
* @brief
* ��������ÿ���������ֵ
* @param
* arr : ����
* @return
* ���������ʽ
*/
ArrayCesOperation<Array, double> ces(const Array& arr);

/*
* @brief
* ��������ÿ���������ֵ
* @param
* arr : ����
* @return
* ���������ʽ
*/
ArrayCesOperation<ArrayOperation<double>, double> ces(const ArrayOperation<double>& arr);

/*
* @brief
* ��������ÿ���������ֵ
* @param
* arr : ����
* @return
* ���������ʽ
*/
ArrayCesOperation<ArrayI, Complex> ces(const ArrayI& arr);

/*
* @brief
* ��������ÿ���������ֵ
* @param
* arr : ����
* @return
* ���������ʽ
*/
ArrayCesOperation<ArrayOperation<Complex>, Complex> ces(const ArrayOperation<Complex>& arr);

/*
* @brief
* ��������ÿ����������ֵ
* @param
* arr : ����
* @return
* �������б��ʽ
*/
ArrayCotOperation<Array, double> cot(const Array& arr);

/*
* @brief
* ��������ÿ����������ֵ
* @param
* arr : ����
* @return
* �������б��ʽ
*/
ArrayCotOperation<ArrayOperation<double>, double> cot(const ArrayOperation<double>& arr);

/*
* @brief
* ��������ÿ����������ֵ
* @param
* arr : ����
* @return
* �������б��ʽ
*/
ArrayCotOperation<ArrayI, Complex> cot(const ArrayI& arr);

/*
* @brief
* ��������ÿ����������ֵ
* @param
* arr : ����
* @return
* �������б��ʽ
*/
ArrayCotOperation<ArrayOperation<Complex>, Complex> cot(const ArrayOperation<Complex>& arr);

/*
* @brief
* ����eΪ�׵ģ�����Ϊָ����ֵ
* @param
* arr : ����
* @return
* ����ָ�����ʽ
*/
ArrayExpOperation<Array, double> exp(const Array& arr);

/*
* @brief
* ����eΪ�׵ģ�����Ϊָ����ֵ
* @param
* arr : ����
* @return
* ����ָ�����ʽ
*/
ArrayExpOperation<ArrayOperation<double>, double> exp(const ArrayOperation<double>& arr);

/*
* @brief
* ����eΪ�׵ģ�����Ϊָ����ֵ
* @param
* arr : ����
* @return
* ����ָ�����ʽ
*/
ArrayExpOperation<ArrayI, Complex> exp(const ArrayI& arr);

/*
* @brief
* ����eΪ�׵ģ�����Ϊָ����ֵ
* @param
* arr : ����
* @return
* ����ָ�����ʽ
*/
ArrayExpOperation<ArrayOperation<Complex>, Complex> exp(const ArrayOperation<Complex>& arr);

/*
* @brief
* ��������ÿ��������Ȼ����ֵ
* @param
* arr : ����
* @return
* ������Ȼ�������ʽ
*/
ArrayLnOperation<Array, double> log(const Array& arr);

/*
* @brief
* ��������ÿ��������Ȼ����ֵ
* @param
* arr : ����
* @return
* ������Ȼ�������ʽ
*/
ArrayLnOperation<ArrayOperation<double>, double> log(const ArrayOperation<double>& arr);

/*
* @brief
* ��������ÿ��������Ȼ����ֵ
* @param
* arr : ����
* @return
* ������Ȼ�������ʽ
*/
ArrayLnOperation<ArrayI, Complex> log(const ArrayI& arr);

/*
* @brief
* ��������ÿ��������Ȼ����ֵ
* @param
* arr : ����
* @return
* ������Ȼ�������ʽ
*/
ArrayLnOperation<ArrayOperation<Complex>, Complex> log(const ArrayOperation<Complex>& arr);

/*
* @brief
* ��������ÿ������10Ϊ�׵Ķ���ֵ
* @param
* arr : ����
* @return
* ������10Ϊ�׵Ķ���ֵ
*/
ArrayLogOperation<Array, double> log10(const Array& arr);

/*
* @brief
* ��������ÿ������10Ϊ�׵Ķ���ֵ
* @param
* arr : ����
* @return
* ������10Ϊ�׵Ķ���ֵ
*/
ArrayLogOperation<ArrayOperation<double>, double> log10(const ArrayOperation<double>& arr);

/*
* @brief
* ��������ÿ������10Ϊ�׵Ķ���ֵ
* @param
* arr : ����
* @return
* ������10Ϊ�׵Ķ���ֵ
*/
ArrayLogOperation<ArrayI, Complex> log10(const ArrayI& arr);

/*
* @brief
* ��������ÿ������10Ϊ�׵Ķ���ֵ
* @param
* arr : ����
* @return
* ������10Ϊ�׵Ķ���ֵ
*/
ArrayLogOperation<ArrayOperation<Complex>, Complex> log10(const ArrayOperation<Complex>& arr);

/*
* @brief
* ��������ÿ����ȡ����ֵ
* @param
* arr ������
* @return
* ���о���ֵ���ʽ
*/
ArrayAbsOperation<Array> abs(const Array& arr);

/*
* @brief
* ��������ÿ����ȡ����ֵ
* @param
* arr ������
* @return
* ���о���ֵ���ʽ
*/
ArrayAbsOperation<ArrayOperation<double>> abs(const ArrayOperation<double>& arr);

/*
* @brief
* ��������ÿ����ȡ����ֵ
* @param
* arr ������
* @return
* ���о���ֵ���ʽ
*/
ArrayAbsOperation<ArrayOperation<Complex>> abs(const ArrayOperation<Complex>& arr);

/*
* @brief
* ���������������
* @param
* start: ��ʼֵ
* @param
* end: ����ֵ��������
* @param
* step: ���
* @return
* �ȼ������
*/
Array arange(double start, double end, double step = 1);

/*
* @brief
* �������Կռ�
* @param
* start: ��ʼֵ
* @param
* end: ��ֵֹ
* @param
* count: ��ĸ���
* @param
* endpoint: �Ƿ��������ֵ��1��ʾ������0��ʾ������
* @return
* ���Կռ�����
*/
Array linspace(double start, double end, const size_t count, bool endpoint = true);

/*
* @brief
* �������οռ�
* @param
* start: ��ʼֵ
* @param
* end: ��ֵֹ
* @param
* count: ��ĸ���
* @param
* endpoint: �Ƿ��������ֵ��1��ʾ������0��ʾ������
* @return
* ���οռ�����
*/
Array geomspace(double start, double end, const size_t count, bool endpoint = true);

/*
* @brief
* ���������ռ�
* @param
* start: ��ʼָ��
* @param
* end: ��ָֹ��
* @param
* count: ��ĸ���
* @param
* endpoint: �Ƿ��������ֵ��1��ʾ������0��ʾ������
* @param
* base: ����
* @return
* �����ռ�����
*/
Array logspace(double start, double end, const size_t count, bool endpoint = true, double base = 10);


#endif // !ARRAY_H
