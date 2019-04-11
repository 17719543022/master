/*! \file: fileattribute.cpp
\brief 文件属性的访问类定义
\author 星点课堂 女儿叫老白
\Date : 2018/10
*/

#include <QDataStream>
#include <QDomElement>
#include <QFile>

#include "fileattribute.h"
#include "filehead.h"
#include "base/basedll/serialize.h"

namespace ns_train {


QDataStream& operator<<(QDataStream& stream, const SFileAttr& attrs)
{
	stream << attrs.mainVer;
	stream << attrs.subVer;
	QByteArray byData;
	byData.setRawData((const char *)(attrs.md5), c_MD5_Length);
	stream.device()->write(byData.data(), c_MD5_Length);	
	
	return stream;
}

QDataStream& operator>>(QDataStream& stream, SFileAttr& attrs)
{
	stream >> attrs.mainVer;
	stream >> attrs.subVer;
	SFileHead header(attrs.mainVer, attrs.subVer);
	stream.device()->read((char*)attrs.md5, c_MD5_Length);		
	
	return stream;
}
// todo
ESerializeCode readInfoFromBinary(const QString& fileName, SFileAttr& attrs)
{
	ESerializeCode code = ESERIALIZECODE_OK;
	QFile file(fileName);
	if (file.open(QFile::ReadOnly))
	{
		QDataStream stream(&file);
		stream.setByteOrder(QDataStream::LittleEndian);
		stream >> attrs;
		SFileHead header(attrs.mainVer, 0);
		if (header.isLaterMainVersion(getMainVersion()))
		{
			code = ESERIALIZECODE_VERSION_NOTRECOGNIZE;
		}
		file.close();
	}
	else
	{
		code = ESERIALIZECODE_FILENOTFOND;
	}
	return code;
}

QDomElement& operator<<(QDomElement& ele, const SFileAttr& attrs)
{
	SFileHead head(attrs.mainVer, attrs.subVer);
	ele.setAttribute("ver", head.toQString());	

	return ele;
}

QDomElement& operator>>(QDomElement& ele, SFileAttr& attrs)
{
	SFileHead head = SFileHead::fromQString(ele.attribute("ver"));
	attrs.mainVer = head.getMainVersion();
	attrs.subVer = head.getSubVersion();
	
	return ele;
}
// todo
ESerializeCode readInfoFromXML(const QString& fileName, SFileAttr& attrs)
{
	ESerializeCode code = ESERIALIZECODE_OK;
	QFile file(fileName);
	if (file.open(QFile::ReadOnly))
	{
		QDomDocument doc;
		if (doc.setContent(&file, false))
		{
			QDomElement rootDoc = doc.firstChildElement();
			if (rootDoc.nodeName() == "doc")
			{
				rootDoc >> attrs;
				SFileHead header(attrs.mainVer, 0);
				if (header.isLaterMainVersion(getMainVersion()))
				{
					code = ESERIALIZECODE_VERSION_NOTRECOGNIZE;
				}
			}
			else
			{
				code = ESERIALIZECODE_DOC_ELEMENT_NOTFOUND;
			}
		}
		else
		{
			code = ESERIALIZECODE_SETCONTENT_ERROR;
		}
		file.close();
	}
	else
	{
		code = ESERIALIZECODE_FILENOTFOND;
	}
	return code;
}


} // namespace ns_train
