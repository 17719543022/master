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
	//���ð�ť��Action
	void setAction(QAction *action);
	
	//���ð�ťͼƬ
	void setStateIcon(const QString& normUrl, const QString& overUrl, const QString& downUrl, const QString& disableUrl);

protected:
	bool eventFilter(QObject *, QEvent *);
protected slots :
	void onActionChanged();//����Action״̬�Զ�������ť״̬
	
private:
	void setButtonStyle(bool isEnable);

private:
	QAction* m_pAction;			//��ť��Ӧ��Aciton

	QString m_IconNormUrl;			//����״̬ͼƬ
	QString m_IconOverUrl;			//��꽹��״̬ͼƬ
	QString m_IconDownUrl;			//��갴��״̬ͼƬ
	QString m_IconDisableUrl;		//������״̬ͼƬ
};

#endif