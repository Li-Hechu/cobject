#pragma once

#ifndef COBJECT_H
#define COBJECT_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include <iostream>
using namespace std;

#ifndef ERROR_HEADER_MAXLEN
/*�������ʶͷ��󳤶�*/
#define ERROR_HEADER_MAXLEN 20
#endif // !ERROR_HEADER_MAXLEN

#ifndef NUMERIC_ZERO
/*��ֵ�����е�0*/
#define ZERO(val) (abs(val)<1e-15 ? true : false)
#define ZERO14(val) (abs(val)<1e-14 ? true : false)
#endif // !NUMERIC_ZERO

#ifndef NUMERIC_EQ
/*�Ƚϸ������Ƿ����*/
#define EQ(v1,v2) ((abs((v1) - (v2)) < 1e-15) ? true : false)
#define EQ14(v1,v2) ((abs((v1) - (v2)) < 1e-14) ? true : false)
#endif // !NUMERIC_EQ

#ifndef PI
/*Բ����*/
#define PI		3.1415926535897932384626
#endif // !PI

#ifndef DOUBLE_MAX
//˫���ȸ��������ֵ
#define DOUBLE_MAX	1.7976931348623158e+308 
#endif // !DB_MAX

#ifndef DOUBLE_MIN
//˫���ȸ�������Сֵ
#define DOUBLE_MIN	2.2250738585072014e-308
#endif // !DOUBLE_MIN

#ifndef DOUBLE_EPS
//˫���ȸ�������С�ֱ���
#define DOUBLE_EPS	2.2204460492503131e-016
/* note: ʹ������x���� x + DOUBLE_EPS != x */
#endif // !EPSILON

#ifndef INF
#define INF		HUGE_VAL
#endif // !INF

#ifndef NAN
#define NAN		-(double)INF*0.0F;
#endif // !NAN

/*������*/
class CObject {
public:
	inline friend bool operator == (const CObject& obj1, const CObject& obj2) {
		return static_cast<const void*>(&obj1) == static_cast<const void*>(&obj2) ? true : false;
	}
public:
	/*Ĭ�Ϲ��캯��*/
	inline CObject() {

	}
	/*��������*/
	virtual ~CObject() {

	}
	/*ָ��������*/
	inline friend ostream& operator << (ostream& out, const CObject* obj_ptr) {
		cout << "<" << typeid(*obj_ptr).name() << " at " << static_cast<const void*>(obj_ptr) << ">";
		return out;
	}
	/*�Ⱥ����㿽��*/
	virtual void operator=(const CObject& obj) {

	}
};

/*������*/
template<typename _Ele>
class Container : public CObject {
public:
	/*Ĭ�Ϲ��캯��*/
	inline Container() : CObject() {

	}
	/*����Ԫ��*/
	virtual void append(const _Ele& var) = 0;
	/*����Ԫ��*/
	virtual void append(_Ele&& var) = 0;
};

/*һά������*/
template<typename _Ele>
class Container1D : public Container<_Ele> {
public:
	/*���캯��*/
	inline Container1D() : Container<_Ele>() {
		this->length = 0;
		this->size = 0;
	}
	/*�������캯��*/
	inline Container1D(const Container1D& container) : Container<_Ele>() {
		this->length = container.length;
		this->size = container.size;
	}
	/*��������*/
	inline ~Container1D() {

	}
	/*��ȡԪ��*/
	virtual _Ele& at(const size_t index) const = 0;
	/*�Ƴ�Ԫ��*/
	virtual void remove(const size_t index) = 0;
	/*�±����������*/
	virtual inline _Ele& operator [] (const size_t index) const {
		return this->at(index);
	}
	/*
	* @brief
	* ��ȡ����
	* @param
	* ��
	* @return
	* ��������
	*/
	inline size_t len() const {
		return this->length;
	}
protected:
	/*
	* @brief
	* �������
	* @param
	* index : ��������
	* @return
	* ��
	*/
	virtual void check_index(const size_t index) const {
		return;
	}
protected:
	/*��������*/
	size_t length;
	/*��������*/
	size_t size;
};

/*��ά��������*/
template<typename _Ele>
class Container2D : public Container<_Ele> {
public:
	/*��ά������ָ��*/
	class Container2D_Ptr : public CObject {
	public:
		/*Ĭ�Ϲ��캯��*/
		inline Container2D_Ptr() : CObject() {
			this->ptr_length = 0;
		}
		/*����ָ�뼰���ȹ���*/
		inline Container2D_Ptr(size_t length) : CObject() {
			this->ptr_length = length;
		}
		/*����ָ��Ԫ��*/
		virtual inline _Ele& operator[](const size_t index) const = 0;
	protected:
		/*ָ�볤��*/
		size_t ptr_length;
		///��Ҫ��������������ָ�����ʽ
	};
public:
	/*Ĭ�Ϲ��캯��*/
	inline Container2D() : Container<_Ele>() {
		this->rowCount = 0;
		this->colCount = 0;
	}
	/*ָ����������������*/
	inline Container2D(size_t _r, size_t _c) : Container<_Ele>() {
		this->rowCount = _r;
		this->colCount = _c;
	}
	/*��������*/
	inline ~Container2D() {

	}
	/*ͨ��������ȡԪ��*/
	virtual _Ele& at(const size_t r_index, const size_t c_index) const = 0;
	/*��ȡһ��Ԫ��*/
	virtual Container2D<_Ele>& getRow(const size_t r_index) = 0;
	/*��ȡһ��Ԫ��*/
	virtual Container2D<_Ele>& getColumn(const size_t c_index) = 0;
	/*
	* @brief
	* ��ȡ����
	* @param
	* ��
	* @return
	* ����
	*/
	inline size_t row() const {
		return this->rowCount;
	}
	/*
	* @brief
	* ��ȡ����
	* @param
	* ��
	* @return
	* ����
	*/
	inline size_t column() const {
		return this->colCount;
	}
protected:
	/*����*/
	size_t rowCount;
	/*����*/
	size_t colCount;
};


/*ƥ����*/
template<typename _X, typename _Y>
class Match : public CObject {
public:
	inline friend ostream& operator << (ostream& out, const Match& match) {
		out << "(" << match.X << "," << match.Y << ")" << endl;
		return out;
	}
public:
	/*Ĭ�Ϲ���*/
	inline Match() : CObject() {
		this->X = new _X();
		this->Y = new _Y();
	}
	/*��ֵ����*/
	inline Match(const _X& l, const _Y& r) : CObject() {
		this->X = l;
		this->Y = r;
	}
	inline Match(const _X&& l, const _Y&& r) : CObject() {
		this->X = l;
		this->Y = r;
	}
	/*��������*/
	inline Match(const Match& match) {
		this->X = match.X;
		this->Y = match.Y;
	}
	/*
	* @brief
	* ������ֵ
	* @param
	* X_var : ��ֵ
	* @return
	* ��
	*/
	inline void setX(const _X& X_var) {
		delete& this->X;
		this->X = X_var;
	}
	/*
	* @brief
	* ������ֵ
	* @param
	* Y_var : ��ֵ
	* @return
	* ��
	*/
	inline void setY(const _Y& Y_var) {
		delete& this->Y;
		this->Y = Y_var;
	}
	/*
	* @brief
	* ��ȡ��ֵ
	* @param
	* ��
	* @return
	* ��ֵ
	*/
	inline _X getX() const {
		return this->X;
	}
	/*
	* @brief
	* ��ȡ��ֵ
	* @param
	* ��
	* @return
	* ��ֵ
	*/
	inline _Y getY() const {
		return this->Y;
	}
	/*
	* @brief
	* �ȺŸ�ֵ
	*/
	inline virtual void operator=(const Match& ma) {
		this->X = ma.X;
		this->Y = ma.Y;
	}
protected:
	_X X;
	_Y Y;
};


/*���ų�ʼ����*/
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


/*�Զ��������*/
template<const char* err_header>
class Error : public CObject, public std::exception {
	friend inline void emit(const Error& err) {
		cout << err.whaterr << endl;
		exit(0);
	}
public:
	/*���캯��*/
	inline Error() : CObject() {
		this->header = err_header;
		this->info = nullptr;
		//ƴ��
		this->whaterr = this->err_concat(this->header, this->spliter);
	}
	/*
	* @brief
	* ���������Ϣ�������
	* @param
	* err_info : ������Ϣ��ʾ
	*/
	inline Error(const char* err_info) : CObject() {
		this->header = err_header;
		this->info = err_info;
		//ƴ��
		const char* tmp = this->err_concat(this->header, this->spliter);
		this->whaterr = this->err_concat(tmp, this->info);
		delete[] tmp;
	}
	/*��������*/
	inline ~Error() {
		delete[] this->whaterr;
	}
	/*
	* @brief
	* ʲô��
	* @param
	* ��
	* @return
	* ������Ϣ��ʾ
	*/
	inline const char* what(void) const {
		return this->whaterr;
	}
protected:
	/*
	* @brief
	* �����ַ���ƴ��
	* @param
	* _left : ����ַ���
	* _right : �Ҳ��ַ���
	* @return
	* ƴ�Ӻ���ַ���
	*/
	inline const char* err_concat(const char* _left, const char* _right) {
		unsigned long long len = strlen(_left) + strlen(_right) + 1;
		char* str = new char[len] {};
		memcpy_s(str, len, _left, strlen(_left));
		strcat_s(str, len, _right);
		return str;
	}
private:
	/*�����ʶͷ*/
	const char* header;
	/*������ʾ����*/
	const char* info;
	/*����������Ϣ*/
	const char* whaterr;
	/*��ʶͷ����ʾ���ַָ�ð��*/
	const char spliter[2] = ":";
};


static const char IndexErrorHeader[ERROR_HEADER_MAXLEN] = "IndexError";
/*��������*/
class IndexError : public Error<IndexErrorHeader> {
public:
	inline IndexError(const char* info) : Error(info) {

	}
};

static const char TypeErrorHeader[ERROR_HEADER_MAXLEN] = "TypeError";
/*���ʹ���*/
class TypeError : public Error<TypeErrorHeader> {
public:
	inline TypeError(const char* info) : Error(info) {

	}
};

static const char MathErrorHeader[ERROR_HEADER_MAXLEN] = "MathError";
/*��ѧ����*/
class MathError : public Error<MathErrorHeader> {
public:
	inline MathError(const char* info) : Error(info) {

	}
};

static const char DateErrorHeader[ERROR_HEADER_MAXLEN] = "DateError";
/*���ڴ���*/
class DateError : public Error<DateErrorHeader> {
public:
	inline DateError(const char* info) : Error(info) {

	}
};

/*������*/
template<typename _Ty>
class Limited : public CObject {
public:
	/*Ĭ�Ϲ���*/
	inline Limited() : CObject(), left(), right() {

	}
	/*��ֵ����*/
	inline Limited(const _Ty& l, const _Ty& r, bool check = 0) : CObject(), left(l), right(r) {
		if (check) {
			if (l > r) {
				emit(MathError("�����������Ӧ�����Ҳ�С\n"));
			}
		}
	}
	/*��������*/
	inline Limited(const Limited& lim) : left(lim.left), right(lim.right) {

	}
	/*
	* @brief
	* �ж��Ƿ����ĳ��ֵ
	* @param
	* val: ֵ
	* @return
	* bool��1��ʾ������0��ʾ������
	*/
	inline bool include(const _Ty& val) const {
		if (this->left <= val && val <= this->right) {
			return true;
		}
		else {
			return false;
		}
	}
	/*���*/
	inline friend ostream& operator<<(ostream& out, const Limited& limit) {
		out << "[" << limit.left << "," << limit.right << "]" << endl;
		return out;
	}
	//��ֵ
	const _Ty left;
	//��ֵ
	const _Ty right;
};

/*ʵ������*/
typedef Limited<double> LimitedF;

/*��*/
template<typename _Ly, typename _Ry>
class Point : public CObject {
public:
	/*Ĭ�Ϲ��캯��*/
	inline Point() : CObject(), x(), y() {

	}
	/*��ֵ���캯��*/
	inline Point(const _Ly& _x, const _Ry& _y) : CObject(), x(_x), y(_y) {

	}
	/*�������캯��*/
	inline Point(const Point& pt) : CObject(), x(pt.x), y(pt.y) {
		
	}
	/*���*/
	inline friend ostream& operator<<(ostream& out, const Point& pt) {
		out << "(" << pt.x << "," << pt.y << ")" << endl;
		return out;
	}
	const _Ly x;
	const _Ry y;
};

/*ʵ����*/
typedef Point<double, double> PointF;


#define DATE_STR_LEN	10
#define DATE_YY_LEN		4
#define DATE_MM_LEN		2
#define DATE_DD_LEN		2

/*������*/
class Date : public CObject {
public:
	//���ڸ�ʽ
	typedef enum _DateFormat {
		YMD,		//yyyy-mm-dd
		YDM,		//yyyy-dd-mm
		MDY,		//mm-dd-yyyy
		DMY			//dd-mm-yyyy
	}DateFormat;
	//�ָ���
	typedef enum _DateSpliter {
		hypen = '-',	/*-*/
		slash = '/',	/*/*/
		bslash = '\\',	/*\*/
		none = '\0',	/**/
		dot = '.'		/*.*/
	}DateSpliter;
public:
	inline friend ostream& operator<<(ostream& out, const Date& date) {
		out << date.year << "��" << date.month << "��" << date.day << "��" << endl;
		return out;
	}
public:
	/*Ĭ�Ϲ���*/
	inline Date() : CObject(), year(1971), month(1), day(1) {

	}
	/*ָ�����ڹ���*/
	inline Date(const short _Y, const short _M, const short _D) : CObject(), year(_Y), month(_M), day(_D) {
		this->check_date_valid(_D, _M, _Y);
	}
	/*���ַ�������*/
	inline Date(const char* datestr, const Date::DateFormat type = Date::YMD, const Date::DateSpliter spliter = Date::hypen) : CObject() {
		//�жϳ���
		if (strlen(datestr) != DATE_STR_LEN) {
			emit(DateError("���ڱ��ʽ��ʽ����ȷ\n"));
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
			emit(DateError("δʶ��ĸ�ʽ\n"));
			break;
		}
		this->year = this->get_year(datestr, year_id);
		this->check_spliter(datestr, spl1_id, spliter);
		this->month = this->get_month(datestr, month_id);
		this->check_spliter(datestr, spl2_id, spliter);
		this->day = this->get_day(datestr, day_id);
		this->check_date_valid(this->day, this->month, this->year);
	}
	/*��������*/
	inline Date(const Date& date) : CObject(), year(date.year), month(date.month), day(date.day) {

	}
	/*��������*/
	~Date() {

	}
	/*�ȺŸ�ֵ*/
	inline void operator = (const Date& date) {
		this->year = date.year;
		this->month = date.month;
		this->day = date.day;
	}
protected:
	/*
	* @brief
	* ����ַ���ĳһ���Ƿ�ȫΪ����
	* @param
	* str: ������ַ���
	* @param
	* start: ��ʼ����
	* @param
	* end: ����������������
	* @return
	* 1��ʾȫΪ���֣�0��ʾ��ȫΪ����
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
	* ���ַ�����ȡ���
	* @param
	* str: �ַ���
	* @param
	* start: ����ַ���ʼ����
	* @return
	* ���
	*/
	inline short get_year(const char* str, const size_t start) const {
		if (!check_digit(str, start, start + 4)) {
			emit(DateError("��ݱ��ʽ���ַ�����\n"));
		}
		return (*(str + start) - '0') * 1000 + (*(str + start + 1) - '0') * 100 + \
			(*(str + start + 2) - '0') * 10 + (*(str + start + 3) - '0');
	}
	/*
	* @brief
	* ���ַ�����ȡ�·�
	* @param
	* str: �ַ���
	* @param
	* start: �·��ַ���ʼ����
	* @return
	* �·�
	*/
	inline short get_month(const char* str, const size_t start) const {
		if (!this->check_digit(str, start, start + 2)) {
			emit(DateError("�·ݱ��ʽ���ַ�����\n"));
		}
		short mon = (*(str + start) - '0') * 10 + (*(str + start + 1) - '0');
		if (mon < 1 || mon>12) {
			emit(DateError("�·�Ӧ�ô�1��12\n"));
		}
		return mon;
	}
	/*
	* @brief
	* ���ַ�����ȡ����
	* @param
	* str: �ַ���
	* @param
	* start: �����ַ���ʼ����
	* @return
	* ����
	*/
	inline short get_day(const char* str, const size_t start) const {
		if (!this->check_digit(str, start, start + 2)) {
			emit(DateError("�������ʽ���ַ�����\n"));
		}
		return (*(str + start) - '0') * 10 + (*(str + start + 1) - '0');
	}
	/*
	* @brief
	* ��������Ƿ���Ч
	* @param
	* day: ����
	* @param
	* month: �·�
	* @return
	* 1��ʾ��Ч��0��ʾ��Ч
	*/
	inline void check_date_valid(const short _day, const short _month, const short _year) const {
		bool flag = false;
		if (_month == 2) {
			//����
			if ((_year % 400 != 0 && _year % 4 == 0) || (_year % 400 == 0)) {
				if (_day < 1 || _day >29) flag = false;
				else flag = true;
			}
			//������
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
			emit(DateError("���ڲ�����\n"));
		}
	}
	/*
	* @brief
	* ���ָ���
	* @param
	* str: �����ַ���
	* @param
	* index: �ָ�������
	* @param
	* spliter: ��Ҫ�Ƚϵķָ���
	* @return
	* 1��ʾ������ָ���һ�£�0��ʾ��һ��
	*/
	inline void check_spliter(const char* str, const size_t index, const char spliter) const {
		if (*(str + index) != spliter) {
			emit(DateError("�ָ�����һ��\n"));
		}
	}
private:
	short year;
	short month;
	short day;
};

/*
* @brief
* �ڴ濽��,ģ�����ΪԪ������
* @param
* dst: Ŀ���ַ
* @param
* dst_t: Ŀ���ַ����
* @param
* src: Դ��ַ
* @param
* src_t: Դ��ַ����
* @return
* ��
*/
template<typename _Ty>
void deepcopy(_Ty* dst, size_t dst_t, _Ty* src, size_t src_t) {
	//�����c++��������
	if (!is_class<_Ty>::value) {
		memcpy_s(dst, dst_t * sizeof(_Ty), src, src_t * sizeof(_Ty));
	}
	else {
		//������࣬��ʹ�õȺ����㸳ֵ
		for (size_t i = 0; i < min<size_t>(dst_t, src_t); i++) {
			*(dst + i) = *(src + i);
		}
	}
}

/*
* @brief
* ����תʮ����������
* @param
* num: ����
* @param
* hex: ����
* @return
* ��
*/
template<typename _Ele>
void num2hex(const _Ele num, uint8_t hex[]) {
	*(_Ele*)hex = num;
}

/*
* @brief
* ʮ����������ת����
* @param
* hex: ����
* @param
* num: ����
* @return
* ��
*/
template<typename _Ele>
void hex2num(uint8_t hex[], _Ele* num) {
	*num = *(_Ele*)hex;
}

/*
* @brief
* ���ص�ǰ��ֵ����С���㾫��
* @param
* num: ��ֵ
* @return
* ��С���㾫��
*/
template<typename _Ele>
_Ele eps(const _Ele num) {
	///����ת��Ϊ16��������ʱ��Ϊ������䣬��λ��ǰ����λ�ں�
	///����ת��Ϊ16��������ʱ��Ϊ������䣬��λ��ǰ����λ�ں�
	if (typeid(_Ele) == typeid(double)) {
		uint8_t hex[8] = { 0,0,0,0,0,0,0,0 };
		num2hex<_Ele>(num, hex);
		//������ָ��λ
		uint16_t symbol = 0;
		//��ȡ���ź�ָ��λ
		symbol |= hex[7] << 8;
		symbol |= hex[6];
		//����λ�ͷ���λ����
		symbol &= 0x7FF0;
		//������λ
		symbol >>= 4;
		//��ȥ52��ʣ���ֵ
		uint16_t remain = 0;
		if (symbol > 52) {
			//С��λ��0
			memset(hex, 0x00, sizeof(uint8_t) * 6);
			remain = symbol - 52;
			//����4λ����λ
			remain <<= 4;
			//�����ź�ָ��λ
			hex[6] = (uint8_t)remain & 0xFF;			//��λ
			hex[7] = (uint8_t)(remain >> 8) & 0xFF;		//��λ
		}
		else if (symbol <= 52 && symbol > 0) {		///�Ⱥű���������ȷ�����ź�ָ��λ��Ϊ0ʱ������С��λ��
			//��������
			uint64_t aux = 0x0008000000000000;
			//�ƶ�λ��
			remain = 52 - symbol;
			//����remainλ
			aux >>= remain;
			//���
			hex[7] = (uint8_t)(aux >> 56) & 0xFF;
			hex[6] = (uint8_t)(aux >> 48) & 0xFF;
			hex[5] = (uint8_t)(aux >> 40) & 0xFF;
			hex[4] = (uint8_t)(aux >> 32) & 0xFF;
			hex[3] = (uint8_t)(aux >> 24) & 0xFF;
			hex[2] = (uint8_t)(aux >> 16) & 0xFF;
			hex[1] = (uint8_t)(aux >> 8) & 0xFF;
			hex[0] = (uint8_t)(aux >> 0) & 0xFF;
		}
		else {				///�����ƶ�����51λ�������ȷ���������ȫΪ0�����
			//����
			memset(hex, 0x00, sizeof(uint8_t) * 8);
			//���λ��1
			hex[0] = 0x01;
		}
		_Ele convert{};
		hex2num<_Ele>(hex, &convert);
		return convert;
	}
	else if (typeid(_Ele) == typeid(float)) {
		uint8_t hex[4] = { 0,0,0,0 };
		num2hex<_Ele>(num, hex);
		//������ָ��λ
		uint8_t symbol = 0;
		//��ȡ���ź�ָ��λ
		symbol = (hex[3] & 0x7F) << 1;
		symbol |= (hex[2] >> 7);
		//��ȥ23��ʣ���ֵ
		uint8_t remain = 0;
		if (symbol > 23) {
			//С��λ��0
			memset(hex, 0x00, sizeof(uint8_t) * 3);
			remain = symbol - 23;
			//���ָ��λ
			hex[3] = remain >> 1;
			hex[2] |= remain << 7;
		}
		else if (symbol <= 23 && symbol > 0) {		///�Ⱥű���������ȷ�����ź�ָ��λ��Ϊ0ʱ������С��λ��
			//��������
			uint64_t aux = 0x00400000;
			//�ƶ�λ��
			remain = 23 - symbol;
			//����remainλ
			aux >>= remain;
			//���
			hex[3] = (uint8_t)(aux >> 24) & 0xFF;
			hex[2] = (uint8_t)(aux >> 16) & 0xFF;
			hex[1] = (uint8_t)(aux >> 8) & 0xFF;
			hex[0] = (uint8_t)(aux >> 0) & 0xFF;
		}
		else {				///�����ƶ�����22λ�������ȷ���������ȫΪ0�����
			//����
			memset(hex, 0x00, sizeof(uint8_t) * 4);
			//���λ��1
			hex[0] = 0x01;
		}
		_Ele convert{};
		hex2num<_Ele>(hex, &convert);
		return convert;
	}

	//����
	return _Ele(1);
}

/*
* @brief
* �������������
* @param
* list: Ԫ���б�
* @param
* begin: ������ʼλ��
* @param
* N: �б���
* @param
* aux: �������飬��־��Щ���ֱ�ѡȡ
* @param
* m: ��ʾѡȡ�˶���Ԫ��
* @param
* M: Ҫѡȡ����Ԫ��
* @param
* result: ����洢����
* @return
* ��
*/
template<typename Ty, typename InnerList, typename ReList>
static void combination_aux(const Container1D<Ty>& list, const size_t begin, const size_t N, size_t aux[], size_t m, const size_t M, ReList& result) {
	for (size_t i = begin; i <= N - M + m; i++) {    // ��ǰ���
		if (m < M) {
			aux[m] = i;                         // ѡ��� m ��Ԫ��
		}

		if (m < M - 1) {                          // ûѡ����, �����µ� input[i+1..N] ��ѡ�����µ�Ԫ��
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
* �ӳ���ΪN���б���ѡ��M��Ԫ��
* @param
* list: �б�
* @param
* M: ��Ҫѡ����Ԫ�ظ���
* @return
* ����ѡȡ���
*/
template<typename Ty, typename InnerList, typename ReList>
ReList combine(const Container1D<Ty>& list, const size_t M) {
	/// <summary>
	/// InnerList Ϊ�����б�
	/// ReList Ϊ˫���б����ڲ�ΪInnerList����
	/// </summary>
	size_t* aux = new size_t[M]{};      //��������
	ReList result{};
	combination_aux<Ty, InnerList, ReList>(list, 0, list.len(), aux, 0, M, result);
	delete[] aux;
	return result;
}

/*
* @brief
* Ѱ��һά����Ԫ�����ֵ
* @param
* list: һά����
* @return
* ���ֵ��������������
*/
template<typename _Ele>
Point<size_t, const _Ele&> max(const Container1D<_Ele>& list) {
	size_t len = list.len();
	if (len == 0) {
		emit(MathError("�����б���Ϊ0"));
	}
	//���ֵ����
	size_t index = 0;
	//���ֵ
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
* Ѱ��һά����Ԫ�����ֵ
* @param
* list: һά����
* @param
* method: ����ָ��
* @return
* ���ֵ��������������
*/
template<typename _Ele, typename _F>
Point<size_t, const _Ele&> max(const Container1D<_Ele>& list, _F method) {
	size_t len = list.len();
	if (len == 0) {
		emit(MathError("�����б���Ϊ0"));
	}
	//���ֵ����
	size_t index = 0;
	//���ֵ
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
* Ѱ��һά����Ԫ����Сֵ
* @param
* list: һά����
* @param
* method: ����ָ��
* @return
* ��Сֵ��������������
*/
template<typename _Ele, typename _F>
Point<size_t, const _Ele&> min(const Container1D<_Ele>& list, _F method) {
	size_t len = list.len();
	if (len == 0) {
		emit(MathError("�����б���Ϊ0"));
	}
	//���ֵ����
	size_t index = 0;
	//���ֵ
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
* Ѱ��һά����Ԫ����Сֵ
* @param
* list: һά����
* @return
* ��Сֵ��������������
*/
template<typename _Ele>
Point<size_t, const _Ele&> min(const Container1D<_Ele>& list) {
	size_t len = list.len();
	if (len == 0) {
		emit(MathError("�����б���Ϊ0"));
	}
	//���ֵ����
	size_t index = 0;
	//���ֵ
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
* ��������Ԫ�صĺ�
* @param
* list: ����
* @return
* Ԫ��֮��
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
* ��������Ԫ�صĻ�
* @param
* list: ����
* @return
* Ԫ��֮��
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
* ���򣬸ı�ԭ������Ԫ��˳��
* @param
* list: �б�
* @param
* flag: 0��ʾ����1��ʾ����
* @return
* ��
*/
template<typename _Ele>
void sort(Container1D<_Ele>& list, bool flag) {
	size_t N = list.len();
	if (N == 0 || N == 1) {
		return;
	}
	//��ѭ���Ƿ���Ԫ�ؽ���
	bool exchange = false;
	//����
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
				if (exchange == false) {		//�����ѭ��û��Ԫ�ؽ��������ʾ�Ѿ��������
					return;
				}
			}
		}
	}
	//����
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
