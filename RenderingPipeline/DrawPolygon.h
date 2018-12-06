#pragma once

#include <QWidget>
#include <QPainter>
#include <vector>
#include "user_data.h"
#include "PolygonCliper.h"
#include "DrawLineAlgorithm.h"

/*
绘制多边形
*/
class DrawPolygon
{
public:
	DrawPolygon();
	~DrawPolygon();

	///////////////////////////新版的接口////////////////////////////////////
	// 这里的Object的每个点都是投影归一化后的
	// 绘制函数
	void drawPolygonTexture(QWidget* widget, QPainter* painter, Object& object);
	// 绘制边框
	void drawFrame(QWidget* widget, QPainter* painter, Object& points);
	// 绘制填充
	void drawFill(QWidget* widget, QPainter* painter, Object& points);

	// 设置纹理
	void setTexture(int** red, int** green, int** blue);
	// 设置深度缓冲
	void setDepth(double** depth);

	inline void setMode(int mode) { m_mode = mode; }
protected:
	// 外界的窗口
	QWidget* m_widget{ nullptr };
	// 外界的画刷
	QPainter* m_painter{ nullptr };
	// 裁剪器
	PolygonCliper* m_PolygonCliper{ nullptr };
	// 画线算法
	DrawLineAlgorithm* m_drawLine;

	// 裁剪后的多边形顶点
	std::vector<Point> m_polygonPoints;
	// 纹理RGB
	int** m_textureRed{ nullptr };
	int** m_textureGreen{ nullptr };
	int** m_textureBlue{ nullptr };
	// 深度缓冲矩阵
	double** m_depthBuffer{ nullptr };

	// 绘制模式，0是填充，其他是贴图
	int m_mode{ 0 };
};

