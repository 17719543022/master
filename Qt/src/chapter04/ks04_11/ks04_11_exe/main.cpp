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
#include <QStringList>
#include <QDir>

#include <iostream>

#include "qglobal.h"
#include "ks04_11/myclass.h"


using std::cout;
using std::endl;

void example01(void);
void example02(void);

/////////////////////////////////////////////////////////////////////
int main(int argc, char * argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);

    if (0) {
        example01();
    }

    if (1) {
        example02();
    }
	return 0;
}


/**
* @brief example01, 调用dll中的接口

* @return void
*/
void example01(void) {
    QString strPath = "d:\\temp_D";
    QStringList strFilters;
    strFilters << "*.gdf" << "*.xml";

    QStringList strList = ns_train::getFileList(strPath, strFilters, true);

}

/**
* @brief 示例1, 简单介绍QDir的使用

* @return void
*/
void example02(void) {

    QString strPath = "$TRAINDEVHOME/src/";
    strPath = ns_train::getPath(strPath);
	strPath = ns_train::getDirectory(strPath);
    QDir dir(strPath);
    QString absPath = dir.absolutePath();	// 返回路径的绝对路径字符串
    QString cancPath = dir.canonicalPath(); // 返回路径的规范路径名字符串

	strPath = "../../../../test/chapter04/ks04_11/a.txt";
    strPath = ns_train::getPath(strPath);
	dir.setPath(strPath);
	//dir.mkdir(strPath);		// 当上层路径不存在时，mkdir()失败
	absPath = dir.absolutePath();
	strPath = ns_train::getDirectory(absPath);
	dir.mkpath(strPath);	// 当上层路径不存在时，mkpath()自动创建所有的父目录层次。
	cancPath = dir.canonicalPath(); // 当a.txt不存在时，canonicalPath()返回空。

}
