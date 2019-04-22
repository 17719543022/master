/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: main.cpp
\brief qDebug的使用示例

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/

//#include "qglobal.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QLibraryInfo>
#include <qlogging.h>
#include <QMutex>
#include <QMutexLocker>
#include <QObject>
#include <QRectF>
#include <QString>
#include <QTranslator>

#include <iostream>
#include "myclass.h"
#include "base/basedll/baseapi.h"

void example01();
void example02();
void example03();

QString getPath(const QString& strInputPath);
QMutex g_mutex; // 为了支持多线程功能，需要使用锁来保护对日志文件的操作。
void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& info)
{
	// 加锁
	QMutexLocker locker(&g_mutex);
	// 把信息格式化
	QString log = QString::fromLocal8Bit("msg-[%1], file-[%2], func-[%3], category-[%4]\n").arg(info).arg(context.file)
		.arg(context.function).arg(context.category);
	
	bool bok = true;
	switch (type)
	{
	case QtDebugMsg:
		log.prepend("Qt dbg:");
		break;
	case QtWarningMsg:
		log.prepend("Qt warn:");
		break;
	case QtCriticalMsg:
		log.prepend("Qt critical:");
		break;
	case QtFatalMsg:
		log.prepend("Qt fatal:");
		break;
	case QtInfoMsg:
		log.prepend("Qt info:");
		break;
	default:
		bok = false;
		break;
	}
	if (bok) {
		QString strFileName = getPath("$TRAINDEVHOME/test/chapter04/ks04_04/log04_04.inf");
		QString strDir = ns_train::getDirectory(strFileName);
		QDir dir;
		dir.mkpath(strDir);
		QFile file(strFileName);
		if (!file.open(QFile::ReadWrite | QFile::Append)) {
			return;
		}
		file.write(log.toLocal8Bit().data());
		file.close();
	}
}
using std::cout;
using std::cin;
int main(int argc, char * argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);
	QApplication app(argc, argv);
	
	// 输出重定向
	//qInstallMessageHandler(customMessageHandler);

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
	strPath += "/system/lang";					// $TRAINDEVHOME/system/lang/ks03_01.qm
	QScopedPointer<QTranslator> gpTranslator(new QTranslator(QCoreApplication::instance()));
	if (gpTranslator->load("ks04_04.qm", strPath))
	{
		QCoreApplication::installTranslator(gpTranslator.take());
	}
	// 
	//QVector<QString> vec;
	//vec.push_back("nice to meet you!");
	//qDebug("%s", vec[0].toLocal8Bit().data());

	// example01 
	if (0) {
		example01();
	}

	// example02 
	if (1) {
		example02();
	}
	
	// example03 
	if (0) {
		example03();
	}

	cout << "please input any key to exit......";
	char ch = '\0';
	cin >> ch; // 键入任意字符退出

	return 0;
}

/**
* @brief  qDebug()<< 方式输出信息
*		  可以直接用<<操作符将需要输出的信息输出到qDebug()。
* @return 无
*/
void example01(){
	
	int iVal = 334;
	QString str = "I live in China";
	qreal dPi = 3.1415926535897932f;
	qDebug() << "My Value is " << iVal << ". " << str << ". Pi=" << dPi;
	qWarning() << "My Value is " << iVal << ". " << str;
	qCritical() << "My Value is " << iVal << ". " << str;

}

/**
* @brief  使用qDebug("%")格式化输出信息
* @return 无
*/
void example02(){
	
	QString str = "China";
	QDateTime dt = QDateTime::fromTime_t(time(NULL));
	qreal dPi = 3.141592653589793;
	QString strPi = QString::number(dPi, 'g', 16);
	qDebug("I live in %s. Today is %04d-%02d-%02d, PI = %s", str.toLocal8Bit().data(),
		dt.date().year(), dt.date().month(), dt.date().day(), strPi.toLocal8Bit().data());
	
	qWarning("I live in %s. Today is %04d-%02d-%02d", str.toLocal8Bit().data(),
		dt.date().year(), dt.date().month(), dt.date().day());
	qCritical("I live in %s. Today is %04d-%02d-%02d", str.toLocal8Bit().data(),
		dt.date().year(), dt.date().month(), dt.date().day());
	// 下面两行代码如果解封，其功能是弹出异常界面，并显示我们给出的异常信息。
	//qFatal("I live in %s. Today is %04d-%02d-%02d", str.toLocal8Bit().data(),
	//	dt.date().year(), dt.date().month(), dt.date().day());
}


/**
* @brief  将自定义类输出到qDebug
* @param[in] mc 自定义类
* @return 
*/
void example03(){
	CMyClass mc;
	mc.setId(10000);
	mc.setName(QString::fromLocal8Bit("秦始皇"));
	qDebug() << mc;
}


QString getPath(const QString& strInputPath) {
	QString strPath = strInputPath;
	strPath.replace("\\", "/");
	int idx = strPath.indexOf("$");
	if (idx < 0) {
		return strPath.toLower();
	}
	QString strRight = strPath.right(strPath.length() - idx);
	idx = strRight.indexOf("/");
	QString strEnvironmentVariable = strRight.left(idx);
	strPath.remove(strEnvironmentVariable);
	strEnvironmentVariable.remove("$");
	QString str = qEnvironmentVariable(strEnvironmentVariable.toLocal8Bit().data());
	if (str.length() > 0) {
		str.replace("\\", "/");
		if (str.right(1) == "/") { // 删除环境变量中最后的"/"
			str = str.left(str.length() - 1);
		}
		strPath.insert(0, str);
	}
	strPath = strPath.toLower();
	return strPath;
}