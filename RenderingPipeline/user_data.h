#pragma once

#include <vector>

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;
const double PI = 3.1415926;
const double INF = 100000000.0;
const int PIC_WIDTH = 500;
const int PIC_HEIGHT = 500;
const int AMBIENT_LIGHT = 55;    // 环境光强度
const int DIRECTION_LIGHT = 200; // 方向光强度

enum DrawMode
{
	frame, fill, texture
};

struct Point {
	double x, y, z;
	int r, g, b;
	int u, v;
	bool show;
	double I;  // 光照强度系数
	Point(double x_ = 0, double y_ = 0, double z_ = 0.0,
		int r_ = 0, int g_ = 0, int b_ = 0,
		int u_ = 0, int v_ = 0) {
		x = x_;
		y = y_;
		z = z_;
		r = r_;
		g = g_;
		b = b_;
		u = u_;
		v = v_;
		I = 1;
	}
};