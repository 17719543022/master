/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: ctrlwindow.cpp
\brief  对话框编程示例, 控制窗口类实现文件
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/10
*/


#include <QtWidgets>
#include "ctrlwindow.h"

CCtrlWindow::CCtrlWindow()
{
    setupUi(this);
    connectHintsGroupBox();
    connectTypeGroupBox();

	m_pPreviewWindow = new CPreviewWindow(this);

    connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    setWindowTitle(tr("Window Flags"));
    updatePreview();
}

void CCtrlWindow::updatePreview()
{
    Qt::WindowFlags flags = 0;

    if (windowRadioButton->isChecked()) {
        flags = Qt::Window;
    } else if (dialogRadioButton->isChecked()) {
        flags = Qt::Dialog;
    } else if (sheetRadioButton->isChecked()) {
        flags = Qt::Sheet;
    } else if (drawerRadioButton->isChecked()) {
        flags = Qt::Drawer;
    } else if (popupRadioButton->isChecked()) {
        flags = Qt::Popup;
    } else if (toolRadioButton->isChecked()) {
        flags = Qt::Tool;
    } else if (toolTipRadioButton->isChecked()) {
        flags = Qt::ToolTip;
    } else if (splashScreenRadioButton->isChecked()) {
        flags = Qt::SplashScreen;
    }

    if (msWindowsFixedSizeDialogCheckBox->isChecked())
        flags |= Qt::MSWindowsFixedSizeDialogHint;
    if (x11BypassWindowManagerCheckBox->isChecked())
        flags |= Qt::X11BypassWindowManagerHint;
    if (framelessWindowCheckBox->isChecked())
        flags |= Qt::FramelessWindowHint;
    if (windowNoShadowCheckBox->isChecked())
        flags |= Qt::NoDropShadowWindowHint;
    if (windowTitleCheckBox->isChecked())
        flags |= Qt::WindowTitleHint;
    if (windowSystemMenuCheckBox->isChecked())
        flags |= Qt::WindowSystemMenuHint;
    if (windowMinimizeButtonCheckBox->isChecked())
        flags |= Qt::WindowMinimizeButtonHint;
    if (windowMaximizeButtonCheckBox->isChecked())
        flags |= Qt::WindowMaximizeButtonHint;
    if (windowCloseButtonCheckBox->isChecked())
        flags |= Qt::WindowCloseButtonHint;
    if (windowContextHelpButtonCheckBox->isChecked())
        flags |= Qt::WindowContextHelpButtonHint;
    if (windowShadeButtonCheckBox->isChecked())
        flags |= Qt::WindowShadeButtonHint;
    if (windowStaysOnTopCheckBox->isChecked())
        flags |= Qt::WindowStaysOnTopHint;
    if (windowStaysOnBottomCheckBox->isChecked())
        flags |= Qt::WindowStaysOnBottomHint;
    if (customizeWindowHintCheckBox->isChecked())
        flags |= Qt::CustomizeWindowHint;

	m_pPreviewWindow->setWindowFlags(flags);


    QPoint pos = m_pPreviewWindow->pos();
    if (pos.x() < 0)
        pos.setX(0);
    if (pos.y() < 0)
        pos.setY(0);
	m_pPreviewWindow->move(pos);
	m_pPreviewWindow->show();
}

void CCtrlWindow::connectTypeGroupBox()
{
    connect(windowRadioButton, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(dialogRadioButton, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(sheetRadioButton, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(drawerRadioButton, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(popupRadioButton, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(toolRadioButton, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(toolTipRadioButton, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(splashScreenRadioButton, SIGNAL(clicked()), this, SLOT(updatePreview()));

    windowRadioButton->setChecked(true);
  
}

void CCtrlWindow::connectHintsGroupBox()
{
    connect(msWindowsFixedSizeDialogCheckBox, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(x11BypassWindowManagerCheckBox, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(framelessWindowCheckBox, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(windowNoShadowCheckBox, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(windowTitleCheckBox, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(windowSystemMenuCheckBox, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(windowMinimizeButtonCheckBox, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(windowMaximizeButtonCheckBox, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(windowCloseButtonCheckBox, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(windowContextHelpButtonCheckBox, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(windowShadeButtonCheckBox, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(windowStaysOnTopCheckBox, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(windowStaysOnBottomCheckBox, SIGNAL(clicked()), this, SLOT(updatePreview()));
    connect(customizeWindowHintCheckBox, SIGNAL(clicked()), this, SLOT(updatePreview()));

}

