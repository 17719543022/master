/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���

\file: dialog.h
\brief ��ʾ��ͷ�ļ�
  
\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
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