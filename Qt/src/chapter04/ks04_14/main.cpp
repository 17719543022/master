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

#include "qglobal.h"

#include "iniconfig.h"
#include "ks04_11/myclass.h"


void example01();
void example02();

int main(int argc, char * argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);


    if (true) {
        example01();
    }

    if (true) {
        example02();
    }
	return 0;
}


void example01() {
    ns_train::CIniConfig cfg;
	QString strFileName = ns_train::getPath("$TRAINDEVHOME/ini/ks04_14.ini");
    cfg.setFileName(strFileName);

    cfg.setAllKeys("config", "x=xx\ny=yy\nz=zz");
    
    cfg.setBoolean("datatype", "bool-1", true);
    cfg.setBoolean("datatype", "bool-2", false);

    cfg.setInteger("datatype", "int-1", 0);
    cfg.setInteger("datatype", "int-2", -1);
    cfg.setInteger("datatype", "int-3", 65535);

    cfg.setDouble("datatype", "real-1", 0.03);
    cfg.setDouble("datatype", "real-2", 10000.982);

    cfg.setString("datatype", "string", QString::fromLocal8Bit("星点课堂"));
}

void example02() {
    ns_train::CIniConfig cfg;
	QString strFileName = ns_train::getPath("$TRAINDEVHOME/ini/ks04_14.ini");
    cfg.setFileName(strFileName);

   
    bool bok = false;
    bok = cfg.getBoolean("datatype", "bool-1", true);
    bok = cfg.setBoolean("datatype", "bool-2", false);

    int iValue = 0;
    iValue = cfg.getInteger("datatype", "int-1", 0);
    iValue = cfg.getInteger("datatype", "int-2", 0);
    iValue = cfg.getInteger("datatype", "int-3", 0);

    double dValue = 0;
    dValue = cfg.getDouble("datatype", "real-1", 0.f);
    dValue = cfg.getDouble("datatype", "real-2", 0.f);

    QString str;
    str = cfg.getString("datatype", "string", "星点课堂");
}

