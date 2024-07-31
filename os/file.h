#pragma once

#ifndef FILE_H
#define FILE_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "../vector.h"
#include "../string.h"

/*�ļ���*/
class File;

typedef struct FileLine {
	long long forwardsize;
	String str;
}FileLine;

/*����ļ�һ������*/
ostream& operator << (ostream& out, const FileLine& line);

class File : public CObject{
public:
	//�ļ�ָ��λ��
	typedef enum FilePtrPlace {
		Start,	//�ļ���ͷ
		End		//�ļ���β
	}FilePtrPlace;

	//�ļ���ģʽ
	typedef enum FileOpenMode {
		Read = 0x01,			//ֻ��
		Write = 0x02,			//ֻд
		ReadWrite = 0x04,		//��д
		Append = 0x08,			//׷��
		Binary = 0x10			//������
	}FileOpenMode;

	/*�ļ���ģʽ*/
	typedef unsigned int OpenModeType;
protected:
	//�ļ�״̬
	typedef enum FileState {
		Open,	//��
		Close	//�ر�
	}FileState;
public:
	/*
	* @brief
	* ����ļ�����
	*/
	friend ostream& operator << (ostream& out, const File& file);
	/*
	* @brief
	* ��ֵ
	*/
	void operator = (const File& fp);
public:
	/*
	* @brief
	* Ĭ�Ϲ��캯��
	*/
	File();
	/*
	* @brief
	* ���ļ�
	* @param
	* name : �ļ���
	* mode : �ļ���ģʽ
	* @return
	* �Ƿ�򿪳ɹ�
	*/
	bool open(const char* name, OpenModeType mode);
	/*
	* @brief
	* ��ȡ�ļ���С
	* @param
	* ��
	* @return
	* �ļ��ֽ���
	*/
	long long size() const;
	/*
	* @brief
	* ��ȡ�ļ�����
	* @param
	* ��
	* @return
	* �ļ�����
	*/
	long line() const;
	/*
	* @brief
	* �ƶ��ļ�ָ��
	* @param
	* byte ���ļ�ָ������׼���ֽ���������0��
	* origin : ָ���ƶ���׼
	* @return
	* ��
	*/
	void move(long byte, FilePtrPlace origin) const;
	/*
	* @brief
	* �ƶ��ļ�ָ�뵽��ͷ���߽�β
	* @param
	* origin : �ļ���ͷ���߽�β
	* @return
	* ��
	*/
	void move(FilePtrPlace origin) const;
	/*
	* @brief
	* ��ȡ�ļ�ָ�뵱ǰλ��
	* @param
	* ��
	* @return
	* �ļ���ǰ���ֽ���
	*/
	long long tell() const;
	/*
	* @brief
	* �ж��ļ��Ƿ�Ϊ��
	* @param
	* ��
	* @return
	* 1��ʾΪ�գ�0��ʾ�ǿ�
	*/
	bool isEmpty() const;
	/*
	* @brief
	* ָ���Ƿ񵽴��ļ���β
	* @param
	* ��
	* @return
	* 1��ʾ�����β��0��ʾû�н�β
	*/
	bool eof() const;
	/*
	* @biref
	* ��ȡ�ļ�һ������
	* @param
	* ������
	* @return
	* FileLine�ṹ�壬��������ǰ����ֽ����Լ���������
	*/
	FileLine getline(long index);
	/*
	* @brief
	* ��ȡ������
	* @param
	* ��
	* @return
	* �����е��б�
	*/
	Vector<String> getlines();
	/*
	* @brief
	* ��ȡ�ļ�
	* @param
	* buffer : ������
	* @param
	* size : ����Ԫ�ش�С
	* @param
	* count : Ԫ�ظ���
	* @return
	* �ɹ���ȡ���������е�Ԫ�ظ���
	*/
	size_t read(void* buffer, size_t size, size_t count) const;
	/*
	* @brief
	* д���ļ�
	* @param
	* buffer : ��д�������
	* @param
	* size : ����Ԫ�ش�С
	* @param
	* count : Ԫ�ظ���
	* @return
	* �ɹ�д���Ԫ�ظ���
	*/
	size_t write(const void* buffer, size_t size, size_t count) const;
	/*
	* @brief
	* �ر��ļ�
	* @param
	* ��
	* @return
	* ��
	*/
	void close();
protected:
	/*
	* @brief
	* ��ö����ת��Ϊ�ַ���
	* @param
	* mode : �򿪷�ʽö����
	* @return
	* ��򿪷�ʽ���Ӧ���ַ���
	*/
	const char* ModeConvert(OpenModeType mode);
private:
	FILE* fptr;				//�ļ�ָ��
	const char* filename;	//�ļ�����
	OpenModeType filemode;	//�ļ�������
	FileState filestate;	//�ļ���״̬
};


#endif
