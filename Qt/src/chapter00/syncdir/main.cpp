/*! \file: main.cpp
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\brief mian()函数的实现文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/8
*/
#include <QCoreApplication>
#include <QStringList>
#include <QDir>

#include <iostream>

#include "qglobal.h"
#include "sync.h"


using std::cerr;
using std::cout;
using std::endl;

/////////////////////////////////////////////////////////////////////
int main(int argc, char * argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);
	QCoreApplication app(argc, argv);

	CSync sync;
	sync.exec();  

	

	return 0;
}




