/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file tableview.h
\brief tableview头文件
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2019/1
*/

#ifndef CTABLEVIEW_H
#define CTABLEVIEW_H

#include <QTableView>

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

class CTableView : public QTableView
{
    Q_OBJECT

public:
	explicit CTableView(QWidget *parent = nullptr):QTableView(parent) {}

signals:

protected:
	virtual void mousePressEvent(QMouseEvent *event) override;

private:
	QModelIndex m_indexLast;
};

#endif
