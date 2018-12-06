#pragma once

#include "Vector4.h"

/*
变换矩阵，使用齐次坐标系
*/

class Matrix4x4
{
public:
	Matrix4x4();
	Matrix4x4(double m[4][4]);
	Matrix4x4(const Matrix4x4& m);
	~Matrix4x4();

	Matrix4x4 operator+(const Matrix4x4& Mat);
	Matrix4x4 operator-(const Matrix4x4& Mat);
	Matrix4x4 operator*(const Matrix4x4& Mat);
	Vector4 operator*(Vector4& vec);
	void operator+=(const Matrix4x4& Mat);
	void operator-=(const Matrix4x4& Mat);
	void operator*=(const Matrix4x4& Mat);

	void transpose();
	void setIdentity();
	void setZero();

	inline void setVal(int i, int j, double val) { mat[i][j] = val; }
	inline double getVal(int i, int j) { return mat[i][j]; }
protected:
	double mat[4][4];
};

