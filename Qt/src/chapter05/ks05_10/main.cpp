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
#include <QTranslator>	// 国际化
#include "qglobal.h"
#include <QLibraryInfo> // 国际化

#include <iostream>


#include "maindialog.h"


using std::cout;
using std::endl;

int main(int argc, char * argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);
	QApplication app(argc, argv);

	// 国际化
	// 安装qt自带的中文翻译
	const QString localSysName = QLocale::system().name();
	QScopedPointer<QTranslator> qtTranslator(new QTranslator(QCoreApplication::instance()));
	if (qtTranslator->load(QStringLiteral("qt_") + localSysName,
		QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
	{
		QCoreApplication::installTranslator(qtTranslator.take());
	}

	// 安装我们项目的翻译文件
	QString strPath = qgetenv("TRAINDEVHOME");	// 获取环境变量所指向的路径
	strPath += "/system/lang";					// $TRAINDEVHOME/system/lang/ks05_10.qm
	QScopedPointer<QTranslator> gpTranslator(new QTranslator(QCoreApplication::instance()));
	if (gpTranslator->load("ks05_10.qm", strPath))
	{
		QCoreApplication::installTranslator(gpTranslator.take());
	}

	CMainDialog dlg(NULL);
	dlg.exec();
   
	return 0;
}
