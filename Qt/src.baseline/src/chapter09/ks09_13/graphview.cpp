/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: graphview.cpp
\brief	
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9 

*/
#include "graphview.h"
#include "base/basedll/baseapi.h"
#include <QMouseEvent>



CGraphView::CGraphView(QWidget* parent) : QGraphicsView(parent)
{
    setMouseTracking(true);

}

CGraphView::~CGraphView()
{
}

void CGraphView::mousePressEvent(QMouseEvent *event)
{
    QMatrix matx = matrix();
    matx.m11();
    m_ptView = event->localPos();
    m_ptScene = mapToScene(m_ptView.toPoint());
    qDebug()<<m_ptView.x()<<","<<m_ptView.y() << " " << m_ptScene.x() << "," << m_ptScene.y();
}
void CGraphView::addRect()
{
    QGraphicsScene* pScene = scene();
    CGraphRectItem* pItem = new CGraphRectItem();
    pItem->setWidth(50);
    pItem->setHeight(50);
    pItem->setPos(m_ptScene);
    pScene->addItem(pItem);
}

void CGraphView::addEllipse()
{
    QGraphicsScene* pScene = scene();
    CGraphEllipseItem* pItem = new CGraphEllipseItem();
    pItem->setWidth(50);
    pItem->setHeight(50);
    pItem->setPos(m_ptScene);
    pScene->addItem(pItem);
}

void CGraphView::drawBackground(QPainter *painter, 
    const QRectF &rect)
{
    QGraphicsView::drawBackground(painter, rect);

    // 绘制一个矩形用来表示场景(scene)的占用区域
    QRectF rct = sceneRect();
    QPen pn = painter->pen();
    pn.setColor(Qt::gray);
    painter->setPen(pn);
    painter->drawRect(rct);
}
void CGraphView::mouseMoveEvent(QMouseEvent *e)
{
    QPointF pt = mapToScene(e->localPos().toPoint());
    emit(viewMouseMove(pt)); // 触发信号，以便可以在状态栏显示鼠标坐标
}