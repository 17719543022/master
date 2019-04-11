/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: customwidget.h
\brief 演示用头文件
  
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/8 
*/

#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>

#include "ui_customwidgetbase.h"

class CCustomWidget : public QWidget
{
public:
	CCustomWidget(QWidget* parent);
	~CCustomWidget(){;}

protected:
	virtual void resizeEvent(QResizeEvent *event);
private:
	void initialize();

private:
	Ui::CCustomWidgetBase ui;
	QMovie*	m_movie;
	QLabel* m_transparentLabel;
};

#endif // CUSTOMWIDGET_H