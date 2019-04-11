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
#include <QPushButton>

#include "dialog.h"


CDialog::CDialog(QWidget* pParent) : QDialog(pParent) {
	setupUi(this);


	connect(btnTest, &QPushButton::clicked, this, &CDialog::onTest);
	//connect(cbFontSize, &QFontComboBox::currentIndexChanged, this, &CDialog::on_fontSizeChanged);
}

CDialog::~CDialog(){
	
}


void CDialog::onTest(){
	QImage* imgScaled = new QImage(":/images/qt.png");
	int w = imgScaled->width();
	int h = imgScaled->height();
	//int w = 1600;
	//int h = 1200;
	unsigned char *p = imgScaled->bits();
	int nsize = imgScaled->sizeInBytes();
	unsigned char *q = new unsigned char[nsize];
	if (!p)
	{
		//qDebug() << "NULL!";
	}
	else
	{	
		//a = Enhance(p, q, w, h, 0.01f, 0.01f);
		memcpy(q, p, nsize); // 相当于调用enhance
		QImage image(q, w, h, imgScaled->format());
		image = image.scaled(600,
			400,
			Qt::KeepAspectRatio);

		imageLabel->setPixmap(QPixmap::fromImage(image));
	}

}

