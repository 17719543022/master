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
#include <QListWidget>
#include "base/basedll/baseapi.h"
#include "mainwindow.h"
#include "textedit.h"


CMainWindow::CMainWindow(QWidget* parent) : QMainWindow(parent)
{
	initialize();

	createActions();
	createMenus();
	createToolBars();
	createStatusBar();
	createDockWindows();

	connectSignalAndSlot();

	setWindowTitle(tr("Demo"));
	setMinimumSize(160, 160);
	resize(480, 320);
}

void CMainWindow::initialize()
{
	m_pTextEdit = new CTextEdit(this);

	setCentralWidget(m_pTextEdit);


	setCorner(Qt::TopLeftCorner, Qt::TopDockWidgetArea);

}

void CMainWindow::connectSignalAndSlot()
{
	connect(m_pTextEdit, SIGNAL(viewMouseMove(QMouseEvent*)), 
			this, SLOT(onMouseMoveInView(QMouseEvent*)));

	connect(m_pTextEdit, SIGNAL(selectionChanged()),
			this, SLOT(onSelectionChanged()));
	
	connect(m_pParagraphsList, &QListWidget::currentTextChanged,
			this, &CMainWindow::addParagraph);
}
/// 鼠标位置更新
void CMainWindow::onMouseMoveInView(QMouseEvent* event)
{
	const QPointF ptLocal = event->localPos();
	QPoint pt = ptLocal.toPoint();
	QString str;
	str.sprintf("%d, %d", pt.x(), pt.y());
	m_pMouseLabel->setText(str);
}

void CMainWindow::onSelectionChanged()
{
	QTextCursor tc = m_pTextEdit->textCursor(); // 获取光标下选中的文本对象
	QTextCharFormat textCharFormat = tc.charFormat(); // 获取它的格式
	bool b = textCharFormat.font().bold(); // 获取字体的粗体信息
	
	m_pBoldAct->blockSignals(true); // 必须先阻塞信号，否则，setChecked()调用将触发m_pBoldAct的triggered()信号。
	m_pBoldAct->setChecked(b);		// 设置粗体按钮的状态
	m_pBoldAct->blockSignals(false); // 解锁信号
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
void CMainWindow::open()
{
	m_pInfoLabel->setText(tr("Invoked <b>File|Open</b>"));

	QString szDir = ns_train::getDirectory("$TRAINDEVHOME/test/chapter08/ks08_01/");
//  QString strFilter ("*.txt *.doc");
	QString strFilter ("text file(*.txt);;XML File(*.xml);;*(*.*)");

#ifdef WIN32
	QString fileName = QFileDialog::getOpenFileName(this, tr("select file to open"), szDir, strFilter);
#else
	QString fileName = QFileDialog::getOpenFileName(this, tr("select file to open"),
		szDir, strFilter, NULL, QFileDialog::DontUseNativeDialog);
#endif
	if (!fileName.isEmpty())
	{
		fileName = ns_train::getFileName(fileName);
		QString str = m_pTextEdit->currentFileName();
		if (str == fileName)
		{
			return;
		}

		QString strError;
		if (m_pTextEdit->openFile(fileName))
		{
			m_pInfoLabel->setText(tr("file has been loaded"));
		}
		else
		{
			m_pInfoLabel->setText(tr("file can not open!"));
			return;
		}
	}
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

void CMainWindow::bold(bool bChecked)
{
	m_pInfoLabel->setText(tr("Invoked <b>Edit|Format|Bold</b>"));
	QTextCursor tc = m_pTextEdit->textCursor();  // 获取当前光标下的文本对象
	QTextCharFormat textCharFormat = tc.blockCharFormat();// 获取该对象的格式信息
	QFont ft = textCharFormat.font();	// 获取字体信息
	ft.setBold(bChecked);				// 根据按钮的状态设置字体的粗体信息
	textCharFormat.setFont(ft);			// 重新为格式信息对象设置字体
	m_pTextEdit->setCurrentCharFormat(textCharFormat); // 为选中的文本更新格式。
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

	m_pSaveAct = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
	m_pSaveAct->setShortcuts(QKeySequence::Save);
	m_pSaveAct->setStatusTip(tr("Save the document to disk"));
	connect(m_pSaveAct, &QAction::triggered, this, &CMainWindow::save);

	m_pExitAct = new QAction(tr("E&xit"), this);
	m_pExitAct->setShortcuts(QKeySequence::Quit);
	m_pExitAct->setStatusTip(tr("Exit the application"));
	connect(m_pExitAct, &QAction::triggered, this, &QWidget::close);

	m_pCutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
	m_pCutAct->setShortcuts(QKeySequence::Cut);
	m_pCutAct->setStatusTip(tr("Cut the current selection's contents to the "
		"clipboard"));
	connect(m_pCutAct, &QAction::triggered, this, &CMainWindow::cut);

	m_pCopyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
	m_pCopyAct->setShortcuts(QKeySequence::Copy);
	m_pCopyAct->setStatusTip(tr("Copy the current selection's contents to the "
		"clipboard"));
	connect(m_pCopyAct, &QAction::triggered, this, &CMainWindow::copy);

	m_pPasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
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


void CMainWindow::createToolBars()
{
	m_pFileToolBar = addToolBar(tr("file tool bar"));
	m_pFileToolBar->setObjectName("file tool bar");

	m_pFileToolBar->addAction(m_pOpenAct);
	m_pFileToolBar->addAction(m_pSaveAct);

	m_pEditToolBar = addToolBar(tr("edit tool bar"));
	m_pEditToolBar->setObjectName("edit tool bar");
	m_pEditToolBar->addAction(m_pCutAct);
	m_pEditToolBar->addAction(m_pCopyAct);
	m_pEditToolBar->addAction(m_pPasteAct);
	m_pEditToolBar->addAction(m_pBoldAct);

}
void CMainWindow::createDockWindows()
{
	QDockWidget *dock = new QDockWidget(tr("Paragraphs"), this);
	m_pParagraphsList = new QListWidget(dock);
	QStringList strList;
	strList << "I have learned how to use QDockWidget today."
		<< "Thank for beging with me."
		<< "I will make some practice tonight.";
	m_pParagraphsList->addItems(strList);
		
	dock->setWidget(m_pParagraphsList);
	addDockWidget(Qt::RightDockWidgetArea, dock);
	//viewMenu->addAction(dock->toggleViewAction());

}
void CMainWindow::addParagraph(const QString &paragraph)
{
	if (paragraph.isEmpty())
		return;
	QTextCursor cursor = m_pTextEdit->textCursor();
	if (cursor.isNull())
		return;
	cursor.beginEditBlock();
	cursor.movePosition(QTextCursor::PreviousBlock, QTextCursor::MoveAnchor, 2);
	cursor.insertBlock();
	cursor.insertText(paragraph);
	cursor.insertBlock();
	cursor.endEditBlock();

}