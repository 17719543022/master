#ifndef _TOOLBARPANEL_H_
#define _TOOLBARPANEL_H_

#include <QWidget>

class CToolBarPanel : public QWidget  
{
	Q_OBJECT
public:
	CToolBarPanel(QWidget * parent,int id);
	virtual ~CToolBarPanel();

	int getPanelId()
	{
		return m_id;
	};

	QString getName()
	{
		return m_name;
	}
	// ��������
	void setName(const QString& name)
	{
		m_name = name;
	};

protected:
	virtual void resizeEvent(QResizeEvent * e);

private:
	int m_id;
	QString     m_name;		//�������
};

#endif // _TOOLBARPANEL_H_
