/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.h
\brief 演示用头文件
  
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/8 
*/

#ifndef DIALOG_H
#define DIALOG_H

#include "ui_dialogbase.h"
#include <QDialog>

class CCustomWidget;

class CDialog : public QDialog
{
	Q_OBJECT
public:
	CDialog(QWidget* parent);
	~CDialog(){;}

private:
	void initialize();

private Q_SLOTS:
	void slot_move2Left();
	void slot_move2Right();
	void slot_leftItemClicked(QListWidgetItem *item);
	void slot_leftItemDoubleClicked(QListWidgetItem *item);
	void slot_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
	void slot_Ascending();
	void slot_Descending();

private:
	Ui::CDialogBase ui;
};

#endif 