/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: customwidget.cpp
\brief	
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9 

*/
#include "customwidget.h"
#include <QLabel>
#include <QLineF>
#include <QMovie>
#include <QPainter>
#include <QPaintEvent>
#include <QPointF>


CCustomWidget::CCustomWidget(QWidget* parent) : QWidget(parent)
{
	ui.setupUi(this);
	initialize();
}
void CCustomWidget::initialize() {
	m_img = QImage(":/images/rainman.gif");
}


void CCustomWidget::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
}

void CCustomWidget::paintEvent(QPaintEvent *event)
{	
	QWidget::paintEvent(event);
	QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	
	
	// 帽子-直线
	QLineF line(QPointF(100, 20), QPointF(400, 20));
	painter.drawLine(line);

	// 脸-矩形
	QRectF rct(120, 50, 260, 120);
	painter.drawRect(rct);


	// 耳朵-封闭折线
	QPolygonF polygonLeft;
	polygonLeft << QPointF(84,70) << QPointF(64,100) << QPointF(84,130) << QPointF(104,100);
	painter.drawPolygon(polygonLeft);

	QPolygonF polygonRight;
	polygonRight << QPointF(422,66) << QPointF(402,96) << QPointF(422,126) << QPointF(442,96);
	painter.drawPolygon(polygonRight);

	// 嘴-开放折线
	QPolygonF polyline;
	polyline << QPointF(154,146) << QPointF(172,156) << QPointF(325,154) << QPointF(344,135);
	painter.drawPolyline(polyline);

	// 左眼-椭圆
	painter.drawEllipse(154, 79, 32, 33);
		// 小试牛刀，体验一下坐标转换
		painter.save();
		painter.translate(170, 95); // 把瞳孔画在眼睛(椭圆)的中心位置。抱歉，把眼睛画成铜钱啦。
		painter.rotate(45);
		painter.drawRect(-5, -5, 10, 10);
		painter.restore();

	// 右眼-椭圆
	painter.drawEllipse(300, 79, 32, 33);
		// 右边也来一下
		painter.save();
		painter.translate(316, 95); // 把瞳孔画在眼睛(椭圆)的中心位置
		painter.rotate(45);
		painter.drawRect(-5, -5, 10, 10);
		painter.restore();	

	// 文本
	painter.drawText(QPointF(202,266), "Hi! I'm ROBO!");
	//painter.drawText(QPointF(182,206), "Hi! I'm ROBO!");

	// 鼻子-弦
	QRectF rctChord(219,110,45,60);
	painter.drawChord(rctChord, 40 * 16, 103 * 16); // 需要将角度转换为弧度

	// 左脚-扇形
	QRectF rctPieLeft(20.5,200.5,269,85);
	painter.drawPie(rctPieLeft, 90 * 16, 90 * 16); // 需要将角度转换为弧度
	
	// 右脚-扇形
	QRectF rctPieRight(221,200.5,269,85);
	painter.drawPie(rctPieRight, 0 * 16, 90 * 16); // 需要将角度转换为弧度

	QRectF rctImage(51,300.5,300,300);
	painter.drawImage(rctImage, m_img); 

	painter.end();
	//update();
}

