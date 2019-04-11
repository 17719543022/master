/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: ellipseitem.cpp
\brief 演示用头文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/8
*/

#include "ellipseitem.h"

#include <QPainter>

CGraphEllipseItem::CGraphEllipseItem(QGraphicsItem * parent /* = 0 */)
    :CGraphItemBase(parent)
{
}


CGraphEllipseItem::~CGraphEllipseItem()
{
}

void CGraphEllipseItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget/* = 0*/)
{
	Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->drawEllipse(boundingRect());	
}

QRectF  CGraphEllipseItem::getItemRect() const
{
    QRectF rct(-getWidth()/2, -getHeight()/2, getWidth(), getHeight());
    return rct;
}

QRectF CGraphEllipseItem::boundingRect() const
{
    QRectF boundRt(-getWidth() / 2 - 2, -getHeight() / 2 - 2, getWidth() + 4, getHeight() + 4);
    return boundRt;
}
QPainterPath CGraphEllipseItem::shape() const
{
	QPainterPath paintPath;
    paintPath.addRect(getItemRect());
	return paintPath;
}
