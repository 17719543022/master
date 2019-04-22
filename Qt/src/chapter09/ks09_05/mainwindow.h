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

QT_BEGIN_NAMESPACE
class QMenu;
class QActionGroup;
class QAction;
class QLabel;
QT_END_NAMESPACE

class CTextEdit;

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

	void onMouseMoveInView(QMouseEvent* event);

private:
	void createActions();		/// 构建菜单项对应的QAction。
	void createMenus();			/// 构建菜单
	void createToolBars();		/// 构建工具条
	void createStatusBar();		/// 构建状态栏
	void initialize();			/// 初始化

private:
	QMenu *m_pFileMenu;			/// 文件菜单
	QMenu *m_pEditMenu;			/// 编辑菜单
	QMenu *m_pFormatMenu;		/// 格式菜单(二级菜单)
	QMenu *m_pHelpMenu;			/// 帮助菜单
	
	QToolBar *m_pFileToolBar;	/// 文件工具条
	QToolBar *m_pEditToolBar;	/// 编辑工具条

	QActionGroup *m_pAlignmentGroup;

	QAction *m_pOpenAct;		/// 打开
	QAction *m_pSaveAct;		/// 保存
	QAction *m_pExitAct;		/// 退出

	QAction *m_pCutAct;			/// 剪切
	QAction *m_pCopyAct;		/// 复制
	QAction *m_pPasteAct;		/// 黏贴
	QAction *m_pBoldAct;		/// 粗体 
	QAction *m_pItalicAct;		/// 斜体
	QAction *m_pLeftAlignAct;	/// 左对齐
	QAction *m_pRightAlignAct;	/// 右对齐
	QAction *m_pCenterAct;		/// 居中
	
	QAction *m_pSetLineSpacingAct; /// 设置行间距
	QAction *m_pSetParagraphSpacingAct;/// 设置段间距

	QAction *m_pAboutAct;	/// 关于

	QLabel *m_pInfoLabel;	/// 信息标签
	QLabel* m_pMouseLabel;	/// 鼠标位置显示

	CTextEdit* m_pTextEdit; /// 编辑器
};

#endif // MAINWINDOW_H