/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.cpp
\brief	
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9 

*/
#include <QGridLayout>
#include <QPainter>

#include "dialog.h"
#include "customwidget.h"


CDialog::CDialog(QWidget* parent) : QDialog(parent)
{
	ui.setupUi(this);

	QGridLayout* gridLayout = new QGridLayout(this);
	gridLayout->setObjectName(QStringLiteral("gridLayout"));

	m_pWidget = new CCustomWidget(this);
	gridLayout->addWidget(m_pWidget, 0, 0);
}

void CDialog::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	QPainter painter;
	painter.begin(this);
	painter.setPen(Qt::blue);
	painter.drawText(QPointF(-20, 80), "Painted Text");
	painter.end();
}