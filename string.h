#pragma once

#ifndef STRING_H
#define STRING_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "cobject.h"
#include "vector.h"

/*�ַ�����*/
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
	* Ĭ�Ϲ��캯��
	*/
	String();
	/*
	* @brief
	* ��c�����ַ�������string��
	*/
	String(const char* c_str);
	/*
	* @brief
	* �������캯��
	*/
	String(const String& str);
	/*
	* @brief
	* ��������
	*/
	~String();
	/*
	* @brief
	* ��ȡ�ַ�������
	* @param
	* ��
	* @return
	* ����
	*/
	size_t len() const;
	/*
	* @brief
	* ���ַ���ת��Ϊc���Է���ַ���
	* @param
	* ��
	* @return
	* ת�����c�����ַ���
	*/
	char* toChar() const;
	/*
	* @brief
	* ׷���ַ���
	* @param
	* str : String�����ַ���
	* @return
	* ��
	*/
	virtual void append(const String& str);
	/*
	* @brief
	* ׷���ַ���
	* @param
	* str : c���Է���ַ���
	* @return
	* ��
	*/
	virtual void append(const char* str);
	/*
	* @brief
	* ���ո����ַ�����ַ���
	* @param
	* ch : �����ļ���ַ�
	* @return
	* ��ֺ���ַ���ÿ������
	*/
	Vector<String> split(const char ch);
	/*
	* @brief
	* �ַ�����Ƭ
	* @param
	* start : ��ʼ����������
	* @param
	* end : ����������������
	* @return
	* ��Ƭ�����ַ���
	*/
	String slice(size_t start, size_t end);
	/*
	* @brief
	* �ж��ַ������Ƿ���ĳ�����ַ�������Ҫȫ��ƥ��
	* @param
	* str : ���ַ���
	* @return
	* ���ڷ����棬����Ϊ��
	*/
	bool have(const char* str) const;
	/*
	* @brief
	* �ж�һ���ַ����Ƿ��Ը����ַ�����β
	* @param
	* str: �ַ���
	* @return
	* 1��ʾ�Ը����ַ�����β��0��ʾ���Ը����ַ�����β
	*/
	bool endswith(const char* str) const;
	/*
	* @brief
	* ��ȡ������Ӧ���ַ�
	* @param
	* index: ����
	* @return
	* ��������Ӧ���ַ�
	*/
	char at(const size_t index) const;
	/*
	* @brief
	* ��ȡ������Ӧ���ַ�
	* @param
	* index: ����
	* @return
	* ��������Ӧ���ַ�
	*/
	char operator[](const size_t index) const;
	/*
	* @brief
	* �����ֵ
	* @param
	* str: ��һ���ַ���
	* @return
	* ��
	*/
	void operator=(const String& str);
	/*
	* @brief
	* �����ֵ
	* @param
	* str: ��һ���ַ���
	* @return
	* ��
	*/
	void operator=(const char* str);
protected:
	//����
	char* container;
	//����
	size_t length;
};


/*c���Է���ַ�����ز�������*/
namespace c_string {
	/*
	* @brief
	* �ж��ַ��Ƿ�������
	* @param
	* ch : �ַ�
	* @return
	* 1��ʾ�ַ�Ϊ���֣�0��ʾ����
	*/
	bool isDigit(const char ch);
	/*
	* @brief
	* �ж��ַ����Ƿ�ȫ������
	* @param
	* str : �ַ���
	* @return
	* 1��ʾ�ַ���ȫΪ���֣�0��ʾ����
	*/
	bool isDigit(const char* str);
	/*
	* @brief
	* �ж��ַ��Ƿ�Ϊ��ĸ
	* @param
	* ch : �ַ�
	* @return
	* 1��ʾ�ַ�Ϊ��ĸ��0��ʾ����
	*/
	bool isAlpha(const char ch);
	/*
	* @brief
	* �ж��ַ����Ƿ�ȫ����ĸ
	* @param
	* str : �ַ���
	* @return
	* 1��ʾ�ַ���ȫΪ��ĸ��0��ʾ����
	*/
	bool isAlpha(const char* str);
	/*
	* @brief
	* �ж��ַ��Ƿ�Ϊ��ĸ��������
	* @param
	* ch : �ַ�
	* @return
	* 1��ʾ�ַ�ȫΪ��ĸ�������֣�0��ʾ����
	*/
	bool isAlnum(const char ch);
	/*
	* @brief
	* �ж��ַ����Ƿ�Ϊ��ĸ��������
	* @param
	* ch : �ַ���
	* @return
	* 1��ʾ�ַ�ȫΪ��ĸ�������֣�0��ʾ����
	*/
	bool isAlnum(const char* str);
	/*
	* @brief
	* �ж��ַ��Ƿ�Сд
	* @param
	* ch : �ַ�
	* @return
	* 1��ʾСд��0����
	*/
	bool isLower(const char ch);
	/*
	* @brief
	* �ж��ַ����Ƿ�ȫ��Сд
	* @param
	* ch : �ַ���
	* @return
	* 1��ʾ�ַ���ȫ��Сд��0����
	*/
	bool isLower(const char* str);
	/*
	* @brief
	* �ж��ַ��Ƿ��д
	* @param
	* ch : �ַ�
	* @return
	* 1��ʾ��д��0����
	*/
	bool isUpper(const char ch);
	/*
	* @brief
	* �ж��ַ����Ƿ�ȫ����д
	* @param
	* str : �ַ���
	* @return
	* 1��ʾ�ַ���ȫ����д��0����
	*/
	bool isUpper(const char* str);
	/*
	* @brief
	* ���ַ���ΪСд������Ϊ��ĸ����ԭ�����
	* @param
	* ch : �ַ�
	* @return
	* �ַ���ĸ��Ӧ��Сд
	*/
	char lower(const char ch);
	/*
	* @brief
	* ���ַ�����ΪСд
	* @param
	* str : �ַ���
	* @return
	* ��
	*/
	void lower(char* ch);
	/*
	* @brief
	* ���ַ���Ϊ��д������Ϊ��ĸ����ԭ�����
	* @param
	* ch : �ַ�
	* @return
	* �ַ���ĸ��Ӧ�Ĵ�д
	*/
	char upper(const char ch);
	/*
	* @brief
	* ���ַ�����Ϊ��д
	* @param
	* str : �ַ���
	* @return
	* ��
	*/
	void upper(char* str);
	/*
	* @brief
	* �ַ���ƴ��
	* @param
	* str1 : �ַ���1
	* @param
	* str2 : �ַ���2
	* @return
	* ƴ�Ӻ���ַ���
	*/
	char* stringcat(const char* str1, const char* str2);

	/*
	* @brief
	* �ַ�������
	* @param
	* str : ��Ҫ���Ƶ��ַ���
	* @return
	* ���ƺ���ַ���
	*/
	char* stringcpy(const char* str);
}

#endif
