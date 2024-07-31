#pragma once

#ifndef MATRIXABSTYPE
#define MATRIXABSTYPE

#pragma comment(lib,"lib/cobjectLib.lib")
#include "../cobject.h"
#include "expresstree.h"

/*�������ͻ���*/
template<typename _Ele>
class MatrixAbsType : public Container2D<_Ele> {
	/*��������*/
	inline friend CommaInitializer<_Ele>& operator << (MatrixAbsType<_Ele>& mat, _Ele& ele) {
		mat.append(ele);
		delete mat.commainitializer;
		mat.commainitializer = new CommaInitializer<_Ele>(&mat);
		return *mat.commainitializer;
	}
	inline friend CommaInitializer<_Ele>& operator << (MatrixAbsType<_Ele>& mat, _Ele&& ele) {
		mat.append(ele);
		delete mat.commainitializer;
		mat.commainitializer = new CommaInitializer<_Ele>(&mat);
		return *mat.commainitializer;
	}
	/*�������*/
	inline friend ostream& operator << (ostream& out, const MatrixAbsType<_Ele>& mat) {
		//���������
		out << '[';
		for (size_t i = 0; i < mat.rowCount; i++) {
			//���ǵ�һ�У����һ���ո�
			if (i != 0) out << ' ';
			for (size_t j = 0; j < mat.colCount; j++) {
				//�����ÿ�е�һ������ǰ���������
				if (j == 0) out << '[';
				out << std::scientific << mat.container[i * mat.colCount + j];
				if (j < mat.colCount - 1) out << "  ";
				else out << ']';
			}
			if (i < mat.rowCount - 1) out << endl;
		}
		//���������
		out << ']' << endl;
		return out;
	}
public:
	//������״
	typedef Match<size_t, size_t> matShape;
	/*������ָ��*/
	class matRowPtr : public Container2D<_Ele>::Container2D_Ptr {
	public:
		/*����ָ�뼰�䳤�ȹ���*/
		inline matRowPtr(_Ele* pointer, size_t length) : Container2D<_Ele>::Container2D_Ptr(length) {
			this->ptr = pointer;
		}
		inline _Ele& operator[](const size_t index) const {
			if (index >= this->ptr_length) {
				emit(IndexError("����Խ��"));
			}
			return this->ptr[index];
		}
		inline void operator=(const MatrixAbsType<_Ele>::matRowPtr& rowptr) {
			//ָ�븳ֵ
			this->ptr = rowptr.ptr;
		}
	protected:
		/*��ָ��*/
		_Ele* ptr;
	};
public:
	/*Ĭ�Ϲ��캯��*/
	inline MatrixAbsType() : Container2D<_Ele>() {
		this->cur = 0;
		this->container = nullptr;
		this->commainitializer = nullptr;
	}
	/*ָ����״����*/
	inline MatrixAbsType(size_t row, size_t col) : Container2D<_Ele>(row, col) {
		this->cur = 0;
		this->container = new _Ele[row * col]{};
		this->commainitializer = nullptr;
	}
	/*ָ����״��Ԫ�ع���*/
	inline MatrixAbsType(size_t row, size_t col, std::initializer_list<_Ele> data) : Container2D<_Ele>(row, col) {
		this->cur = 0;
		this->container = new _Ele[row * col]{};
		this->commainitializer = nullptr;
		for (auto ele = data.begin(); ele != data.end(); ele++) {
			if (this->cur >= row * col) {
				return;
			}
			this->container[this->cur++] = *ele;
		}
	}
	/*�������*/
	inline MatrixAbsType(const MatrixAbsType<_Ele>& matrixtype) {
		this->rowCount = matrixtype.rowCount;
		this->colCount = matrixtype.colCount;
		this->cur = matrixtype.cur;
		this->commainitializer = nullptr;
		size_t len = this->rowCount * this->colCount;
		this->container = new _Ele[len]{};
		//Ԫ�ؿ���
		memcpy_s(this->container, sizeof(_Ele) * len, matrixtype.container, sizeof(_Ele) * len);
	}
	/*��������*/
	inline ~MatrixAbsType() {
		delete[] this->container;
		delete this->commainitializer;
	}
	/*
	* @brief
	* ˳���ʼ��
	* @param
	* var : �����Ԫ��
	* @return
	* ��
	*/
	inline virtual void append(const _Ele& var) {
		//���Ԫ��ȫ����ʼ�����
		if (this->cur >= this->rowCount * this->colCount) {
			return;
		}
		//���Ԫ��û�г�ʼ�����
		this->container[this->cur++] = var;
	}
	/*
	* @brief
	* ˳���ʼ��
	* @param
	* var : �����Ԫ��
	* @return
	* ��
	*/
	inline virtual void append(_Ele&& var) {
		//���Ԫ��ȫ����ʼ�����
		if (this->cur >= this->rowCount * this->colCount) {
			return;
		}
		//���Ԫ��û�г�ʼ�����
		this->container[this->cur++] = var;
	}
	/*
	* @brief
	* ͨ��������ȡԪ��
	* @param
	* r_index : ������
	* @param
	* c_index : ������
	* @return
	* ��λ���ϵ�Ԫ��
	*/
	inline virtual _Ele& at(const size_t r_index, const size_t c_index) const {
		//�ж�����
		if (r_index >= this->rowCount || c_index >= this->colCount) {
			emit(MatrixError("��������������Χ"));
		}
		return this->container[r_index * this->colCount + c_index];
	}
	/*
	* @brief
	* ��ȡ����һ��
	* @param
	* r_index : ������
	* @return
	* һ�е�Ԫ��
	*/
	virtual MatrixAbsType<_Ele>& getRow(const size_t r_index) {
		//�ж�����
		if (r_index >= this->rowCount) {
			emit(MatrixError("����������������Χ"));
		}
		//�����¾���
		MatrixAbsType<_Ele> *mat = new MatrixAbsType<_Ele>(1, this->colCount);
		//����Ԫ��
		memcpy_s(mat->container, this->colCount * sizeof(_Ele), \
			this->container + (r_index * this->colCount), this->colCount * sizeof(_Ele));
		return *mat;
	}
	/*
	* @brief
	* ��ȡ����һ��
	* @param
	* c_index : ������
	* @return
	* һ�е�Ԫ��
	*/
	inline virtual MatrixAbsType<_Ele>& getColumn(const size_t c_index) {
		//�ж�����
		if (c_index >= this->colCount) {
			emit(MatrixError("����������������Χ"));
		}
		//�����¾���
		MatrixAbsType<_Ele> *mat = new MatrixAbsType<_Ele>(this->rowCount, 1);
		//��ֵ
		for (size_t i = 0; i < this->rowCount; i++) {
			mat->container[i] = this->container[i * this->colCount + c_index];
		}
		//����
		return *mat;
	}
	/*
	* @brief
	* ��ȡ������״
	* @param
	* ��
	* @return
	* ������״
	*/
	inline matShape shape() const {
		return matShape(this->rowCount, this->colCount);
	}
	/*
	* @brief
	* ��ȡ������ָ��
	* @param
	* index : ������
	* @return
	* ��ָ������
	*/
	inline MatrixAbsType<_Ele>::matRowPtr operator[](const size_t index) const {
		return MatrixAbsType<_Ele>::matRowPtr(this->container + index * this->colCount, this->colCount);
	}
	/*
	* @brief
	* �����ֵ
	* @param
	* matobj : �������
	* @return
	* ��
	*/
	inline virtual void deepcopy(const MatrixAbsType<_Ele>& matobj) {
		delete[] this->container;
		delete this->commainitializer;
		this->container = new _Ele[matobj.rowCount * matobj.colCount];
		this->rowCount = matobj.rowCount;
		this->colCount = matobj.colCount;
		delete this->commainitializer;
		this->commainitializer = nullptr;
		this->cur = matobj.cur;
		size_t size = this->rowCount * this->colCount * sizeof(_Ele);
		memcpy_s(this->container, size, matobj.container, size);
	}
	/*
	* @brief
	* �н���
	* @param
	* mat : ����
	* @param
	* h1 : ��1
	* @param
	* h2 : ��2
	* @return
	* ��
	*/
	static void rowSwap(MatrixAbsType<_Ele>& mat, size_t h1, size_t h2) {
		if (h1 >= mat.rowCount || h2 >= mat.rowCount) {
			emit(MatrixError("������Խ��"));
		}
		//������
		_Ele* buffer = new _Ele[mat.colCount]{};
		//��������С
		size_t buffersize = sizeof(_Ele) * mat.colCount;
		//����
		memcpy_s(buffer, buffersize, mat.container + h1 * mat.colCount, buffersize);
		memcpy_s(mat.container + h1 * mat.colCount, buffersize, mat.container + h2 * mat.colCount, buffersize);
		memcpy_s(mat.container + h2 * mat.colCount, buffersize, buffer, buffersize);
		//�ڴ�ɾ��
		delete[] buffer;
	}
protected:
	/*Ԫ�������������ڴ�洢*/
	_Ele* container;
	/*��ǰ��ʼ����Ԫ�ظ���*/
	size_t cur;
	/*���ŷָ���*/
	CommaInitializer<_Ele>* commainitializer;
};


template <typename _Ele>
class MatrixXdType;

template<typename _Ele>
class VectorXdType;

template <typename _Ele>
class VectorRowType;

template <typename _Ele>
class VectorColumnType;


/*������������*/
template<typename _Ele>
class MatrixXdType : public MatrixAbsType<_Ele> {
	friend class VectorRow;
	friend class VectorColumn;
	friend class VectorRowI;
	friend class VectorColumnI;
	friend class Matrix;
	friend class MatrixI;
	template<typename _Ele>
	friend size_t _seek(const MatrixXdType<_Ele>& mat, size_t row);
	template<typename ty>
	friend void _sort(MatrixXdType<ty>& matrix, VectorXdType<ty>& vector);
	template<typename ty>
	friend VectorXdType<ty> _gauss(const MatrixXdType<ty>& matrix, const VectorXdType<ty>& vector);
	template<typename MatType, typename _Ele>
	friend MatType matrixConcat(const Container1D<MatrixXdType<_Ele>>& matlist, bool direct);
public:
	inline friend MatrixAddOperation< _Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>> operator +(const MatrixXdType<_Ele>& left, const MatrixXdType<_Ele>& right) {
		return MatrixAddOperation<_Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>>(left, right);
	}
	inline friend MatrixAddOperation< _Ele, MatrixOperation<_Ele>, MatrixXdType<_Ele>> operator +(const MatrixOperation<_Ele>& left, const MatrixXdType<_Ele>& right) {
		return MatrixAddOperation<_Ele, MatrixOperation<_Ele>, MatrixXdType<_Ele>>(left, right);
	}
	inline friend MatrixAddOperation< _Ele, MatrixXdType<_Ele>, MatrixOperation<_Ele>> operator +(const MatrixXdType<_Ele>& left, const MatrixOperation<_Ele>& right) {
		return MatrixAddOperation<_Ele, MatrixXdType<_Ele>, MatrixOperation<_Ele>>(left, right);
	}
	inline friend MatrixSubOperation< _Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>> operator -(const MatrixXdType<_Ele>& left, const MatrixXdType<_Ele>& right) {
		return MatrixSubOperation<_Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>>(left, right);
	}
	inline friend MatrixSubOperation< _Ele, MatrixOperation<_Ele>, MatrixXdType<_Ele>> operator -(const MatrixOperation<_Ele>& left, const MatrixXdType<_Ele>& right) {
		return MatrixSubOperation<_Ele, MatrixOperation<_Ele>, MatrixXdType<_Ele>>(left, right);
	}
	inline friend MatrixSubOperation< _Ele, MatrixXdType<_Ele>, MatrixOperation<_Ele>> operator -(const MatrixXdType<_Ele>& left, const MatrixOperation<_Ele>& right) {
		return MatrixSubOperation<_Ele, MatrixXdType<_Ele>, MatrixOperation<_Ele>>(left, right);
	}
	inline friend MatrixMultiOperation< _Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>> operator *(const MatrixXdType<_Ele>& left, const MatrixXdType<_Ele>& right) {
		return MatrixMultiOperation<_Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>>(left, right);
	}
	inline friend MatrixMultiOperation< _Ele, MatrixOperation<_Ele>, MatrixXdType<_Ele>> operator *(const MatrixOperation<_Ele>& left, const MatrixXdType<_Ele>& right) {
		return MatrixMultiOperation<_Ele, MatrixOperation<_Ele>, MatrixXdType<_Ele>>(left, right);
	}
	inline friend MatrixMultiOperation< _Ele, MatrixXdType<_Ele>, MatrixOperation<_Ele>> operator *(const MatrixXdType<_Ele>& left, const MatrixOperation<_Ele>& right) {
		return MatrixMultiOperation<_Ele, MatrixXdType<_Ele>, MatrixOperation<_Ele>>(left, right);
	}
	inline friend MatrixMultiNumberOperation<_Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>> operator *(const MatrixXdType<_Ele>& mat, _Ele var) {
		return MatrixMultiNumberOperation<_Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>>(var, mat);
	}
	inline friend MatrixMultiNumberOperation<_Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>> operator *(_Ele var, const MatrixXdType<_Ele>& mat) {
		return MatrixMultiNumberOperation<_Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>>(var, mat);
	}
	inline friend MatrixMultiNumberOperation<_Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>> operator /(const MatrixXdType<_Ele>& mat, _Ele var) {
		return MatrixMultiNumberOperation<_Ele, MatrixXdType<_Ele>, MatrixXdType<_Ele>>(1.0 / var, mat);
	}
	inline friend void operator *=(MatrixXdType<_Ele>& mat, _Ele var) {
		for (size_t i = 0; i < mat.rowCount * mat.colCount; i++) {
			mat.container[i] *= var;
		}
	}
	inline friend void operator /= (MatrixXdType<_Ele>& mat, _Ele var) {
		for (size_t i = 0; i < mat.rowCount * mat.colCount; i++) {
			mat.container[i] /= var;
		}
	}
	inline friend void operator +=(MatrixXdType<_Ele>& mat, const MatrixXdType<_Ele>& mat1) {
		_assert_matrix_add_(mat, mat1);
		for (size_t i = 0; i < mat.rowCount * mat.colCount; i++) {
			mat.container[i] += mat1.container[i];
		}
	}
	inline friend void operator +=(MatrixXdType<_Ele>& mat, const MatrixOperation<_Ele>& mat1) {
		_assert_matrix_add_(mat, mat1);
		for (size_t i = 0; i < mat.rowCount; i++) {
			for (size_t j = 0; j < mat.colCount; j++) {
				mat.container[i * mat.colCount + j] += mat1.at(i, j);
			}
		}
	}
	inline friend void operator -=(MatrixXdType<_Ele>& mat, const MatrixXdType<_Ele>& mat1) {
		_assert_matrix_sub_(mat, mat1);
		for (size_t i = 0; i < mat.rowCount * mat.colCount; i++) {
			mat.container[i] -= mat1.container[i];
		}
	}
	inline friend void operator -=(MatrixXdType<_Ele>& mat, const MatrixOperation<_Ele>& mat1) {
		_assert_matrix_sub_(mat, mat1);
		for (size_t i = 0; i < mat.rowCount; i++) {
			for (size_t j = 0; j < mat.colCount; j++) {
				mat.container[i * mat.colCount + j] -= mat1.at(i, j);
			}
		}
	}
	inline void operator =(const MatrixOperation<_Ele>& tree) {
		this->rowCount = tree.row();
		this->colCount = tree.column();
		this->container = new _Ele[this->rowCount * this->colCount];	//���ó�ʼ��
		for (size_t i = 0; i < this->rowCount; i++) {
			for (size_t j = 0; j < this->colCount; j++) {
				this->container[i * this->colCount + j] = tree.at(i, j);
			}
		}
		this->cur = this->rowCount * this->colCount;
	}
	inline MatrixXdType<_Ele>& operator=(const MatrixXdType<_Ele>& matobj) {
		this->deepcopy(matobj);
		return *this;
	}
public:
	inline MatrixXdType() : MatrixAbsType<_Ele>() {

	}
	inline MatrixXdType(size_t row, size_t col) : MatrixAbsType<_Ele>(row, col) {

	}
	inline MatrixXdType(size_t row, size_t col, const initializer_list<_Ele>& list) : MatrixAbsType<_Ele>(row, col, list) {

	}
	inline MatrixXdType(const MatrixXdType<_Ele>& mat) : MatrixAbsType<_Ele>(mat) {

	}
	/*
	* @brief
	* ��ȡ����һ��
	* @param
	* r_index : ������
	* @return
	* һ�е�Ԫ��
	*/
	inline virtual MatrixXdType<_Ele>& getRow(const size_t r_index) {
		//�ж�����
		if (r_index >= this->rowCount) {
			emit(MatrixError("����������������Χ"));
		}
		//�����¾���
		MatrixXdType<_Ele> *mat = new MatrixXdType<_Ele>(1, this->colCount);
		//����Ԫ��
		memcpy_s(mat->container, this->colCount * sizeof(_Ele), \
			this->container + (r_index * this->colCount), this->colCount * sizeof(_Ele));
		return *mat;
	}
	/*
	* @brief
	* ��ȡ����һ��
	* @param
	* c_index : ������
	* @return
	* һ�е�Ԫ��
	*/
	inline virtual MatrixXdType<_Ele>& getColumn(const size_t c_index) {
		//�ж�����
		if (c_index >= this->colCount) {
			emit(MatrixError("����������������Χ"));
		}
		//�����¾���
		MatrixXdType<_Ele>* mat = new MatrixXdType<_Ele>(this->rowCount, 1);
		//��ֵ
		for (int i = 0; i < this->rowCount; i++) {
			mat->container[i] = this->container[i * this->colCount + c_index];
		}
		//����
		return *mat;
	}
	/*
	* @brief
	* ת��
	* @param
	* ��
	* @return
	* ת�ñ��ʽ
	*/
	inline virtual MatrixTransposeOperation<_Ele, MatrixXdType<_Ele>> T() const {
		return MatrixTransposeOperation<_Ele, MatrixXdType<_Ele>>(*this);
	}
	/*
	* @brief
	* ������ת��
	* @param
	* ��
	* @return
	* ת�ú�ľ���
	*/
	inline virtual MatrixHermitianOperation<_Ele, MatrixXdType<_Ele>> H() const {
		return MatrixHermitianOperation<_Ele, MatrixXdType<_Ele>>(*this);
	}
	/*
	* @brief
	* ���������
	* @param
	* ��
	* @return
	* ���ظþ���ĸ�������󣬶�ʵ��������Ч
	*/
	inline virtual MatrixConjugateOperation<_Ele, MatrixXdType<_Ele>> conj() const {
		return MatrixConjugateOperation<_Ele, MatrixXdType<_Ele>>(*this);
	}
	/*
	* @brief
	* ����ȡ�෴��
	* @param
	* ��
	* @return
	* �Ծ���ÿһ��Ԫ�ؾ�ȡ���෴��
	*/
	inline virtual MatrixContraryOperation<_Ele, MatrixXdType<_Ele>> operator- () {
		return MatrixContraryOperation<_Ele, MatrixXdType<_Ele>>(*this);
	}
	/*
	* @brief
	* ����ļ�
	* @param
	* ��
	* @return
	* ��
	*/
	inline _Ele trace() const {
		_assert_matrix_square_ptr_(this)
		_Ele re = _Ele();
		for (size_t i = 0; i < this->rowCount; i++) {
			re += this->at(i, i);
		}
		return re;
	}
};

/*��������*/
template<typename _Ele>
class VectorXdType : public MatrixXdType<_Ele> {
public:
	typedef enum class VectorShape {
		vectorShapeRow,
		vectorShapeColumn
	}VectorShape;
public:
	/*Ĭ�Ϲ���*/
	inline VectorXdType() : MatrixXdType<_Ele>() {
		this->length = 0;
	}
	/*ָ�����Ⱥ���״����*/
	inline VectorXdType(size_t len, VectorXdType<_Ele>::VectorShape shape = VectorShape::vectorShapeColumn) : \
		MatrixXdType<_Ele>(shape == VectorShape::vectorShapeRow ? 1 : len, shape == VectorShape::vectorShapeRow ? len : 1) {
		this->length = len;
	}
	/*���б���*/
	inline VectorXdType(const Container1D<_Ele>& list, VectorXdType<_Ele>::VectorShape shape = VectorShape::vectorShapeColumn) : \
		MatrixXdType<_Ele>(shape == VectorShape::vectorShapeRow ? 1 : list.len(), shape == VectorShape::vectorShapeRow ? list.len() : 1) {
		this->length = list.len();
		this->cur = this->length;
		for (size_t i = 0; i < this->length; i++) {
			this->container[i] = list.at(i);
		}
	}
	/*�ӳ�ʼ���б���*/
	inline VectorXdType(const initializer_list<_Ele>& list, VectorXdType<_Ele>::VectorShape shape = VectorShape::vectorShapeColumn) : \
		MatrixXdType<_Ele>(shape == VectorShape::vectorShapeRow ? 1 : list.size(), shape == VectorShape::vectorShapeRow ? list.size() : 1) {
		this->length = list.size();
		for (auto start = list.begin(); start != list.end(); start++) {
			this->container[this->cur++] = *start;
		}
	}
	/*��������*/
	inline VectorXdType(const VectorXdType<_Ele>& vec) : MatrixXdType<_Ele>(vec) {
		this->length = vec.length;
	}
	/*
	* @brief
	* ��ȡ����Ԫ��
	* @param
	* index : Ԫ������
	* @return
	* ��λ���ϵ�Ԫ��
	*/
	inline virtual _Ele& at(const size_t index) const {
		if (index >= this->length) {
			emit(MatrixError("����Խ��"));
		}
		return this->container[index];
	}
	/*
	* @brief
	* ��ȡ��������
	* @param
	* ��
	* @return
	* ��������
	*/
	inline size_t size() const {
		return this->length;
	}
	/*
	* @brief
	* ��ȡ����Ԫ��
	* @param
	* index: ����
	* @return
	* ����Ԫ��
	*/
	inline _Ele& operator[] (const size_t index) const {
		if (index >= this->length) {
			emit(MatrixError("����Խ��"));
		}
		return this->container[index];
	}
	/*
	* @brief
	* �����ֵ
	* @param
	* vecobj : ��������
	* @return
	* ��
	*/
	inline virtual void deepcopy(const VectorXdType<_Ele>& vecobj) {
		delete[] this->container;
		delete this->commainitializer;
		this->container = new _Ele[vecobj.rowCount * vecobj.colCount];
		this->rowCount = vecobj.rowCount;
		this->colCount = vecobj.colCount;
		this->commainitializer = nullptr;
		this->cur = vecobj.cur;
		this->length = vecobj.length;
		size_t size = this->rowCount * this->colCount * sizeof(_Ele);
		memcpy_s(this->container, size, vecobj.container, size);
	}
protected:
	size_t length;
};

#endif // !MATRIXABSTYPE
