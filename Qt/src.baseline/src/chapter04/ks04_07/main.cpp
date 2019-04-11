/*! * Copyright (C) 2018 女儿叫老白
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

#include <iostream>


void example01();
void example02();
void example03();

using std::cin;
int main(int argc, char * argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);


	// example01 
	if (false) {
		example01();
	}

	// example02 
	if (false) {
		example02();
	}
	
	// example03 
	if (false) {
		example03();
	}

	char ch = '\0';
	cin >> ch;

	return 0;
}

/**
* @brief  qDebug()<< 方式输出信息
*		  可以直接用<<操作符将需要输出的信息输出到qDebug()。
* @return 无
*/
void example01(){
	
	

}

/**
* @brief  使用qDebug("%")格式化输出信息
* @return 无
*/
void example02(){
	
	
}


/**
* @brief  将自定义类输出到qDebug
* @param[in] mc 自定义类
* @return 
*/
void example03(){
	
}
