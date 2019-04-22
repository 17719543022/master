/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���

\file: ctrlwindow.h
\brief  �Ի�����ʾ��, ���ƴ����ඨ��ͷ�ļ�
\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
\Date 2018/10
*/

#ifndef CCTRLWINDOW_H
#define CCTRLWINDOW_H

#include <QWidget>

#include "ui_ctrlwindow.h"
#include "prevwindow.h"

QT_BEGIN_NAMESPACE
class QCheckBox;
class QGroupBox;
class QLabel;
class QPushButton;
class QRadioButton;
QT_END_NAMESPACE

class CCtrlWindow : public QWidget, public Ui::CControllerWindowBase
{
    Q_OBJECT

public:
    /// ���캯��
    CCtrlWindow();

private slots:
    void updatePreview();

private:
    void connectTypeGroupBox();
    void connectHintsGroupBox();
    QCheckBox *createCheckBox(const QString &text);
    QRadioButton *createRadioButton(const QString &text);

	CPreviewWindow *m_pPreviewWindow;
};


#endif // CCTRLWINDOW_H
