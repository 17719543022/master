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
#include "base/basedll/baseapi.h"
#include <QApplication>
#include <QDrag>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QMimeData>
#include <QPainter>
#include <QPaintEvent>
#include <QTextStream>



CTextEdit::CTextEdit(QWidget* parent) : QTextEdit(parent)
{
	setMouseTracking(true);
	m_bDrag = false;
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

void CTextEdit::mousePressEvent(QMouseEvent *e) {
	QTextEdit::mousePressEvent(e); // 首先，调用基类接口
	
	m_ptMousePress = e->globalPos();
	QTextCursor tc = textCursor();			// 获取光标下选中的文本对象
	if (tc.selectedText().length()>0)
		m_bDrag = true;
}
void CTextEdit::mouseReleaseEvent(QMouseEvent *e) {
	QTextEdit::mouseReleaseEvent(e); // 首先，调用基类接口
	m_bDrag = false;
}
void CTextEdit::mouseMoveEvent(QMouseEvent *e)
{
	emit(viewMouseMove(e)); // 触发信号，以便可以在状态栏显示鼠标坐标

	Qt::MouseButtons btns = e->buttons();
	if (!(btns | Qt::NoButton)) {
		m_bDrag = false;
	}
	bool bDistance = false;
	QPoint ptDistance = e->globalPos() - m_ptMousePress;
	if (ptDistance.manhattanLength() > QApplication::startDragDistance())
	{ // 超过允许的拖放距离才启动拖放操作
		bDistance = true;
	}
	if (m_bDrag && 
		 bDistance && 
		 (btns & Qt::LeftButton))	{
		m_bDrag = false;
		QTextCursor tc = textCursor();			// 获取光标下选中的文本对象
		QTextCharFormat textCharFormat = tc.charFormat(); // 获取它的格式
		bool b = textCharFormat.font().bold(); // 获取字体的粗体信息
		
		// 开始准备拖放的数据
		QMimeData *mimeData = new QMimeData;
		QByteArray itemData;
		QTextStream textStream(&itemData, QIODevice::ReadWrite);
		textStream.setCodec("UTF-8");
		
		QDomDocument doc;
		QDomElement rootDoc = doc.createElement("root");
		doc.appendChild(rootDoc);
		QDomElement eleDoc = doc.createElement("document");
		eleDoc.setAttribute("text", tc.selectedText());
		eleDoc.setAttribute("bold", b);
		rootDoc.appendChild(eleDoc);
		doc.save(textStream, 1, QDomNode::EncodingFromTextStream);

		mimeData->setData("dnd/format", itemData);
		QDrag *drag = new QDrag(this);
		drag->setMimeData(mimeData);
		//QPixmap img;
		//img.load(":/images/dnd.png");
		//drag->setPixmap(img);
		//drag->setHotSpot(hotSpot);
		if (drag->exec(Qt::DropActions(Qt::MoveAction | Qt::CopyAction), Qt::CopyAction) == Qt::MoveAction)
		{
		}
		return;
	}
	QTextEdit::mouseMoveEvent(e); // 首先，调用基类接口

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