#pragma once

#include "user_data.h"
#include "Matrix4x4.h"
#include "Vector4.h"
#include <vector>

/*
局部坐标转换到世界坐标，需要知道局部坐标中心在世界的坐标，传入的是局部的坐标点
平移变换是局部中心的位移，旋转是围绕局部中心的旋转
*/
class Transformer
{
public:
	Transformer();
	~Transformer();
	// 平移变换，不改变原来的局部数据，这里的平移变化是整个局部中心的平移
	void transformOffset(std::vector<Point>& pointsIn, std::vector<Point>& pointsOut, const Vector4& offset);
	// X轴旋转
	void transformRotationX(std::vector<Point>& points, double angle);
	// Y轴旋转
	void transformRotationY(std::vector<Point>& points, double angle);
	// Z轴旋转
	void transformRotationZ(std::vector<Point>& points, double angle);
	// 设置局部坐标中心
	void setLocalCenter(const Vector4& pos);
protected:
	// 转换矩阵
	Matrix4x4 m_transMat;
	// 局部坐标中心的坐标
	Vector4 m_localCenter;
};

