#pragma once

#include <QtWidgets/QWidget>
#include "ui_RenderingPipeline.h"

#include "user_data.h"
#include "Transformer.h"
#include "Camera.h"
#include "DrawPolygon.h"
#include "Light.h"
#include "Vector4.h"

class RenderingPipeline : public QWidget
{
	Q_OBJECT

public:
	RenderingPipeline(QWidget *parent = Q_NULLPTR);
	virtual ~RenderingPipeline();

protected:

	void paintEvent(QPaintEvent *event)override;
	void keyPressEvent(QKeyEvent *event)override;

	// 更新深度缓冲数据
	void updateDepthBuffer();
	
	// 计算绕局部XYZ轴旋转后的局部坐标
	void setRotationX(double angle);
	void setRotationY(double angle);
	void setRotationZ(double angle);

	// 在世界平移后的坐标
	void setOffsetXYZ(const Vector4& offset);

	// 第一次先绘制一个立方体，空间图形必须是平面的，否则无法正确绘制。
	// 立体图案由平面拼接

	// 这是局部的坐标
	std::vector<Point> m_polygonLocal1;
	std::vector<Point> m_polygonLocal2;
	std::vector<Point> m_polygonLocal3;
	std::vector<Point> m_polygonLocal4;
	std::vector<Point> m_polygonLocal5;
	std::vector<Point> m_polygonLocal6;

	// 这是世界的坐标
	std::vector<Point> m_polygonWorld1;
	std::vector<Point> m_polygonWorld2;
	std::vector<Point> m_polygonWorld3;
	std::vector<Point> m_polygonWorld4;
	std::vector<Point> m_polygonWorld5;
	std::vector<Point> m_polygonWorld6;


	Transformer* m_tranformer{ nullptr };
	Camera* m_camera{ nullptr };
	DrawPolygon* m_drawPolygon{ nullptr };
	Light* m_light{ nullptr };

	// 纹理RGB
	int** m_textureRed{ nullptr };
	int** m_textureGreen{ nullptr };
	int** m_textureBlue{ nullptr };

	// 深度缓冲矩阵
	double** m_depthBuffer{ nullptr };

	// 局部坐标中心
	Vector4 m_localPos;
	// 相机位置
	Vector4 m_camPos;
	// 相机焦点
	Vector4 m_camTarget;
	// 上轴
	Vector4 m_UpVec;
	// 光线的方向
	Vector4 m_lightDir;

	bool m_showFrame{ true };
	bool m_showFill{ false };
	bool m_showTexture{ true };

private:
	Ui::RenderingPipelineClass ui;
};