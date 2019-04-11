/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: sendthread.cpp
\brief  CSendThread 目录扫描线程，负责扫描指定目录并发送事件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2019/3
*/
#include <QFile>
#include <QTextStream>
#include "baseapi.h"
#include "config.h"
#include "sendthread.h"

CSendThread::CSendThread() {

}

CSendThread::~CSendThread() {

}

void CSendThread::run()
{
	QString strFileName = ns_train::getPath("$TRAINDEVHOME/test/chapter12/ks12_03/send.txt");
	QFile file(strFileName);
    QString str;
	while (isRunning()) {
		sleep(1);
        str = QString("teacher:%1, ").arg(CConfig::instance().getTeacherNumber());
        str += QString("student:%1\n").arg(CConfig::instance().getStudentNumber());
       
        if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text))
            continue;
        QTextStream out(&file);
        out << str;
        file.close();
	}
}