/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: listwidget.cpp
\brief	
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9 

*/
#include "listwidget.h"
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>


CListWidget::CListWidget(QWidget* parent) : QListWidget(parent)
{
	setAcceptDrops(true);
}

//! 析构函数
CListWidget::~CListWidget()
{

}

/**
* @brief 拖拽进入事件响应
* @param[in] event 拖拽事件
*/
void CListWidget::dragEnterEvent(QDragEnterEvent* event)
{
	if (event->mimeData()->hasFormat("dnd/format"))
	{
		event->setDropAction(Qt::MoveAction);
		event->setAccepted(true);
	}
	else
	{
		event->setAccepted(false);
	}
}

/**
* @brief 拖拽移动事件响应
* @param[in] event 拖拽事件
*/
void CListWidget::dragMoveEvent(QDragMoveEvent* event)
{
	if (event->mimeData()->hasFormat("dnd/format"))
	{
		event->setAccepted(true);
		event->setDropAction(Qt::MoveAction);
	}
	else
	{
		event->setAccepted(false);
	}
}

/**
* @brief 拖拽离开事件响应
* @param[in] event 拖拽事件
*/
void CListWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
	QListWidget::dragLeaveEvent(event);
}

/**
* @brief 拖拽放下事件响应
* @param[in] event 拖拽事件
*/
void CListWidget::dropEvent(QDropEvent *event)
{
	if (event->mimeData() && event->mimeData()->hasFormat("dnd/format"))
	{
		QByteArray mimeData = event->mimeData()->data("dnd/format");
		QString info;
		QDomDocument document;
		document.setContent(mimeData);
		QDomElement rootDoc = document.firstChildElement();
		if (rootDoc.isNull() || (rootDoc.tagName() != "root"))
			return;
		QDomElement eleDoc = rootDoc.firstChildElement();
		// 判断格式的合法性
		if (eleDoc.isNull() || (eleDoc.tagName() != "document")) 
			return;
		QString strText = eleDoc.attribute("text");
		bool bBold = eleDoc.attribute("bold").toInt();
		
		QListWidgetItem* pItem = new QListWidgetItem(strText, this);
		QFont ft = pItem->font();
		ft.setBold(bBold);
		pItem->setFont(ft);
		addItem(pItem);
	}
}