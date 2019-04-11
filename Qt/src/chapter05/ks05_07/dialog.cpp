/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dialog.cpp
\brief  CDialog

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/

#include "customevent.h"
#include "dialog.h"


CDialog::CDialog(QWidget* pParent) : QDialog(pParent) {
	setupUi(this);
	plainTextEdit->setPlainText("file detected:");

	//connect(fontComboBox, SIGNAL(currentFontChanged(const QFont &)), this, SLOT(on_fontFamilyChanged(const QFont &)));
	connect(cbFontSize, SIGNAL(currentIndexChanged(int)), this, SLOT(on_fontSizeChanged(int)));

	connect(fontComboBox, &QFontComboBox::currentFontChanged, this, &CDialog::on_fontFamilyChanged);
	//connect(cbFontSize, &QFontComboBox::currentIndexChanged, this, &CDialog::on_fontSizeChanged);
}

CDialog::~CDialog(){
	
}


void CDialog::on_fontFamilyChanged(const QFont &font){
	int fontSize = cbFontSize->currentText().toInt();
	QFont ft = font;
	ft.setPointSize(fontSize);
	plainTextEdit->setFont(ft);
}

void CDialog::on_fontSizeChanged(int /*idx*/){
	int fontSize = cbFontSize->currentText().toInt();
	QFont ft = fontComboBox->currentFont();
	ft.setPointSize(fontSize);
	plainTextEdit->setFont(ft);
}

void CDialog::customEvent(QEvent *event) {
	QString str;
	CCustomEvent* pEvent = NULL;
	switch (event->type()) {
	case (QEvent::User+1): 	{
			pEvent = dynamic_cast<CCustomEvent*>(event);
			if (NULL != pEvent) {
				str = plainTextEdit->toPlainText();
				str += "\n";
				str += pEvent->getFileName();
				plainTextEdit->setPlainText(str);
			}
		}
		break;
	default:
		break;
	}
}
