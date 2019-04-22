/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: main.cpp
\brief mian()函数的实现文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/

//#include "qglobal.h"
#include <QString>
#include <QRectF>
#include <QObject>
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

#include <iostream>

bool example01(const QString& strInput, QString& strDir, QString& strFileName);
QString example02(int level, const QString& strPerson, const QString& strComputer, const QString& strInfo);
QString example03(const QRectF& rect);
QString example04(const QString& strTemplateName, int nTerminalCount);
void example05();
void example06();


using std::cout;
using std::cin;
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
	strPath += "/system/lang";					// $TRAINDEVHOME/system/lang/ks03_01.qm
	QScopedPointer<QTranslator> gpTranslator(new QTranslator(QCoreApplication::instance()));
	if (gpTranslator->load("ks04_03.qm", strPath))
	{
		QCoreApplication::installTranslator(gpTranslator.take());
	}

	// example01, 从输入目录中获取目录名、文件名
	if (false) {
		QString strInput = "d:\\project\\gui\\src\\chapter01\\ks01_01\\ks01_01.pro";
		bool bok;
		QString strDir;
		QString strFileName;
		bok = example01(strInput, strDir, strFileName);
	}

	// example02, 组织日志信息
	if (false) {
		QString strWholeInfo = example02(3, "Lisa", "adm01", "modified data at 12:00PM.");
	}

	// example03, 使用arg()接口对信息格式化, 输出矩形的坐标、宽高
	if (false) {
		QRectF rct(20.f, 30.f, 50.f, 60.f);
		example03(rct);
	}

	// example04, 使用arg()接口对信息格式化, 带翻译
	if (false) {
		example04(QString::fromLocal8Bit("柱上断路器"), 2);
	}


	// example05, 解析用特定分隔符组成的字符串
	if (false) {
		example05();
	}

	// example06, 字符串与数值的相互转换
	if (true) {
		example06();
	}


	char ch = '\0';
	cin >> ch;

	return 0;
}

/**
* @brief  从输入目录中获取目录名、文件名
* @param[in] strInput  文件全路径
* @param[out] strDir	文件所在目录
* @param[out] strFileName  文件名(不含目录)
* @return true:成功, false:失败
*/
bool example01(const QString& strInput, QString& strDir, QString& strFileName){
	
	if (0 == strInput.length())
		return false;

	QString str = strInput;		// str = "d:\\project\\gui\\src\\chapter01\\ks01_01\\ks01_01.pro";

	// 首先将分隔符统一，便于统一处理windows及linux的目录
	str.replace("\\", "/");		// str=d:/project/gui/src/chapter01/ks01_01/ks01_01.pro
	
	int idx = str.lastIndexOf("/");
	strDir = str.left(idx);		// strDir=d:/project/gui/src/chapter01/ks01_01


	strFileName = str.right(str.length()-(idx+1));	// 用idx+1的目的是忽略文件名前面的"/"
								// strFileName = ks01_01.pro

	return true;
}

/**
* @brief  组织日志信息
* @param[in] level  日志等级
* @param[in] strPerson	人员信息
* @param[in] strComputer  机器信息
* @param[in] strInfo  日志详情
* @return 拼接后的日志
*/
QString example02(int level, const QString& strPerson, const QString& strComputer, const QString& strInfo){
	QString str;
	str.sprintf("---- level=%02d, Person:", level);	// str = "---- level=01, Person:"
	str += strPerson;								// str = "---- level=01, Person:Lisa"
	str += ", Computer:";							// str = "---- level=01, Person:Lisa, Computer:"
	str += strComputer;								// str = "---- level=01, Person:Lisa, Computer:adm01"
	str += ", info=";								// str = "---- level=01, Person:Lisa, Computer:adm01, info="
	str += strInfo;									// str = "---- level=01, Person:Lisa, Computer:adm01, info=xxxxxx";
	return str;
}


/**
* @brief  使用arg()接口对信息格式化,输出矩形的坐标、宽高
* @param[in] rect  矩形
* @return 矩形的坐标、宽高
*/
QString example03(const QRectF& rect){
	QString strRect = QString("%1,%2,%3,%4").arg(rect.x()).arg(rect.y()).arg(rect.width()).arg(rect.height());
	return strRect;
}
/**
* @brief  使用arg()接口对信息格式化,带翻译
* @param[in] strTemplateName  模板名称
* @param[in] nTerminalCount  端子个数
* @return 格式化后的信息
*/
QString example04(const QString& strTemplateName, int nTerminalCount){
	QString strInfo = QObject::tr("template name:%1 already has terminal count=%2.").arg(strTemplateName).arg(nTerminalCount);
	cout << strInfo.toLocal8Bit().data() << endl;
	return strInfo;
}

/**
* @brief  解析用特定分隔符组成的字符串
* @return 格式化后的信息
*/
void example05(){
	QString str = QString::fromLocal8Bit(" 星点课堂, 女儿叫老白, C++|Qt");
	
	// 删除多余的空格
	str = str.trimmed();	

	QStringList strList = str.split(",");	// strList[0] : "星点课堂"
											// strList[1] : "女儿叫老白"
											// strList[2] : "C++|Qt"

	cout << "机构:" << strList[0].toLocal8Bit().data() << endl;
	cout << "姓名:" << strList[1].toLocal8Bit().data() << endl;

	// 把"|"换成","
	QString strCategory = strList[2];		// strCategory : "C++|Qt"
	strCategory.replace("|", ",");			// strCategory : "C++,Qt"
	cout << "领域:" << strCategory.toLocal8Bit().data() << endl;
}

/**
* @brief  字符串与数字互相转换
* @return 无
*/
void example06(){

	QString str1 = "2147483648"; // int32最大值：2147483647
	int nInt32 = str1.toInt();
	uint uInt32 = str1.toUInt();
	cout << "int32 data = " << nInt32 << endl;
	cout << "uInt32 data = " << uInt32 << endl;

	QString str2;
	nInt32 = 2147483647;
	str1.sprintf("%d", nInt32);
	cout << "new int32 data = " << str1.toLocal8Bit().data() << endl;

	str2.sprintf("%d", uInt32);
	cout << "new uint32 data = " << str2.toLocal8Bit().data() << endl;

	str2.sprintf("%u", uInt32);
	cout << "new uint32 data = " << str2.toLocal8Bit().data() << endl;

	str1 = QString("%1").arg(nInt32);
	cout << "another new int32 data = " << str1.toLocal8Bit().data() << endl;

	QString str3 = "200.f";
	float f = str3.toFloat();
	cout << "float data = " << f << endl;

	str3 = "200";
	f = str3.toFloat();
	cout << "float data = " << f << endl;

	QString str4 = "3.1415926535897932";
	qreal d = str4.toDouble();
	QString strData;
	strData = QString::number(d);
	cout << "double data = " << strData.toLocal8Bit().data() << endl;
	strData = QString::number(d, 'g', 16); // 需要明确指明精度，否则默认只有6位小数。
	cout << "double data = " << strData.toLocal8Bit().data() << endl;

}

