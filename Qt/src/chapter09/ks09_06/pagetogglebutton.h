
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
	//设置按钮状态图片
	void setStateIcon(const QString& norm, const QString& over, const QString& down);
	qint32 getPageID()
	{
		return m_PageId;
	}
public slots :
	void onClicked();
	void onPageToggled(int index);
signals:
	void togglePage(int);	//切换页面信号

private:
	void setNormalButtonStyle();//正常情况下的样式
	void setSelectButtonStyle();//选中情况下的样式
private:
	qint32 m_PageId;		//控制页面ID
	QString m_IconNorm;		//正常状态图片
	QString m_IconOver;		//焦点状态图片
	QString m_IconDown;		//按下状态图片
};

#endif