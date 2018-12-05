#pragma once

#include "user_data.h"
#include "Matrix4x4.h"
#include "Vector4.h"
#include <vector>

class Camera
{
public:
	Camera();
	~Camera();
	// 传入的顶点数据从世界转换到相机，输入的是转换到世界的坐标系，输出的是相机
	void transform(std::vector<Point>& pointsIn, std::vector<Point>& pointsOut);
	// 设计相机参数，位置、焦点、上轴
	void setCamera(const Vector4& pos, const Vector4& target, const Vector4& up);
protected:
	// 变换矩阵
	Matrix4x4 m_transMat;  
	// 相机位置
	Vector4 m_cameraPos;
	// 相机的焦点
	Vector4 m_cameraTarget;
	// 相机的右轴
	Vector4 m_cameraRight;
	// 相机的上轴
	Vector4 m_cameraUp;
};

