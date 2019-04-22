/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: serialize.h
\brief 序列化错误码定义文件。

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/10
* please import basedll.dll
*/

#ifndef _SERIALIZE_H_
#define _SERIALIZE_H_


/**
* @brief 序列化错误码的枚举
*
* ESerializeCode 枚举。
* 用来说明序列化时出现错误的原因
*
*/
enum ESerializeCode
{
	ESERIALIZECODE_OK = 0,					/// 正常
	ESERIALIZECODE_FILENOTFOND,				/// 文件不存在
	ESERIALIZECODE_DOC_ELEMENT_NOTFOUND,	/// doc元素不存在: 文件中必须存在<doc>元素
	ESERIALIZECODE_CONTENT_ELEMENT_NOTFOUND,/// content元素不存在: 文件中必须存在<content>元素
	ESERIALIZECODE_SETCONTENT_ERROR,		/// QDomDocument::setContent()调用失败
	ESERIALIZECODE_VERSION_NOTRECOGNIZE,	/// 不可识别的版本号
	ESERIALIZECODE_OTHERERROR,					/// 其他错误

};


#endif  // _SERIALIZE_H_
