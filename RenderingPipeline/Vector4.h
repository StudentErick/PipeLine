#pragma once

#include "user_data.h"

/*
向量或者顶点
*/

class Vector4
{
public:
	Vector4(const Point& point);
	Vector4(const Vector4& vec);
	Vector4(double vec[4]);
	Vector4(double _x = 0, double _y = 0, double _z = 0, double _w = 1);
	~Vector4();
	
	Vector4 operator+(const Vector4& vec);
	Vector4 operator-(const Vector4& vec);
	void operator+=(const Vector4& vec);
	void operator-=(const Vector4& vec);
	Vector4 cross(const Vector4& vec);
	double dot(const Vector4& vec);
	double length();
	void normalize();
	void reverse();

	inline void X(double _x) { v[0] = _x; }
	inline double X() { return v[0]; }
	inline void Y(double _y) { v[1] = _y; }
	inline double Y() { return v[1]; }
	inline void Z(double _z) { v[2] = _z; }
	inline double Z() { return v[2]; }
	inline void W(double _w) { v[3] = _w; }
	inline double W() { return v[3]; }

protected:
	double v[4];
};

// 一个平面由它的顶点组成
using Plane = std::vector<Point>;

// 空间物体的对象
struct Object {
	Vector4 centerPos;            // 物体局部坐标中心在世界中的位置
	std::vector<Plane> planes;    // 物体的各个平面
};