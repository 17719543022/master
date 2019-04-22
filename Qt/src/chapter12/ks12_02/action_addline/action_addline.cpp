/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: action_addline.cpp
\brief 演示用头文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2019/3
*/

#include <QAction>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QWidget>

#include "action_addline.h"

extern "C"
{
	/// 生成action
    CActionObjectInterface* createAction(int i)
	{
        CActionAddLineObject* pObject1 = new CActionAddLineObject;
        CActionObjectInterface* pObject = pObject1;
        QAction* pAction = NULL;
        pAction = new QAction(QObject::tr("addline"), pObject);
        pAction->setStatusTip(QObject::tr("add line"));
        pObject->setAction(pAction);
        QObject::connect(pAction, &QAction::triggered, pObject1, &CActionAddLineObject::slot_addLine);
        return pObject;
	}
};

void CActionAddLineObject::slot_addLine()
{
    static double s_PosX = 0.f;
    static double s_PosY = 0.f;
    QGraphicsView* pView = getView();
    QGraphicsScene* pScene = pView->scene();
    QGraphicsLineItem* pItem = new QGraphicsLineItem();
    pItem->setLine(s_PosX, s_PosY, 100., 100.f);
    pScene->addItem(pItem);

    s_PosX += 60.f;
    s_PosY += 30.f;
}