#ifndef _TOOLBARBUTTON_H
#define _TOOLBARBUTTON_H

#include <QPushButton>


class QAction;


class CMyPushButton : public QPushButton
{
	Q_OBJECT
public:
	CMyPushButton(const QString &text, QWidget *parent = 0);
	~CMyPushButton();


public:
	//设置按钮的Action
	void setAction(QAction *action);
	
	//设置按钮图片
	void setStateIcon(const QString& normUrl, const QString& overUrl, const QString& downUrl, const QString& disableUrl);

protected:
	bool eventFilter(QObject *, QEvent *);
protected slots :
	void onActionChanged();//根据Action状态自动调整按钮状态
	
private:
	void setButtonStyle(bool isEnable);

private:
	QAction* m_pAction;			//按钮对应的Aciton

	QString m_IconNormUrl;			//正常状态图片
	QString m_IconOverUrl;			//鼠标焦点状态图片
	QString m_IconDownUrl;			//鼠标按下状态图片
	QString m_IconDisableUrl;		//不可用状态图片
};

#endif