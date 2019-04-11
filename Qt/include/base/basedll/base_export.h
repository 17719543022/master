/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: baseapi.h
\brief 通用dll，引出类所在的头文件
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/10
* please import basedll.dll
*/

#ifndef _BASE_EXPORT_H
#define _BASE_EXPORT_H


// 动态库导出宏定义
#ifdef WIN32		// windows platform
#	if defined __BASEDLL_SOURCE__
#		define BASE_API __declspec(dllexport)
#	else
#		define BASE_API __declspec(dllimport)
#	endif

#else				// other platform
#  define BASE_API
#endif // WIN32


#endif  // _BASE_EXPORT_H