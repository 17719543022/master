/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: ctrlwindow.h
\brief  对话框编程示例, 控制窗口类定义头文件
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
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
    /// 构造函数
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
