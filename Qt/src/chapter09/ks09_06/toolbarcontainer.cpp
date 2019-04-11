#include <QFocusEvent>
#include <QHBoxLayout>
#include <QStackedWidget>

#include "publicinfomgr.h"
#include "toolbarcontainer.h"
#include "toolbarpage.h"
#include "toolbarpanel.h"

CToolBarContainer::CToolBarContainer(QWidget* parent)
: QFrame(parent), m_pStackWidget(NULL)
{
	//QString widgetStyle = QString::fromLocal8Bit(
	//	" QFrame{ background-image:url('%1');border:none;margin:0px}"
	//	).arg(CPublicInfoMgr::instance()->getUiIconPathName("mainbar/bg_01",eState_SingleState));
	QString widgetStyle = QString::fromLocal8Bit(
		" QFrame{ background:rgb(225,241,245);border:none;margin:0px}"
		);
	
	setStyleSheet(widgetStyle);
	setMouseTracking(false);
	setFrameShape(QFrame::Panel);
	//setCurrentIndex(1);
	QHBoxLayout* layout = new QHBoxLayout;
	m_pStackWidget = new QStackedWidget();
	layout->addWidget(m_pStackWidget);
	layout->setContentsMargins(0, 0, 0, 0);//设置布局与窗口间隔
	setLayout(layout);
	m_bMouseIn = false;

}

CToolBarContainer::~CToolBarContainer()
{
}

bool CToolBarContainer::addPage(CToolBarPage* page)
{
	if (!page)
		return false;

	int id = page->getPageId();
	for (int i = 0;i < m_pages.size();++i)
	{
		if (m_pages[i]->getPageId() == id)
			return false;
	}
	m_pStackWidget->insertWidget(page->getPageId(),page );
	m_pages.push_back(page);
	return true;
}

void CToolBarContainer::removePage(int id)
{
	QVector<CToolBarPage*>::iterator it = m_pages.begin();
	for (;it != m_pages.end();++it)
	{
		if ((*it)->getPageId() == id)
		{
			m_pStackWidget->removeWidget(*it);
			m_pages.erase(it);
			break;
		}
	}
}

bool CToolBarContainer::addTool(const QString& page_name, const QString& panel_name, QWidget* tool, PToolPos pToolPos)
{
	if (page_name.isEmpty() || panel_name.isEmpty())
		return false;
	if (tool == NULL)
		return false;

	for (int i = 0;i < m_pages.size();++i)
	{
		QString name = m_pages[i]->objectName();
		if (name == page_name)
		{
			bool bRet = m_pages[i]->addTool(panel_name, tool, pToolPos);
			return bRet;
		}
	}
	return false;
}

bool CToolBarContainer::addLayoutItem(const QString& page_name, const QString& panel_name, QLayoutItem* item, PToolPos pToolPos)
{
	if (page_name.isEmpty() || panel_name.isEmpty())
		return false;
	if (item == NULL)
		return false;

	for (int i = 0; i < m_pages.size(); ++i)
	{
		QString name = m_pages[i]->objectName();
		if (name == page_name)
		{
			bool bRet = m_pages[i]->addLayoutItem(panel_name, item, pToolPos);
			return bRet;
		}
	}
	return false;
}
void CToolBarContainer::onPageChanged(const QString& name)
{
	for (int i = 0;i < m_pages.size();++i)
	{
		if (m_pages[i]->objectName() == name)
		{
			m_pStackWidget->setCurrentIndex(m_pages[i]->getPageId());
			break;
		}
	}
}

void CToolBarContainer::onPageChanged(const int& id)
{
	for (int i = 0; i < m_pages.size(); ++i)
	{
		if (m_pages[i]->getPageId() == id)
		{
			m_pStackWidget->setCurrentIndex(id);
			break;
		}
	}
}

void CToolBarContainer::updatePanel(const QString& page_name,const QString& panel_name,bool bShown)
{
	for (int i = 0;i < m_pages.size();++i)
	{
		QString name = m_pages[i]->objectName();
		if (name == page_name)
		{
			m_pages[i]->updatePanel(panel_name,bShown);
			break;
		}
	}
}

void CToolBarContainer::focusOutEvent(QFocusEvent *e)
{
	if (Qt::MouseFocusReason == e->reason())
	{
		emit loseFocus();
	}
	QFrame::focusOutEvent(e);
}
