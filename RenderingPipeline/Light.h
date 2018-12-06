#pragma once

#include "user_data.h"
#include "Vector4.h"
#include "user_data.h"
#include <vector>

/*
设置物体的光照强度，配置alpha即可
*/
class Light
{
public:
	Light();
	~Light();
	// 设置光线方向
	void setLightDir(const Vector4& lightDir);
	// 漫反射模型
	void setPolygonLight(Object& object);
protected:
	// 相机方向，这里的相机方向是 camTarget-camPos
	Vector4 m_cameraDir;
	// 光线方向
	Vector4 m_lightDir;
	// 平面法线方向
	Vector4 m_normalDir;
	// 入射光的强度
};

