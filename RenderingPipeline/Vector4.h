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

