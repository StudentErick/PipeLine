#pragma once
#include "DrawLineAlgorithm.h"

/*
DDAª≠œﬂÀ„∑®
*/

class DrawLineDDA :
	public DrawLineAlgorithm
{
public:
	DrawLineDDA();
	virtual ~DrawLineDDA();
	virtual void drawLine(const Point& start,
		const Point& stop,
		std::vector<Point>& pointsOut)override;
};

