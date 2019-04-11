/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: myclass.h
\brief exe+dll编程示例，引出类CPrint的定义头文件
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9 
* please import ks04_01_dll.dll
*/

#ifndef _MYCLASS_DLL_H
#define _MYCLASS_DLL_H

#include "ks04_01_export.h"
/// 打印类CPrint定义
class KS04_01_Export CPrint {
public:
	CPrint(){}
	~CPrint(){}
public:
	/**
	* @brief 将指定信息打印到屏幕

	* @param[in] szInfo  待打印的信息
	* @return void
	*/
	void printOnScreen(const char*);
};

KS04_01_Export int func1();
KS04_01_Export int func2(int, float);

#endif  // _MYCLASS_DLL_H