/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。
\file: main.cpp
\brief mian()函数的实现文件


\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/8
*/
#include <QApplication>
#include <QFile>
#include <QMainWindow>
#include <QTextEdit>
#include <QTextStream>
#include "base/basedll/baseapi.h"

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
	
	QMainWindow mainWindow(NULL);
	QTextEdit textEdit(&mainWindow);
	QFile file;
	QString strFile = ns_train::getFileName("$TRAINDEVHOME/test/chapter09/ks09_01/input.txt");
	file.setFileName(strFile);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		return -1;
	}
	QTextStream input(&file);
	input.setCodec("GBK"); // 读者可以试试用: UTF-8。

	QString str = input.readAll();
	textEdit.setText(str);

	mainWindow.setCentralWidget(&textEdit);
	mainWindow.show();

    return app.exec();
}
