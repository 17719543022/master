/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: action_addline.h
\brief 演示用头文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2019/3
*/

#ifndef ACTION_ADDLINE_H
#define ACTION_ADDLINE_H

#ifdef WIN32		// windows platform
#	if defined __ACTION_ADDLINE_SOURCE__
#		define EXPORT_ACTION_ADDLINE __declspec(dllexport)
#	else
#		define EXPORT_ACTION_ADDLINE __declspec(dllimport)
#	endif
#else				// other platform
#  define EXPORT_ACTION_ADDLINE
#endif // WIN32

#include "qglobal.h"
#include "ks12_02/action_interface.h"

QT_BEGIN_NAMESPACE
class QAction;
class QWidget;
class QGraphicsView;
QT_END_NAMESPACE

class CActionObject;
// 获取插件指针的导出函数
extern "C"
{
    EXPORT_ACTION_ADDLINE CActionObjectInterface* createAction(int i);
};

class CActionAddLineObject : public CActionObjectInterface
{
    Q_OBJECT
public:
    CActionAddLineObject() :CActionObjectInterface(){ ; }
    ~CActionAddLineObject() {}
public:
public slots:
    void slot_addLine();
private:
};
#endif // ACTION_ADDLINE_H
