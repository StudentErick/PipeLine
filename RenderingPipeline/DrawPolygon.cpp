#include "DrawPolygon.h"
#include "DrawLineDDA.h"
#include <QPen>
#include <QColor>
#include <vector>
#include <list>
#include <algorithm>
#include <QImage>
#include <QPixmap>
#include <QString>

DrawPolygon::DrawPolygon()
{
	m_PolygonCliper = new PolygonCliper;
	m_drawLine = new DrawLineDDA;
}

DrawPolygon::~DrawPolygon()
{
	if (m_PolygonCliper != nullptr) {
		delete m_PolygonCliper;
	}
	if (m_drawLine != nullptr) {
		delete m_drawLine;
	}
}

void DrawPolygon::setTexture(int** red, int** green, int** blue)
{
	m_textureRed = red;
	m_textureGreen = green;
	m_textureBlue = blue;
}

void DrawPolygon::setDepth(double ** depth)
{
	m_depthBuffer = depth;
	m_drawLine->setBuffer(m_depthBuffer);
}

void DrawPolygon::drawPolygonTexture(QWidget * widget, QPainter * painter, Object & object)
{
}

void DrawPolygon::drawFrame(QWidget * widget, QPainter * painter, Object & object)
{
	m_painter = painter;
	m_widget = widget;
	m_painter->begin(m_widget);
	int L = -widget->width() / 2;
	int R = -L;
	int T = widget->height();
	int B = -T;
	m_PolygonCliper->setBoundary(T, B, L, R);
	m_PolygonCliper->clip(object);
	for (auto& plane : object.planes) {
		if (plane.empty())
			continue;
		for (int i = 0; i < plane.size() - 1; ++i) {
			std::vector<Point>points;
			m_drawLine->drawLine(plane[i], plane[i + 1], points);
			for (const auto& p : points) {
				QPen pen;
				pen.setColor(QColor(p.r, p.g, p.b));
				m_painter->setPen(pen);
				// 绘制点的坐标，注意坐标转换
				m_painter->drawPoint(QPoint(p.x + WINDOW_WIDTH / 2, (WINDOW_HEIGHT) / 2 - p.y));
			}
		}
	}
}

void DrawPolygon::drawFill(QWidget * widget, QPainter * painter, Object & object)
{
	// 扫描线填充多边形算法
	// 扫描线的算法思路参考自：https://www.jianshu.com/p/d9be99077c2b
	// 色彩填充是按照水平单线性插值进行计算的

	if (object.planes.empty())
		return;
	m_painter = painter;
	m_widget = widget;
	m_painter->begin(m_widget);

	// 边的数据结构，一定要使用浮点数，，否则精度丢失，绘制失败！！ WTF，坑死劳资了！！！！！！
	struct EDGE {
		double x;
		double delta_x;
		double ymax;

		// 当前的RGB与深度，同时保留插值，这里全部改成浮点数，防止误差累计
		double r;
		double delta_r;
		double g;
		double delta_g;
		double b;
		double delta_b;
		double depth;
		double delta_depth;
		double u;
		double delta_u;
		double v;
		double delta_v;
	};

	// 绘制每一个平面
	for (auto& plane : object.planes) {
		int maxY = -500;
		for (const auto& p : plane) {
			if (p.y > maxY)
				maxY = p.y;
		}
		std::list<EDGE>AET;                     // 活动边表 Active Edge Table，像素是800
		std::vector<std::list<EDGE>>ET(maxY + WINDOW_HEIGHT + 5);    // 边表 Edge Table +405标准化，并且防止溢出

		for (int i = 0; i < plane.size() - 1; ++i) {
			EDGE edge;

			// 处理普通的坐标递增坐标
			double xmin = (plane[i].y < plane[i + 1].y) ? plane[i].x : plane[i + 1].x;
			double ymax = std::max(plane[i].y, plane[i + 1].y);
			edge.x = xmin;
			edge.ymax = ymax;
			if (plane[i].y == plane[i + 1].y)  // 舍弃水平直线
				continue;
			else   // 斜率倒数
				edge.delta_x = (double)(plane[i].x - plane[i + 1].x) / (double)(plane[i].y - plane[i + 1].y);

			// 处理RGB和深度
			auto& low_point = (plane[i].y < plane[i + 1].y) ? plane[i] : plane[i + 1];
			auto& high_point = (plane[i].y >= plane[i + 1].y) ? plane[i] : plane[i + 1];

			// 保存初始的状态
			edge.r = low_point.r;
			edge.g = low_point.g;
			edge.b = low_point.b;
			edge.depth = low_point.z;
			edge.u = low_point.u;
			edge.v = low_point.v;

			// 计算RGB、深度、纹理插值
			double steps = (high_point.y - low_point.y);
			edge.delta_r = (high_point.r - low_point.r) / steps;
			edge.delta_g = (high_point.g - low_point.g) / steps;
			edge.delta_b = (high_point.b - low_point.b) / steps;
			edge.delta_depth = (high_point.z - low_point.z) / steps;
			edge.delta_u = (high_point.u - low_point.u) / steps;
			edge.delta_v = (high_point.v - low_point.v) / steps;

			// 进入边表
			ET[std::max(0.0, std::min(plane[i].y, plane[i + 1].y) + WINDOW_HEIGHT / 2)].push_back(edge);
		}

		// 开始扫描，从下往上，记得标准化 WTF！！！！！
		for (int i = 0; i < maxY + WINDOW_HEIGHT / 2 + 5; ++i) {
			// 取出ET中当前所有的边，按照x递增的顺序插入AE中
			while (!ET[i].empty()) {
				EDGE edge = *ET[i].begin();
				ET[i].erase(ET[i].begin());
				auto it = AET.begin();
				// 寻找合适的位置，按照递增的顺序排列
				while (it != AET.end() && it->x < edge.x)
					++it;
				if (it != AET.end() && it->x == edge.x&&it->delta_x < edge.delta_x)  // 相等按照delta_x递增排序
					++it;
				AET.insert(it, edge);  // 插入数据
			}

			// AET中的边两两配对，填充颜色
			int n = AET.size();
			int m = 0;
			auto itAET = AET.begin();
			while (m <= n - 2) {
				Point p1(itAET->x, i - WINDOW_HEIGHT / 2, itAET->depth, itAET->r, itAET->g, itAET->b, itAET->u, itAET->v);
				++itAET;
				Point p2(itAET->x, i - WINDOW_HEIGHT / 2, itAET->depth, itAET->r, itAET->g, itAET->b, itAET->u, itAET->v);
				++itAET;
				std::vector<Point>pvec;
				m_drawLine->drawLine(p1, p2, pvec);   // 生成所有的点
				// 绘制顶点
				QColor color;
				for (const auto& p : pvec) {
					if (m_mode == 0) {
						color.setRed(p.r);
						color.setGreen(p.g);
						color.setBlue(p.r);
					}
					else {
						int u = std::min(PIC_HEIGHT - 1, p.u);
						int v = std::min(PIC_HEIGHT - 1, p.v);
						auto r = std::min(255.0, p.I*m_textureRed[u][v]);
						auto g = std::min(255.0, p.I*m_textureGreen[u][v]);
						auto b = std::min(255.0, p.I*m_textureBlue[u][v]);
						color.setRed(r);
						color.setGreen(g);
						color.setBlue(b);
					}
					QPen pen(color);
					m_painter->setPen(pen);
					int x = static_cast<int>(p.x + WINDOW_HEIGHT / 2 + 0.5);
					int y = static_cast<int>(WINDOW_HEIGHT / 2 - p.y + 0.5);
					m_painter->drawPoint(QPoint(x, y));  //    注意绘制的标准化
				}
				pvec.clear();
				m += 2;// 注意+2
			}

			// 删除AET中的ymax==y的边
			itAET = AET.begin();
			while (itAET != AET.end()) {
				// 利用减法，等效浮点数减法，防止误差干扰
				if (itAET->ymax - (i - WINDOW_HEIGHT / 2) < 2.0) {  // 别忘了-400恢复！！！！ /// 浮点数一定要使用<=，WTF。。。。。。。。
					auto curIt = itAET;
					++itAET;
					AET.erase(curIt);  // ++先于函数调用
				}
				else {
					itAET++;
				}
			}

			// 更新数据
			for (auto& aet : AET) {
				// 注意浮点数误差， 坑死劳资了， WTF！！！！！！！！！
				aet.x += aet.delta_x;
				aet.r += aet.delta_r;
				aet.g += aet.delta_g;
				aet.b += aet.delta_b;
				aet.depth += aet.delta_depth;
				aet.u += aet.delta_u;
				aet.v += aet.delta_v;
			}
		}
	}
}
