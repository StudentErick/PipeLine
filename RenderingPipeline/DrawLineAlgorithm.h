#pragma once

#include "user_data.h"
#include <vector>

/*
画线算法的基类，这里输入的是二维空间的点，是在二维空间中画线
*/

class DrawLineAlgorithm
{
public:
	DrawLineAlgorithm();
	virtual ~DrawLineAlgorithm();
	// 起点、终点、保存需要绘制的点
	virtual void drawLine(const Point& start,
		const Point& stop,
		std::vector<Point>& pointsOut) = 0;

	inline void setBuffer(double** buf) { m_buffer = buf; }
protected:
	double** m_buffer;  // 深度缓冲，来决定是否绘制某个点
};

