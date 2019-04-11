#ifndef _TOOLBARCONTAINER_H_
#define _TOOLBARCONTAINER_H_

#include <QFrame>
#include <QVector>

#include "uifiledef.h"

class QLayoutItem;
class QStackedWidget;


class CToolBarPage;
class CToolBarPanel;

class CToolBarContainer : public QFrame
{
	Q_OBJECT
public:
	CToolBarContainer(QWidget* parent);
	virtual ~CToolBarContainer();

	//添加工具页
	bool addPage(CToolBarPage* page);

	QStackedWidget* getStackWidget(void) const
	{
		return m_pStackWidget;
	}

	//添加对应关系
	void addPagePanel(QString page,QStringList panels);

	//删除工具页
	void removePage(int id);

	// 外部传入一个按钮到二级工具条
	bool addTool(const QString& page_name, const QString& panel_name, QWidget* tool, PToolPos pToolPos);

	//从外部传入一个SpaceItem
	bool addLayoutItem(const QString& page_name, const QString& panel_name, QLayoutItem* tool, PToolPos pToolPos);

	// 隐藏一个工具面板
	void updatePanel(const QString& page_name,const QString& panel_name,bool bShown = true);

signals:
	void loseFocus();
public slots:
	void onPageChanged(const QString&);
	void onPageChanged(const int&);

protected:
	virtual void focusOutEvent(QFocusEvent *);
private:
	QStackedWidget* m_pStackWidget;
	QVector<CToolBarPage*> m_pages;//容器里包含的页
	bool m_bMouseIn;		//鼠标是否在qmenu内

};

#endif // _TOOLBARCONTAINER_H_
