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
//#include <QDebug>
#include <QDomDocument>
#include <QDomElement>
#include <QGraphicsItem>
#include <QMenu>
#include <QMimeData>
#include <QMouseEvent>
#include <QTextStream>

#include "ellipseitem.h"
#include "rectitem.h"

#include "base/basedll/baseapi.h"


CGraphView::CGraphView(QWidget* parent) : QGraphicsView(parent)
{
    setMouseTracking(true);
    createActions();
}

CGraphView::~CGraphView()
{	
}
void CGraphView::keyPressEvent(QKeyEvent *event)
{
    QPointF ptOffset;
    qreal dCoef = 1.f;
    if (event->modifiers()& Qt::AltModifier) {
        dCoef = 4.f;
    }
    switch (event->key()) {
    case Qt::Key_Up:
        ptOffset.setY(-2.f*dCoef);
        break;
    case Qt::Key_Down:
        ptOffset.setY(2.f*dCoef);
        break;
    case Qt::Key_Left:
        ptOffset.setX(-2.f*dCoef);
        break;
    case Qt::Key_Right:
        ptOffset.setX(2.f*dCoef);
        break;
    default:
        return;
    }
    QList<QGraphicsItem*>::iterator iteLst = m_selectedItems.begin();
    for (; iteLst != m_selectedItems.end(); iteLst++) {
        (*iteLst)->moveBy(ptOffset.x(), ptOffset.y());
    }
}

void CGraphView::mousePressEvent(QMouseEvent *event)
{
    QPointF ptView = event->localPos();
    m_ptScene = mapToScene(ptView.toPoint());
    m_ptLastMousePosition = m_ptScene;
    QList<QGraphicsItem*> lst = items(ptView.toPoint());
    if (0 == lst.size()) {
        m_selectedItems.clear();
    }
    else {
        QGraphicsItem* pItem = *(lst.begin());
        if (!m_selectedItems.contains(pItem)) {
            if (!(event->modifiers() && Qt::ControlModifier)) {
                m_selectedItems.clear();
            }
            m_selectedItems.append(pItem);
        }
    }
    QGraphicsView::mousePressEvent(event);
    viewport()->update();
}

void CGraphView::drawForeground(QPainter *painter, const QRectF &rect)
{
    if (m_selectedItems.size() > 0)
    {
        QPolygonF path;
        QRectF rct;
        QList<QGraphicsItem*>::iterator ite = m_selectedItems.begin();
        QPen pn = painter->pen();
        pn.setStyle(Qt::DotLine);
        CGraphItemBase* pItem = NULL;
        painter->setPen(pn);
        for (ite = m_selectedItems.begin(); ite != m_selectedItems.end(); ite++) {
            pItem = dynamic_cast<CGraphItemBase*>(*ite);
            if (NULL == pItem)
                continue;
            rct = pItem->getItemRect();
            rct.setWidth(rct.width() + 3);
            rct.setHeight(rct.height() + 3);
            rct.setLeft(rct.left() - 1.5f);
            rct.setTop(rct.top() - 1.5f);
            path = (*ite)->mapToScene(rct);
            painter->drawPolygon(path);
        }
    }
    QGraphicsView::drawForeground(painter, rect);
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
       // qDebug() << strTagName;
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
    QPointF ptOffset = pt - m_ptLastMousePosition;
    m_ptLastMousePosition = pt;
    if (e->buttons()&Qt::LeftButton)
    {
        QList<QGraphicsItem*>::iterator iteLst = m_selectedItems.begin();
        for (; iteLst != m_selectedItems.end(); iteLst++) {
            (*iteLst)->moveBy(ptOffset.x(), ptOffset.y());
        }
    }
}

void CGraphView::createActions()
{
#ifndef QT_NO_CLIPBOARD
    m_pCutAct = new QAction(tr("&cut"), this);
    m_pCutAct->setStatusTip(tr("cut the selected text to the clipboard"));
    connect(m_pCutAct, SIGNAL(triggered()), this, SLOT(cut()));

    m_pCopyAct = new QAction(tr("&copy"), this);
    m_pCopyAct->setShortcuts(QKeySequence::Copy);
    m_pCopyAct->setStatusTip(tr("Copy selected content to the clipboard"));
    connect(m_pCopyAct, SIGNAL(triggered()), this, SLOT(copy()));

    m_pPasteAct = new QAction(tr("&paste"), this);
    m_pPasteAct->setShortcuts(QKeySequence::Paste);
    m_pPasteAct->setStatusTip(tr("Paste the contents of the clipboard to the current location"));
    connect(m_pPasteAct, SIGNAL(triggered()), this, SLOT(paste()));
#endif
}

#ifndef QT_NO_CONTEXTMENU
void CGraphView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu* pPopMenu = new QMenu(this);
    #ifndef QT_NO_CLIPBOARD
    m_ptScene = mapToScene(event->pos());
    QGraphicsScene* pScene = scene();
    QList<QGraphicsItem*> lst = pScene->items(m_ptScene);
    if (0 != lst.size())
    {
        pPopMenu->addAction(m_pCutAct);
        pPopMenu->addAction(m_pCopyAct);
     }
    else {
        pPopMenu->addAction(m_pPasteAct);

        // 判断一下有没有事先执行过剪切、拷贝操作
        QClipboard* clipboard = QApplication::clipboard();
        const QMimeData* mimeData = clipboard->mimeData();
        if (!mimeData->hasFormat("gp/copyItem"))
        {
            m_pPasteAct->setEnabled(false);
        }
    }
    #endif

    QPoint popPt = event->globalPos();
    pPopMenu->move(popPt);
    pPopMenu->show();
}
#endif