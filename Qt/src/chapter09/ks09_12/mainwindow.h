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
#include <QLabel>
#include <QMainWindow>
#include <QMutex>

#include "logevt.h"

QT_BEGIN_NAMESPACE
class QMenu;
class QActionGroup;
class QAction;
class QLabel;
QT_END_NAMESPACE

class CTextEdit;
class CCountry;
class CTreeView;
class CLogDockWidget;

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

	void bold(bool bChecked);
	void italic();

	void leftAlign();
	void rightAlign();
	void center();
	void setLineSpacing();
	void setParagraphSpacing();

	void about();

	void onMouseMoveInView(QMouseEvent* event);
	void onSelectionChanged();
	void addParagraph(const QString &paragraph); ///

	void slot_ItemDoubleClicked(const QString&);
private:
	bool openFile(const QString&);
	void createActions();		/// �����˵����Ӧ��QAction��
	void createMenus();			/// �����˵�
	void createToolBars();		/// ����������
	void createStatusBar();		/// ����״̬��
	void initialize();			/// ��ʼ��
	
	void createDockWindows();
	void createDockWindows_Left();
	void createDockWindows_Down();
	void connectSignalAndSlot();/// ���źŲ�
	
	void notify(const SLog&);

	/**
	* @brief����CCountry����.
	* @return CCountry����ָ��
	*/
	CCountry* createCountry(void); 

private:
	QMenu *m_pFileMenu;			/// �ļ��˵�
	QMenu *m_pEditMenu;			/// �༭�˵�
	QMenu *m_pFormatMenu;		/// ��ʽ�˵�(�����˵�)
	QMenu *m_pHelpMenu;			/// �����˵�
	
	QToolBar *m_pFileToolBar;	/// �ļ�������
	QToolBar *m_pEditToolBar;	/// �༭������

	QActionGroup *m_pAlignmentGroup;

	QAction *m_pOpenAct;		/// ��
	QAction *m_pSaveAct;		/// ����
	QAction *m_pExitAct;		/// �˳�

	QAction *m_pCutAct;			/// ����
	QAction *m_pCopyAct;		/// ����
	QAction *m_pPasteAct;		/// ���
	QAction *m_pBoldAct;		/// ���� 
	QAction *m_pItalicAct;		/// б��
	QAction *m_pLeftAlignAct;	/// �����
	QAction *m_pRightAlignAct;	/// �Ҷ���
	QAction *m_pCenterAct;		/// ����
	
	QAction *m_pSetLineSpacingAct; /// �����м��
	QAction *m_pSetParagraphSpacingAct;/// ���öμ��

	QAction *m_pAboutAct;	/// ����

	QLabel *m_pInfoLabel;	/// ��Ϣ��ǩ
	QLabel* m_pMouseLabel;	/// ���λ����ʾ

	CTextEdit* m_pTextEdit; /// �༭��
	CTreeView* m_pTreeView; /// ����������ͼ

	QMutex		m_mtx;			// ����������������m_pLogDockWidget
	CLogDockWidget*	m_pLogDockWidget;		/// ��־�������

};

#endif // MAINWINDOW_H