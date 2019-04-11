/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: mainwindow.h
\brief 主窗体头文件
  
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/12 
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QToolBar>
#include <QMainWindow>
#include <QLabel>

#include "uifiledef.h"


QT_BEGIN_NAMESPACE
class QMenu;
class QActionGroup;
class QAction;
class QLabel;
QT_END_NAMESPACE

class CDrawGeneralBar;
class CToolBarContainer;

class CMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	CMainWindow(QWidget* parent);
	~CMainWindow(){;}

protected:

private slots:
	void open();
	void save();

	void cut();
	void copy();
	void paste();

	void bold();
	void italic();

	void leftAlign();
	void rightAlign();
	void center();
	void setLineSpacing();
	void setParagraphSpacing();

	void about();


private:
	void createActions();
	void createMenus();
    
    void initialToolbar(); // 初始化主工具条
    void createMainMenu();//创建主菜单    
    void createToolContainer();// 创建二级工具条
    void createMainBar();    // 创建主工具条                             
    void createToolPages();// 创建工具页
    void createTools();// 创建工具按钮
     //! 添加各种类型单一控件工具
    void addTooltoPanel(QString& pageName, QString& panelName, PDrawTool pTool, PToolPos pToolPos);
    //! 添加自定义按钮
    void addToolMyPushButton(QString& pageName, QString& panelName, PDrawTool pTool, PToolPos pToolPos);
    //! 添加标签
    void addToolQtLabel(QString& pageName, QString& panelName, PDrawTool pTool, PToolPos pToolPos);
    //！添加自定义checkbox
    void addToolMyCheckBox(QString& pageName, QString& panelName, PDrawTool pTool, PToolPos pToolPos);
    //！添加自定义radioButton
    void addToolMyRadioButton(QString& pageName, QString& panelName, PDrawTool pTool, PToolPos pToolPos);
    //! 添加图形平台widget控件
    void addToolGPWidget(QString& pageName, QString& panelName, PDrawTool pTool, PToolPos pToolPos);
    //! 添加弹簧
    void addToolQtSpaceitem(QString& pageName, QString& panelName, PDrawTool pTool, PToolPos pToolPos);
    //! 添加分隔符
    void addToolSeparator(QString& pageName, QString& panelName, PDrawTool pTool, PToolPos pToolPos);

    //! 添加多选项控件工具
    void addMultiToolToPanel(QString& pageName, QString& panelName, PMultiTool pMultiTool, PToolPos pToolPos);
    void addMultiToolGraUnitWidget(QString& pageName, QString& panelName, PMultiTool pMultiTool, PToolPos pToolPos);
    void addMultiToolQtBar(QString& pageName, QString& panelName, PMultiTool pMultiTool, PToolPos pToolPos);
    void addMultiToolQtMenu(QString& pageName, QString& panelName, PMultiTool pMultiTool, PToolPos pToolPos);
    void setTip(QWidget* pWidget, const QString& caption, const QString& desc);

private:
	QMenu *m_pFileMenu;
	QMenu *m_pEditMenu;
	QMenu *m_pFormatMenu;
	QMenu *m_pHelpMenu;
	
	QActionGroup *m_pAlignmentGroup;

	QAction *m_pOpenAct;
	QAction *m_pSaveAct;
	QAction *m_pExitAct;

	QAction *m_pCutAct;
	QAction *m_pCopyAct;
	QAction *m_pPasteAct;
	QAction *m_pBoldAct;
	QAction *m_pItalicAct;
	QAction *m_pLeftAlignAct;
	QAction *m_pRightAlignAct;

	QAction *m_pCenterAct;
	QAction *m_pSetLineSpacingAct;
	QAction *m_pSetParagraphSpacingAct;
	QAction *m_pAboutAct;

	QLabel *m_pInfoLabel;

    ///
    CDrawGeneralBar* m_pGeneralBar;//主工具条
    CToolBarContainer* m_pToolBarContainer;// 二级工具条
                                           //! 从ui文件加载的Tool信息
    PDrawToolMap m_DrawTools;
    //! 从ui文件加载的工具页信息
    PDrawToolPageMap m_Toolpages;
    //! 从ui文件加载的工具面板信息
    PDrawToolPanelMap m_ToolPanels;
    //! 从ui文件加载的多选项工具信息
    PMultiToolMap m_MultiTools;
    //! 从ui文件加载的页面切换按钮
    PPageControlToolMap m_PageContrlTools;
    //！从文件中加载的主菜单信息
    PMultiToolMap m_MainMenu;
    //! 从文件中加载的二级菜单信息
    PMultiToolMap m_SubMenu;
};

#endif // MAINWINDOW_H