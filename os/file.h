#pragma once

#ifndef FILE_H
#define FILE_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "../vector.h"
#include "../string.h"

/*文件类*/
class File;

typedef struct FileLine {
	long long forwardsize;
	String str;
}FileLine;

/*输出文件一行内容*/
ostream& operator << (ostream& out, const FileLine& line);

class File : public CObject{
public:
	//文件指针位置
	typedef enum FilePtrPlace {
		Start,	//文件开头
		End		//文件结尾
	}FilePtrPlace;

	//文件打开模式
	typedef enum FileOpenMode {
		Read = 0x01,			//只读
		Write = 0x02,			//只写
		ReadWrite = 0x04,		//读写
		Append = 0x08,			//追加
		Binary = 0x10			//二进制
	}FileOpenMode;

	/*文件打开模式*/
	typedef unsigned int OpenModeType;
protected:
	//文件状态
	typedef enum FileState {
		Open,	//打开
		Close	//关闭
	}FileState;
public:
	/*
	* @brief
	* 输出文件内容
	*/
	friend ostream& operator << (ostream& out, const File& file);
	/*
	* @brief
	* 赋值
	*/
	void operator = (const File& fp);
public:
	/*
	* @brief
	* 默认构造函数
	*/
	File();
	/*
	* @brief
	* 打开文件
	* @param
	* name : 文件名
	* mode : 文件打开模式
	* @return
	* 是否打开成功
	*/
	bool open(const char* name, OpenModeType mode);
	/*
	* @brief
	* 获取文件大小
	* @param
	* 无
	* @return
	* 文件字节数
	*/
	long long size() const;
	/*
	* @brief
	* 获取文件行数
	* @param
	* 无
	* @return
	* 文件行数
	*/
	long line() const;
	/*
	* @brief
	* 移动文件指针
	* @param
	* byte ：文件指针距离基准的字节数（大于0）
	* origin : 指针移动基准
	* @return
	* 无
	*/
	void move(long byte, FilePtrPlace origin) const;
	/*
	* @brief
	* 移动文件指针到开头或者结尾
	* @param
	* origin : 文件开头或者结尾
	* @return
	* 无
	*/
	void move(FilePtrPlace origin) const;
	/*
	* @brief
	* 获取文件指针当前位置
	* @param
	* 无
	* @return
	* 文件当前的字节数
	*/
	long long tell() const;
	/*
	* @brief
	* 判断文件是否为空
	* @param
	* 无
	* @return
	* 1表示为空，0表示非空
	*/
	bool isEmpty() const;
	/*
	* @brief
	* 指针是否到达文件结尾
	* @param
	* 无
	* @return
	* 1表示到达结尾，0表示没有结尾
	*/
	bool eof() const;
	/*
	* @biref
	* 获取文件一行内容
	* @param
	* 行索引
	* @return
	* FileLine结构体，包括该行前面的字节数以及该行内容
	*/
	FileLine getline(long index);
	/*
	* @brief
	* 获取所有行
	* @param
	* 无
	* @return
	* 所有行的列表
	*/
	Vector<String> getlines();
	/*
	* @brief
	* 读取文件
	* @param
	* buffer : 缓冲区
	* @param
	* size : 单个元素大小
	* @param
	* count : 元素个数
	* @return
	* 成功读取到缓冲区中的元素个数
	*/
	size_t read(void* buffer, size_t size, size_t count) const;
	/*
	* @brief
	* 写入文件
	* @param
	* buffer : 待写入的数据
	* @param
	* size : 单个元素大小
	* @param
	* count : 元素个数
	* @return
	* 成功写入的元素个数
	*/
	size_t write(const void* buffer, size_t size, size_t count) const;
	/*
	* @brief
	* 关闭文件
	* @param
	* 无
	* @return
	* 无
	*/
	void close();
protected:
	/*
	* @brief
	* 将枚举类转换为字符串
	* @param
	* mode : 打开方式枚举类
	* @return
	* 与打开方式相对应的字符串
	*/
	const char* ModeConvert(OpenModeType mode);
private:
	FILE* fptr;				//文件指针
	const char* filename;	//文件名称
	OpenModeType filemode;	//文件打开类型
	FileState filestate;	//文件打开状态
};


#endif
