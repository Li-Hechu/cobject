#pragma once

#ifndef STRING_H
#define STRING_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "cobject.h"
#include "vector.h"

/*字符串类*/
class String : public CObject
{
public:
	friend String operator + (const String&, const char*);
	friend String operator + (const String&, const String&);
	friend String operator + (const char*, const String&);
	friend String operator * (const String&, size_t);
	friend String operator * (size_t, const String&);
	friend void operator += (String&, const char*);
	friend void operator += (String&, const String&);
	friend void operator *= (String&, size_t);
	friend bool operator > (const String&, const String&);
	friend bool operator >= (const String&, const String&);
	friend bool operator < (const String&, const String&);
	friend bool operator <= (const String&, const String&);
	friend bool operator == (const String&, const String&);
	friend ostream& operator << (ostream&, const String&);
	friend String& operator <<(String&, const String&);
	friend String& operator <<(String&, const char*);
public:
	/*
	* @brief
	* 默认构造函数
	*/
	String();
	/*
	* @brief
	* 从c语言字符串创建string类
	*/
	String(const char* c_str);
	/*
	* @brief
	* 拷贝构造函数
	*/
	String(const String& str);
	/*
	* @brief
	* 析构函数
	*/
	~String();
	/*
	* @brief
	* 获取字符串长度
	* @param
	* 无
	* @return
	* 长度
	*/
	size_t len() const;
	/*
	* @brief
	* 将字符串转换为c语言风格字符串
	* @param
	* 无
	* @return
	* 转换后的c语言字符串
	*/
	char* toChar() const;
	/*
	* @brief
	* 追加字符串
	* @param
	* str : String类型字符串
	* @return
	* 无
	*/
	virtual void append(const String& str);
	/*
	* @brief
	* 追加字符串
	* @param
	* str : c语言风格字符串
	* @return
	* 无
	*/
	virtual void append(const char* str);
	/*
	* @brief
	* 按照给定字符拆分字符串
	* @param
	* ch : 给定的间隔字符
	* @return
	* 拆分后的字符串每个部分
	*/
	Vector<String> split(const char ch);
	/*
	* @brief
	* 字符串切片
	* @param
	* start : 起始索引，包含
	* @param
	* end : 结束索引，不包含
	* @return
	* 切片出的字符串
	*/
	String slice(size_t start, size_t end);
	/*
	* @brief
	* 判断字符串中是否含有某个子字符串，需要全字匹配
	* @param
	* str : 子字符串
	* @return
	* 存在返回真，否则为假
	*/
	bool have(const char* str) const;
	/*
	* @brief
	* 判断一个字符串是否以给定字符串结尾
	* @param
	* str: 字符串
	* @return
	* 1表示以给定字符串结尾，0表示不以给定字符串结尾
	*/
	bool endswith(const char* str) const;
	/*
	* @brief
	* 获取索引对应的字符
	* @param
	* index: 索引
	* @return
	* 该索引对应的字符
	*/
	char at(const size_t index) const;
	/*
	* @brief
	* 获取索引对应的字符
	* @param
	* index: 索引
	* @return
	* 该索引对应的字符
	*/
	char operator[](const size_t index) const;
	/*
	* @brief
	* 深拷贝赋值
	* @param
	* str: 另一个字符串
	* @return
	* 无
	*/
	void operator=(const String& str);
	/*
	* @brief
	* 深拷贝赋值
	* @param
	* str: 另一个字符串
	* @return
	* 无
	*/
	void operator=(const char* str);
protected:
	//容器
	char* container;
	//长度
	size_t length;
};


/*c语言风格字符串相关操作函数*/
namespace c_string {
	/*
	* @brief
	* 判断字符是否是数字
	* @param
	* ch : 字符
	* @return
	* 1表示字符为数字，0表示不是
	*/
	bool isDigit(const char ch);
	/*
	* @brief
	* 判断字符串是否全是数字
	* @param
	* str : 字符串
	* @return
	* 1表示字符串全为数字，0表示不是
	*/
	bool isDigit(const char* str);
	/*
	* @brief
	* 判断字符是否为字母
	* @param
	* ch : 字符
	* @return
	* 1表示字符为字母，0表示不是
	*/
	bool isAlpha(const char ch);
	/*
	* @brief
	* 判断字符串是否全是字母
	* @param
	* str : 字符串
	* @return
	* 1表示字符串全为字母，0表示不是
	*/
	bool isAlpha(const char* str);
	/*
	* @brief
	* 判断字符是否为字母或者数字
	* @param
	* ch : 字符
	* @return
	* 1表示字符全为字母或者数字，0表示不是
	*/
	bool isAlnum(const char ch);
	/*
	* @brief
	* 判断字符串是否为字母或者数字
	* @param
	* ch : 字符串
	* @return
	* 1表示字符全为字母或者数字，0表示不是
	*/
	bool isAlnum(const char* str);
	/*
	* @brief
	* 判断字符是否小写
	* @param
	* ch : 字符
	* @return
	* 1表示小写，0则不是
	*/
	bool isLower(const char ch);
	/*
	* @brief
	* 判断字符串是否全部小写
	* @param
	* ch : 字符串
	* @return
	* 1表示字符串全部小写，0则不是
	*/
	bool isLower(const char* str);
	/*
	* @brief
	* 判断字符是否大写
	* @param
	* ch : 字符
	* @return
	* 1表示大写，0则不是
	*/
	bool isUpper(const char ch);
	/*
	* @brief
	* 判断字符串是否全部大写
	* @param
	* str : 字符串
	* @return
	* 1表示字符串全部大写，0则不是
	*/
	bool isUpper(const char* str);
	/*
	* @brief
	* 将字符改为小写，若不为字母，则原样输出
	* @param
	* ch : 字符
	* @return
	* 字符字母对应的小写
	*/
	char lower(const char ch);
	/*
	* @brief
	* 将字符串改为小写
	* @param
	* str : 字符串
	* @return
	* 无
	*/
	void lower(char* ch);
	/*
	* @brief
	* 将字符改为大写，若不为字母，则原样输出
	* @param
	* ch : 字符
	* @return
	* 字符字母对应的大写
	*/
	char upper(const char ch);
	/*
	* @brief
	* 将字符串改为大写
	* @param
	* str : 字符串
	* @return
	* 无
	*/
	void upper(char* str);
	/*
	* @brief
	* 字符串拼接
	* @param
	* str1 : 字符串1
	* @param
	* str2 : 字符串2
	* @return
	* 拼接后的字符串
	*/
	char* stringcat(const char* str1, const char* str2);

	/*
	* @brief
	* 字符串复制
	* @param
	* str : 需要复制的字符串
	* @return
	* 复制后的字符串
	*/
	char* stringcpy(const char* str);
}

#endif
