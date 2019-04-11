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
	
}


void CCustomWidget::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
}



