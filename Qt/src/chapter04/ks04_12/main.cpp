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

#include <QDebug>
#include <QDir>
#include <QFile>
//#include "qglobal.h"

#include <iostream>

#include "ks04_11/myclass.h"

using std::cin;
using std::endl;
void pauseOnce();
void initialize(void);
void example01(void);
void example02(void);
void example03(void);
void example04(void);

// 暂停一下
void pauseOnce()
{
	char c = '\0';
	cin >> c;
   // system("pause");
}

int main(int argc, char * argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);

    // 文本文件初始化
    initialize();


    // 文本文件读取
    if (0) {
        example01();
    }

    // 文本文件,追加写入
    if (0) {
        example02();
    }

    // 文本文件,在开头写入
    if (0) {
        example03();
    }

    // 文件拷贝、改名、移动、删除
    if (1) {
        example04();
    }
    
    pauseOnce();

	return 0;
}


/**
* @brief 文本文件初始化
*
* @return void
*/
void initialize(void)
{
    QString strFileName;
    strFileName = ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_12/example01.txt");
	QString strDir = ns_train::getDirectory(strFileName);
	QDir dir;
	dir.mkpath(strDir);

    QFile file(strFileName);
    // 打开方式：只读、文本方式
    if (!file.open(QFile::Truncate | QFile::WriteOnly | QFile::Text)) {
        qDebug("open failed! file name is:%s", strFileName.toLocal8Bit().data());
        return;
    }
    // 输出整个文件的内容
    QString strContent;
    strContent += "i have an apple, here you are.\n";
    strContent += "i have a pear, here you are.\n";
    strContent += "i have an orange, here you are.\n";
	if (1) {
		file.write(strContent.toLocal8Bit());
	} 
	else {
		QTextStream out(&file);
		out << strContent;
	}

    qDebug("File created, this is the content:\n");
	qDebug() << strContent;
	
    file.close();
}

/**
* @brief 文本文件读取
*
* @return void
*/
void example01()
{
    QString strFileName;
    strFileName = ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_12/example01.txt");

    QFile file(strFileName);
    // 打开方式：只读、文本方式
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug("open failed! file name is:%s", strFileName.toLocal8Bit().data());
        return;
    }
    // 输出整个文件的内容
    QString strContent = file.readAll();
    qDebug("=====================================\n");
    qDebug("File Opened, this is the content:\n");
    qDebug() << strContent;
    
    
    // 将文件游标移到文件开头，否则的话，现在游标已经移动到文件尾，再执行后面的代码将无法读取到内容。
    file.seek(0);

    // 按行打印
    qDebug("\n\n=====================================\n");
    qDebug("All the lines:\n");
	if (false) {
		const int c_maxNumber = 10240;
		char buf[c_maxNumber];
		qint64 nRead = 0;
		qDebug("File Opened, this is the lines:");
		while (!file.atEnd()) {
			nRead = file.readLine(buf, c_maxNumber);
			strContent = buf;
			strContent.remove("\r");
			strContent.remove("\n");
			qDebug("%s", strContent.toLocal8Bit().data());
		}
	}
	else {
		QTextStream in(&file);
		while (!in.atEnd()) {
			QString line = in.readLine();
			qDebug("%s", line.toLocal8Bit().data());
		}
	}
    file.close(); // 千万不要忘记关闭文件哦

}

/**
* @brief 文本文件，追加写入
*
* @return void
*/
void example02()
{
    QString strFileName;
    strFileName = ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_12/example01.txt");

    QFile file(strFileName);
    // 打开方式：只读、文本方式
    //if (!file.open(QFile::ReadWrite | QFile::Text)) {
    if (!file.open(QFile::ReadWrite | QFile::Append | QFile::Text)) {
        qDebug("open failed! file name is:%s", strFileName.toLocal8Bit().data());
        return;
    }
	qDebug("\n\n=====================================\n");
	qDebug("File Opened, this is the content:\n");
	file.seek(0);// 使用QFile::Append打开文件后，游标默认在文件尾。
	QString strContent = file.readAll();// readAll()导致文件的游标到达文件尾。
    qDebug() << strContent;

    QString strNew = "i got another apple.";
    file.write(strNew.toLocal8Bit());

     // 输出整个文件的内容
	qDebug("\n\n=====================================\n");
	qDebug("File appended, this is the content:\n");
 	file.seek(0);
    strContent = file.readAll();// readAll()导致文件的游标到达文件尾。
    qDebug() << strContent;

    file.close();

}


/**
* @brief 文本文件，在开头写入
*
* @return void
*/
void example03()
{
    QString strFileName;
    strFileName = ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_12/example01.txt");

    QFile file(strFileName);
    // 打开方式：只读、文本方式
    if (!file.open(QFile::ReadWrite | QFile::Text)) {
        qDebug("open failed! file name is:%s", strFileName.toLocal8Bit().data());
        return;
    }
    // 输出整个文件的内容
	qDebug("\n\n=====================================\n");
	qDebug("File Opened, this is the content:\n");
    QString strContent = file.readAll();
    qDebug() << strContent;

	qDebug("\n\n=====================================\n");
    QString strNew = "add new line at the first line\n";
    strContent = strNew + strContent;
    
    file.resize(0); // 将文件内容清空

    file.write(strContent.toLocal8Bit());

    file.seek(0);   // 将文件游标移到文件开头，否则的话，现在游标已经移动到文件尾，再执行后面的代码将无法读取到内容。
	strContent = file.readAll();
    qDebug() << strContent;

    file.close();

}


/**
* @brief 文件拷贝、改名、移动、删除
*
* @return void
*/
void example04()
{
    QString strFileName;
    strFileName = ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_12/example01.txt");

    QFile file;
    file.setFileName(strFileName);
    if (!file.exists()) {
        return;
    }
    QDir dir;
    QString strDirectory;
    // 拷贝
    QString strNewFileName = ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_12/copy.txt");
    strDirectory  = ns_train::getDirectory(strNewFileName);
    dir.mkpath(strDirectory); // 请注意makepath()与makedir()的区别
    file.copy(strNewFileName);
    pauseOnce();

    // 改名
    strNewFileName = ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_12/new.txt");
    strDirectory = ns_train::getDirectory(strNewFileName);
    dir.mkpath(strDirectory);
    file.rename(strNewFileName);
    pauseOnce();

    // 移动
    strNewFileName = ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_12/move/dir/new.txt");
    strDirectory = ns_train::getDirectory(strNewFileName);
    dir.mkpath(strDirectory);
    file.rename(strNewFileName);
    pauseOnce();

    // 删除
    file.remove();

    file.close();

}