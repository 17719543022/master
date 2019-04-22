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

	//��ӹ���ҳ
	bool addPage(CToolBarPage* page);

	QStackedWidget* getStackWidget(void) const
	{
		return m_pStackWidget;
	}

	//��Ӷ�Ӧ��ϵ
	void addPagePanel(QString page,QStringList panels);

	//ɾ������ҳ
	void removePage(int id);

	// �ⲿ����һ����ť������������
	bool addTool(const QString& page_name, const QString& panel_name, QWidget* tool, PToolPos pToolPos);

	//���ⲿ����һ��SpaceItem
	bool addLayoutItem(const QString& page_name, const QString& panel_name, QLayoutItem* tool, PToolPos pToolPos);

	// ����һ���������
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
	QVector<CToolBarPage*> m_pages;//�����������ҳ
	bool m_bMouseIn;		//����Ƿ���qmenu��

};

#endif // _TOOLBARCONTAINER_H_
