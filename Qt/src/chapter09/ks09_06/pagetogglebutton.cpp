
#include "pagetogglebutton.h"

CPageToggleButton::CPageToggleButton(const QString &text, const qint32 pageId, QWidget *parent)
:QPushButton(text, parent), m_PageId(pageId)
{
	setObjectName(text);
	setFlat(true);
	connect(this, SIGNAL(pressed()),this,SLOT(onClicked()));
}

CPageToggleButton::~CPageToggleButton()
{

}

void CPageToggleButton::setStateIcon(const QString& norm, const QString& over, const QString& down)
{
	m_IconNorm = norm;
	m_IconOver = over;
	m_IconDown = down;
	setNormalButtonStyle();
}

void CPageToggleButton::onClicked()
{
	emit togglePage(m_PageId);
}

void CPageToggleButton::onPageToggled(int index)
{
	if (index == m_PageId)
	{
		setSelectButtonStyle();
	}
	else
	{
		setNormalButtonStyle();
	}
}
void CPageToggleButton::setNormalButtonStyle()
{
	QImage x(m_IconNorm);
	QImage y(m_IconOver);
	QImage z(m_IconDown);

	//…Ë÷√QPushbuttonœ‘ æ—˘ Ω
	QString styleSheet = QString::fromLocal8Bit(
		"QPushButton{width:%1px;height:%2px;background-image:url('%3')}"			//…Ë÷√∆’Õ®◊¥Ã¨Õº∆¨
		"QPushButton:hover{width:%4px;height:%5px;background-image:url('%6')}"		//…Ë÷√Ωπµ„◊¥Ã¨Õº∆¨
		"QPushButton:pressed{width:%7px;height:%8px;background-image:url('%9')}"	//…Ë÷√µ„ª˜◊¥Ã¨Õº∆¨
		"QPushButton{border:none}"
		)
		.arg(x.size().width()).arg(x.size().height()).arg(m_IconNorm)
		.arg(y.size().width()).arg(y.size().height()).arg(m_IconOver)
		.arg(z.size().width()).arg(z.size().height()).arg(m_IconDown);
	setStyleSheet(styleSheet);
	setEnabled(true);
}

void CPageToggleButton::setSelectButtonStyle()
{
	QImage x(m_IconDown);

	//…Ë÷√QPushbuttonœ‘ æ—˘ Ω
	QString styleSheet = QString::fromLocal8Bit(
		"QPushButton{width:%1px;height:%2px;background-image:url('%3')}"			//…Ë÷√∆’Õ®◊¥Ã¨Õº∆¨
		"QPushButton:hover{width:%4px;height:%5px;background-image:url('%6')}"		//…Ë÷√Ωπµ„◊¥Ã¨Õº∆¨
		"QPushButton:pressed{width:%7px;height:%8px;background-image:url('%9')}"	//…Ë÷√µ„ª˜◊¥Ã¨Õº∆¨
		"QPushButton{border:none}"
		)
		.arg(x.size().width()).arg(x.size().height()).arg(m_IconDown)
		.arg(x.size().width()).arg(x.size().height()).arg(m_IconDown)
		.arg(x.size().width()).arg(x.size().height()).arg(m_IconDown);
	setStyleSheet(styleSheet);
	setEnabled(true);
}