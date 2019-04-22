/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���

\file: maindialog.h
\brief  CMainDialog�ඨ��ͷ�ļ�

\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
\Date 2018/9
*/

#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QPixmap>

#include "ui_maindialogbase.h" // ͷ�ļ���������: maindailogbase.ui  ---> ui_maindialogbase.h

QT_BEGIN_NAMESPACE
class QMovie;
QT_END_NAMESPACE

// �������������ui�ļ��жԻ��������������鿴���е�����
class CMainDialog : public QDialog
{
	Q_OBJECT
public:
	CMainDialog(QWidget* pParent);
	~CMainDialog();

protected:

private slots:
	void onTimeOut();
	void onStartStop();
private:
	
	void initialDialog();
private:
	bool	m_bStart;
	QTimer* m_pTimer;
	Ui::CMainDialogBase ui;
	QPixmap	m_png[4];
	QMovie* m_movie;
	int		m_idx;
};

#endif