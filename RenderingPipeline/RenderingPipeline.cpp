#include "RenderingPipeline.h"

#include <QPalette>

RenderingPipeline::RenderingPipeline(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// 设置背景纯黑色
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::black);
	setAutoFillBackground(true);
	setPalette(pal);

	// 申请纹理空间
	m_textureRed = new int*[PIC_HEIGHT];
	m_textureGreen = new int*[PIC_HEIGHT];
	m_textureBlue = new int*[PIC_HEIGHT];
	for (int i = 0; i < PIC_HEIGHT; ++i) {
		m_textureRed[i] = new int[PIC_WIDTH];
		m_textureGreen[i] = new int[PIC_WIDTH];
		m_textureBlue[i] = new int[PIC_WIDTH];
	}

	// 申请深度缓存空间
	m_depthBuffer = new double*[WINDOW_HEIGHT];
	for (int i = 0; i < WINDOW_HEIGHT; ++i) {
		m_depthBuffer[i] = new double[WINDOW_WIDTH];
	}

	
	/******************************这里设置纹理、光线、局部中心等基本数据******************************/

	/************************************************************************************************/
	

	m_tranformer = new Transformer;
	m_tranformer->setLocalCenter(m_localPos);

	m_camera = new Camera;
	m_camera->setCamera(m_camPos, m_camTarget, m_UpVec);

	m_drawPolygon = new DrawPolygon;
	m_drawPolygon->setTexture(m_textureRed, m_textureGreen, m_textureBlue);
	m_drawPolygon->setDepth(m_depthBuffer);

	m_light = new Light;
	// m_light->setCameraDir(m_camTarget - m_camPos);
	m_light->setLightDir(m_lightDir);



	/******************************以下是初始化的转换代码******************************/
	double initAlgle = 0;
	setRotationX(initAlgle);
	setRotationY(initAlgle);
	setRotationZ(initAlgle);
	// 在世界中平移，初始化肯定是平移局部的中心
	setOffsetXYZ(m_localPos);
	/*********************************************************************************/

}

RenderingPipeline::~RenderingPipeline() {
	if (m_camera != nullptr) {
		delete m_camera;
		m_camera = nullptr;
	}
	if (m_tranformer != nullptr) {
		delete m_tranformer;
	}
	if (m_drawPolygon != nullptr) {
		delete m_drawPolygon;
	}
	if (m_light != nullptr) {
		delete m_light;
	}
	for (int i = 0; i < PIC_HEIGHT; ++i) {
		delete[] m_textureRed[i];
		delete[] m_textureGreen[i];
		delete[] m_textureBlue[i];
	}
	for (int i = 0; i < WINDOW_HEIGHT; ++i) {
		delete[] m_depthBuffer[i];
	}
}

void RenderingPipeline::updateDepthBuffer() {
	for (int i = 0; i < WINDOW_HEIGHT; ++i) {
		for (int j = 0; j < WINDOW_WIDTH; ++j) {
			m_depthBuffer[i][j] = INF;
		}
	}
}

void RenderingPipeline::setRotationX(double angle)
{
	m_tranformer->transformRotationX(m_polygonLocal1, angle);
	m_tranformer->transformRotationX(m_polygonLocal2, angle);
	m_tranformer->transformRotationX(m_polygonLocal3, angle);
	m_tranformer->transformRotationX(m_polygonLocal4, angle);
	m_tranformer->transformRotationX(m_polygonLocal5, angle);
	m_tranformer->transformRotationX(m_polygonLocal6, angle);
}

void RenderingPipeline::setRotationY(double angle)
{
	m_tranformer->transformRotationY(m_polygonLocal1, angle);
	m_tranformer->transformRotationY(m_polygonLocal2, angle);
	m_tranformer->transformRotationY(m_polygonLocal3, angle);
	m_tranformer->transformRotationY(m_polygonLocal4, angle);
	m_tranformer->transformRotationY(m_polygonLocal5, angle);
	m_tranformer->transformRotationY(m_polygonLocal6, angle);
}

void RenderingPipeline::setRotationZ(double angle)
{
	m_tranformer->transformRotationY(m_polygonLocal1, angle);
	m_tranformer->transformRotationY(m_polygonLocal2, angle);
	m_tranformer->transformRotationY(m_polygonLocal3, angle);
	m_tranformer->transformRotationY(m_polygonLocal4, angle);
	m_tranformer->transformRotationY(m_polygonLocal5, angle);
	m_tranformer->transformRotationY(m_polygonLocal6, angle);
}

void RenderingPipeline::setOffsetXYZ(const Vector4 & offset)
{
	m_tranformer->transformOffset(m_polygonLocal1, m_polygonWorld1, offset);
	m_tranformer->transformOffset(m_polygonLocal2, m_polygonWorld2, offset);
	m_tranformer->transformOffset(m_polygonLocal3, m_polygonWorld3, offset);
	m_tranformer->transformOffset(m_polygonLocal4, m_polygonWorld4, offset);
	m_tranformer->transformOffset(m_polygonLocal5, m_polygonWorld5, offset);
	m_tranformer->transformOffset(m_polygonLocal6, m_polygonWorld6, offset);
}

void RenderingPipeline::paintEvent(QPaintEvent *event) {
	QPainter painter;

	if (m_showFrame) {
		m_drawPolygon->drawFrame(this, &painter, m_polygonWorld1);
		m_drawPolygon->drawFrame(this, &painter, m_polygonWorld2);
		m_drawPolygon->drawFrame(this, &painter, m_polygonWorld3);
		m_drawPolygon->drawFrame(this, &painter, m_polygonWorld4);
		m_drawPolygon->drawFrame(this, &painter, m_polygonWorld5);
		m_drawPolygon->drawFrame(this, &painter, m_polygonWorld6);
	}

	if (m_showFill) {
		m_drawPolygon->drawFill(this, &painter, m_polygonWorld1);
		m_drawPolygon->drawFill(this, &painter, m_polygonWorld2);
		m_drawPolygon->drawFill(this, &painter, m_polygonWorld3);
		m_drawPolygon->drawFill(this, &painter, m_polygonWorld4);
		m_drawPolygon->drawFill(this, &painter, m_polygonWorld5);
		m_drawPolygon->drawFill(this, &painter, m_polygonWorld6);
	}

	if (m_showTexture) {
		m_drawPolygon->drawPolygonTexture(this, &painter, m_polygonWorld1);
		m_drawPolygon->drawPolygonTexture(this, &painter, m_polygonWorld2);
		m_drawPolygon->drawPolygonTexture(this, &painter, m_polygonWorld3);
		m_drawPolygon->drawPolygonTexture(this, &painter, m_polygonWorld4);
		m_drawPolygon->drawPolygonTexture(this, &painter, m_polygonWorld5);
		m_drawPolygon->drawPolygonTexture(this, &painter, m_polygonWorld6);
	}
}

void RenderingPipeline::keyPressEvent(QKeyEvent * event) {
}
