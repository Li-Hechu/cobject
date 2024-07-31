#pragma once

#ifndef SYSTEM_H
#define SYSTEM_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "../vector.h"
#include "../string.h"

/*CPU��Ϣ*/
typedef struct CPUInfo {
	//������
	char vendor[0x20];
	//�ͺ�
	char brand[0x40];
}CPUInfo;

/*���CPU��Ϣ*/
ostream& operator<<(ostream& out, const CPUInfo& cpuinfo);

typedef Vector<String> fdlist;

/*Ŀ¼��Ϣ*/
typedef struct Directory {
	fdlist file;
	fdlist direct;
}Directory;

/*���Ŀ¼��Ϣ*/
ostream& operator<<(ostream& out, const Directory& direct);

/*
* @brief
* ��ȡCPU��Ϣ
* @param
* ��
* @return
* CPU��Ϣ�ṹ��
*/
CPUInfo getCPUInfo();

/*
* @brief
* ����Ŀ¼�µ��ļ�������Ŀ¼����Ҫʹ��ͨ���
* @param
* path : ·��������ͨ���
* @return
* �ļ����ƻ���Ŀ¼����
* @note
* 1.��Ҫ���������ļ����ļ��У�ʹ��: *.*
* 2.����ĳһ���͵��ļ���ʹ��: *.<��׺>
* 3.����ĳ�������ļ���ʹ��: <�ļ���>.<��׺>
*/
fdlist dirfilter(const char* path);

/*
* @brief
* ����Ŀ¼�������ļ����ļ���
* @param
* path : Ŀ¼·��
* @return
* �ṹ�壬�����ļ��б���ļ����б�
*/

Directory dirwalk(const char* dirpath);

/*
* @brief
* �ж�ĳ���ļ������ļ����Ƿ����
* @param
* path: �ļ�����Ŀ¼·��
* @return
* 1��ʾ���ڣ�0��ʾ������
*/
bool exists(const char* path);

/*
* @brief
* �ж���·���Ƿ�Ϊ�ļ�
* @param
* path: ·��
* @return
* 0��ʾ��Ϊ�ļ��򲻴��ڣ�1��ʾΪ�ļ�
*/
bool isfile(const char* path);

/*
* @brief
* �ж���·���Ƿ�ΪĿ¼
* @param
* path: ·��
* @return
* 0��ʾ��ΪĿ¼�򲻴��ڣ�1��ʾΪĿ¼
*/
bool isdir(const char* path);

#endif // !SYSTEM_H
