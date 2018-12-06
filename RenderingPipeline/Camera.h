#pragma once

#include "user_data.h"
#include "Matrix4x4.h"
#include "Vector4.h"
#include <vector>
#include "Light.h"

class Camera
{
public:
	Camera();
	~Camera();

	// 设计相机参数，位置、焦点、上轴、光照方向
	void setCamera(const Vector4& pos, const Vector4& target, const Vector4& up);

	// 新版的转换接口，传入世界坐标中的立方体，传出相机坐标中的立方体
	void transform(Object& objectIn, Object& objectOut);

protected:
	// 变换矩阵
	Matrix4x4 m_lookAt;  
	// 相机位置
	Vector4 m_cameraPos;
	// 相机的焦点
	Vector4 m_cameraTarget;
	// 相机的右轴
	Vector4 m_cameraRight;
	// 相机的上轴
	Vector4 m_cameraUp;
	// 世界的上向量
	Vector4 m_Up;
};

