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

#include <QApplication>
#include <QClipboard>
#include <QDebug>
#include <QDomDocument>
#include <QDomElement>
#include <QGraphicsItem>
#include <QMimeData>
#include <QMouseEvent>
#include <QTextStream>

#include "ellipseitem.h"
#include "rectitem.h"

#include "base/basedll/baseapi.h"




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

#ifndef QT_NO_CLIPBOARD
void CGraphView::cut()
{
    QGraphicsScene* pScene = scene();
    QList<QGraphicsItem*> lst = pScene->items(m_ptScene);
    if (lst.size() == 0)
        return;
    // 此处剪切的处理是隐藏图元，然后拷贝。当然也可以删除图元，
    //   但是如果删除图元，则会影响redo/undo的实现。
    QList<QGraphicsItem*>::iterator ite = lst.begin();
    for (ite = lst.begin(); ite != lst.end(); ite++) {
        (*ite)->setVisible(false);
    }
    copyItems(lst);
}

void CGraphView::copy()
{
    QGraphicsScene* pScene = scene();
    QList<QGraphicsItem*> lst = pScene->items(m_ptScene);

    copyItems(lst);
}


void CGraphView::copyItems(QList<QGraphicsItem*>& lst)
{
    // 清除剪贴板的原数据
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->clear();
   
    // 如果没有图元可拷贝，则返回。 
    if (lst.size() == 0)
        return;
    
    QByteArray dataArr;
    // 拷贝的信息写到数据流
    QTextStream stream(&dataArr, QIODevice::WriteOnly);

    // 只拷贝选中图元中第一个图元
    QList<QGraphicsItem*>::iterator iteLst = lst.begin();
    QGraphicsItem* pItem = *iteLst;
    qint64 type =  pItem->type();
    QPointF pt = pItem->pos();

    QDomDocument document;
    QDomElement root = document.createElement("doc");

    // 图元信息
    QDomElement itemEle = document.createElement("item");

    itemEle.setAttribute("type", type);
    itemEle.setAttribute("x", pt.x());
    itemEle.setAttribute("y", pt.y());

    switch (type) {
    case QGraphicsItem::UserType+1:
    {
        CGraphRectItem* pRectItem = dynamic_cast<CGraphRectItem*>(pItem);
        if (NULL != pRectItem) {
            itemEle.setAttribute("w", pRectItem->getWidth());
            itemEle.setAttribute("h", pRectItem->getHeight());
        }
    }
        break;
    case QGraphicsItem::UserType + 2:
    {
        CGraphEllipseItem* pEllipseItem = dynamic_cast<CGraphEllipseItem*>(pItem);
        if (NULL != pEllipseItem) {
            itemEle.setAttribute("w", pEllipseItem->getWidth());
            itemEle.setAttribute("h", pEllipseItem->getHeight());
        }
    }
    break;
    }

    root.appendChild(itemEle);
    document.appendChild(root);
    stream << document;

    QMimeData* data = new QMimeData();
    data->setData("gp/copyItem", dataArr);
    clipboard->setMimeData(data);
}

void CGraphView::paste()
{
    QClipboard* clipboard = QApplication::clipboard();
    const QMimeData* mimeData = clipboard->mimeData();
    QGraphicsScene* pScene = scene();
    if (NULL == pScene)
        return;

    if (mimeData->hasFormat("gp/copyItem"))
    {
        QDomDocument doc;
        doc.setContent(mimeData->data("gp/copyItem"));
        QDomElement root = doc.firstChildElement();
        QDomElement itemEle = root.firstChildElement();
        QString strTagName = itemEle.tagName();
        qDebug() << strTagName;
        if (strTagName != "item")
        {
            return;
        }

        QString strValue = itemEle.attribute("type", "0");
        qint64 type = strValue.toUInt();
        //QPointF pt(itemEle.attribute("x").toDouble()+30, 
        //                itemEle.attribute("y").toDouble()+30);
        QPointF pt = m_ptScene;
        if (itemEle.hasAttribute("w")) {
            qreal w = itemEle.attribute("w", 0).toDouble();
            qreal h = itemEle.attribute("h", 0).toDouble();
            switch (type)
            {
            case QGraphicsItem::UserType + 1:
            {
                //QPen pn(Qt::darkBlue);
                //QBrush brsh(Qt::darkBlue);
                CGraphRectItem* pItem = new CGraphRectItem();
                pItem->setWidth(w);
                pItem->setHeight(h);
                pItem->setPos(pt);
                pScene->addItem(pItem);
            }
            break;
            case QGraphicsItem::UserType + 2:
            {
                //QPen pn(Qt::darkBlue);
                //QBrush brsh(Qt::darkBlue);
                CGraphEllipseItem* pItem = new CGraphEllipseItem();
                pItem->setWidth(w);
                pItem->setHeight(h);
                pItem->setPos(pt);
                pScene->addItem(pItem);
            }
            break;
            default:
                return;
            }
        }
    }
}
#endif

void CGraphView::mouseMoveEvent(QMouseEvent *e)
{
    QPointF pt = mapToScene(e->localPos().toPoint());
    emit(viewMouseMove(pt)); // 触发信号，以便可以在状态栏显示鼠标坐标
}