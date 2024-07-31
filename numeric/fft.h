#pragma once

#ifndef FFT_H
#define FFT_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "../matrix/matrix.h"
#include "../array/array.h"

/*����Ҷ�任����ֽ�Ϊ��ֵ����λ*/
typedef struct FFT {
	Array amplitude;	//��ֵ
	Array phase;		//��λ
}FFT;

/*
* @brief
* ����Ҷ�任����ֽ�Ϊ��ֵ����λ
* @param
* fftseq: Ƶ������
* @param
* half: �Ƿ������ȡ��
* @return
* ������ֵ����λ�Ľṹ��
*/
FFT freq(const ArrayI& fftresult, bool half = true);

/*
* @brief
* ʵ�����п��ٸ���Ҷ�任
* @param
* seq: ʵ������
* @return
* ���ٸ���Ҷ�任���
*/
ArrayI fft(const Container1D<double>& seq);

/*
* @brief
* �������и���Ҷ�任
* @param
* seq: ʵ������
* @return
* ����Ҷ�任���
*/
ArrayI fft(const Container1D<Complex>& seq);

/*
* @brief
* ����Ҷ���任
* @param
* fftresult: Ƶ������
* @return
* ʱ������
*/
ArrayI ifft(const Container1D<Complex>& fftresult);

/*
* @brief
* ��ά��ɢ����Ҷ�任
* @param
* mat: ��άʱ������
* @return
* ����Ҷ�任���
*/
MatrixI fft2(const Container2D<double>& mat);

/*
* @brief
* ��ά��ɢ����Ҷ�任
* @param
* mat: ��άʱ������
* @return
* ����Ҷ�任���
*/
MatrixI fft2(const Container2D<Complex>& mat);

/*
* @brief
* ��ά��ɢ������Ҷ�任
* @param
* fftresult: ��άƵ������
* @return
* ����Ҷ���任���
*/
MatrixI ifft2(const Container2D<Complex>& fftresult);

/*
* @brief
* һά��ɢ���ұ任
* @param
* seq: ʵ������
* @return
* �任���
*/
Array dct(const Container1D<double>& seq);

/*
* @brief
* һά��ɢ���ҷ��任
* @param
* dctresult: �任��Ľ��
* @return
* ԭʼ����
*/
Array idct(const Container1D<double>& dctresult);

/*
* @brief
* ��ά��ɢ���ұ任
* @param
* mat: ʵ������
* @return
* �任���
*/
Matrix dct2(const Container2D<double>& mat);

/*
* @brief
* ��ά��ɢ���ҷ��任
* @param
* dctresult: �任��Ľ��
* @return
* ԭʼ����
*/
Matrix idct2(const Container2D<double>& mat);

#endif // !FFT_H
