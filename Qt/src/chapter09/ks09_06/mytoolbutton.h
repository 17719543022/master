
#ifndef _MYTOOLBUTTON_H_
#define _MYTOOLBUTTON_H_

#include <QToolButton>

class CToolButtonDecorator:public QObject
{
	Q_OBJECT
public:
	CToolButtonDecorator(QObject* parent = 0);
	~CToolButtonDecorator();

	void setToolButton(QToolButton* pToolButton);

	void setToolButtonIcon(const QString& norm, const QString& over, const QString& down, const QString&disable);

	QToolButton* getToolButton();

	void onToolButtonChange();

private:
	QToolButton* m_pToolButton;
	QString m_NormIcon;
	QString m_OverIcon;
	QString m_DownIcon;
	QString m_DisableIcon;
};

#endif

