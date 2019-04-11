
#include <QLayout>
#include <QtEvents>
#include <QWidget>

#include "toolbarpage.h"
#include "toolbarpanel.h"

CToolBarPage::CToolBarPage(QWidget* parent, int id, Qt::WindowFlags f)
:QWidget(parent, f), m_id(id), m_gap(4)
{
	m_panels.clear();
}

CToolBarPage::~CToolBarPage()
{
	for (int i = 0;i < m_panels.size();++i)
	{
		if (m_panels[i])
			delete m_panels[i];
	}
	m_panels.clear();
}

bool CToolBarPage::addPanel(CToolBarPanel *panel)
{
	if (!panel)
		return false;

	int id = panel->getPanelId();
	int size = m_panels.size();
	for (int i = 0; i < size; ++i)
	{
		if (m_panels[i]->getPanelId() == id)
			return false;
	}

	//// 起始点坐标根据图片留2个像素偏移
	//QPoint pos(2,2);
	//if (size > 0)
	//{
	//	pos = m_panels[size - 1]->geometry().topLeft();

	//	int offset = m_panels[size - 1]->width();
	//	offset += m_gap;
	//	pos.setX(pos.x() + offset);
	//} 
	//int x = pos.x();
	//int y = pos.y();
	//int w = panel->width();
	//int h = panel->height();
	//panel->setGeometry(pos.x(),pos.y(),panel->width(),panel->height());
	panel->setFixedHeight(height());
	m_panels.push_back(panel);

	return true;
}

void CToolBarPage::removePanel(int id)
{
	if (m_panels.size() == 1)
	{
		delete m_panels[0];
		m_panels.clear();
		return;
	}

	bool bFind = false;
	QPoint pos(0,0);
	for (int i = 0;i < m_panels.size();++i)
	{
		if (m_panels[i]->getPanelId() == id)
		{
			pos = m_panels[i]->geometry().topLeft();
			delete m_panels[i];
			bFind = true;
		}
		if (bFind)
		{
			// 前移
			m_panels[i]->setGeometry (pos.x(), pos.y(), m_panels[i]->width(), m_panels[i]->height());
			pos.setX(pos.x() + m_panels[i]->width());
			m_panels[i - 1] = m_panels[i];
		}
	}
	m_panels.resize(m_panels.size() - 1);
}

bool CToolBarPage::addTool(const QString &panel_name, QWidget *tool, PToolPos pToolPos)
{
	for (int i = 0;i < m_panels.size();++i)
	{
		CToolBarPanel*  pPanel = m_panels[i];
		QString name = pPanel->getName();
		if (name == panel_name)
		{
			QGridLayout* pGridLayout = dynamic_cast<QGridLayout*>(pPanel->layout());
			//pPanel->setStyleSheet(QString::fromUtf8("border:1px solid red"));

			pGridLayout->addWidget(tool, pToolPos->m_row, pToolPos->m_col, pToolPos->m_rowSpan, pToolPos->m_colSpan,pToolPos->m_align);
		}
	}
	return true;
}

bool CToolBarPage::addLayoutItem(const QString& panel_name, QLayoutItem* item, PToolPos pToolPos)
{
	for (int i = 0; i < m_panels.size(); ++i)
	{
		CToolBarPanel*  pPanel = m_panels[i];
		QString name = pPanel->getName();
		if (name == panel_name)
		{
			QGridLayout* pGridLayout = dynamic_cast<QGridLayout*>(pPanel->layout());
			pGridLayout->addItem(item, pToolPos->m_row, pToolPos->m_col, pToolPos->m_rowSpan, pToolPos->m_colSpan,pToolPos->m_align);
		}
	}
	return true;
}

void CToolBarPage::updatePanel(const QString& panel_name,bool bShown)
{
	// 设置显示或隐藏面板
	for (int i = 0;i < m_panels.size();++i)
	{
		QString name = m_panels[i]->getName();
		if (name == panel_name)
		{
			if (bShown)
			{
				m_panels[i]->show();
				//TODO
			} 
			else
			{
				m_panels[i]->hide();
			}
			break;
		}
	}
	//重新调整显示位置
	QPoint pos(0,0);
	for (int i = 0;i < m_panels.size();++i)
	{
		m_panels[i]->setGeometry (pos.x(), pos.y(), m_panels[i]->width(), m_panels[i]->height());
		pos.setX(pos.x() + m_panels[i]->width());
	}
}

void CToolBarPage::resizeEvent(QResizeEvent * e)
{
	//int offset = e->size().width() - e->oldSize().width();
	//update(offset);
	resize(e->size().width(), height());
	QWidget::resizeEvent(e);
}