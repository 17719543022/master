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


class CDialog : public QDialog
{
	Q_OBJECT
public:
	CDialog(QWidget* parent);
	~CDialog(){;}
	void openFile(const QString &fileName);

protected:
	void initialDialog();
private:
	void initialControls();
	void connectSignalsAndSlots();
	void changeFrameSliderMaxMin();

private slots:
	void slot_open();
	//void slot_pause(bool);
	void slot_goToTheFrame(int frame);
	void slot_updateButtons();
	void slot_updateFrameSlider();
private:
	Ui::CDialogBase ui;
	QString m_currentDirectory;
	QMovie* m_movie;
};

#endif 