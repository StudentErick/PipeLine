#pragma once

#include "user_data.h"
#include "Vector4.h"
#include <vector>

/*
设置物体的光照强度，配置alpha即可
*/
class Light
{
public:
	Light();
	~Light();
	// 设置相机方向
	void setCameraDir(const Vector4& cameraDir);
	// 设置光线方向
	void setLightDir(const Vector4& lightDir);
	// 设置光线
	void setPolygonLight(std::vector<Point>& polygon);
protected:
	// 相机方向
	Vector4 m_cameraDir;
	// 光线方向
	Vector4 m_lightDir;
	// 平面法线方向
	Vector4 m_normalDir;
};

