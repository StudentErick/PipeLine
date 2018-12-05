#pragma once

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;
const double PI = 3.1415926;
const double INF = 100000000.0;
const int PIC_WIDTH = 500;
const int PIC_HEIGHT = 500;

struct Point {
	double x, y, z;
	int r, g, b, alpha;
	int u, v;
	Point(double x_ = 0, double y_ = 0, double z_ = 0.0,
		int r_ = 0, int g_ = 0, int b_ = 0, int alpha_ = 55,
		int u_ = 0, int v_ = 0) {
		x = x_;
		y = y_;
		z = z_;
		r = r_;
		g = g_;
		b = b_;
		alpha = alpha_;
		u = u_;
		v = v_;
	}
};
