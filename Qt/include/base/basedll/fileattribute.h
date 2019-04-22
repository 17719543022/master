/*! \file: fileattribute.h
	\brief 文件属性的访问类定义
	\author 星点课堂 女儿叫老白
	\Date : 2018/1/10
* please import basedll.dll
*/
#ifndef _FILEATTR_H
#define _FILEATTR_H


#include <QString>
#include "qglobal.h"

#include "base_export.h"
#include "base/basedll/serialize.h"


class QDomElement;

namespace ns_train {
	

const quint16 c_MD5_Length = 16;			/// md5码的长度，单位：字节。
/// 文件的属性
struct BASE_API SFileAttr
{
	quint16	mainVer;						/// 主版本号
	quint16	subVer;							/// 次版本号
	quint8	md5[c_MD5_Length];				/// 本文件的md5码, 二进制格式使用，文本格式不用该属性。

	SFileAttr(){ mainVer = 1; subVer = 0; memset(md5, 0, c_MD5_Length); }
};
/// 序列化文件的自定义属性(二进制)
BASE_API QDataStream& operator<<(QDataStream& stream, const SFileAttr& attrs);
/// 反序列化文件的自定义属性(二进制)
BASE_API QDataStream& operator>>(QDataStream& stream, SFileAttr& attrs);
/// 序列化文件的基本数据(XML)
BASE_API QDomElement& operator<<(QDomElement& ele, const SFileAttr& attrs);
/// 反序列化文件的基本数据(XML)
BASE_API QDomElement& operator>>(QDomElement& ele, SFileAttr& attrs);

//！读取文件的属性-二进制方式
/**
* @param[in] fileName	文件全路径名
* @param[out] attrs		属性
* @retval ESerializeCode
*/
BASE_API ESerializeCode readInfoFromBinary(const QString& fileName, SFileAttr& attrs);

//！读取文件的属性-xml方式
/**
* @param[in] fileName	文件全路径名
* @param[out] attrs		属性
* @retval ESerializeCode
*/
BASE_API ESerializeCode readInfoFromXML(const QString& fileName, SFileAttr& attrs);


} // namespace iesgp

#endif //_FILEATTR_H
