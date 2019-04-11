

#include <QAction>
#include <QApplication>
#include <QBitmap>
#include <QCursor>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPainter>
#include <QResizeEvent>
#include <QStackedWidget>
#include <QToolTip>

#include "drawgeneralbar.h"
#include "mypushbutton.h"
#include "pagetogglebutton.h"
#include "publicinfomgr.h"
#include "toolbarpage.h"
#include "toolbarcontainer.h"


void CDrawGeneralBar::CStyle::drawControl(ControlElement element, const QStyleOption * opt, QPainter * p, const QWidget * widget) const
{
	if (m_pOwner->m_bUseBackgroundPixmap)
	{
		p->fillRect(opt->rect, QBrush(m_pOwner->m_backgroundPixmap));
	}
	else
	{
		p->fillRect(opt->rect, QBrush(m_pOwner->m_backgroundColor));
	}
	QProxyStyle::drawControl(element, opt, p, widget);
}

CDrawGeneralBar::CDrawGeneralBar(QWidget *parent)
: QToolBar(tr("MainToolBar"), parent),
m_pGeneralBarFrame(NULL), m_pToolBarContainer(NULL), m_pToolBarContainerShowBtn(NULL),
m_pMainMenuBtn(NULL), m_pMinimizeBtn(NULL), m_pMaximizeBtn(NULL),
m_pCloseBtn(NULL),  m_pTitleLable(NULL)
{
	toggleViewAction()->setVisible(false);
	//主工具条属性设置
	setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
	setMovable(false);
	setMouseTracking(true);
	setStyle(new CStyle(this));
	setStyleSheet("margin:0px 0px 0px 0px");

	QPixmap back_pixmap(CPublicInfoMgr::instance()->getIconPath()+"mainbar/bg_01.png");
	QPalette palette = this->palette();
	palette.setBrush(QPalette::Window, QBrush(back_pixmap));
	this->setPalette(palette);

	m_pPageToggleBtns.clear();
	m_bToolContainerShowFlag = true;
	m_bUseBackgroundPixmap = false;
	m_backgroundPixmap = back_pixmap;
	m_backgroundColor = QColor(145,199,213);
}

CDrawGeneralBar::~CDrawGeneralBar()
{
}

void CDrawGeneralBar::setTitleLable(QLabel* pTitleLable)
{
	m_pTitleLable = pTitleLable;
}

void CDrawGeneralBar::setTitle(const QString& title)
{
	m_pTitleLable->setText(title);
}

void CDrawGeneralBar::setMainMenuBtn(CMyPushButton* pMainMenuBtn)
{
	m_pMainMenuBtn = pMainMenuBtn;
}

CMyPushButton* CDrawGeneralBar::getMainMenuBtn(void) const
{
	return m_pMainMenuBtn;
}

void CDrawGeneralBar::addPageToggleBtn(CPageToggleButton* pPageToggleBtn)
{
	if (pPageToggleBtn != NULL)
	{
		connect(pPageToggleBtn, SIGNAL(togglePage(int)), this, SLOT(onTogglePage(int)));
		connect(m_pToolBarContainer->getStackWidget(), SIGNAL(currentChanged(int)), pPageToggleBtn, SLOT(onPageToggled(int)));
	}
	m_pPageToggleBtns.insert(pPageToggleBtn->objectName(), pPageToggleBtn);
}

void CDrawGeneralBar::setToolContainerShowBtn(CMyPushButton* pToolContainerShow) 
{
	m_pToolBarContainerShowBtn = pToolContainerShow;
	if (m_pToolBarContainerShowBtn != NULL)
	{
		connect(m_pToolBarContainerShowBtn, SIGNAL(clicked()), this, SLOT(setToolCantainerShow()));
	}
}


void CDrawGeneralBar::setMaximizeBtn(CMyPushButton* pMaximizeBtn)
{
	m_pMaximizeBtn = pMaximizeBtn;
}

void CDrawGeneralBar::setMinimizeBtn(CMyPushButton* pMinimizeBtn)
{
	m_pMinimizeBtn = pMinimizeBtn;
}

void CDrawGeneralBar::setCloseBtn(CMyPushButton* pCloseBtn)
{
	m_pCloseBtn = pCloseBtn;
}

void CDrawGeneralBar::setToolBarContainer(CToolBarContainer* pToolBarContainer)
{
	m_pToolBarContainer = pToolBarContainer;
	connect(m_pToolBarContainer, SIGNAL(loseFocus()), this, SLOT(loseFocusCantainer()));
}

void CDrawGeneralBar::initInstance()
{
	//设置主工具条的布局
	m_pGeneralBarFrame = new QFrame(this);
	QGridLayout* wholeLayout = new QGridLayout();

	//第一行布局
	QHBoxLayout* pFirstLayout = new QHBoxLayout();
	////创建标题栏左侧弹簧
	QSpacerItem* pSpaceItemLeft = new QSpacerItem(400, 25, QSizePolicy::Fixed, QSizePolicy::Fixed);
	pFirstLayout->addItem(pSpaceItemLeft);
	pFirstLayout->addStretch();
	//添加标题栏
	pFirstLayout->addWidget(m_pTitleLable, 0, Qt::AlignHCenter);
	//创建标题栏右侧弹簧
	pFirstLayout->addStretch();

    //插入分割线
	QWidget* pWidgetLine1 = new QWidget(NULL);
	QHBoxLayout* pLayout1 = new QHBoxLayout(pWidgetLine1);
	pLayout1->setContentsMargins(QMargins(2, 0, 2, 0));
	QLabel* pVLineLable1 = new QLabel(NULL);
	pVLineLable1->setFixedSize(1, 21);
	QString vLableStyle = QString::fromLocal8Bit(
		" QLabel{ background: #c9c9c9}"
		);
	pVLineLable1->setStyleSheet(vLableStyle);
	pLayout1->addWidget(pVLineLable1);
	pWidgetLine1->setLayout(pLayout1);
	pFirstLayout->addWidget(pWidgetLine1);

	//添加功能区最小化按钮
	pFirstLayout->addWidget(m_pToolBarContainerShowBtn);

	//插入垂直分隔线
	QWidget* pWidgetLine2 = new QWidget(NULL);
	QHBoxLayout* pLayout2 = new QHBoxLayout(pWidgetLine2);
	pLayout2->setContentsMargins(QMargins(2, 0, 2, 0));
	QLabel* pVLineLable2 = new QLabel(NULL);
	pVLineLable2->setFixedSize(1, 21);
	pVLineLable2->setStyleSheet(vLableStyle);
	pLayout2->addWidget(pVLineLable2);
	pWidgetLine2->setLayout(pLayout2);
	pFirstLayout->addWidget(pWidgetLine2);

	//添加窗口控制按钮
	pFirstLayout->addWidget(m_pMinimizeBtn);
	pFirstLayout->addWidget(m_pMaximizeBtn);
	pFirstLayout->addWidget(m_pCloseBtn);

	//第二行布局
	QGridLayout* pSecondLayout = new QGridLayout();
	pSecondLayout->addWidget(m_pMainMenuBtn, 0, 0, 2, 1);
	//创建工具页切换按钮
	int i = 1;
	QMap<QString, CPageToggleButton*>::iterator it = m_pPageToggleBtns.begin();
	for (it; it != m_pPageToggleBtns.end(); it++)
	{
		CPageToggleButton* pPageToggleBtn = it.value();
		pSecondLayout->addWidget(pPageToggleBtn, 0, i, 2, 1);
		i++;
	}
	//创建弹簧
	QSpacerItem* pSpaceItemButtonRight = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	pSecondLayout->addItem(pSpaceItemButtonRight,0,i,1,1);

	//插入水平线
	QLabel* pHLineLable = new QLabel;
	pHLineLable->setFixedHeight(1);
	QString hLableStyle = QString::fromLocal8Bit(
		" QLabel{ background: #c9c9c9}"
		);
	pHLineLable->setStyleSheet(hLableStyle);
	pSecondLayout->addWidget(pHLineLable, 1, i, 1, 3, Qt::AlignBottom);

	//工具条总布局
	wholeLayout->addLayout(pFirstLayout, 0, 0, 1, 1);
	wholeLayout->addLayout(pSecondLayout, 1, 0, 1, 1);
	wholeLayout->addWidget(m_pToolBarContainer, 3, 0, 1, 1);
	wholeLayout->setContentsMargins(0, 0, 0, 0);//设置布局与窗口间隔
	wholeLayout->setSpacing(0);
	m_pGeneralBarFrame->setLayout(wholeLayout);
	m_pGeneralBarFrame->setFixedSize(size());

	//主工具条的默认设置
	m_pToolBarContainer->hide();
	setToolCantainerShow();
	setCurrentPage(0);
}

void CDrawGeneralBar::setToolCantainerShow()
{
	if (m_pToolBarContainer->isHidden())
	{
		m_pToolBarContainer->show();
		setFixedHeight(160);
		m_bToolContainerShowFlag = true;
	}
	else
	{
		m_pToolBarContainer->hide();
		setFixedHeight(51);
		m_bToolContainerShowFlag = false;
	}
}

void CDrawGeneralBar::onTogglePage(int index)
{
	if (m_bToolContainerShowFlag)
	{
		m_pToolBarContainer->onPageChanged(index);
	}
	else
	{
		m_pToolBarContainer->onPageChanged(index);
		m_pToolBarContainer->show();
		m_pToolBarContainer->activateWindow();
		m_pToolBarContainer->setFocus(Qt::ActiveWindowFocusReason);
		setFixedHeight(160);
	}
}

void CDrawGeneralBar::loseFocusCantainer()
{
	if (m_bToolContainerShowFlag)
	{
		return;
	}
	m_pToolBarContainer->hide();
	setFixedHeight(51);
}

void CDrawGeneralBar::setCurrentPage(int index)
{
	QMap<QString, CPageToggleButton*>::iterator it = m_pPageToggleBtns.begin();
	for (it; it != m_pPageToggleBtns.end();it++)
	{
		CPageToggleButton* pButton = it.value();
		if (pButton->getPageID() == index)
		{
			pButton->onPageToggled(index);
			break;
		}
	}
	m_pToolBarContainer->onPageChanged(index);
}

void CDrawGeneralBar::resizeEvent(QResizeEvent * e)
{
	resize(e->size().width(), height());
	m_pGeneralBarFrame->setFixedSize(size());
	QToolBar::resizeEvent(e);
}

