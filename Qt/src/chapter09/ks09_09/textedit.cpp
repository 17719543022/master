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
#include "base/basedll/baseapi.h"
#include <QPaintEvent>
#include <QTextStream>



CTextEdit::CTextEdit(QWidget* parent) : QTextEdit(parent)
{
	setMouseTracking(true);
}


void CTextEdit::paintEvent(QPaintEvent *event)
{	

	QPainter painter;
	painter.begin(viewport());
	painter.setRenderHint(QPainter::Antialiasing, true);
	
	painter.setPen(Qt::blue);

	painter.fillRect(event->rect(), QColor(0, 255, 255, 100));

	QFont ft("宋体", 18);
	ft.setItalic(true);
	painter.setFont(ft);
	painter.drawText(QPointF(100,100), "file read ok!");

	painter.end();
	QTextEdit::paintEvent(event);

}

void CTextEdit::mouseMoveEvent(QMouseEvent *e)
{
	QTextEdit::mouseMoveEvent(e); // 首先，调用基类接口
//	QTextCursor curCursor = textCursor();
	emit(viewMouseMove(e));
}
bool CTextEdit::openFile(const QString& strFile)
{
	QFile file;
	file.setFileName(strFile);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		return false;
	}
	QTextStream input(&file);
	input.setCodec("GBK"); // 读者可以试试用: UTF-8。

	QString str = input.readAll();
	setText(str);

	m_strFileName = strFile;
	
	return true;
}