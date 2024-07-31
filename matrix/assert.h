#pragma once

#ifndef ASSERT_H
#define ASSERT_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "../cobject.h"

static const char MatrixErrorHeader[ERROR_HEADER_MAXLEN] = "MatrixError";
/*�������*/
class MatrixError : public Error<MatrixErrorHeader> {
public:
	inline MatrixError(const char* info) : Error(info) {

	}
};

#define _assert_matrix_add_(matobj1, matobj2) \
{\
	if (matobj1.row() != matobj2.row() || matobj1.column() != matobj2.column()) {\
		char info[100]{};\
		sprintf_s(info, "��״(%lld,%lld)����״(%lld,%lld)��һ�£��������", matobj1.row(), matobj1.column(), matobj2.row(), matobj2.column());\
		emit(MatrixError(info));\
	}\
}

#define _assert_matrix_sub_(matobj1, matobj2) \
{\
	if (matobj1.row() != matobj2.row() || matobj1.column() != matobj2.column()) {\
		char info[100]{};\
		sprintf_s(info, "��״(%lld,%lld)����״(%lld,%lld)��һ�£��������", matobj1.row(), matobj1.column(), matobj2.row(), matobj2.column());\
		emit(MatrixError(info));\
	}\
}

#define _assert_matrix_multi_(matobj1, matobj2) \
{\
	if (matobj1.column() != matobj2.row()) {\
		char info[100]{};\
		sprintf_s(info, "��״(%lld,%lld)����״(%lld,%lld)��һ�£��������", matobj1.row(), matobj1.column(), matobj2.row(), matobj2.column());\
		emit(MatrixError(info));\
	}\
}

#define _assert_matrix_square_ptr_(matobj) \
{\
	if (matobj->rowCount != matobj->colCount) {\
		char info[100]{};\
		sprintf_s(info, "���������״(%lld,%lld)�����Ƿ���", matobj->rowCount, matobj->colCount);\
		emit(MatrixError(info));\
	}\
}

#define _assert_matrix_square_(matobj) \
{\
	if (matobj.row() != matobj.column()) {\
		char info[100]{};\
		sprintf_s(info, "���������״(%lld,%lld)�����Ƿ���", matobj.row(), matobj.column());\
		emit(MatrixError(info));\
	}\
}

#define _assert_row_vector_transmission_(vecobj) \
{\
	if(vecobj.row() != 1){\
		char info[50]{};\
		sprintf_s(info,"������������״(%lld,%lld)������ת��Ϊ������",vecobj.row(),vecobj.column());\
		emit(MatrixError(info));\
	}\
}

#define _assert_column_vector_transmission_(vecobj)\
{\
	if(vecobj.column() != 1){\
		char info[50]{};\
		sprintf_s(info,"������������״(%lld,%lld)������ת��Ϊ������",vecobj.row(),vecobj.column());\
		emit(MatrixError(info));\
	}\
}

#define _assert_row_repalce_ptr_(vecobj, matptr)\
{\
	if(vecobj.size() != matptr->colCount){\
		char info[50]{};\
		sprintf_s(info,"�������� %lld �;������� %lld �����ݣ��޷��滻",vecobj.size(),matptr->colCount);\
		emit(MatrixError(info));\
	}\
}

#define _assert_column_repalce_ptr(vecobj,matptr)\
{\
	if(vecobj.size() != matptr->rowCount){\
		char info[50]{};\
		sprintf_s(info,"�������� %lld �� �������� %lld �����ݣ��޷��滻",vecobj.size(),matptr->rowCount);\
	}\
}

#endif // !ASSERT_H
