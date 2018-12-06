#pragma once

#include "user_data.h"
#include "Matrix4x4.h"
#include "Vector4.h"
#include <vector>

/*
局部坐标转换到世界坐标，需要知道局部坐标中心在世界的坐标，传入的是局部的坐标点
平移变换是局部中心的位移，旋转是围绕局部中心的旋转

// X轴从负向到正向看去是顺时针
*/

class Transformer
{
public:
	Transformer();
	~Transformer();

	// 新版的接口
	// 物体在空间中的移动
	void transformOffset(Object& object, Vector4& offset);
	// X轴旋转
	void transformRotationX(Object& object, double angle);
	// Y轴旋转
	void transformRotationY(Object& object, double angle);
	// Z轴旋转
	void transformRotationZ(Object& object, double angle);

protected:
	// 转换矩阵
	Matrix4x4 m_transMatRotX;
	Matrix4x4 m_transMatRotY;
	Matrix4x4 m_transMatRotZ;
	Matrix4x4 m_transMatOffset;
};

