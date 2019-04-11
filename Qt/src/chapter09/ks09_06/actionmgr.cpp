
#include <QAction>

#include "actionmgr.h"


CActionMgr* CActionMgr::pInstance = NULL;
CActionMgr::CActionMgr()
{
	pActionMap.clear();
}
CActionMgr::~CActionMgr()
{
}

CActionMgr* CActionMgr::instance()
{
	if (NULL == pInstance)
	{
		pInstance = new CActionMgr;
	}
	return pInstance;
}

void CActionMgr::destroy()
{
	if (NULL != pInstance)
	{
		delete pInstance;
		pInstance = NULL;
	}
}

void CActionMgr::initInstance()
{


}

void CActionMgr::exitInstance()
{

}

QAction* CActionMgr::getAction(CActionenum::EDrawAction eAction)const
{
	QMap<CActionenum::EDrawAction, QAction*>::const_iterator it = pActionMap.find(eAction);
	if (it!= pActionMap.end())
	{
		QAction* retAction = it.value();
		return retAction;
	}
	return NULL;
}

QWidget* CActionMgr::getWidget(CActionenum::EDrawWidget eWidget)const
{
	QMap<CActionenum::EDrawWidget, QWidget*>::const_iterator it = pWidgetMap.find(eWidget);
	if (it != pWidgetMap.end())
	{
		QWidget* retWidget = it.value();
		return retWidget;
	}
	return NULL;
}

void CActionMgr::addAction(CActionenum::EDrawAction eAction, QAction* pAction)
{
	pActionMap.insert(eAction, pAction);
}

void CActionMgr::addWidget(CActionenum::EDrawWidget eWidget, QWidget* pWidget)
{
	pWidgetMap.insert(eWidget, pWidget);
}
