#include "Light.h"
#include <algorithm>


Light::Light()
{
}


Light::~Light()
{
}

void Light::setLightDir(const Vector4 & lightDir)
{
	m_lightDir = lightDir;
}

void Light::setPolygonLight(Object& object) {
	for (auto& plane: object.planes) {
		// 处理每个面的光照
		if (plane.size() <= 2)   // 一个平面最少3个点
			return;
		// 假定所有的顶点不共线
		const auto& p0 = plane[0];
		const auto& p1 = plane[1];
		const auto& p2 = plane[2];
		Vector4 vec1(p0.x - p1.x, p0.y - p1.y, p0.z - p1.z);
		Vector4 vec2(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
		auto&& normalVec = vec1.cross(vec2);  // 平面的法向量

		double I = 1;
		double dif = fabs(normalVec.dot(m_lightDir)) / (normalVec.length()*m_lightDir.length());
		for (auto& p : plane) {
			p.r *= (I + dif);
			p.g *= (I + dif);
			p.b *= (I + dif);
			p.r = std::min(255, p.r);
			p.g = std::min(255, p.g);
			p.b = std::min(255, p.b);
		}
	}
}
