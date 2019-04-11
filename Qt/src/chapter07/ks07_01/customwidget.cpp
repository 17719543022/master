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
#include <QMovie>
#include <QPainter>
#include <QPaintEvent>


CCustomWidget::CCustomWidget(QWidget* parent) : QWidget(parent)
{
	ui.setupUi(this);
	initialize();
}
void CCustomWidget::initialize() {

	QString imgStr(":/images/rainman.gif");
	m_movie = new QMovie(imgStr);
	m_movie->setScaledSize(QSize(ui.label_gif->geometry().size()));
	ui.label_gif->setMovie(m_movie);
	m_movie->start();
	m_transparentLabel = new QLabel(this);
	m_transparentLabel->setText("Can You See Me?");
	m_transparentLabel->setGeometry(100, 250, 100, 30);
	m_transparentLabel->setStyleSheet("color: rgb(255, 48, 190);border:none");
}


void CCustomWidget::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	m_movie->setScaledSize(QSize(ui.label_gif->geometry().size()));
	QRectF rctGif = ui.label_gif->geometry();
	qreal x = rctGif.x()+rctGif.width()/3.f;
	qreal y = rctGif.y() + rctGif.height() / 6;
	m_transparentLabel->setGeometry(x, y, 100, 30);
}

void CCustomWidget::paintEvent(QPaintEvent *event)
{	
	QWidget::paintEvent(event);
	QPainter painter;
	painter.begin(this);
	painter.setPen(Qt::red);
	QFont ft("宋体", 26);
	painter.setFont(ft);
	painter.drawText(QPointF(ui.label_gif->geometry().bottomLeft()+QPointF(10, 12)), "Painted Text in CustomWidget");
	painter.end();
	//update();
}

