#pragma once

#include <QWidget>
#include <QPainter>
#include <vector>
#include "user_data.h"
#include "PolygonCliper.h"

/*
绘制多边形
*/
class DrawPolygon
{
public:
	DrawPolygon();
	~DrawPolygon();
	// 绘制多边形纹理
	void drawPolygonTexture(QWidget* widget, QPainter* painter, std::vector<Point>& points);
	// 绘制边框
	void drawFrame(QWidget* widget, QPainter* painter, std::vector<Point>& points);
	// 绘制填充
	void drawFill(QWidget* widget, QPainter* painter, std::vector<Point>& points);
	// 设置纹理
	void setTexture(int** red, int** green, int** blue);
	
	// 设置深度缓冲
	inline void setDepth(double** depth) { m_depthBuffer = depth; }
protected:
	// 外界的窗口
	QWidget* m_widget{ nullptr };
	// 外界的画刷
	QPainter* m_painter{ nullptr };
	// 裁剪器
	PolygonCliper* m_PolygonCliper{ nullptr };
	// 裁剪后的多边形顶点
	std::vector<Point> m_polygonPoints;
	// 纹理RGB
	int** m_textureRed{ nullptr };
	int** m_textureGreen{ nullptr };
	int** m_textureBlue{ nullptr };
	// 深度缓冲矩阵
	double** m_depthBuffer{ nullptr };
};

