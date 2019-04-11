/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.h
\brief  CDialog类定义头文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/

#ifndef DIALOG_H
#define DIALOG_H

#include "ui_dialogbase.h" // 头文件名称来自: dialogbase.ui  ---> ui_dialogbase.h

class CRecvThread;
class CSendThread;

class CDialog : public QDialog
{
	Q_OBJECT
public:
	CDialog(QWidget* pParent);
	~CDialog();

protected:

private slots:
	void on_startthread();

private:
    Ui::CDialogBase ui;
    CRecvThread* m_pRecvThread;
    CSendThread* m_pSendThread;
};

#endif