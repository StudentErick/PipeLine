#pragma once

#include "user_data.h"
#include <vector>
#include "Matrix4x4.h"

/*
投影的虚基类
*/

class Projector
{
public:
	Projector();
	virtual ~Projector();

	// 设置投影矩阵
	virtual void setProjectMat(double n = 10, double f = 1000,
		double t = 20, double b = -20,
		double l = 20, double r = -20) = 0;

	// 投影函数，把坐标映射为NDC后，在转换到用户的屏幕坐标
	virtual void project(Object& object, int width = WINDOW_WIDTH, int hegiht = WINDOW_HEIGHT) final;

protected:
	// 近平面，远平面，顶部，底部，左侧，右侧
	double N, F, T, B, L, R;
	// 投影变换矩阵
	Matrix4x4 m_proMat;
};

