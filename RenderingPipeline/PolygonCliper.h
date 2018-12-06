#pragma once

#include "user_data.h"
#include "Vector4.h"
#include <vector>

/*
多边形裁剪器，传入的多边形裁剪到合适的平面上
*/

class PolygonCliper
{
public:
	PolygonCliper();
	~PolygonCliper();
	// 裁剪算法，输入的点、输出的点
	void clip(std::vector<Point>& pointsIn, std::vector<Point>& pointsOut);

	// 新版的裁剪算法，把多边形裁剪成新的图形
	void clip(Object& object);

	// 设置边界，上边界、下边界、左边界、右边界
	void setBoundary(double t, double b, double l, double r);

protected:
	// 上下左右
	double T, D, L, R;
};

