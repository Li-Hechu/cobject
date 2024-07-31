#pragma once

#ifndef FFT_H
#define FFT_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "../matrix/matrix.h"
#include "../array/array.h"

/*傅里叶变换结果分解为幅值和相位*/
typedef struct FFT {
	Array amplitude;	//幅值
	Array phase;		//相位
}FFT;

/*
* @brief
* 傅里叶变换结果分解为幅值和相位
* @param
* fftseq: 频域序列
* @param
* half: 是否对序列取半
* @return
* 包含幅值和相位的结构体
*/
FFT freq(const ArrayI& fftresult, bool half = true);

/*
* @brief
* 实数序列快速傅里叶变换
* @param
* seq: 实数序列
* @return
* 快速傅里叶变换结果
*/
ArrayI fft(const Container1D<double>& seq);

/*
* @brief
* 复数序列傅里叶变换
* @param
* seq: 实数序列
* @return
* 傅里叶变换结果
*/
ArrayI fft(const Container1D<Complex>& seq);

/*
* @brief
* 傅里叶反变换
* @param
* fftresult: 频域序列
* @return
* 时域序列
*/
ArrayI ifft(const Container1D<Complex>& fftresult);

/*
* @brief
* 二维离散傅里叶变换
* @param
* mat: 二维时域数据
* @return
* 傅里叶变换结果
*/
MatrixI fft2(const Container2D<double>& mat);

/*
* @brief
* 二维离散傅里叶变换
* @param
* mat: 二维时域数据
* @return
* 傅里叶变换结果
*/
MatrixI fft2(const Container2D<Complex>& mat);

/*
* @brief
* 二维离散反傅里叶变换
* @param
* fftresult: 二维频域数据
* @return
* 傅里叶反变换结果
*/
MatrixI ifft2(const Container2D<Complex>& fftresult);

/*
* @brief
* 一维离散余弦变换
* @param
* seq: 实数序列
* @return
* 变换结果
*/
Array dct(const Container1D<double>& seq);

/*
* @brief
* 一维离散余弦反变换
* @param
* dctresult: 变换后的结果
* @return
* 原始序列
*/
Array idct(const Container1D<double>& dctresult);

/*
* @brief
* 二维离散余弦变换
* @param
* mat: 实数矩阵
* @return
* 变换结果
*/
Matrix dct2(const Container2D<double>& mat);

/*
* @brief
* 二维离散余弦反变换
* @param
* dctresult: 变换后的结果
* @return
* 原始矩阵
*/
Matrix idct2(const Container2D<double>& mat);

#endif // !FFT_H
