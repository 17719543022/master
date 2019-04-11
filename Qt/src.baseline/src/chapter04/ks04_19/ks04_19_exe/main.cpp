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

#include "qglobal.h"
#include <iostream>

#include "config.h"

#include "myclass.h"


using std::cout;
using std::endl;

int main(int argc, char * argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);

    CModel model;
    model.initialize();

    qreal r = 0.f;// todo，调用CConfig的getSelectRadius()接口来获取配置参数。
    cout << "r = " << r << endl;
	return 0;
}
