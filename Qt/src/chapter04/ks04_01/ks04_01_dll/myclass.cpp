/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: dll.cpp

\brief	


\author 女儿叫老白  星点分享: http://xingdianketang.cn/

\Date 2018/9 

*/
#include "myclass.h"
#include <iostream>

using std::cout;
using std::endl;

///////////////////////////////////////////////////////////////////
void CPrint::printOnScreen(const char* szStr)
{
	if (NULL == szStr)
		return;
	cout << szStr << endl;
}

///////////////////////////////////////////////////////////////////
int func1()
{
	return 0;
}

int  func2(int i, float f)
{
	float val = i + f;
	int iVal = static_cast<int>(val);
	return iVal;
}