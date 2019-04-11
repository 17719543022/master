
#ifndef _PAGETOGGLEBUTTON_H
#define _PAGETOGGLEBUTTON_H

#include <QPushButton>


class CPageToggleButton :public QPushButton
{
	Q_OBJECT
public:
	CPageToggleButton(const QString &text, const qint32 pageId,QWidget *parent = 0);
	~CPageToggleButton();

public:
	//���ð�ť״̬ͼƬ
	void setStateIcon(const QString& norm, const QString& over, const QString& down);
	qint32 getPageID()
	{
		return m_PageId;
	}
public slots :
	void onClicked();
	void onPageToggled(int index);
signals:
	void togglePage(int);	//�л�ҳ���ź�

private:
	void setNormalButtonStyle();//��������µ���ʽ
	void setSelectButtonStyle();//ѡ������µ���ʽ
private:
	qint32 m_PageId;		//����ҳ��ID
	QString m_IconNorm;		//����״̬ͼƬ
	QString m_IconOver;		//����״̬ͼƬ
	QString m_IconDown;		//����״̬ͼƬ
};

#endif