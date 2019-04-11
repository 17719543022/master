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
#include "ks12_02/action_interface.h"


CMainWindow::CMainWindow(QWidget* parent) : QMainWindow(parent)
{
	initialize();

	createActions();
    
    createPluginActions(); // 构建插件Action

	createToolBars();
	createStatusBar();
	connectSignalAndSlot();

	setWindowTitle(tr("Demo"));
	setMinimumSize(160, 160);
	resize(480, 320);
}


void CMainWindow::initialize()
{
    m_pScene = new QGraphicsScene(this);
    m_pView = new CGraphView(this);
    m_pView->setScene(m_pScene);
    QRectF rct(0, 0, 400,400);
    m_pScene->setSceneRect(rct);
	setCentralWidget(m_pView);
}

void CMainWindow::connectSignalAndSlot()
{
    connect(m_pView, SIGNAL(viewMouseMove(const QPointF&)),
        this, SLOT(onMouseMoveInView(const QPointF&)));
}

/// 鼠标位置更新
void CMainWindow::onMouseMoveInView(const QPointF& pt)
{
	QString str;
	str.sprintf("%.2f, %.2f", pt.x(), pt.y());
	m_pMouseLabel->setText(str);
}

void CMainWindow::slot_addRect()
{
    m_pView->addRect();
}

void CMainWindow::slot_addEllipse()
{
    m_pView->addEllipse();
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

#ifndef QT_NO_CLIPBOARD
void CMainWindow::slot_cut()
{
    m_pView->cut();
}

void CMainWindow::slot_copy()
{
    m_pView->copy();
}

void CMainWindow::slot_paste()
{
    m_pView->paste();
}
#endif

void CMainWindow::about()
{
	m_pInfoLabel->setText(tr("Invoked <b>Help|About</b>"));
	QMessageBox::about(this, tr("About Menu"),
		tr("The <b>Menu</b> example shows how to create "
			"menu-bar menus and context menus."));
}
typedef CActionObjectInterface* (*FuncType)(int);

void CMainWindow::createActions()
{
#ifndef QT_NO_CLIPBOARD
    m_pCutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
    m_pCutAct->setShortcuts(QKeySequence::Cut);
    m_pCutAct->setStatusTip(tr("Cut the current selection's contents to the "
        "clipboard"));
    connect(m_pCutAct, &QAction::triggered, this, &CMainWindow::slot_cut);

    m_pCopyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    m_pCopyAct->setShortcuts(QKeySequence::Copy);
    m_pCopyAct->setStatusTip(tr("Copy the current selection's contents to the "
        "clipboard"));
    connect(m_pCopyAct, &QAction::triggered, this, &CMainWindow::slot_copy);

    m_pPasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    m_pPasteAct->setShortcuts(QKeySequence::Paste);
    m_pPasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
        "selection"));
    connect(m_pPasteAct, &QAction::triggered, this, &CMainWindow::slot_paste);
#endif

    m_pRectAct = new QAction(tr("addRect"), this);
    m_pRectAct->setStatusTip(tr("add rect to view"));
    connect(m_pRectAct, &QAction::triggered, this, &CMainWindow::slot_addRect);

    m_pEllipseAct = new QAction(tr("addEllipse"), this);
    m_pEllipseAct->setStatusTip(tr("add ellipse to view"));
    connect(m_pEllipseAct, &QAction::triggered, this, &CMainWindow::slot_addEllipse);

    m_pAboutAct = new QAction(tr("&About"), this);
    m_pAboutAct->setStatusTip(tr("Show the application's About box"));
    connect(m_pAboutAct, &QAction::triggered, this, &CMainWindow::about);
}
void CMainWindow::createPluginActions()
{

    QDir dir(ns_train::getPath("$TRAINDEVHOME/bin"));
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList();
    if (!list.empty())   {
        for (int i = 0; i < list.size(); ++i)     {
            QFileInfo fileInfo = list.at(i);
            // 区分release版本与debug版本，根据文件名区分即可，debug版只加载debug版的插件文件。
            QString strFileName = fileInfo.fileName();
#ifdef TRAIN_DEBUG
            if (!strFileName.contains("_d."))  {
                continue;
            }
#else
            if (strFileName.contains("_d."))   {
                continue;
            }
#endif // ICCS_DEBUG
            QFunctionPointer createFunc = QLibrary::resolve(fileInfo.absoluteFilePath(), "createAction");
            if (NULL != createFunc)  {
                FuncType pFunc = reinterpret_cast<FuncType>(createFunc);
                if (NULL != pFunc)   {
                    CActionObjectInterface* pActionObject = pFunc(6);
                    m_lstActionObject.push_back(pActionObject);
                }
            }
        }
    }
}


void CMainWindow::createToolBars()
{
	m_pEditToolBar = addToolBar(tr("edit tool bar"));
	m_pEditToolBar->setObjectName("edit tool bar");
#ifndef QT_NO_CLIPBOARD
    m_pEditToolBar->addAction(m_pCutAct);
	m_pEditToolBar->addAction(m_pCopyAct);
	m_pEditToolBar->addAction(m_pPasteAct);
#endif

    m_pEditToolBar->addAction(m_pRectAct);
	m_pEditToolBar->addAction(m_pEllipseAct);

    QList<CActionObjectInterface*>::iterator iteList = m_lstActionObject.begin();
    for (iteList = m_lstActionObject.begin(); iteList != m_lstActionObject.end(); iteList++)
    {
        m_pEditToolBar->addAction((*iteList)->getAction());
        (*iteList)->setView(m_pView);
    }
}
