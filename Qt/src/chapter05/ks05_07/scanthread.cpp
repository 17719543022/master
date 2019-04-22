/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: scan.cpp
\brief  CScanThread 目录扫描线程，负责扫描指定目录并发送事件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/
#include "baseapi.h"
#include <QDir>
#include <QFileInfoList>
#include <QFileInfoList>
#include "customevent.h"
#include "dialog.h"
#include "scanthread.h"

CScanThread::CScanThread() {

}

CScanThread::~CScanThread() {

}

void CScanThread::run()
{
	QString str = ns_train::getPath("$TRAINDEVHOME/test/chapter05/ks05_07/");
	QDir dir(str);
	QFile file;
	QStringList filters;
	QString strFileName;
	QFileInfoList fileInfoList;
	QFileInfoList::iterator iteFileInfo;
	QFileInfo fileInfo;
	CCustomEvent* pEvent = NULL;
	while (isRunning()) {
		sleep(1);
		
		if (NULL == m_pDialog) {
			continue;
		}
		fileInfoList = dir.entryInfoList(filters, QDir::Dirs | QDir::Files | QDir::NoSymLinks);
		iteFileInfo = fileInfoList.begin();
		fileInfo;
		for (iteFileInfo = fileInfoList.begin(); iteFileInfo != fileInfoList.end(); iteFileInfo++) {
			fileInfo = *iteFileInfo;
			strFileName = fileInfo.fileName();
			if ((strFileName == ".") || (strFileName == "..")) { // 跳过本目录和上级目录指示符。
				continue;
			}
			if (fileInfo.isFile()) {
				pEvent = new CCustomEvent();
				pEvent->setFileName(strFileName);
				strFileName = str + strFileName;
				file.setFileName(strFileName);
				file.remove();
				QCoreApplication::postEvent(m_pDialog, pEvent);
			}
		}
	}
}