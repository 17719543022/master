/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: logdockwidget.h
\brief 日志窗口类定义文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2019/01
*/

#ifndef LOGDOCKWIDGET_H
#define LOGDOCKWIDGET_H

#include <QDockWidget>


class QTableWidget;

class CLogDockWidget : public QDockWidget
{
public:
	CLogDockWidget(const QString &title, QWidget *parent = 0, Qt::WindowFlags flags = 0);
	virtual ~CLogDockWidget();

protected:
	void customEvent(QEvent* e) Q_DECL_OVERRIDE;

private:
	QTableWidget *m_pTableWidget;
};

#endif		// LOGDOCKWIDGET_H