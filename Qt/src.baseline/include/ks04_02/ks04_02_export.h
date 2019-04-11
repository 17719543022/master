/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: myclass.h
\brief exe+dll编程示例，引出类所在的头文件
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9 
*/

#ifndef _KS04_02_EXPORT_H
#define _KS04_02_EXPORT_H


// 动态库导出宏定义
#ifdef WIN32		// windows platform
#	if defined __KS04_02_DLL_SOURCE__
#		define KS04_02_Export __declspec(dllexport)
#	else
#		define KS04_02_Export __declspec(dllimport)
#	endif

#else				// other platform
#  define KS04_02_Export
#endif // WIN32


#endif  // _KS04_02_EXPORT_H