
#include <QAction>
#include <QActionEvent>
#include <QEvent>

#include "mypushbutton.h"

CMyPushButton::CMyPushButton(const QString &text, QWidget *parent)
:QPushButton(text, parent), m_pAction(NULL)
{
	setFlat(true);
	setCheckable(false);
	setEnabled(true);
}

CMyPushButton::~CMyPushButton()
{
}

void CMyPushButton::setAction(QAction *pAction)
{
	if (pAction == NULL)
	{
		return;
	}
	m_pAction = pAction;
	m_pAction->installEventFilter(this);

	//使用Action初始化按钮状态
	setEnabled(m_pAction->isEnabled());
	setCheckable(m_pAction->isCheckable());
	setChecked(m_pAction->isChecked());

	//设置按钮的初始样式
	setButtonStyle(isEnabled());

	//按钮状态触发Action变化
	connect(this, SIGNAL(clicked()), m_pAction, SIGNAL(triggered()));
	connect(this, SIGNAL(toggled(bool)), m_pAction, SLOT(setChecked(bool)));

	//监视action状态信号
	////action的信号已经发射，但是始终就是无法触发槽函数，不知道为什么？？？
	//connect(m_pAction, SIGNAL(toggled(bool)), this, SLOT(setChecked(bool)));
	connect(m_pAction, SIGNAL(changed()), this, SLOT(onActionChanged()));
}

void CMyPushButton::setStateIcon(const QString& normUrl, const QString& overUrl, const QString& downUrl, const QString& disableUrl)
{
	m_IconNormUrl = normUrl;
	m_IconOverUrl = overUrl;
	m_IconDownUrl = downUrl;
	m_IconDisableUrl = disableUrl;
	setButtonStyle(true);
}

void CMyPushButton::onActionChanged()
{
	setEnabled(m_pAction->isEnabled());
	setButtonStyle(m_pAction->isEnabled());
}

void CMyPushButton::setButtonStyle(bool isEnable)
{
	QImage normImg(m_IconNormUrl);
	QImage downImg(m_IconDownUrl);
	QImage overImg(m_IconOverUrl);
	QImage disableImg(m_IconDisableUrl);

	QString styleSheet= QString::null;
	if (isEnable)
	{
		styleSheet = QString::fromLocal8Bit(
			"QPushButton{width:%1px;height:%2px;background-image:url('%3')}"			//设置普通状态图片
			"QPushButton:hover{background-image:url('%4')}"
			"QPushButton:pressed{background-image:url('%5')}"
			"QPushButton:checked{background-image:url('%6')}"
			"QPushButton::menu-indicator{image:none;}"
			"QPushButton{border:none;margin:0px;}"
			)
			.arg(normImg.size().width())
			.arg(normImg.size().height())
			.arg(m_IconNormUrl)
			.arg(m_IconOverUrl)
			.arg(m_IconDownUrl)
			.arg(m_IconDownUrl);
	}
	else
	{
		styleSheet = QString::fromLocal8Bit(
			"QPushButton{width:%1px;height:%2px;background-image:url('%3')}"			//设置普通状态图片
			"QPushButton:hover{background-image:url('%4')}"
			"QPushButton:pressed{background-image:url('%5')}"
			"QPushButton:checked{background-image:url('%6')}"
			"QPushButton::menu-indicator{image:none;}"
			"QPushButton{border:none;margin:0px;}"
			)
			.arg(disableImg.size().width())
			.arg(disableImg.size().height())
			.arg(m_IconDisableUrl)
			.arg(m_IconDisableUrl)
			.arg(m_IconDisableUrl)
			.arg(m_IconDisableUrl);
	}

	setStyleSheet(styleSheet);
}

//action的toggle信号虽然发射，但是始终无法触发槽函数onCheckChanged(bool)，
//不知道是什么原因，无奈之下，只能通过action的change事项来同步按钮状态。
bool CMyPushButton::eventFilter(QObject *obj, QEvent *e)
{
	if (e->type() == QEvent::ActionChanged)
	{
		QActionEvent* event = dynamic_cast<QActionEvent*>(e);
		if (event->action() == m_pAction)
		{
			setChecked(m_pAction->isChecked());
			return true;
		}
	}

	return QPushButton::eventFilter(obj, e);
}