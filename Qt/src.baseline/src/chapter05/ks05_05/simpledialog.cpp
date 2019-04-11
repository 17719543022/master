/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: simpledialog.cpp
\brief  CSimpleDialog类的实现文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/
#include "simpledialog.h"


CSimpleDialog::CSimpleDialog(QWidget* pParent) : QDialog(pParent) {
	setupUi(this);
	
	//connect(fontComboBox, SIGNAL(currentFontChanged(const QFont &)), this, SLOT(on_fontFamilyChanged(const QFont &)));
	//connect(cbFontSize, SIGNAL(currentIndexChanged(int)), this, SLOT(on_fontSizeChanged(int)));

	//connect(fontComboBox, &QFontComboBox::currentFontChanged, this, &CDialog::on_fontChanged);
	//connect(cbFontSize, &QFontComboBox::currentIndexChanged, this, &CDialog::on_fontSizeChanged);
}

CSimpleDialog::~CSimpleDialog() {

}

void CSimpleDialog::on_addressSaved(const QString& strAddress){
	
	if (NULL != m_plainTextEdit->document()) {
		QString str = "The Address is:" + strAddress;
		m_plainTextEdit->document()->setPlainText(str);

	}
}

