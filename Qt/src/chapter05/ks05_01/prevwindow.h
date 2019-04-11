/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: previewwindow.h
\brief  对话框编程示例, 预览窗口类定义头文件
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
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
    /// 构造函数
    CPreviewWindow(QWidget *parent = 0);

    /**
    * @brief 设置窗体的flags

    * @param[in] flags  窗体的flags
    * @return void
    */
    void setWindowFlags(Qt::WindowFlags flags);

private:
};


#endif
