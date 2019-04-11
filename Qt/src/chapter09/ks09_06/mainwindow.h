/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���

\file: mainwindow.h
\brief ������ͷ�ļ�
  
\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
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
    
    void initialToolbar(); // ��ʼ����������
    void createMainMenu();//�������˵�    
    void createToolContainer();// ��������������
    void createMainBar();    // ������������                             
    void createToolPages();// ��������ҳ
    void createTools();// �������߰�ť
     //! ��Ӹ������͵�һ�ؼ�����
    void addTooltoPanel(QString& pageName, QString& panelName, PDrawTool pTool, PToolPos pToolPos);
    //! ����Զ��尴ť
    void addToolMyPushButton(QString& pageName, QString& panelName, PDrawTool pTool, PToolPos pToolPos);
    //! ��ӱ�ǩ
    void addToolQtLabel(QString& pageName, QString& panelName, PDrawTool pTool, PToolPos pToolPos);
    //������Զ���checkbox
    void addToolMyCheckBox(QString& pageName, QString& panelName, PDrawTool pTool, PToolPos pToolPos);
    //������Զ���radioButton
    void addToolMyRadioButton(QString& pageName, QString& panelName, PDrawTool pTool, PToolPos pToolPos);
    //! ���ͼ��ƽ̨widget�ؼ�
    void addToolGPWidget(QString& pageName, QString& panelName, PDrawTool pTool, PToolPos pToolPos);
    //! ��ӵ���
    void addToolQtSpaceitem(QString& pageName, QString& panelName, PDrawTool pTool, PToolPos pToolPos);
    //! ��ӷָ���
    void addToolSeparator(QString& pageName, QString& panelName, PDrawTool pTool, PToolPos pToolPos);

    //! ��Ӷ�ѡ��ؼ�����
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
    CDrawGeneralBar* m_pGeneralBar;//��������
    CToolBarContainer* m_pToolBarContainer;// ����������
                                           //! ��ui�ļ����ص�Tool��Ϣ
    PDrawToolMap m_DrawTools;
    //! ��ui�ļ����صĹ���ҳ��Ϣ
    PDrawToolPageMap m_Toolpages;
    //! ��ui�ļ����صĹ��������Ϣ
    PDrawToolPanelMap m_ToolPanels;
    //! ��ui�ļ����صĶ�ѡ�����Ϣ
    PMultiToolMap m_MultiTools;
    //! ��ui�ļ����ص�ҳ���л���ť
    PPageControlToolMap m_PageContrlTools;
    //�����ļ��м��ص����˵���Ϣ
    PMultiToolMap m_MainMenu;
    //! ���ļ��м��صĶ����˵���Ϣ
    PMultiToolMap m_SubMenu;
};

#endif // MAINWINDOW_H