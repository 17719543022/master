

#include <QAccessible>
#include <QEvent>

#include "mytoolbutton.h"
#include "publicinfomgr.h"


CToolButtonDecorator::CToolButtonDecorator(QObject * parent)
:QObject(parent), m_pToolButton(NULL)
{
}

CToolButtonDecorator::~CToolButtonDecorator()
{
}

void CToolButtonDecorator::setToolButton(QToolButton* pToolButton)
{
	if (pToolButton!=NULL)
	{
		m_pToolButton = pToolButton;
		onToolButtonChange();
	}
}

QToolButton* CToolButtonDecorator::getToolButton()
{
	return m_pToolButton;
}


void CToolButtonDecorator::setToolButtonIcon(const QString& norm, const QString& over, const QString& down, const QString&disable)
{
	m_NormIcon = norm;
	m_OverIcon = over;
	m_DownIcon = down;
	m_DisableIcon = disable;
}

void CToolButtonDecorator::onToolButtonChange()
{
	//设置按钮正常状态风格
	QImage x(m_NormIcon);
	QImage y(m_OverIcon);
	QImage z(m_DownIcon);
	QImage u(m_DisableIcon);
	QString styleSheet;
	if (m_pToolButton->isEnabled())
	{
		styleSheet = QString::fromLocal8Bit("QToolButton{width:%1px;height:%2px;background-image:url('%3')}"
			"QToolButton:hover{background-image:url('%4')}"
			"QToolButton:pressed{background-image:url('%5')}"
			"QToolButton:checked{background-image:url('%6')}"
			"QToolButton{padding:0px}"
			"QToolButton{border:none;margin:0px;}"
			"QToolButton::menu-button{image:none;}"
			)
			.arg(x.size().width()-3).arg(x.size().height()-3).arg(m_NormIcon)
			.arg(m_OverIcon)
			.arg(m_DownIcon)
			.arg(m_DownIcon);
	}
	else
	{
		styleSheet = QString::fromLocal8Bit("QToolButton{width:%1px;height:%2px;background-image:url('%3')}"
			"QToolButton:hover{background-image:url('%4')}"
			"QToolButton:pressed{background-image:url('%5')}"
			"QToolButton:checked{background-image:url('%6')}"
			"QToolButton{padding:0px}"
			"QToolButton{border:none;margin:0px;}"
			"QToolButton::menu-button{image:none;}"
			)
			.arg(x.size().width() - 3).arg(x.size().height() - 3).arg(m_DisableIcon)
			.arg(m_DisableIcon)
			.arg(m_DisableIcon)
			.arg(m_DisableIcon);
	}
	m_pToolButton->setStyleSheet(styleSheet);
}
