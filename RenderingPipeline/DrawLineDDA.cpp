#include "DrawLineDDA.h"
#include <cmath>
#include <algorithm>


DrawLineDDA::DrawLineDDA()
{
}


DrawLineDDA::~DrawLineDDA()
{
}

void DrawLineDDA::drawLine(const Point & start,
	const Point & stop,
	std::vector<Point>& pointsOut)
{
	double x0 = start.x;
	double y0 = start.y;
	double z0 = start.z;
	int r0 = start.r;
	int g0 = start.g;
	int b0 = start.b;
	int u0 = start.u;
	int v0 = start.v;
	double x1 = stop.x;
	double y1 = stop.y;
	double z1 = stop.z;
	int r1 = stop.r;
	int g1 = stop.g;
	int b1 = stop.b;
	int u1 = stop.u;
	int v1 = stop.v;

	double dx = x1 - x0;
	double dy = y1 - y0;
	double dz = z1 - z0;
	int dr = r1 - r0;
	int dg = g1 - g0;
	int db = b1 - b0;
	int du = u1 - u0;
	int dv = v1 - v0;

	using std::fabs;

	double steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	double Xinc = dx / steps;
	double Yinc = dy / steps;
	double Zinc = dz / steps;

	double Rinc = 0;
	if (r1 != r0)
		Rinc = 1.0*dr / steps;

	double Ginc = 0;
	if (g1 != g0)
		Ginc = 1.0*dg / steps;

	double Binc = 0;
	if (b1 != b0)
		Binc = 1.0*db / steps;

	double Uinc = 0;
	if (u1 != u0)
		Uinc = 1.0*du / steps;

	double Vinc = 0;
	if (v1 != v0)
		Vinc = 1.0*dv / steps;

	double X = x0, Y = y0, Z = z0;
	double R = r0, G = g0, B = b0;
	double U = u0, V = v0;

	// 在计算的同时进行插值处理
	for (int i = 0; i < steps; ++i) {
		// 深度缓冲，只有当前的位置靠前才能进行绘制，注意标准，注意可能的浮点数误差
		int x = std::max(0, std::min((int)X + WINDOW_HEIGHT / 2, WINDOW_HEIGHT - 1));
		int y = std::max(std::min((int)Y + WINDOW_HEIGHT / 2, WINDOW_WIDTH - 1), 0);
		if (Z < m_buffer[x][y]) {
			pointsOut.emplace_back(Point(X, Y, Z,
				(int)R, (int)G, (int)B,
				(int)U, (int)V));
			//m_buffer[(int)X + WINDOW_HEIGHT / 2][(int)Y + WINDOW_HEIGHT / 2] = Z;   // 更新缓冲值
			m_buffer[x][y] = Z;   // 更新缓冲值
		}

		// 坐标和颜色的插值
		X += Xinc;
		Y += Yinc;
		Z += Zinc;
		R += Rinc;
		G += Ginc;
		B += Binc;
		// 纹理插值
		U += Uinc;
		V += Vinc;
	}
}
