#pragma once

#ifndef ASSERT_H
#define ASSERT_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "../cobject.h"

static const char MatrixErrorHeader[ERROR_HEADER_MAXLEN] = "MatrixError";
/*矩阵错误*/
class MatrixError : public Error<MatrixErrorHeader> {
public:
	inline MatrixError(const char* info) : Error(info) {

	}
};

#define _assert_matrix_add_(matobj1, matobj2) \
{\
	if (matobj1.row() != matobj2.row() || matobj1.column() != matobj2.column()) {\
		char info[100]{};\
		sprintf_s(info, "形状(%lld,%lld)与形状(%lld,%lld)不一致，不可相加", matobj1.row(), matobj1.column(), matobj2.row(), matobj2.column());\
		emit(MatrixError(info));\
	}\
}

#define _assert_matrix_sub_(matobj1, matobj2) \
{\
	if (matobj1.row() != matobj2.row() || matobj1.column() != matobj2.column()) {\
		char info[100]{};\
		sprintf_s(info, "形状(%lld,%lld)与形状(%lld,%lld)不一致，不可相减", matobj1.row(), matobj1.column(), matobj2.row(), matobj2.column());\
		emit(MatrixError(info));\
	}\
}

#define _assert_matrix_multi_(matobj1, matobj2) \
{\
	if (matobj1.column() != matobj2.row()) {\
		char info[100]{};\
		sprintf_s(info, "形状(%lld,%lld)与形状(%lld,%lld)不一致，不可相乘", matobj1.row(), matobj1.column(), matobj2.row(), matobj2.column());\
		emit(MatrixError(info));\
	}\
}

#define _assert_matrix_square_ptr_(matobj) \
{\
	if (matobj->rowCount != matobj->colCount) {\
		char info[100]{};\
		sprintf_s(info, "矩阵具有形状(%lld,%lld)，不是方阵", matobj->rowCount, matobj->colCount);\
		emit(MatrixError(info));\
	}\
}

#define _assert_matrix_square_(matobj) \
{\
	if (matobj.row() != matobj.column()) {\
		char info[100]{};\
		sprintf_s(info, "矩阵具有形状(%lld,%lld)，不是方阵", matobj.row(), matobj.column());\
		emit(MatrixError(info));\
	}\
}

#define _assert_row_vector_transmission_(vecobj) \
{\
	if(vecobj.row() != 1){\
		char info[50]{};\
		sprintf_s(info,"矩阵对象具有形状(%lld,%lld)，不可转换为行向量",vecobj.row(),vecobj.column());\
		emit(MatrixError(info));\
	}\
}

#define _assert_column_vector_transmission_(vecobj)\
{\
	if(vecobj.column() != 1){\
		char info[50]{};\
		sprintf_s(info,"矩阵对象具有形状(%lld,%lld)，不可转换为列向量",vecobj.row(),vecobj.column());\
		emit(MatrixError(info));\
	}\
}

#define _assert_row_repalce_ptr_(vecobj, matptr)\
{\
	if(vecobj.size() != matptr->colCount){\
		char info[50]{};\
		sprintf_s(info,"向量长度 %lld 和矩阵列数 %lld 不兼容，无法替换",vecobj.size(),matptr->colCount);\
		emit(MatrixError(info));\
	}\
}

#define _assert_column_repalce_ptr(vecobj,matptr)\
{\
	if(vecobj.size() != matptr->rowCount){\
		char info[50]{};\
		sprintf_s(info,"向量长度 %lld 和 矩阵行数 %lld 不兼容，无法替换",vecobj.size(),matptr->rowCount);\
	}\
}

#endif // !ASSERT_H
