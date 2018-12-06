#include "Vector4.h"
#include <cmath>


Vector4::Vector4(const Point & point)
{
	v[0] = point.x;
	v[1] = point.y;
	v[2] = point.z;
	v[3] = 1;
}

Vector4::Vector4(const Vector4 & vec)
{
	v[0] = vec.v[0];
	v[1] = vec.v[1];
	v[2] = vec.v[2];
	v[3] = vec.v[3];
}

Vector4::Vector4(double vec[4])
{
	for (int i = 0; i < 4; ++i) {
		v[i] = vec[i];
	}
}

Vector4::Vector4(double _x, double _y, double _z, double _w)
{
	v[0] = _x;
	v[1] = _y;
	v[2] = _z;
	v[3] = _w;
}


Vector4::~Vector4()
{
}

Vector4 Vector4::operator+(const Vector4 & vec)
{
	double x_ = v[0] + vec.v[0];
	double y_ = v[1] + vec.v[1];
	double z_ = v[2] + vec.v[2];
	return Vector4(x_, y_, z_);
}

Vector4 Vector4::operator-(const Vector4 & vec)
{
	double x_ = v[0] - vec.v[0];
	double y_ = v[1] - vec.v[1];
	double z_ = v[2] - vec.v[2];
	return Vector4(x_, y_, z_);
}

void Vector4::operator+=(const Vector4 & vec)
{
	v[0] += vec.v[0];
	v[1] += vec.v[1];
	v[2] += vec.v[2];
}

void Vector4::operator-=(const Vector4 & vec)
{
	v[0] -= vec.v[0];
	v[1] -= vec.v[1];
	v[2] -= vec.v[2];
}

double Vector4::dot(const Vector4 & vec)
{
	double sum = 0;
	sum = v[0] * vec.v[0] + v[1] * vec.v[1] + v[2] * vec.v[2];
	return sum;
}

Vector4 Vector4::cross(const Vector4 & vec)
{
	double x_ = v[1] * vec.v[2] - vec.v[1] * v[2];
	double y_ = vec.v[0] * v[2] - v[0] * vec.v[2];
	double z_ = v[0] * vec.v[1] - vec.v[0] * v[1];
	return Vector4(x_, y_, z_);
}

double Vector4::length()
{
	return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void Vector4::normalize()
{
	double len = length();
	v[0] /= len;
	v[1] /= len;
	v[2] /= len;
}

void Vector4::reverse()
{
	v[0] = -v[0];
	v[1] = -v[1];
	v[2] = -v[2];
}
