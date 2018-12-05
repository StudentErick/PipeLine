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
	// 坐标进行投影
	virtual void project(std::vector<Point>& points) final;

	// 设置投影矩阵
	virtual void setProjectMat(double n = 10, double f = 1000,
		double t = 20, double b = -20,
		double l = 20, double r = -20) = 0;

protected:
	// 近平面，远平面，顶部，底部，左侧，右侧
	double N, F, T, B, L, R;
	// 投影变换矩阵
	Matrix4x4 m_proMat;
};

