/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: textedit.cpp
\brief	
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9 

*/
#include "textedit.h"
#include <QPainter>
#include <QPaintEvent>



CTextEdit::CTextEdit(QWidget* parent) : QTextEdit(parent)
{
}


void CTextEdit::paintEvent(QPaintEvent *event)
{	

	QPainter painter;
	painter.begin(viewport());
	painter.setRenderHint(QPainter::Antialiasing, true);
	
	painter.setPen(Qt::blue);

	painter.fillRect(event->rect(), QColor(0, 255, 255, 100));

	QFont ft("宋体", 18);
	painter.setFont(ft);
	painter.drawText(QPointF(100,100), "file read ok!");

	painter.end();
	QTextEdit::paintEvent(event);

}

