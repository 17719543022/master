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
#include "actionmgr.h"
#include "mainwindow.h"
#include "mypushbutton.h"
#include "mytoolbutton.h"
#include "publicinfomgr.h"
#include "toolbarcontainer.h"
#include "toolbarpage.h"
#include "toolbarpanel.h"


CMainWindow::CMainWindow(QWidget* parent) : QMainWindow(parent, Qt::FramelessWindowHint | Qt::Window)
{
	createActions();
	createMenus();

	m_pInfoLabel = new QLabel(tr(""
		""));
	m_pInfoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	m_pInfoLabel->setAlignment(Qt::AlignCenter);
	statusBar()->addPermanentWidget(m_pInfoLabel);

	setWindowTitle(tr("Menus"));
	setMinimumSize(160, 160);
	resize(480, 320);
}



void CMainWindow::open()
{
	m_pInfoLabel->setText(tr("Invoked <b>File|Open</b>"));
}

void CMainWindow::save()
{
	m_pInfoLabel->setText(tr("Invoked <b>File|Save</b>"));
}


void CMainWindow::cut()
{
	m_pInfoLabel->setText(tr("Invoked <b>Edit|Cut</b>"));
}

void CMainWindow::copy()
{
	m_pInfoLabel->setText(tr("Invoked <b>Edit|Copy</b>"));
}

void CMainWindow::paste()
{
	m_pInfoLabel->setText(tr("Invoked <b>Edit|Paste</b>"));
}

void CMainWindow::bold()
{
	m_pInfoLabel->setText(tr("Invoked <b>Edit|Format|Bold</b>"));
}

void CMainWindow::italic()
{
	m_pInfoLabel->setText(tr("Invoked <b>Edit|Format|Italic</b>"));
}

void CMainWindow::leftAlign()
{
	m_pInfoLabel->setText(tr("Invoked <b>Edit|Format|Left Align</b>"));
}

void CMainWindow::rightAlign()
{
	m_pInfoLabel->setText(tr("Invoked <b>Edit|Format|Right Align</b>"));
}

void CMainWindow::center()
{
	m_pInfoLabel->setText(tr("Invoked <b>Edit|Format|Center</b>"));
}

void CMainWindow::setLineSpacing()
{
	m_pInfoLabel->setText(tr("Invoked <b>Edit|Format|Set Line Spacing</b>"));
}

void CMainWindow::setParagraphSpacing()
{
	m_pInfoLabel->setText(tr("Invoked <b>Edit|Format|Set Paragraph Spacing</b>"));
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
	m_pOpenAct = new QAction(QIcon(":/images/open.png"),tr("&Open..."), this);
	m_pOpenAct->setShortcuts(QKeySequence::Open);
	m_pOpenAct->setStatusTip(tr("Open an existing file"));
	connect(m_pOpenAct, &QAction::triggered, this, &CMainWindow::open);

	m_pSaveAct = new QAction(tr("&Save"), this);
	m_pSaveAct->setShortcuts(QKeySequence::Save);
	m_pSaveAct->setStatusTip(tr("Save the document to disk"));
	connect(m_pSaveAct, &QAction::triggered, this, &CMainWindow::save);

	m_pExitAct = new QAction(tr("E&xit"), this);
	m_pExitAct->setShortcuts(QKeySequence::Quit);
	m_pExitAct->setStatusTip(tr("Exit the application"));
	connect(m_pExitAct, &QAction::triggered, this, &QWidget::close);

	m_pCutAct = new QAction(tr("Cu&t"), this);
	m_pCutAct->setShortcuts(QKeySequence::Cut);
	m_pCutAct->setStatusTip(tr("Cut the current selection's contents to the "
		"clipboard"));
	connect(m_pCutAct, &QAction::triggered, this, &CMainWindow::cut);

	m_pCopyAct = new QAction(tr("&Copy"), this);
	m_pCopyAct->setShortcuts(QKeySequence::Copy);
	m_pCopyAct->setStatusTip(tr("Copy the current selection's contents to the "
		"clipboard"));
	connect(m_pCopyAct, &QAction::triggered, this, &CMainWindow::copy);

	m_pPasteAct = new QAction(tr("&Paste"), this);
	m_pPasteAct->setShortcuts(QKeySequence::Paste);
	m_pPasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
		"selection"));
	connect(m_pPasteAct, &QAction::triggered, this, &CMainWindow::paste);

	m_pBoldAct = new QAction(tr("&Bold"), this);
	m_pBoldAct->setCheckable(true);
	m_pBoldAct->setShortcut(QKeySequence::Bold);
	m_pBoldAct->setStatusTip(tr("Make the text bold"));
	connect(m_pBoldAct, &QAction::triggered, this, &CMainWindow::bold);

	QFont boldFont = m_pBoldAct->font();
	boldFont.setBold(true);
	m_pBoldAct->setFont(boldFont);

	m_pItalicAct = new QAction(tr("&Italic"), this);
	m_pItalicAct->setCheckable(true);
	m_pItalicAct->setShortcut(QKeySequence::Italic);
	m_pItalicAct->setStatusTip(tr("Make the text italic"));
	connect(m_pItalicAct, &QAction::triggered, this, &CMainWindow::italic);

	QFont italicFont = m_pItalicAct->font();
	italicFont.setItalic(true);
	m_pItalicAct->setFont(italicFont);

	m_pSetLineSpacingAct = new QAction(tr("Set &Line Spacing..."), this);
	m_pSetLineSpacingAct->setStatusTip(tr("Change the gap between the lines of a "
		"paragraph"));
	connect(m_pSetLineSpacingAct, &QAction::triggered, this, &CMainWindow::setLineSpacing);

	m_pSetParagraphSpacingAct = new QAction(tr("Set &Paragraph Spacing..."), this);
	m_pSetParagraphSpacingAct->setStatusTip(tr("Change the gap between paragraphs"));
	connect(m_pSetParagraphSpacingAct, &QAction::triggered,
		this, &CMainWindow::setParagraphSpacing);

	m_pAboutAct = new QAction(tr("&About"), this);
	m_pAboutAct->setStatusTip(tr("Show the application's About box"));
	connect(m_pAboutAct, &QAction::triggered, this, &CMainWindow::about);

	m_pLeftAlignAct = new QAction(tr("&Left Align"), this);
	m_pLeftAlignAct->setCheckable(true);
	m_pLeftAlignAct->setShortcut(tr("Ctrl+L"));
	m_pLeftAlignAct->setStatusTip(tr("Left align the selected text"));
	connect(m_pLeftAlignAct, &QAction::triggered, this, &CMainWindow::leftAlign);

	m_pRightAlignAct = new QAction(tr("&Right Align"), this);
	m_pRightAlignAct->setCheckable(true);
	m_pRightAlignAct->setShortcut(tr("Ctrl+R"));
	m_pRightAlignAct->setStatusTip(tr("Right align the selected text"));
	connect(m_pRightAlignAct, &QAction::triggered, this, &CMainWindow::rightAlign);


	m_pCenterAct = new QAction(tr("&Center"), this);
	m_pCenterAct->setCheckable(true);
	m_pCenterAct->setShortcut(tr("Ctrl+E"));
	m_pCenterAct->setStatusTip(tr("Center the selected text"));
	connect(m_pCenterAct, &QAction::triggered, this, &CMainWindow::center);

	m_pAlignmentGroup = new QActionGroup(this);
	m_pAlignmentGroup->addAction(m_pLeftAlignAct);
	m_pAlignmentGroup->addAction(m_pRightAlignAct);
	m_pAlignmentGroup->addAction(m_pCenterAct);
	m_pLeftAlignAct->setChecked(true);
}

void CMainWindow::createMenus()
{
	m_pFileMenu = menuBar()->addMenu(tr("&File"));
	m_pFileMenu->addAction(m_pOpenAct);
	m_pFileMenu->addAction(m_pSaveAct);

	m_pFileMenu->addSeparator();
	m_pFileMenu->addAction(m_pExitAct);

	m_pEditMenu = menuBar()->addMenu(tr("&Edit"));
	m_pEditMenu->addAction(m_pCutAct);
	m_pEditMenu->addAction(m_pCopyAct);
	m_pEditMenu->addAction(m_pPasteAct);
	m_pEditMenu->addSeparator();

	m_pHelpMenu = menuBar()->addMenu(tr("&Help"));
	m_pHelpMenu->addAction(m_pAboutAct);

	m_pFormatMenu = m_pEditMenu->addMenu(tr("&Format"));
	m_pFormatMenu->addAction(m_pBoldAct);
	m_pFormatMenu->addAction(m_pItalicAct);
	m_pFormatMenu->addSeparator()->setText(tr("Alignment"));
	m_pFormatMenu->addAction(m_pLeftAlignAct);
	m_pFormatMenu->addAction(m_pRightAlignAct);
	m_pFormatMenu->addAction(m_pCenterAct);
	m_pFormatMenu->addSeparator();
	m_pFormatMenu->addAction(m_pSetLineSpacingAct);
	m_pFormatMenu->addAction(m_pSetParagraphSpacingAct);
}

void CMainWindow::initialToolbar()
{

}
void CMainWindow::createMainMenu()
{

}
void CMainWindow::createToolContainer()
{
    // 创建二级工具条
    m_pToolBarContainer = new CToolBarContainer(NULL);

    //创建工具页
    createToolPages();
    //创建工具
    createTools();

    //m_pToolBarContainer->onPageChanged(m_pUIParser->m_Toolpages.begin().value()->m_id);
}
void CMainWindow::createMainBar()
{

}
void CMainWindow::createToolPages()
{
    PDrawToolPageMap::iterator itPage = m_Toolpages.begin();
    for (itPage; itPage != m_Toolpages.end(); itPage++)
    {
        PDrawToolPage pToolPage = itPage.value();
        CToolBarPage* page = new CToolBarPage(m_pToolBarContainer, pToolPage->m_id);
        //page->setStyleSheet(QString::fromUtf8("border:2px solid red"));
        page->setObjectName(pToolPage->m_name);
        page->setFixedHeight(94);
        m_pToolBarContainer->addPage(page);//添加工具页

        QGridLayout* layout = new QGridLayout(page);
        layout->setSizeConstraint(QLayout::SetFixedSize);
        for (int i = 0; i < pToolPage->m_panels.size(); i++)
        {
            //createToolPanels(page, pToolPage->m_panels[i],layout);
            PDrawToolPanelMap::iterator itPanel = m_ToolPanels.find(pToolPage->m_panels[i]);
            if (itPanel != m_ToolPanels.end())
            {
                //插入面板
                PDrawToolPanel pToolPanel = itPanel.value();
                CToolBarPanel* pPanel = new CToolBarPanel(NULL, pToolPanel->m_id);
                pPanel->setName(pToolPanel->m_name);
                QGridLayout* pGridLayout = new QGridLayout();
                pGridLayout->setContentsMargins(0, 0, 0, 0);
                pGridLayout->setSizeConstraint(QLayout::SetFixedSize);
                pGridLayout->setHorizontalSpacing(2);
                pGridLayout->setVerticalSpacing(0);
                pPanel->setLayout(pGridLayout);
                page->addPanel(pPanel);
                layout->addWidget(pPanel, 0, i * 2, 1, 1, Qt::AlignBottom);

                //插入分隔线
                QLabel* pLineLable = new QLabel;
                pLineLable->setFixedSize(1, 94);
                QString lableStyle = QString::fromLocal8Bit(
                    " QLabel{ background: #c9c9c9}"
                );
                pLineLable->setStyleSheet(lableStyle);
                layout->addWidget(pLineLable, 0, i * 2 + 1, 2, 1, Qt::AlignVCenter);

                //插入面板标签
                QLabel* pPanelLabel = new QLabel;
                pPanelLabel->setText(pToolPanel->m_caption);
                pPanelLabel->setFixedHeight(15);
                layout->addWidget(pPanelLabel, 1, i * 2, 1, 1, Qt::AlignBottom | Qt::AlignHCenter);

                //设置比例
                layout->setRowStretch(0, 4);
                layout->setRowStretch(1, 1);
                layout->setHorizontalSpacing(5);
            }
        }
        layout->setContentsMargins(5, 2, 5, 2);//设置布局与窗口间隔
        page->setLayout(layout);
    }
}

void CMainWindow::createTools()
{
    PDrawToolPageMap::iterator itPage = m_Toolpages.begin();
    for (itPage; itPage != m_Toolpages.end(); itPage++)  {
        PDrawToolPage pPage = itPage.value();
        for (int i = 0; i < pPage->m_panels.size(); i++)     {
            QString panelname = pPage->m_panels[i];
            PDrawToolPanelMap::iterator itPanel = m_ToolPanels.find(panelname);
            if (itPanel != m_ToolPanels.end())     {
                PDrawToolPanel pPanel = itPanel.value();
                for (int j = 0; j < pPanel->m_tools.size(); j++)
                {
                    PToolPos pToolPos = pPanel->m_tools[j];
                    switch (pToolPos->eToolType)
                    {
                    case e_MultiTool:
                    {
                        PMultiToolMap::iterator it = m_MultiTools.find(pToolPos->m_toolName);
                        if (it != m_MultiTools.end())
                        {
                            addMultiToolToPanel(pPage->m_name, pPanel->m_name, it.value(), pToolPos);
                        }
                    }
                    break;
                    case e_SingleTool:
                    {
                        PDrawToolMap::iterator it = m_DrawTools.find(pToolPos->m_toolName);
                        if (it != m_DrawTools.end())
                        {
                            addTooltoPanel(pPage->m_name, pPanel->m_name, it.value(), pToolPos);
                        }
                    }
                    break;
                    default:
                        break;
                    }

                }
            }
        }
    }
}
void CMainWindow::addTooltoPanel(QString& pageName, QString& panelName, PDrawTool pTool, PToolPos pToolPos)
{
    switch (pTool->m_type)
    {
    case CUiTypeenum::EMyPushButton:
        addToolMyPushButton(pageName, panelName, pTool, pToolPos);
        break;
    case CUiTypeenum::EMyCheckBox:
     //   addToolMyCheckBox(pageName, panelName, pTool, pToolPos);
        break;
    case CUiTypeenum::EMyRadioButton:
     //   addToolMyRadioButton(pageName, panelName, pTool, pToolPos);
        break;
    case CUiTypeenum::ELable_Qt:
      //  addToolQtLabel(pageName, panelName, pTool, pToolPos);
        break;
    case  CUiTypeenum::EGPWidget:
       // addToolGPWidget(pageName, panelName, pTool, pToolPos);
        break;
    case CUiTypeenum::EHSpaceItem_Qt:
    case CUiTypeenum::EVSpaceItem_Qt:
      //  addToolQtSpaceitem(pageName, panelName, pTool, pToolPos);
        break;

    case CUiTypeenum::ESeparator:
       // addToolSeparator(pageName, panelName, pTool, pToolPos);
        break;
    default:
        break;
    }

}

void CMainWindow::addToolMyPushButton(QString& pageName, QString& panelName, PDrawTool pTool, PToolPos pToolPos)
{
    //创建按钮
    CMyPushButton* pMyPushButton = new CMyPushButton(pTool->m_name, NULL);

    //设置按钮的状态图片
    pMyPushButton->setStateIcon(CPublicInfoMgr::instance()->getUiIconPathName(pTool->m_icon, eState_Normal),
        CPublicInfoMgr::instance()->getUiIconPathName(pTool->m_icon, eState_Over),
        CPublicInfoMgr::instance()->getUiIconPathName(pTool->m_icon, eState_Down),
        CPublicInfoMgr::instance()->getUiIconPathName(pTool->m_icon, eState_Unable));

    //重新配置快捷键
    QAction* pAction = CActionMgr::instance()->getAction(pTool->m_Action);
    if (pAction != NULL)
    {
        if (pTool->m_bChecked == "true")
        {
            pAction->setCheckable(true);
            pAction->setChecked(true);
        }
        else if (pTool->m_bChecked == "false")
        {
            pAction->setCheckable(true);
            pAction->setChecked(false);
        }
        else
        {
            pAction->setCheckable(false);
        }

        if (pTool->m_accel != QString::null)
        {
            pAction->setShortcut(QKeySequence(pTool->m_accel));

            //将Action使用addAction方法添加到主窗口中才能够正常使用快捷键
            addAction(pAction);
        }

        //设置按钮动作
        pMyPushButton->setAction(pAction);
    }

    //屏蔽按钮文字，使用纯图片
    pMyPushButton->setText(QString::null);

    //配置按钮的提示状态
    setTip(pMyPushButton, pTool->m_caption, pTool->m_desc);

    m_pToolBarContainer->addTool(pageName, panelName, pMyPushButton, pToolPos);
}
void CMainWindow::setTip(QWidget* pWidget, const QString& caption, const QString& desc)
{
    // 提示状态
    QString toolTip = QString::fromLocal8Bit("<h1><font size='4'>%1</font></h1></br><p align='justify'>%2</p>")
        .arg(caption).arg(desc);
    pWidget->setToolTip(toolTip);

    // 状态栏显示
    pWidget->setStatusTip(desc);
}
void CMainWindow::addMultiToolToPanel(QString& pageName, QString& panelName, PMultiTool pMultiTool, PToolPos pToolPos)
{
    switch (pMultiTool->m_type)
    {
    case CUiTypeenum::EGroupBar_Qt:
        addMultiToolQtBar(pageName, panelName, pMultiTool, pToolPos);
        break;
    case CUiTypeenum::EGroupMenu_Qt:
        //addMultiToolQtMenu(pageName, panelName, pMultiTool, pToolPos);
        break;
    case CUiTypeenum::EGroupGraUnitWidget:
        //addMultiToolGraUnitWidget(pageName, panelName, pMultiTool, pToolPos);
        break;
    default:
        break;
    }
}

//void CMainWindow::addMultiToolQtMenu(QString& pageName, QString& panelName, PMultiTool pMultiTool, PToolPos pToolPos)
//{
//    CSubMenuIconStyle* pStyle = new CSubMenuIconStyle();
//    QMenu* pMenu = new QMenu();
//    pMenu->setStyle(pStyle);
//    pMenu->setStyleSheet(CPublicInfoMgr::instance()->getStyleSheet("toolbarmenu"));
//    pMenu->setToolTipsVisible(true);
//    for (int i = 0; i < pMultiTool->m_tools.size(); i++)
//    {
//        PToolPos pToolPos = pMultiTool->m_tools[i];
//        //一级菜单
//        if (pToolPos->eToolType == e_SingleTool)
//        {
//            PDrawToolMap::iterator it = m_DrawTools.find(pToolPos->m_toolName);
//            if (it != m_DrawTools.end())
//            {
//                PDrawTool pTool = it.value();
//                //菜单中插入分隔符
//                if (pTool->m_type == CUiTypeenum::ESeparator)
//                {
//                    pMenu->addSeparator();
//                }
//                //菜单中插入Action
//                else
//                {
//                    QAction* pAction = CActionMgr::instance()->getAction(pTool->m_Action);
//                    if (pAction == NULL)
//                    {
//                        pAction = new QAction(pMenu);
//                    }
//                    //配置icon
//                    pAction->setIcon(QIcon(CPublicInfoMgr::instance()->getUiIconPathName(pTool->m_icon, eState_Normal)));
//                    //配置显示文字
//                    pAction->setText(pTool->m_caption);
//                    //配置工具提示文字
//                    QString toolTip = QString::fromLocal8Bit("<h1><font size='4'>%1</font></h1></br><p align='justify'>%2</p>")
//                        .arg(pTool->m_caption).arg(pTool->m_desc);
//                    pAction->setToolTip(toolTip);
//                    //配置状态栏提示
//                    pAction->setStatusTip(pTool->m_desc);
//                    //配置菜单动作
//                    pMenu->addAction(pAction);
//                    //重新配置快捷键
//                    if (pTool->m_accel != QString::null)
//                    {
//                        pAction->setShortcut(QKeySequence(pTool->m_accel));
//
//                        //将Action使用addAction方法添加到主窗口中才能够正常使用快捷键
//                        m_pMainWindow->addAction(pAction);
//                    }
//                }
//            }
//        }
//        //二级菜单
//        else
//        {
//            PMultiToolMap::Iterator it = m_pUIParser->m_MultiTools.find(pToolPos->m_toolName);
//            if (it != m_pUIParser->m_MultiTools.end())
//            {
//                PMultiTool pSubMultiTool = it.value();
//                QMenu* pSubMenu = new QMenu();
//                pSubMenu->setToolTipsVisible(true);
//                for (int j = 0; j < pSubMultiTool->m_tools.size(); j++)
//                {
//                    PToolPos pSubToolPos = pSubMultiTool->m_tools[j];
//                    PDrawToolMap::iterator itSub = m_pUIParser->m_DrawTools.find(pSubToolPos->m_toolName);
//                    if (itSub != m_pUIParser->m_DrawTools.end())
//                    {
//                        PDrawTool pSubTool = itSub.value();
//                        if (pSubTool->m_type == CUiTypeenum::ESeparator)
//                        {
//                            pSubMenu->addSeparator();
//                        }
//                        else
//                        {
//                            QAction* pAction = CActionMgr::instance()->getAction(pSubTool->m_Action);
//                            if (pAction == NULL)
//                            {
//                                pAction = new QAction(pSubMenu);
//                            }
//                            //配置icon
//                            pAction->setIcon(QIcon(CPublicInfoMgr::instance()->getUiIconPathName(pSubTool->m_icon, eState_SingleState)));
//                            //配置显示文字
//                            pAction->setText(pSubTool->m_caption);
//                            //配置工具提示文字
//                            QString toolTip = QString::fromLocal8Bit("<h1><font size='4'>%1</font></h1></br><p align='justify'>%2</p>")
//                                .arg(pSubTool->m_caption).arg(pSubTool->m_desc);
//                            pAction->setToolTip(toolTip);
//                            //配置状态栏提示
//                            pAction->setStatusTip(pSubTool->m_desc);
//                            //配置菜单动作
//                            pMenu->addAction(pAction);
//                            //重新配置快捷键
//                            if (pSubTool->m_accel != QString::null)
//                            {
//                                pAction->setShortcut(QKeySequence(pSubTool->m_accel));
//
//                                //将Action使用addAction方法添加到主窗口中才能够正常使用快捷键
//                                m_pMainWindow->addAction(pAction);
//                            }
//                        }
//                    }
//                }
//                pMenu->addMenu(pSubMenu);
//            }
//        }
//    }
//
//    CMyPushButton* pMyPushButton = new CMyPushButton(pMultiTool->m_name, NULL);
//
//    //设置按钮的状态图片
//    pMyPushButton->setStateIcon(CPublicInfoMgr::instance()->getUiIconPathName(pMultiTool->m_icon, eState_Normal),
//        CPublicInfoMgr::instance()->getUiIconPathName(pMultiTool->m_icon, eState_Over),
//        CPublicInfoMgr::instance()->getUiIconPathName(pMultiTool->m_icon, eState_Down),
//        CPublicInfoMgr::instance()->getUiIconPathName(pMultiTool->m_icon, eState_Unable));
//
//    //屏蔽按钮文字，使用纯图片
//    pMyPushButton->setText(QString::null);
//
//    //配置按钮的提示状态
//    setTip(pMyPushButton, pMultiTool->m_caption, pMultiTool->m_desc);
//
//    pMyPushButton->setMenu(pMenu);
//    m_pToolBarContainer->addTool(pageName, panelName, pMyPushButton, pToolPos);
//}

//void CMainWindow::addMultiToolGraUnitWidget(QString& pageName, QString& panelName, PMultiTool pMultiTool, PToolPos pToolPos)
//{
//    //创建基本图元窗口
//    CGraphUnitWindow* pGrphWindow = new CGraphUnitWindow();
//    for (int i = 0; i < pMultiTool->m_tools.size(); i++)
//    {
//        QString toolName = pMultiTool->m_tools[i]->m_toolName;
//        PDrawToolMap::iterator it = m_DrawTools.find(toolName);
//        if (it != m_DrawTools.end())
//        {
//            PDrawTool pTool = it.value();
//            int row = pMultiTool->m_tools[i]->m_row;
//            int col = pMultiTool->m_tools[i]->m_col;
//            int rowSpan = pMultiTool->m_tools[i]->m_rowSpan;
//            int colSpan = pMultiTool->m_tools[i]->m_colSpan;
//            pGrphWindow->addGraphUnit(pTool, CActionMgr::instance()->getAction(pTool->m_Action), row, col, rowSpan, colSpan);
//        }
//    }
//    m_pToolBarContainer->addTool(pageName, panelName, pGrphWindow, pToolPos);
//}

void CMainWindow::addMultiToolQtBar(QString& pageName, QString& panelName, PMultiTool pMultiTool, PToolPos pToolPos)
{
    //创建工具栏
    QToolBar* pToolBar = new QToolBar();
    pToolBar->setObjectName(pMultiTool->m_name);

    for (int i = 0; i < pMultiTool->m_tools.size(); i++)
    {
        QString toolName = pMultiTool->m_tools[i]->m_toolName;
        PDrawToolMap::iterator it = m_DrawTools.find(toolName);
        if (it != m_DrawTools.end())
        {
            PDrawTool pTool = it.value();
            //工具条上添加widget
            if (pTool->m_type == CUiTypeenum::EGPWidget)
            {
                //QWidget* pWidget = CActionMgr::instance()->getWidget(pTool->m_Widget);
                //ProcessGPWidget(pTool, pWidget);
                //pToolBar->addWidget(pWidget);
            }
            //工具条上添加分隔符
            else if (pTool->m_type == CUiTypeenum::ESeparator)
            {
                pToolBar->addSeparator();
            }
            //工具条上添加按钮
            else if (pTool->m_type == CUiTypeenum::EMyPushButton)
            {
                //创建按钮
                CMyPushButton* pMyPushButton = new CMyPushButton(pTool->m_name, NULL);

                //设置按钮的状态图片
                pMyPushButton->setStateIcon(CPublicInfoMgr::instance()->getUiIconPathName(pTool->m_icon, eState_Normal),
                    CPublicInfoMgr::instance()->getUiIconPathName(pTool->m_icon, eState_Over),
                    CPublicInfoMgr::instance()->getUiIconPathName(pTool->m_icon, eState_Down),
                    CPublicInfoMgr::instance()->getUiIconPathName(pTool->m_icon, eState_Unable));

                //重新配置快捷键
                QAction* pAction = CActionMgr::instance()->getAction(pTool->m_Action);
                if (pAction != NULL)
                {
                    if (pTool->m_bChecked == "true")
                    {
                        pAction->setCheckable(true);
                        pAction->setChecked(true);
                    }
                    else if (pTool->m_bChecked == "false")
                    {
                        pAction->setCheckable(true);
                        pAction->setChecked(false);
                    }
                    else
                    {
                        pAction->setCheckable(false);
                    }

                    if (pTool->m_accel != QString::null)
                    {
                        pAction->setShortcut(QKeySequence(pTool->m_accel));

                        //将Action使用addAction方法添加到主窗口中才能够正常使用快捷键
                        addAction(pAction);
                    }
                    //设置按钮动作
                    pMyPushButton->setAction(pAction);
                }

                //屏蔽按钮文字，使用纯图片
                pMyPushButton->setText(QString::null);

                //配置按钮的提示状态
                //setTip(pMyPushButton, pTool->m_caption, pTool->m_desc);

                pToolBar->addWidget(pMyPushButton);
            }
            //工具条上添加checkbox
            //else if (pTool->m_type == CUiTypeenum::EMyCheckBox)
            //{
            //    //创建checkbox
            //    CMyCheckBox* pMyCheckBox = new CMyCheckBox(pTool->m_name, NULL);

            //    //重新配置快捷键
            //    QAction* pAction = CActionMgr::instance()->getAction(pTool->m_Action);
            //    if (pAction != NULL)
            //    {
            //        if (pTool->m_accel != QString::null)
            //        {
            //            pAction->setShortcut(QKeySequence(pTool->m_accel));

            //            //将Action使用addAction方法添加到主窗口中才能够正常使用快捷键
            //            m_pMainWindow->addAction(pAction);
            //        }

            //        //设置checkbox动作
            //        pMyCheckBox->setAction(pAction);
            //    }
            //    //设置checkbox显示文字
            //    pMyCheckBox->setText(pTool->m_caption);

            //    setTip(pMyCheckBox, pTool->m_caption, pTool->m_desc);
            //    pToolBar->addWidget(pMyCheckBox);
            //}
            ////工具条上添加radioButton
            //else if (pTool->m_type == CUiTypeenum::EMyRadioButton)
            //{
            //    //创建radioButton
            //    CMyRadioButton* pMyRadioButton = new CMyRadioButton(pTool->m_name, NULL);

            //    //重新配置快捷键
            //    QAction* pAction = CActionMgr::instance()->getAction(pTool->m_Action);
            //    if (pAction != NULL)
            //    {
            //        if (pTool->m_accel != QString::null)
            //        {
            //            pAction->setShortcut(QKeySequence(pTool->m_accel));

            //            //将Action使用addAction方法添加到主窗口中才能够正常使用快捷键
            //            m_pMainWindow->addAction(pAction);
            //        }

            //        //设置radioButton动作
            //        pMyRadioButton->setAction(pAction);
            //    }
            //    //设置radioButton显示文字
            //    pMyRadioButton->setText(pTool->m_caption);

            //    setTip(pMyRadioButton, pTool->m_caption, pTool->m_desc);
            //    pToolBar->addWidget(pMyRadioButton);
            //}
        }
    }
    m_pToolBarContainer->addTool(pageName, panelName, pToolBar, pToolPos);
}
