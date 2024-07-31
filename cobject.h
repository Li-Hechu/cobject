#pragma once

#ifndef COBJECT_H
#define COBJECT_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include <iostream>
using namespace std;

#ifndef ERROR_HEADER_MAXLEN
/*错误类标识头最大长度*/
#define ERROR_HEADER_MAXLEN 20
#endif // !ERROR_HEADER_MAXLEN

#ifndef NUMERIC_ZERO
/*数值计算中的0*/
#define ZERO(val) (abs(val)<1e-15 ? true : false)
#define ZERO14(val) (abs(val)<1e-14 ? true : false)
#endif // !NUMERIC_ZERO

#ifndef NUMERIC_EQ
/*比较浮点数是否相等*/
#define EQ(v1,v2) ((abs((v1) - (v2)) < 1e-15) ? true : false)
#define EQ14(v1,v2) ((abs((v1) - (v2)) < 1e-14) ? true : false)
#endif // !NUMERIC_EQ

#ifndef PI
/*圆周率*/
#define PI		3.1415926535897932384626
#endif // !PI

#ifndef DOUBLE_MAX
//双精度浮点数最大值
#define DOUBLE_MAX	1.7976931348623158e+308 
#endif // !DB_MAX

#ifndef DOUBLE_MIN
//双精度浮点数最小值
#define DOUBLE_MIN	2.2250738585072014e-308
#endif // !DOUBLE_MIN

#ifndef DOUBLE_EPS
//双精度浮点数最小分辨率
#define DOUBLE_EPS	2.2204460492503131e-016
/* note: 使得数字x满足 x + DOUBLE_EPS != x */
#endif // !EPSILON

#ifndef INF
#define INF		HUGE_VAL
#endif // !INF

#ifndef NAN
#define NAN		-(double)INF*0.0F;
#endif // !NAN

/*最顶层基类*/
class CObject {
public:
	inline friend bool operator == (const CObject& obj1, const CObject& obj2) {
		return static_cast<const void*>(&obj1) == static_cast<const void*>(&obj2) ? true : false;
	}
public:
	/*默认构造函数*/
	inline CObject() {

	}
	/*析构函数*/
	virtual ~CObject() {

	}
	/*指针对象输出*/
	inline friend ostream& operator << (ostream& out, const CObject* obj_ptr) {
		cout << "<" << typeid(*obj_ptr).name() << " at " << static_cast<const void*>(obj_ptr) << ">";
		return out;
	}
	/*等号运算拷贝*/
	virtual void operator=(const CObject& obj) {

	}
};

/*容器类*/
template<typename _Ele>
class Container : public CObject {
public:
	/*默认构造函数*/
	inline Container() : CObject() {

	}
	/*增加元素*/
	virtual void append(const _Ele& var) = 0;
	/*增加元素*/
	virtual void append(_Ele&& var) = 0;
};

/*一维容器类*/
template<typename _Ele>
class Container1D : public Container<_Ele> {
public:
	/*构造函数*/
	inline Container1D() : Container<_Ele>() {
		this->length = 0;
		this->size = 0;
	}
	/*拷贝构造函数*/
	inline Container1D(const Container1D& container) : Container<_Ele>() {
		this->length = container.length;
		this->size = container.size;
	}
	/*析构函数*/
	inline ~Container1D() {

	}
	/*获取元素*/
	virtual _Ele& at(const size_t index) const = 0;
	/*移除元素*/
	virtual void remove(const size_t index) = 0;
	/*下标运算符重载*/
	virtual inline _Ele& operator [] (const size_t index) const {
		return this->at(index);
	}
	/*
	* @brief
	* 获取长度
	* @param
	* 无
	* @return
	* 容器长度
	*/
	inline size_t len() const {
		return this->length;
	}
protected:
	/*
	* @brief
	* 索引检查
	* @param
	* index : 输入索引
	* @return
	* 无
	*/
	virtual void check_index(const size_t index) const {
		return;
	}
protected:
	/*容器长度*/
	size_t length;
	/*容器容量*/
	size_t size;
};

/*二维容器基类*/
template<typename _Ele>
class Container2D : public Container<_Ele> {
public:
	/*二维容器行指针*/
	class Container2D_Ptr : public CObject {
	public:
		/*默认构造函数*/
		inline Container2D_Ptr() : CObject() {
			this->ptr_length = 0;
		}
		/*给定指针及长度构造*/
		inline Container2D_Ptr(size_t length) : CObject() {
			this->ptr_length = length;
		}
		/*返回指针元素*/
		virtual inline _Ele& operator[](const size_t index) const = 0;
	protected:
		/*指针长度*/
		size_t ptr_length;
		///需要在子类中声明行指针的形式
	};
public:
	/*默认构造函数*/
	inline Container2D() : Container<_Ele>() {
		this->rowCount = 0;
		this->colCount = 0;
	}
	/*指定行数和列数构造*/
	inline Container2D(size_t _r, size_t _c) : Container<_Ele>() {
		this->rowCount = _r;
		this->colCount = _c;
	}
	/*析构函数*/
	inline ~Container2D() {

	}
	/*通过索引获取元素*/
	virtual _Ele& at(const size_t r_index, const size_t c_index) const = 0;
	/*获取一行元素*/
	virtual Container2D<_Ele>& getRow(const size_t r_index) = 0;
	/*获取一列元素*/
	virtual Container2D<_Ele>& getColumn(const size_t c_index) = 0;
	/*
	* @brief
	* 获取行数
	* @param
	* 无
	* @return
	* 行数
	*/
	inline size_t row() const {
		return this->rowCount;
	}
	/*
	* @brief
	* 获取列数
	* @param
	* 无
	* @return
	* 列数
	*/
	inline size_t column() const {
		return this->colCount;
	}
protected:
	/*行数*/
	size_t rowCount;
	/*列数*/
	size_t colCount;
};


/*匹配类*/
template<typename _X, typename _Y>
class Match : public CObject {
public:
	inline friend ostream& operator << (ostream& out, const Match& match) {
		out << "(" << match.X << "," << match.Y << ")" << endl;
		return out;
	}
public:
	/*默认构造*/
	inline Match() : CObject() {
		this->X = new _X();
		this->Y = new _Y();
	}
	/*赋值构造*/
	inline Match(const _X& l, const _Y& r) : CObject() {
		this->X = l;
		this->Y = r;
	}
	inline Match(const _X&& l, const _Y&& r) : CObject() {
		this->X = l;
		this->Y = r;
	}
	/*拷贝构造*/
	inline Match(const Match& match) {
		this->X = match.X;
		this->Y = match.Y;
	}
	/*
	* @brief
	* 设置左值
	* @param
	* X_var : 左值
	* @return
	* 无
	*/
	inline void setX(const _X& X_var) {
		delete& this->X;
		this->X = X_var;
	}
	/*
	* @brief
	* 设置右值
	* @param
	* Y_var : 左值
	* @return
	* 无
	*/
	inline void setY(const _Y& Y_var) {
		delete& this->Y;
		this->Y = Y_var;
	}
	/*
	* @brief
	* 获取左值
	* @param
	* 无
	* @return
	* 左值
	*/
	inline _X getX() const {
		return this->X;
	}
	/*
	* @brief
	* 获取右值
	* @param
	* 无
	* @return
	* 右值
	*/
	inline _Y getY() const {
		return this->Y;
	}
	/*
	* @brief
	* 等号赋值
	*/
	inline virtual void operator=(const Match& ma) {
		this->X = ma.X;
		this->Y = ma.Y;
	}
protected:
	_X X;
	_Y Y;
};


/*逗号初始化类*/
template<typename _Ele>
class CommaInitializer : public CObject {
public:
	inline friend CommaInitializer<_Ele>& operator , (CommaInitializer<_Ele>& initializer, _Ele& ele) {
		initializer.ptr->append(ele);
		return initializer;
	}
	inline friend CommaInitializer<_Ele>& operator , (CommaInitializer<_Ele>& initializer, _Ele&& ele) {
		initializer.ptr->append(ele);
		return initializer;
	}
public:
	CommaInitializer() = delete;
	CommaInitializer(const CommaInitializer<_Ele>& ele) = delete;
	inline CommaInitializer(Container<_Ele>* container) : CObject() {
		this->ptr = container;
	}
	inline virtual void operator=(const CommaInitializer<_Ele>& comma) {
		this->ptr = comma.ptr;
	}
private:
	Container<_Ele>* ptr;
};


/*自定义错误类*/
template<const char* err_header>
class Error : public CObject, public std::exception {
	friend inline void emit(const Error& err) {
		cout << err.whaterr << endl;
		exit(0);
	}
public:
	/*构造函数*/
	inline Error() : CObject() {
		this->header = err_header;
		this->info = nullptr;
		//拼接
		this->whaterr = this->err_concat(this->header, this->spliter);
	}
	/*
	* @brief
	* 输入错误信息构造错误
	* @param
	* err_info : 错误信息提示
	*/
	inline Error(const char* err_info) : CObject() {
		this->header = err_header;
		this->info = err_info;
		//拼接
		const char* tmp = this->err_concat(this->header, this->spliter);
		this->whaterr = this->err_concat(tmp, this->info);
		delete[] tmp;
	}
	/*析构函数*/
	inline ~Error() {
		delete[] this->whaterr;
	}
	/*
	* @brief
	* 什么错
	* @param
	* 无
	* @return
	* 错误信息提示
	*/
	inline const char* what(void) const {
		return this->whaterr;
	}
protected:
	/*
	* @brief
	* 两个字符串拼接
	* @param
	* _left : 左侧字符串
	* _right : 右侧字符串
	* @return
	* 拼接后的字符串
	*/
	inline const char* err_concat(const char* _left, const char* _right) {
		unsigned long long len = strlen(_left) + strlen(_right) + 1;
		char* str = new char[len] {};
		memcpy_s(str, len, _left, strlen(_left));
		strcat_s(str, len, _right);
		return str;
	}
private:
	/*错误标识头*/
	const char* header;
	/*错误提示文字*/
	const char* info;
	/*完整错误信息*/
	const char* whaterr;
	/*标识头和提示文字分隔冒号*/
	const char spliter[2] = ":";
};


static const char IndexErrorHeader[ERROR_HEADER_MAXLEN] = "IndexError";
/*索引错误*/
class IndexError : public Error<IndexErrorHeader> {
public:
	inline IndexError(const char* info) : Error(info) {

	}
};

static const char TypeErrorHeader[ERROR_HEADER_MAXLEN] = "TypeError";
/*类型错误*/
class TypeError : public Error<TypeErrorHeader> {
public:
	inline TypeError(const char* info) : Error(info) {

	}
};

static const char MathErrorHeader[ERROR_HEADER_MAXLEN] = "MathError";
/*数学错误*/
class MathError : public Error<MathErrorHeader> {
public:
	inline MathError(const char* info) : Error(info) {

	}
};

static const char DateErrorHeader[ERROR_HEADER_MAXLEN] = "DateError";
/*日期错误*/
class DateError : public Error<DateErrorHeader> {
public:
	inline DateError(const char* info) : Error(info) {

	}
};

/*限制类*/
template<typename _Ty>
class Limited : public CObject {
public:
	/*默认构造*/
	inline Limited() : CObject(), left(), right() {

	}
	/*赋值构造*/
	inline Limited(const _Ty& l, const _Ty& r, bool check = 0) : CObject(), left(l), right(r) {
		if (check) {
			if (l > r) {
				emit(MathError("区间左侧数字应当比右侧小\n"));
			}
		}
	}
	/*拷贝构造*/
	inline Limited(const Limited& lim) : left(lim.left), right(lim.right) {

	}
	/*
	* @brief
	* 判断是否包含某个值
	* @param
	* val: 值
	* @return
	* bool，1表示包含，0表示不包含
	*/
	inline bool include(const _Ty& val) const {
		if (this->left <= val && val <= this->right) {
			return true;
		}
		else {
			return false;
		}
	}
	/*输出*/
	inline friend ostream& operator<<(ostream& out, const Limited& limit) {
		out << "[" << limit.left << "," << limit.right << "]" << endl;
		return out;
	}
	//左值
	const _Ty left;
	//右值
	const _Ty right;
};

/*实数区间*/
typedef Limited<double> LimitedF;

/*点*/
template<typename _Ly, typename _Ry>
class Point : public CObject {
public:
	/*默认构造函数*/
	inline Point() : CObject(), x(), y() {

	}
	/*赋值构造函数*/
	inline Point(const _Ly& _x, const _Ry& _y) : CObject(), x(_x), y(_y) {

	}
	/*拷贝构造函数*/
	inline Point(const Point& pt) : CObject(), x(pt.x), y(pt.y) {
		
	}
	/*输出*/
	inline friend ostream& operator<<(ostream& out, const Point& pt) {
		out << "(" << pt.x << "," << pt.y << ")" << endl;
		return out;
	}
	const _Ly x;
	const _Ry y;
};

/*实数点*/
typedef Point<double, double> PointF;


#define DATE_STR_LEN	10
#define DATE_YY_LEN		4
#define DATE_MM_LEN		2
#define DATE_DD_LEN		2

/*日期类*/
class Date : public CObject {
public:
	//日期格式
	typedef enum _DateFormat {
		YMD,		//yyyy-mm-dd
		YDM,		//yyyy-dd-mm
		MDY,		//mm-dd-yyyy
		DMY			//dd-mm-yyyy
	}DateFormat;
	//分隔符
	typedef enum _DateSpliter {
		hypen = '-',	/*-*/
		slash = '/',	/*/*/
		bslash = '\\',	/*\*/
		none = '\0',	/**/
		dot = '.'		/*.*/
	}DateSpliter;
public:
	inline friend ostream& operator<<(ostream& out, const Date& date) {
		out << date.year << "年" << date.month << "月" << date.day << "日" << endl;
		return out;
	}
public:
	/*默认构造*/
	inline Date() : CObject(), year(1971), month(1), day(1) {

	}
	/*指定日期构造*/
	inline Date(const short _Y, const short _M, const short _D) : CObject(), year(_Y), month(_M), day(_D) {
		this->check_date_valid(_D, _M, _Y);
	}
	/*从字符串构造*/
	inline Date(const char* datestr, const Date::DateFormat type = Date::YMD, const Date::DateSpliter spliter = Date::hypen) : CObject() {
		//判断长度
		if (strlen(datestr) != DATE_STR_LEN) {
			emit(DateError("日期表达式格式不正确\n"));
		}
		size_t year_id = 0, spl1_id = 0, month_id = 0, spl2_id = 0, day_id = 0;
		switch (type)
		{
		case Date::YMD:
			year_id = 0;
			spl1_id = 4;
			month_id = 5;
			spl2_id = 7;
			day_id = 8;
			break;
		case Date::YDM:
			year_id = 0;
			spl1_id = 4;
			month_id = 8;
			spl2_id = 7;
			day_id = 5;
			break;
		case Date::MDY:
			year_id = 6;
			spl1_id = 2;
			month_id = 0;
			spl2_id = 5;
			day_id = 3;
			break;
		case Date::DMY:
			year_id = 6;
			spl1_id = 2;
			month_id = 3;
			spl2_id = 5;
			day_id = 0;
			break;
		default:
			emit(DateError("未识别的格式\n"));
			break;
		}
		this->year = this->get_year(datestr, year_id);
		this->check_spliter(datestr, spl1_id, spliter);
		this->month = this->get_month(datestr, month_id);
		this->check_spliter(datestr, spl2_id, spliter);
		this->day = this->get_day(datestr, day_id);
		this->check_date_valid(this->day, this->month, this->year);
	}
	/*拷贝构造*/
	inline Date(const Date& date) : CObject(), year(date.year), month(date.month), day(date.day) {

	}
	/*析构函数*/
	~Date() {

	}
	/*等号赋值*/
	inline void operator = (const Date& date) {
		this->year = date.year;
		this->month = date.month;
		this->day = date.day;
	}
protected:
	/*
	* @brief
	* 检查字符串某一段是否全为数字
	* @param
	* str: 待检查字符串
	* @param
	* start: 起始索引
	* @param
	* end: 结束索引，不包含
	* @return
	* 1表示全为数字，0表示不全为数字
	*/
	inline bool check_digit(const char* str, size_t start, size_t end) const {
		size_t i = start;
		while (*(str + i) != '\0' && i < end) {
			if (!isdigit(*(str + i))) {
				return false;
			}
			i++;
		}
		return true;
	}
	/*
	* @brief
	* 从字符串获取年份
	* @param
	* str: 字符串
	* @param
	* start: 年份字符起始索引
	* @return
	* 年份
	*/
	inline short get_year(const char* str, const size_t start) const {
		if (!check_digit(str, start, start + 4)) {
			emit(DateError("年份表达式出现非数字\n"));
		}
		return (*(str + start) - '0') * 1000 + (*(str + start + 1) - '0') * 100 + \
			(*(str + start + 2) - '0') * 10 + (*(str + start + 3) - '0');
	}
	/*
	* @brief
	* 从字符串获取月份
	* @param
	* str: 字符串
	* @param
	* start: 月份字符起始索引
	* @return
	* 月份
	*/
	inline short get_month(const char* str, const size_t start) const {
		if (!this->check_digit(str, start, start + 2)) {
			emit(DateError("月份表达式出现非数字\n"));
		}
		short mon = (*(str + start) - '0') * 10 + (*(str + start + 1) - '0');
		if (mon < 1 || mon>12) {
			emit(DateError("月份应该从1到12\n"));
		}
		return mon;
	}
	/*
	* @brief
	* 从字符串获取天数
	* @param
	* str: 字符串
	* @param
	* start: 天数字符起始索引
	* @return
	* 天数
	*/
	inline short get_day(const char* str, const size_t start) const {
		if (!this->check_digit(str, start, start + 2)) {
			emit(DateError("天数表达式出现非数字\n"));
		}
		return (*(str + start) - '0') * 10 + (*(str + start + 1) - '0');
	}
	/*
	* @brief
	* 检查天数是否有效
	* @param
	* day: 天数
	* @param
	* month: 月份
	* @return
	* 1表示有效，0表示无效
	*/
	inline void check_date_valid(const short _day, const short _month, const short _year) const {
		bool flag = false;
		if (_month == 2) {
			//闰年
			if ((_year % 400 != 0 && _year % 4 == 0) || (_year % 400 == 0)) {
				if (_day < 1 || _day >29) flag = false;
				else flag = true;
			}
			//非闰年
			else {
				if (_day < 1 || _day >28) flag = false;
				else flag = true;
			}
		}
		else if (_month == 1 || _month == 3 || _month == 5 || _month == 7 || _month == 8 || _month == 10 || _month == 12) {
			if (_day < 1 || _day>31) flag = false;
			else flag = true;
		}
		else if (_month == 4 || _month == 6 || _month == 9 || _month == 11) {
			if (_day < 1 || _day>30) flag = false;
			else flag = true;
		}
		else {
			flag = false;
		}

		if (!flag) {
			emit(DateError("日期不存在\n"));
		}
	}
	/*
	* @brief
	* 检查分隔符
	* @param
	* str: 日期字符串
	* @param
	* index: 分隔符索引
	* @param
	* spliter: 需要比较的分隔符
	* @return
	* 1表示与给定分隔符一致，0表示不一致
	*/
	inline void check_spliter(const char* str, const size_t index, const char spliter) const {
		if (*(str + index) != spliter) {
			emit(DateError("分隔符不一致\n"));
		}
	}
private:
	short year;
	short month;
	short day;
};

/*
* @brief
* 内存拷贝,模板参数为元素类型
* @param
* dst: 目标地址
* @param
* dst_t: 目标地址长度
* @param
* src: 源地址
* @param
* src_t: 源地址长度
* @return
* 无
*/
template<typename _Ty>
void deepcopy(_Ty* dst, size_t dst_t, _Ty* src, size_t src_t) {
	//如果是c++基本类型
	if (!is_class<_Ty>::value) {
		memcpy_s(dst, dst_t * sizeof(_Ty), src, src_t * sizeof(_Ty));
	}
	else {
		//如果是类，则使用等号运算赋值
		for (size_t i = 0; i < min<size_t>(dst_t, src_t); i++) {
			*(dst + i) = *(src + i);
		}
	}
}

/*
* @brief
* 数字转十六进制数组
* @param
* num: 数字
* @param
* hex: 数组
* @return
* 无
*/
template<typename _Ele>
void num2hex(const _Ele num, uint8_t hex[]) {
	*(_Ele*)hex = num;
}

/*
* @brief
* 十六进制数组转数字
* @param
* hex: 数组
* @param
* num: 数字
* @return
* 无
*/
template<typename _Ele>
void hex2num(uint8_t hex[], _Ele* num) {
	*num = *(_Ele*)hex;
}

/*
* @brief
* 返回当前数值的最小浮点精度
* @param
* num: 数值
* @return
* 最小浮点精度
*/
template<typename _Ele>
_Ele eps(const _Ele num) {
	///浮点转换为16进制数组时，为倒序填充，低位在前，高位在后
	///整型转换为16进制数组时，为正序填充，高位在前，低位在后
	if (typeid(_Ele) == typeid(double)) {
		uint8_t hex[8] = { 0,0,0,0,0,0,0,0 };
		num2hex<_Ele>(num, hex);
		//符号与指数位
		uint16_t symbol = 0;
		//获取符号和指数位
		symbol |= hex[7] << 8;
		symbol |= hex[6];
		//低四位和符号位清零
		symbol &= 0x7FF0;
		//右移四位
		symbol >>= 4;
		//减去52后剩余的值
		uint16_t remain = 0;
		if (symbol > 52) {
			//小数位填0
			memset(hex, 0x00, sizeof(uint8_t) * 6);
			remain = symbol - 52;
			//左移4位，复位
			remain <<= 4;
			//填充符号和指数位
			hex[6] = (uint8_t)remain & 0xFF;			//低位
			hex[7] = (uint8_t)(remain >> 8) & 0xFF;		//高位
		}
		else if (symbol <= 52 && symbol > 0) {		///等号必须放在这里，确保符号和指数位均为0时，存在小数位数
			//辅助数字
			uint64_t aux = 0x0008000000000000;
			//移动位数
			remain = 52 - symbol;
			//右移remain位
			aux >>= remain;
			//填充
			hex[7] = (uint8_t)(aux >> 56) & 0xFF;
			hex[6] = (uint8_t)(aux >> 48) & 0xFF;
			hex[5] = (uint8_t)(aux >> 40) & 0xFF;
			hex[4] = (uint8_t)(aux >> 32) & 0xFF;
			hex[3] = (uint8_t)(aux >> 24) & 0xFF;
			hex[2] = (uint8_t)(aux >> 16) & 0xFF;
			hex[1] = (uint8_t)(aux >> 8) & 0xFF;
			hex[0] = (uint8_t)(aux >> 0) & 0xFF;
		}
		else {				///处理移动超过51位的情况，确保不会出现全为0的情况
			//清零
			memset(hex, 0x00, sizeof(uint8_t) * 8);
			//最低位置1
			hex[0] = 0x01;
		}
		_Ele convert{};
		hex2num<_Ele>(hex, &convert);
		return convert;
	}
	else if (typeid(_Ele) == typeid(float)) {
		uint8_t hex[4] = { 0,0,0,0 };
		num2hex<_Ele>(num, hex);
		//符号与指数位
		uint8_t symbol = 0;
		//获取符号和指数位
		symbol = (hex[3] & 0x7F) << 1;
		symbol |= (hex[2] >> 7);
		//减去23后剩余的值
		uint8_t remain = 0;
		if (symbol > 23) {
			//小数位填0
			memset(hex, 0x00, sizeof(uint8_t) * 3);
			remain = symbol - 23;
			//填充指数位
			hex[3] = remain >> 1;
			hex[2] |= remain << 7;
		}
		else if (symbol <= 23 && symbol > 0) {		///等号必须放在这里，确保符号和指数位均为0时，存在小数位数
			//辅助数字
			uint64_t aux = 0x00400000;
			//移动位数
			remain = 23 - symbol;
			//右移remain位
			aux >>= remain;
			//填充
			hex[3] = (uint8_t)(aux >> 24) & 0xFF;
			hex[2] = (uint8_t)(aux >> 16) & 0xFF;
			hex[1] = (uint8_t)(aux >> 8) & 0xFF;
			hex[0] = (uint8_t)(aux >> 0) & 0xFF;
		}
		else {				///处理移动超过22位的情况，确保不会出现全为0的情况
			//清零
			memset(hex, 0x00, sizeof(uint8_t) * 4);
			//最低位置1
			hex[0] = 0x01;
		}
		_Ele convert{};
		hex2num<_Ele>(hex, &convert);
		return convert;
	}

	//整型
	return _Ele(1);
}

/*
* @brief
* 组合数辅助函数
* @param
* list: 元素列表
* @param
* begin: 遍历起始位置
* @param
* N: 列表长度
* @param
* aux: 辅助数组，标志哪些数字被选取
* @param
* m: 表示选取了多少元素
* @param
* M: 要选取多少元素
* @param
* result: 结果存储容器
* @return
* 无
*/
template<typename Ty, typename InnerList, typename ReList>
static void combination_aux(const Container1D<Ty>& list, const size_t begin, const size_t N, size_t aux[], size_t m, const size_t M, ReList& result) {
	for (size_t i = begin; i <= N - M + m; i++) {    // 从前向后
		if (m < M) {
			aux[m] = i;                         // 选择第 m 个元素
		}

		if (m < M - 1) {                          // 没选择完, 从余下的 input[i+1..N] 中选择余下的元素
			combination_aux<Ty,InnerList,ReList>(list, i + 1, N, aux, m + 1, M, result);
		}
		else {
			InnerList arr(M);
			for (size_t j = 0; j < M; j++) {
				arr[j] = list[aux[j]];
			}
			result.append(arr);
		}
	}
}

/*
* @brief
* 从长度为N的列表中选出M个元素
* @param
* list: 列表
* @param
* M: 需要选出的元素个数
* @return
* 返回选取结果
*/
template<typename Ty, typename InnerList, typename ReList>
ReList combine(const Container1D<Ty>& list, const size_t M) {
	/// <summary>
	/// InnerList 为单层列表
	/// ReList 为双层列表，其内层为InnerList类型
	/// </summary>
	size_t* aux = new size_t[M]{};      //辅助数组
	ReList result{};
	combination_aux<Ty, InnerList, ReList>(list, 0, list.len(), aux, 0, M, result);
	delete[] aux;
	return result;
}

/*
* @brief
* 寻找一维容器元素最大值
* @param
* list: 一维容器
* @return
* 最大值的索引及其引用
*/
template<typename _Ele>
Point<size_t, const _Ele&> max(const Container1D<_Ele>& list) {
	size_t len = list.len();
	if (len == 0) {
		emit(MathError("排序列表长度为0"));
	}
	//最大值索引
	size_t index = 0;
	//最大值
	_Ele val = list[0];

	for (size_t i = index + 1; i < len; i++) {
		_Ele temp = list[i];
		if (temp > val) {
			index = i;
			val = temp;
		}
	}

	return Point<size_t, const _Ele&>(index, list[index]);
}

/*
* @brief
* 寻找一维容器元素最大值
* @param
* list: 一维容器
* @param
* method: 函数指针
* @return
* 最大值的索引及其引用
*/
template<typename _Ele, typename _F>
Point<size_t, const _Ele&> max(const Container1D<_Ele>& list, _F method) {
	size_t len = list.len();
	if (len == 0) {
		emit(MathError("排序列表长度为0"));
	}
	//最大值索引
	size_t index = 0;
	//最大值
	double val = method(list[0]);

	for (size_t i = index + 1; i < len; i++) {
		double temp = method(list[i]);
		if (temp > val) {
			index = i;
			val = temp;
		}
	}

	return Point<size_t, const _Ele&>(index, list[index]);
}

/*
* @brief
* 寻找一维容器元素最小值
* @param
* list: 一维容器
* @param
* method: 函数指针
* @return
* 最小值的索引及其引用
*/
template<typename _Ele, typename _F>
Point<size_t, const _Ele&> min(const Container1D<_Ele>& list, _F method) {
	size_t len = list.len();
	if (len == 0) {
		emit(MathError("排序列表长度为0"));
	}
	//最大值索引
	size_t index = 0;
	//最大值
	double val = method(list[0]);
	for (size_t i = index + 1; i < len; i++) {
		double temp = method(list[i]);
		if (temp < val) {
			index = i;
			val = temp;
		}
	}

	return Point<size_t, const _Ele&>(index, list[index]);
}

/*
* @brief
* 寻找一维容器元素最小值
* @param
* list: 一维容器
* @return
* 最小值的索引及其引用
*/
template<typename _Ele>
Point<size_t, const _Ele&> min(const Container1D<_Ele>& list) {
	size_t len = list.len();
	if (len == 0) {
		emit(MathError("排序列表长度为0"));
	}
	//最大值索引
	size_t index = 0;
	//最大值
	_Ele val = list[0];

	for (size_t i = index + 1; i < len; i++) {
		_Ele temp = list[i];
		if (temp < val) {
			index = i;
			val = temp;
		}
	}

	return Point<size_t, const _Ele&>(index, list[index]);
}

/*
* @brief
* 求容器内元素的和
* @param
* list: 容器
* @return
* 元素之和
*/
template<typename _Ele>
_Ele sum(const Container1D<_Ele>& list) {
	if (list.len() == 0) {
		return _Ele{};
	}
	_Ele val = list[0];
	for (size_t i = 1; i < list.len(); i++) {
		val += list[i];
	}
	return val;
}

/*
* @brief
* 求容器内元素的积
* @param
* list: 容器
* @return
* 元素之积
*/
template<typename _Ele>
_Ele multi(const Container1D<_Ele>& list) {
	if (list.len() == 0) {
		return _Ele{};
	}
	_Ele val = list[0];
	for (size_t i = 1; i < list.len(); i++) {
		val *= list[i];
	}
	return val;
}

/*
* @brief
* 排序，改变原容器内元素顺序
* @param
* list: 列表
* @param
* flag: 0表示降序，1表示升序
* @return
* 无
*/
template<typename _Ele>
void sort(Container1D<_Ele>& list, bool flag) {
	size_t N = list.len();
	if (N == 0 || N == 1) {
		return;
	}
	//子循环是否有元素交换
	bool exchange = false;
	//升序
	if (flag) {
		for (size_t i = 0; i < N - 1; i++) {
			exchange = false;
			for (size_t j = 0; j < N - 1 - i; j++) {
				if (list[j] > list[j + 1]) {
					_Ele temp = list[j + 1];
					list[j + 1] = list[j];
					list[j] = temp;
					exchange = true;
				}
				if (exchange == false) {		//如果子循环没有元素交换，则表示已经完成排序
					return;
				}
			}
		}
	}
	//降序
	else {
		for (size_t i = 0; i < N - 1; i++) {
			exchange = false;
			for (size_t j = 0; j < N - 1 - i; j++) {
				if (list[j] < list[j + 1]) {
					_Ele temp = list[j + 1];
					list[j + 1] = list[j];
					list[j] = temp;
					exchange = true;
				}
				if (exchange == false) {
					return;
				}
			}
		}
	}
}

#endif // !COBJECT_H
