#include "Projector.h"



Projector::Projector()
{
}


Projector::~Projector()
{
}

void Projector::project(Object & object, int width, int height)
{
	for (auto& plane : object.planes) {
		for (auto& point : plane) {
			Vector4 vec(point);
			auto&& res = m_proMat * vec;
			// 归一化
			point.x = res.X() / res.W();
			point.y = res.Y() / res.W();
			point.z = res.Z() / res.W();   // 深度分量
			// 映射到屏幕
			point.x *= width;
			point.y *= height;
		}
	}
}