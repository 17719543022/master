#ifndef _TOOLBARPAGE_H_
#define _TOOLBARPAGE_H_

#include <QVector>

#include "uifiledef.h"

class QLayoutItem;


class CToolBarPanel;

// 本类不缓存按钮及Widget对象，由外部创建者自行缓存和销毁
class CToolBarPage : public QWidget
{
public:
	CToolBarPage(QWidget* parent, int id,Qt::WindowFlags f = 0);
	virtual ~CToolBarPage();

	// 获得页面唯一ID
	int getPageId()
	{
		return m_id;
	};

	//设置面板间距
	void setPanelGap(int gap)
	{
		m_gap = gap;
	}

	//增加和删除面板
	bool addPanel(CToolBarPanel* panel);
	void removePanel(int id);

	// 外部增加工具按钮到指定面板
	bool addTool(const QString& panel_name, QWidget* tool, PToolPos pToolPos);

	// 外部增加一个布局工具
	bool addLayoutItem(const QString& panel_name, QLayoutItem* tool, PToolPos pToolPos);

	// 更新面板显示
	void updatePanel(const QString& panel_name,bool bShown = true);

protected:
	virtual void resizeEvent(QResizeEvent * e);


private:
	int m_id;	//页面唯一标识
	int m_gap; //两个面板的间隙

	QVector<CToolBarPanel*>		m_panels;
};

#endif // _TOOLBARPAGE_H_
