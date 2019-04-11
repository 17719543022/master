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