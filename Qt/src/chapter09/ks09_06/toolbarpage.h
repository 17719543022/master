#ifndef _TOOLBARPAGE_H_
#define _TOOLBARPAGE_H_

#include <QVector>

#include "uifiledef.h"

class QLayoutItem;


class CToolBarPanel;

// ���಻���水ť��Widget�������ⲿ���������л��������
class CToolBarPage : public QWidget
{
public:
	CToolBarPage(QWidget* parent, int id,Qt::WindowFlags f = 0);
	virtual ~CToolBarPage();

	// ���ҳ��ΨһID
	int getPageId()
	{
		return m_id;
	};

	//���������
	void setPanelGap(int gap)
	{
		m_gap = gap;
	}

	//���Ӻ�ɾ�����
	bool addPanel(CToolBarPanel* panel);
	void removePanel(int id);

	// �ⲿ���ӹ��߰�ť��ָ�����
	bool addTool(const QString& panel_name, QWidget* tool, PToolPos pToolPos);

	// �ⲿ����һ�����ֹ���
	bool addLayoutItem(const QString& panel_name, QLayoutItem* tool, PToolPos pToolPos);

	// ���������ʾ
	void updatePanel(const QString& panel_name,bool bShown = true);

protected:
	virtual void resizeEvent(QResizeEvent * e);


private:
	int m_id;	//ҳ��Ψһ��ʶ
	int m_gap; //�������ļ�϶

	QVector<CToolBarPanel*>		m_panels;
};

#endif // _TOOLBARPAGE_H_
