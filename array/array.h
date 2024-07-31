#pragma once

#ifndef ARRAY_H
#define ARRAY_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "arrayabstype.h"
#include "../complex.h"

class Array;
class ArrayI;

/*实数序列*/
class Array : public ArrayXdType<double> {
	friend class ArrayI;
public:
	/*
	* @brief
	* 无参构造
	* @param
	* 无
	* @return
	* 无
	*/
	Array();
	/*
	* @brief
	* 从一维数组构造
	* @param
	* 一维数组
	* @return
	* 无
	*/
	Array(const initializer_list<double>& list);
	/*
	* @brief
	* 指定生成序列的长度
	* @param
	* n : 序列长度
	* @return
	* 无
	*/
	Array(size_t length);
	/*
	* @brief
	* 从表达式构造序列
	* @param
	* expr : 序列表达式
	* @return
	* 无
	*/
	Array(const ArrayOperation<double>& expr);
	/*
	* @brief
	* 拷贝构造函数
	* @param
	* arr : Array对象
	* ctrl : Array控制器
	* @return
	* 无
	*/
	Array(const Array& arr);
	/*
	* @brief
	* 转换为复数序列
	* @param
	* 无
	* @return
	* 复数序列
	*/
	ArrayI toComplex() const;
	/*
	* @brief
	* 保存序列
	* @param
	* path: 文件路径
	* @return
	* bool型变量，1表示成功，0表示失败
	*/
	bool save(const char* path);
	/*
	* @brief
	* 从文件读取数据
	* @param
	* path: 文件路径
	* @param
	* ok: 是否读取成功
	* @return
	* 序列
	*/
	static Array read(const char* path, bool* ok = nullptr);
	/*
	* @brief
	* 生成随机数序列
	* @param
	* size: 序列长度
	* @return
	* 序列
	*/
	static Array random(const size_t size);
	/*
	* @brief
	* 填充序列
	* @param
	* length: 长度
	* @param
	* value: 填充值
	* @return
	* 填充后的序列
	*/
	static Array fill(const size_t length, double value);
};

/*复数序列*/
class ArrayI : public ArrayXdType<Complex> {
	friend class Array;
public:
	/*
	* @brief
	* 无参构造
	* @param
	* 无
	* @return
	* 无
	*/
	ArrayI();
	/*
	* @brief
	* 从一维数组构造
	* @param
	* 一维数组
	* @return
	* 无
	*/
	ArrayI(const initializer_list<Complex>& list);
	/*
	* @brief
	* 指定生成序列的长度
	* @param
	* n : 序列长度
	* @return
	* 无
	*/
	ArrayI(size_t length);
	/*
	* @brief
	* 从表达式构造序列
	* @param
	* expr : 序列表达式
	* @return
	* 无
	*/
	ArrayI(const ArrayOperation<Complex>& expr);
	/*
	* @brief
	* 拷贝构造函数
	* @param
	* arr : Array对象
	* ctrl : Array控制器
	* @return
	* 无
	*/
	ArrayI(const ArrayI& arr);
	/*
	* @brief
	* 取实部
	* @param
	* 无
	* @return
	* 实数序列
	*/
	Array real() const;
	/*
	* @brief
	* 取虚部
	* @param
	* 无
	* @return
	* 复数序列
	*/
	ArrayI imag() const;
	/*
	* @brief
	* 保存序列
	* @param
	* path: 文件路径
	* @return
	* bool型变量，1表示成功，0表示失败
	*/
	bool save(const char* path);
	/*
	* @brief
	* 从文件读取数据
	* @param
	* path: 文件路径
	* @param
	* ok: 是否读取成功
	* @return
	* 序列
	*/
	static ArrayI read(const char* path, bool* ok);
	/*
	* @brief
	* 生成随机数序列
	* @param
	* size: 序列长度
	* @return
	* 序列
	*/
	static ArrayI random(const size_t size);
	/*
	* @brief
	* 填充序列
	* @param
	* length: 长度
	* @param
	* value: 填充值
	* @return
	* 填充后的序列
	*/
	static ArrayI fill(const size_t length, const Complex& value);
};



/*序列正弦运算*/
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

/*序列余弦运算*/
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

/*序列正切运算*/
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

/*序列正割值*/
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

/*序列余割运算*/
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

/*序列余切运算*/
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

/*序列指数运算*/
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


/*序列自然对数运算*/
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

/*序列以10为底的对数运算*/
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

/*序列绝对值运算*/
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
* 序列中每个数都求正弦值
* @param
* arr : 序列
* @return
* 序列正弦表达式
*/
ArraySinOperation<Array, double> sin(const Array& arr);

/*
* @brief
* 求序列中每个数都求正弦值
* @param
* arr : 序列
* @return
* 序列正弦表达式
*/
ArraySinOperation<ArrayOperation<double>, double> sin(const ArrayOperation<double>& arr);

/*
* @brief
* 求序列中每个数都求正弦值
* @param
* arr : 序列
* @return
* 序列正弦表达式
*/
ArraySinOperation<ArrayI, Complex> sin(const ArrayI& arr);

/*
* @brief
* 求序列中每个数都求正弦值
* @param
* arr : 序列
* @return
* 序列正弦表达式
*/
ArraySinOperation<ArrayOperation<Complex>, Complex> sin(const ArrayOperation<Complex>& arr);

/*
* @brief
* 求序列中每个数的余弦值
* @param
* arr : 序列
* @return
* 序列余弦表达式
*/
ArrayCosOperation<Array, double> cos(const Array& arr);

/*
* @brief
* 求序列中每个数的余弦值
* @param
* arr : 序列
* @return
* 序列余弦表达式
*/
ArrayCosOperation<ArrayOperation<double>, double> cos(const ArrayOperation<double>& arr);

/*
* @brief
* 求序列中每个数的余弦值
* @param
* arr : 序列
* @return
* 序列余弦表达式
*/
ArrayCosOperation<ArrayI, Complex> cos(const ArrayI& arr);

/*
* @brief
* 求序列中每个数的余弦值
* @param
* arr : 序列
* @return
* 序列余弦表达式
*/
ArrayCosOperation<ArrayOperation<Complex>, Complex> cos(const ArrayOperation<Complex>& arr);

/*
* @brief
* 求序列中每个数的正切值
* @param
* arr : 序列
* @return
* 序列正切表达式
*/
ArrayTanOperation<Array, double> tan(const Array& arr);

/*
* @brief
* 求序列中每个数的正切值
* @param
* arr : 序列
* @return
* 序列正切表达式
*/
ArrayTanOperation<ArrayOperation<double>, double> tan(const ArrayOperation<double>& arr);

/*
* @brief
* 求序列中每个数的正切值
* @param
* arr : 序列
* @return
* 序列正切表达式
*/
ArrayTanOperation<ArrayI, Complex> tan(const ArrayI& arr);

/*
* @brief
* 求序列中每个数的正切值
* @param
* arr : 序列
* @return
* 序列正切表达式
*/
ArrayTanOperation<ArrayOperation<Complex>, Complex> tan(const ArrayOperation<Complex>& arr);

/*
* @brief
* 求序列中每个数的正割值
* @param
* arr : 序列
* @return
* 序列正割表达式
*/
ArraySecOperation<Array, double> sec(const Array& arr);

/*
* @brief
* 求序列中每个数的正割值
* @param
* arr : 序列
* @return
* 序列正割表达式
*/
ArraySecOperation<ArrayOperation<double>, double> sec(const ArrayOperation<double>& arr);

/*
* @brief
* 求序列中每个数的正割值
* @param
* arr : 序列
* @return
* 序列正割表达式
*/
ArraySecOperation<ArrayI, Complex> sec(const ArrayI& arr);

/*
* @brief
* 求序列中每个数的正割值
* @param
* arr : 序列
* @return
* 序列正割表达式
*/
ArraySecOperation<ArrayOperation<Complex>, Complex> sec(const ArrayOperation<Complex>& arr);

/*
* @brief
* 求序列中每个数的余割值
* @param
* arr : 序列
* @return
* 序列余割表达式
*/
ArrayCesOperation<Array, double> ces(const Array& arr);

/*
* @brief
* 求序列中每个数的余割值
* @param
* arr : 序列
* @return
* 序列余割表达式
*/
ArrayCesOperation<ArrayOperation<double>, double> ces(const ArrayOperation<double>& arr);

/*
* @brief
* 求序列中每个数的余割值
* @param
* arr : 序列
* @return
* 序列余割表达式
*/
ArrayCesOperation<ArrayI, Complex> ces(const ArrayI& arr);

/*
* @brief
* 求序列中每个数的余割值
* @param
* arr : 序列
* @return
* 序列余割表达式
*/
ArrayCesOperation<ArrayOperation<Complex>, Complex> ces(const ArrayOperation<Complex>& arr);

/*
* @brief
* 求序列中每个数的余切值
* @param
* arr : 序列
* @return
* 序列余切表达式
*/
ArrayCotOperation<Array, double> cot(const Array& arr);

/*
* @brief
* 求序列中每个数的余切值
* @param
* arr : 序列
* @return
* 序列余切表达式
*/
ArrayCotOperation<ArrayOperation<double>, double> cot(const ArrayOperation<double>& arr);

/*
* @brief
* 求序列中每个数的余切值
* @param
* arr : 序列
* @return
* 序列余切表达式
*/
ArrayCotOperation<ArrayI, Complex> cot(const ArrayI& arr);

/*
* @brief
* 求序列中每个数的余切值
* @param
* arr : 序列
* @return
* 序列余切表达式
*/
ArrayCotOperation<ArrayOperation<Complex>, Complex> cot(const ArrayOperation<Complex>& arr);

/*
* @brief
* 求以e为底的，序列为指数的值
* @param
* arr : 序列
* @return
* 序列指数表达式
*/
ArrayExpOperation<Array, double> exp(const Array& arr);

/*
* @brief
* 求以e为底的，序列为指数的值
* @param
* arr : 序列
* @return
* 序列指数表达式
*/
ArrayExpOperation<ArrayOperation<double>, double> exp(const ArrayOperation<double>& arr);

/*
* @brief
* 求以e为底的，序列为指数的值
* @param
* arr : 序列
* @return
* 序列指数表达式
*/
ArrayExpOperation<ArrayI, Complex> exp(const ArrayI& arr);

/*
* @brief
* 求以e为底的，序列为指数的值
* @param
* arr : 序列
* @return
* 序列指数表达式
*/
ArrayExpOperation<ArrayOperation<Complex>, Complex> exp(const ArrayOperation<Complex>& arr);

/*
* @brief
* 求序列中每个数的自然对数值
* @param
* arr : 序列
* @return
* 序列自然对数表达式
*/
ArrayLnOperation<Array, double> log(const Array& arr);

/*
* @brief
* 求序列中每个数的自然对数值
* @param
* arr : 序列
* @return
* 序列自然对数表达式
*/
ArrayLnOperation<ArrayOperation<double>, double> log(const ArrayOperation<double>& arr);

/*
* @brief
* 求序列中每个数的自然对数值
* @param
* arr : 序列
* @return
* 序列自然对数表达式
*/
ArrayLnOperation<ArrayI, Complex> log(const ArrayI& arr);

/*
* @brief
* 求序列中每个数的自然对数值
* @param
* arr : 序列
* @return
* 序列自然对数表达式
*/
ArrayLnOperation<ArrayOperation<Complex>, Complex> log(const ArrayOperation<Complex>& arr);

/*
* @brief
* 求序列中每个数以10为底的对数值
* @param
* arr : 序列
* @return
* 序列以10为底的对数值
*/
ArrayLogOperation<Array, double> log10(const Array& arr);

/*
* @brief
* 求序列中每个数以10为底的对数值
* @param
* arr : 序列
* @return
* 序列以10为底的对数值
*/
ArrayLogOperation<ArrayOperation<double>, double> log10(const ArrayOperation<double>& arr);

/*
* @brief
* 求序列中每个数以10为底的对数值
* @param
* arr : 序列
* @return
* 序列以10为底的对数值
*/
ArrayLogOperation<ArrayI, Complex> log10(const ArrayI& arr);

/*
* @brief
* 求序列中每个数以10为底的对数值
* @param
* arr : 序列
* @return
* 序列以10为底的对数值
*/
ArrayLogOperation<ArrayOperation<Complex>, Complex> log10(const ArrayOperation<Complex>& arr);

/*
* @brief
* 对序列中每个数取绝对值
* @param
* arr ：序列
* @return
* 序列绝对值表达式
*/
ArrayAbsOperation<Array> abs(const Array& arr);

/*
* @brief
* 对序列中每个数取绝对值
* @param
* arr ：序列
* @return
* 序列绝对值表达式
*/
ArrayAbsOperation<ArrayOperation<double>> abs(const ArrayOperation<double>& arr);

/*
* @brief
* 对序列中每个数取绝对值
* @param
* arr ：序列
* @return
* 序列绝对值表达式
*/
ArrayAbsOperation<ArrayOperation<Complex>> abs(const ArrayOperation<Complex>& arr);

/*
* @brief
* 给定间隔创建序列
* @param
* start: 起始值
* @param
* end: 结束值，不包括
* @param
* step: 间隔
* @return
* 等间隔序列
*/
Array arange(double start, double end, double step = 1);

/*
* @brief
* 创建线性空间
* @param
* start: 起始值
* @param
* end: 终止值
* @param
* count: 点的个数
* @param
* endpoint: 是否包含结束值，1表示包含，0表示不包含
* @return
* 线性空间序列
*/
Array linspace(double start, double end, const size_t count, bool endpoint = true);

/*
* @brief
* 创建几何空间
* @param
* start: 起始值
* @param
* end: 终止值
* @param
* count: 点的个数
* @param
* endpoint: 是否包含结束值，1表示包含，0表示不包含
* @return
* 几何空间序列
*/
Array geomspace(double start, double end, const size_t count, bool endpoint = true);

/*
* @brief
* 创建对数空间
* @param
* start: 起始指数
* @param
* end: 终止指数
* @param
* count: 点的个数
* @param
* endpoint: 是否包含结束值，1表示包含，0表示不包含
* @param
* base: 底数
* @return
* 对数空间序列
*/
Array logspace(double start, double end, const size_t count, bool endpoint = true, double base = 10);


#endif // !ARRAY_H
