#pragma once

#include <QtWidgets/QWidget>
#include "ui_RenderingPipeline.h"

#include <QPaintEvent>
#include <QKeyEvent>
#include "user_data.h"
#include "Transformer.h"
#include "Camera.h"
#include "DrawPolygon.h"
#include "Light.h"
#include "Vector4.h"
#include "PerspectiveProjector.h"

/*
渲染管线的总类，但是存在一个设计上的缺陷，
光线的渲染显示是在Camera类内部的，这样耦合性太高。
*/

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

	Object m_initCube;  // 初始的立方体
	Object m_finalCube; // 用于绘制的立方体

	// 工具
	Transformer* m_tranformer{ nullptr };
	Camera* m_camera{ nullptr };
	DrawPolygon* m_drawPolygon{ nullptr };
	//Light* m_light{ nullptr }; 
	PerspectiveProjector* m_perspectiveProjector;

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

	// 显示标记
	bool m_showFrame{ true };
	bool m_showFill{ false };
	bool m_showTexture{ false };

private:
	Ui::RenderingPipelineClass ui;
};