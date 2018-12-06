#include "PerspectiveProjector.h"



PerspectiveProjector::PerspectiveProjector()
{
}


PerspectiveProjector::~PerspectiveProjector()
{
}


void PerspectiveProjector::setProjectMat(double n, double f,
	double t, double b,
	double l, double r) 
{
	N = n;
	F = f;
	T = t;
	B = b;
	L = l;
	R = r;
	m_proMat.setZero();
	m_proMat.setVal(0, 0, 2 * N / (R - L));
	m_proMat.setVal(0, 2, (R + L) / (R - L));
	m_proMat.setVal(1, 1, 2 * N / (T - B));
	m_proMat.setVal(1, 2, (T + B) / (T - B));
	m_proMat.setVal(2, 2, -(F + N) / (F - N));
	m_proMat.setVal(2, 3, -2 * F*N / (F - N));
	m_proMat.setVal(3, 2, -1);
}