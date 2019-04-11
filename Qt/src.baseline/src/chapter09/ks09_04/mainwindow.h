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
};

#endif // MAINWINDOW_H