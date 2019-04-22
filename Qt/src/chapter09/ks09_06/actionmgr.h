#ifndef _ACTIONMGR_H_
#define _ACTIONMGR_H_

#include <QMap>
#include <QObject>

#include "actiondef.h"

class QAction;

class CActionMgr : public QObject
{
	Q_OBJECT
public:
	//! 单体的创建与销毁
	static CActionMgr* instance();
	void destroy();

	//! 单体对象初始化，加载UI文件，解析UI信息
	void initInstance();

	//! 单体退出处理
	void exitInstance();

public:
	//获得Action指针
	QAction* getAction(CActionenum::EDrawAction eAction) const;
	QWidget* getWidget(CActionenum::EDrawWidget eWidget) const;

	void addAction(CActionenum::EDrawAction eAction, QAction* pAction);
	void addWidget(CActionenum::EDrawWidget eWidget, QWidget* pWidget);

private://以下为单体模式的私有构造函数及单体静态指针
	CActionMgr(void);
	CActionMgr(const CActionMgr&);
	CActionMgr& operator=(const CActionMgr&);
	~CActionMgr(void);
	//!单体静态指针
	static CActionMgr* pInstance;

private:
	QMap<CActionenum::EDrawAction, QAction*> pActionMap;

	QMap<CActionenum::EDrawWidget, QWidget*> pWidgetMap;
};

#endif