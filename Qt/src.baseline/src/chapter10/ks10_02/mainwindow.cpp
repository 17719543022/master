/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: CMainWindow.cpp
\brief	主窗体实现文件
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9 

*/
#include <QtWidgets>
#include <QGraphicsScene>

#include "base/basedll/baseapi.h"
#include "mainwindow.h"
#include "graphview.h"
#include "mdiarea.h"


CMainWindow::CMainWindow(QWidget* parent) : QMainWindow(parent)
{
	initialize();

	createActions();
	createMenus();
	createStatusBar();
	connectSignalAndSlot();

	setWindowTitle(tr("Demo"));
	setMinimumSize(160, 160);
	resize(480, 320);
}


void CMainWindow::initialize()
{
    m_pMdiArea = new CEditMdiArea(this);
	setCentralWidget(m_pMdiArea);
}

void CMainWindow::connectSignalAndSlot()
{
    connect(m_pMdiArea, SIGNAL(viewMouseMove(const QPointF&)),
       this, SLOT(onMouseMoveInView(const QPointF&)));
}

/// 鼠标位置更新
void CMainWindow::onMouseMoveInView(const QPointF& pt)
{
	QString str;
	str.sprintf("%.2f, %.2f", pt.x(), pt.y());
	m_pMouseLabel->setText(str);
}


/// 创建状态栏
void CMainWindow::createStatusBar()
{
	m_pInfoLabel = new QLabel(tr(""));
	m_pInfoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	m_pInfoLabel->setAlignment(Qt::AlignCenter);
	statusBar()->addPermanentWidget(m_pInfoLabel);

	m_pMouseLabel = new QLabel("", statusBar());
	m_pMouseLabel->setMinimumWidth(100);
	statusBar()->addPermanentWidget(m_pMouseLabel);

	statusBar()->show();
}

void CMainWindow::createMenus()
{
    m_pHelpMenu = menuBar()->addMenu(QString::fromLocal8Bit("&文件"));
    m_pHelpMenu->addAction(m_pAboutAct);

}

void CMainWindow::about()
{
	m_pInfoLabel->setText(tr("Invoked <b>Help|About</b>"));
	QMessageBox::about(this, tr("About Menu"),
		tr("The <b>Menu</b> example shows how to create "
			"menu-bar menus and context menus."));
}

void CMainWindow::createActions()
{
    m_pAboutAct = new QAction(tr("&About"), this);
	m_pAboutAct->setStatusTip(tr("Show the application's About box"));
	connect(m_pAboutAct, &QAction::triggered, this, &CMainWindow::about);
}



