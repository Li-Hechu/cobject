#pragma once

#ifndef SYSTEM_H
#define SYSTEM_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "../vector.h"
#include "../string.h"

/*CPU信息*/
typedef struct CPUInfo {
	//制造商
	char vendor[0x20];
	//型号
	char brand[0x40];
}CPUInfo;

/*输出CPU信息*/
ostream& operator<<(ostream& out, const CPUInfo& cpuinfo);

typedef Vector<String> fdlist;

/*目录信息*/
typedef struct Directory {
	fdlist file;
	fdlist direct;
}Directory;

/*输出目录信息*/
ostream& operator<<(ostream& out, const Directory& direct);

/*
* @brief
* 获取CPU信息
* @param
* 无
* @return
* CPU信息结构体
*/
CPUInfo getCPUInfo();

/*
* @brief
* 查找目录下的文件或者子目录，需要使用通配符
* @param
* path : 路径，包含通配符
* @return
* 文件名称或者目录名称
* @note
* 1.想要查找所有文件及文件夹，使用: *.*
* 2.查找某一类型的文件，使用: *.<后缀>
* 3.查找某个具体文件，使用: <文件名>.<后缀>
*/
fdlist dirfilter(const char* path);

/*
* @brief
* 遍历目录下所有文件及文件夹
* @param
* path : 目录路径
* @return
* 结构体，包含文件列表和文件夹列表
*/

Directory dirwalk(const char* dirpath);

/*
* @brief
* 判断某个文件或者文件夹是否存在
* @param
* path: 文件或者目录路径
* @return
* 1表示存在，0表示不存在
*/
bool exists(const char* path);

/*
* @brief
* 判断是路径是否为文件
* @param
* path: 路径
* @return
* 0表示不为文件或不存在，1表示为文件
*/
bool isfile(const char* path);

/*
* @brief
* 判断是路径是否为目录
* @param
* path: 路径
* @return
* 0表示不为目录或不存在，1表示为目录
*/
bool isdir(const char* path);

#endif // !SYSTEM_H
