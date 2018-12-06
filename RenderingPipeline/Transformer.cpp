#include "Transformer.h"



Transformer::Transformer()
{
	m_transMatOffset.setIdentity();
	m_transMatRotX.setIdentity();
	m_transMatRotY.setIdentity();
	m_transMatRotZ.setIdentity();
}


Transformer::~Transformer()
{
}

void Transformer::transformOffset(Object & object, Vector4 & offset)
{
	m_transMatOffset.setVal(0, 3, offset.X());
	m_transMatOffset.setVal(1, 3, offset.Y());
	m_transMatOffset.setVal(2, 3, offset.Z());

	object.centerPos = m_transMatOffset * object.centerPos;
}

void Transformer::transformRotationX(Object & object, double angle)
{
	double sin = std::sin(angle);
	double cos = std::cos(angle);
	m_transMatRotX.setVal(1, 1, cos);
	m_transMatRotX.setVal(1, 2, -sin);
	m_transMatRotX.setVal(2, 1, sin);
	m_transMatRotX.setVal(2, 2, cos);

	for (auto& plane : object.planes) {
		for (auto& p : plane) {
			Vector4 posVec(p);
			auto&& res = m_transMatRotX * posVec;
			p.x = res.X();
			p.y = res.Y();
			p.z = res.Z();
		}
	}
}

void Transformer::transformRotationY(Object & object, double angle)
{
	double sin = std::sin(angle);
	double cos = std::cos(angle);
	m_transMatRotY.setVal(0, 0, cos);
	m_transMatRotY.setVal(0, 2, sin);
	m_transMatRotY.setVal(2, 0, -sin);
	m_transMatRotY.setVal(2, 2, cos);

	for (auto& plane : object.planes) {
		for (auto& p : plane) {
			Vector4 posVec(p);
			auto&& res = m_transMatRotY * posVec;
			p.x = res.X();
			p.y = res.Y();
			p.z = res.Z();
		}
	}
}

void Transformer::transformRotationZ(Object & object, double angle)
{
	double sin = std::sin(angle);
	double cos = std::cos(angle);
	m_transMatRotZ.setVal(0, 0, cos);
	m_transMatRotZ.setVal(0, 1, -sin);
	m_transMatRotZ.setVal(1, 0, sin);
	m_transMatRotZ.setVal(1, 1, cos);

	for (auto& plane : object.planes) {
		for (auto& p : plane) {
			Vector4 posVec(p);
			auto&& res = m_transMatRotZ * posVec;
			p.x = res.X();
			p.y = res.Y();
			p.z = res.Z();
		}
	}
}
