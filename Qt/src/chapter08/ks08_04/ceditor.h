/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file ceditor.h
\brief CEditor头文件
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2019/1
*/

#ifndef CEDITOR_H
#define CEDITOR_H

#include <QLabel>


class CEditor : public QLabel
{
    Q_OBJECT

public:
	explicit  CEditor(QWidget *parent = 0);

signals:
    void editingFinished();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:

};

#endif
