#pragma once

#include "Projector.h"
#include <vector>

/*
透视投影的函数
*/

class PerspectiveProjector :
	public Projector
{
public:
	PerspectiveProjector();
	virtual ~PerspectiveProjector();
	// 重写设置矩阵的函数
	void setProjectMat(double n = 10, double f = 1000,
		double t = 20, double b = -20,
		double l = 20, double r = -20)override;
};

