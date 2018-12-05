#include "Matrix4x4.h"



Matrix4x4::Matrix4x4()
{
}

Matrix4x4::Matrix4x4(double m[4][4])
{
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			mat[i][j] = m[i][j];
		}
	}
}

Matrix4x4::Matrix4x4(const Matrix4x4 & m)
{
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			mat[i][j] = m.mat[i][j];
		}
	}
}


Matrix4x4::~Matrix4x4()
{
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4 & Mat)
{
	double m[4][4];
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			m[i][j] = mat[i][j] + Mat.mat[i][j];
		}
	}
	return Matrix4x4(m);
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4 & Mat)
{
	double m[4][4];
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			m[i][j] = mat[i][j] - Mat.mat[i][j];
		}
	}
	return Matrix4x4(m);
}

void Matrix4x4::operator+=(const Matrix4x4 & Mat)
{
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			mat[i][j] += Mat.mat[i][j];
		}
	}
}

void Matrix4x4::operator-=(const Matrix4x4 & Mat)
{
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			mat[i][j] -= Mat.mat[i][j];
		}
	}
}

void Matrix4x4::operator*=(const Matrix4x4 & Mat)
{
	double m[4][4];
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			double sum = 0;
			for (int k = 0; k < 4; ++k) {
				sum += mat[i][k] * Mat.mat[k][j];
			}
			m[i][j] = sum;
		}
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			mat[i][j] = m[i][j];
		}
	}
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 & Mat)
{
	double m[4][4];
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			double sum = 0;
			for (int k = 0; k < 4; ++k) {
				sum += mat[i][k] * Mat.mat[k][j];
			}
			m[i][j] = sum;
		}
	}
	return Matrix4x4(m);
}

Vector4 Matrix4x4::operator*(Vector4& vec)
{
	double v[4];
	for (int i = 0; i < 4; ++i) {
		v[i] = mat[i][0] * vec.X() + mat[i][1] * vec.Y() + mat[i][2] * vec.Z() + mat[i][3] * vec.W();
	}
	return Vector4(v);
}

void Matrix4x4::transpose()
{
	for (int i = 1; i < 4; ++i) {
		for (int j = 0; j < i; ++j) {
			double t = mat[i][j];
			mat[i][j] = mat[j][i];
			mat[j][i] = t;
		}
	}
}

void Matrix4x4::setIdentity()
{
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j)
				mat[i][j] = 1;
			else 
				mat[i][j] = 0;
		}
	}
}

void Matrix4x4::setZero()
{
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			mat[i][j] = 0;
		}
	}
}
