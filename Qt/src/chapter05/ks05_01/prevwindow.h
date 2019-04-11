/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���

\file: previewwindow.h
\brief  �Ի�����ʾ��, Ԥ�������ඨ��ͷ�ļ�
\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
\Date 2018/10
*/

#ifndef PREVIEWWINDOW_H
#define PREVIEWWINDOW_H

#include <QWidget>
#include "ui_prevwindow.h"

QT_BEGIN_NAMESPACE
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE

class CPreviewWindow : public QWidget, public Ui::CPreviewWindowBase
{
    Q_OBJECT

public:
    /// ���캯��
    CPreviewWindow(QWidget *parent = 0);

    /**
    * @brief ���ô����flags

    * @param[in] flags  �����flags
    * @return void
    */
    void setWindowFlags(Qt::WindowFlags flags);

private:
};


#endif
