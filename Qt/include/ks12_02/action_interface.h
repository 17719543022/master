/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: action_interface.h
\brief 演示用头文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2019/3
*/

#ifndef ACTION_INTERFACE_H
#define ACTION_INTERFACE_H

//#ifdef WIN32		// windows platform
//#	if defined __ACTION_INTERFACE_SOURCE__
//#		define EXPORT_ACTION_INTERFACE __declspec(dllexport)
//#	else
//#		define EXPORT_ACTION_INTERFACE __declspec(dllimport)
//#	endif
//#else				// other platform
//#  define EXPORT_ACTION_INTERFACE
//#endif // WIN32

#include "qglobal.h"
#include <QObject>

QT_BEGIN_NAMESPACE
class QAction;
class QWidget;
class QGraphicsView;
QT_END_NAMESPACE

class CActionObjectInterface : public QObject
{
public:
    CActionObjectInterface() :m_pView(NULL), m_pAction(NULL){ ; }
    virtual ~CActionObjectInterface() {}
public:
    void setView(QGraphicsView* pView) { m_pView = pView; }
    QGraphicsView* getView() { return m_pView; }
    void setAction(QAction* pAction) { m_pAction = pAction; }
    QAction* getAction() { return m_pAction; }
private:
    QGraphicsView * m_pView;
    QAction * m_pAction;

};
#endif // ACTION_ADDLINE_H
