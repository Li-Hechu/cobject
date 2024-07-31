#pragma once

#ifndef INTEGRATE_H
#define INTEGRATE_H

#pragma comment(lib,"lib/cobjectLib.lib")
#include "function.h"
#include "../vector.h"
#include <iomanip>

static const char IntegrateErrorHeader[ERROR_HEADER_MAXLEN] = "IntegrateError";
/*积分错误*/
class IntegrateError : public Error<IntegrateErrorHeader> {
public:
	inline IntegrateError(const char* info) : Error(info) {

	}
};

/*积分结果*/
typedef struct InteRe {
	size_t time;				//函数调用次数
	bool ok;					//是否求解成功
	const char* discription;	//求解结果描述 
	double inte_value;			//积分值

	inline friend ostream& operator<<(ostream& out, const InteRe& re) {
		out << "调用次数：" << re.time << endl;
		out << "状    态：" << re.ok << endl;
		out << "描    述：" << re.discription << endl;
		out << "积分结果：" << fixed << setprecision(10) << re.inte_value << endl;
		return out;
	}
}InteRe;


/*
* @brief
* 离散梯形积分
* @param
* y: 因变量y的值
* @param
* x: 自变量x的值
* @return
* 积分结果
*/
double trapezoid(const Container1D<double>& y, const Container1D<double>& x);

/*
* @brief
* 离散梯形积分
* @param
* y: 因变量y的值
* @param
* dx: 点间距
* @return
* 积分结果
*/
double trapezoid(const Container1D<double>& y, const double dx);

/*
* @brief
* 离散辛普森积分
* @param
* y: 因变量y的值
* @param
* x: 自变量x的值
* @return
* 积分结果
*/
double simpson(const Container1D<double>& y, const Container1D<double>& x);

/*
* @brief
* 离散辛普森积分
* @param
* y: 因变量y的值
* @param
* dx: 点间距
* @return
* 积分结果
*/
double simpson(const Container1D<double>& y, const double dx);

/*
* @brief
* 自适应辛普森积分
* @param
* f: 被积函数
* @param
* low: 积分下界
* @param
* up: 积分上界
* @param
* err: 允许积分误差
* @return
* 被积函数在指定区间上的积分结果
*/
InteRe quad(func1d f, const double low, const double up, double err = precision10);

/*
* @brief
* 带瑕点的自适应辛普森积分
* @attention
* 强烈建议瑕点为0以提高积分精度，若瑕点不为0，则可能由于数值精度造成积分失败
* 若瑕点不为0，建议降低积分精度
* @param
* f: 被积函数
* @param
* range: 积分区间
* @param
* point: 瑕点列表
* @param
* err: 积分精度
* @return
* 被积函数在指定区间上的积分结果
*/
InteRe quad(func1d f, const double low, const double up, const Vector<double>& point, const double err = precision10);

/*
* @brief
* 自适应二重积分
* @param
* f: 被积函数
* @param
* low1: 外层积分下界
* @param
* up1: 外层积分上界
* @param
* low2: 内层积分下界
* @param
* up2: 内层积分上界
* @param
* err: 积分精度
* @return
* 积分结果
*/
InteRe dblquad(func2d f, const double low1, const double up1, const double low2, const double up2, const double err = precision10);

/*
* @brief
* 自适应二重积分
* @param
* f: 被积函数
* @param
* low1: 外层积分下界
* @param
* up1: 外层积分上界
* @param
* low2: 内层积分下界
* @param
* up2: 内层积分上界
* @param
* err: 积分精度
* @return
* 积分结果
*/
InteRe dblquad(func2d f, const double low1, const double up1, const func1d low2, const func1d up2, const double err = precision10);

/*
* @brief
* 龙贝格积分
* @param
* f: 被积函数
* @param
* range: 积分区间
* @param
* err: 允许积分误差
* @return
* 被积函数在指定区间上的积分结果
*/
double romberg(func1d f, const LimitedF& range, double err = precision10);

/*
* @brief
* 高斯-勒让德积分
* @param
* f: 被积函数
* @param
* range: 积分区间
* @param
* N: 积分阶数
* @return
* 被积函数在指定区间上的积分结果
*/
double gaussquad(func1d f, const LimitedF& range, const size_t N = 4);

#endif // !INTEGRATE_H
