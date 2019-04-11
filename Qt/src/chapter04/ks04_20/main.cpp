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

#include <QCoreApplication>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QDir>
#include <QFile>
#include "qglobal.h"
#include <QString>
//#include <QTextStream>


#include "myclass.h"

void example01();
void example02();
void parseDoc(QXmlStreamReader &reader);
void parseCourse(QXmlStreamReader &reader);
void parseLesson(QXmlStreamReader &reader);


int main(int argc, char * argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);

	QCoreApplication app(argc, argv);
   

	if (1) {
		example01();
	}

	if (1) {
		example02();
	}
	
	system("pause");

	return 0;
}

/**
* @brief 保存xml格式文件示例代码
*        xml文件内容
*        <doc>
*           <courses institution="星点课堂"  teacher="女儿叫老白" serie="C++跨平台开发干货系列" count="7">
*               <lesson id="1" url="" fee="免费" >C++老鸟日记<lesson/>
*               <lesson id="2" url="" fee="免费" >C++跨平台开发中的编译错误<lesson/>
*               <lesson id="3" url="" >Qt入门与提高-GUI产品开发<lesson/>
*               <lesson id="4" url=""  >C++跨平台服务模块开发<lesson/>
*           </courses>
*        </doc>
*/
void example01() {
	QString strPath = ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_20/");
	if (!strPath.endsWith("/")) {
		strPath += "/";
	}
	QDir dir(strPath);
	dir.mkpath(strPath);
	QString strFileName = strPath + "test04_20.xml"; // 程序运行目录下的xml文件
	QFile file(strFileName);
	if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate))	{ // QFile::Truncate,需要清空原来的内容
		return ;
	}

	QXmlStreamWriter writer(&file);
	writer.setCodec("GB2312");  // XML 编码
	writer.setAutoFormatting(true); // 自动格式化
	writer.writeStartDocument("1.0", true);  // 开始文档（XML 声明）
	writer.writeComment(QString::fromLocal8Bit("星点课堂"));  // 注释
//	writer.writeProcessingInstruction("version=\"1.0\" encoding=\"GB2312\"");  // 处理指令
																								   // DTD
//	writer.writeDTD(QString::fromLocal8Bit("<!DOCTYPE Blogs [ <!ENTITY Copyright \"Copyright 2016《Qt实战一二三》\"> <!ELEMENT Blogs (Blog)> <!ELEMENT Blog (作者,主页,个人说明)> <!ELEMENT 作者     (#PCDATA)> <!ELEMENT 主页     (#PCDATA)> <!ELEMENT 个人说明  (#PCDATA)> ]>"));

	writer.writeStartElement("doc");  // 开始根元素 <doc>

	writer.writeStartElement("courses");  // 开始子元素 <courses>
	writer.writeAttribute("count", "4");
	writer.writeAttribute("institution", QString::fromLocal8Bit("星点课堂"));
	writer.writeAttribute("teacher", QString::fromLocal8Bit("女儿叫老白"));

	// lesson
	writer.writeStartElement("lesson");  // 开始子元素 <lesson>
	writer.writeAttribute("url", "https://study.163.com/instructor/1143174933.htm");
	writer.writeAttribute("id", "1");
	writer.writeAttribute("fee", QString::fromLocal8Bit("免费"));
	writer.writeCharacters(QString::fromLocal8Bit("C++老鸟日记"));
	writer.writeEndElement();  // 结束子元素 </lesson>
	// lesson
	writer.writeStartElement("lesson");  // 开始子元素 <lesson>
	writer.writeAttribute("url", "https://study.163.com/instructor/1143174933.htm");
	writer.writeAttribute("id", "2");
	writer.writeAttribute("fee", QString::fromLocal8Bit("免费"));
	writer.writeCharacters(QString::fromLocal8Bit("C++跨平台开发中的编译错误"));
	writer.writeEndElement();  // 结束子元素 </lesson>
	// lesson
	writer.writeStartElement("lesson");  // 开始子元素 <lesson>
	writer.writeAttribute("url", "https://study.163.com/instructor/1143174933.htm");
	writer.writeAttribute("id", "3");
	writer.writeCharacters(QString::fromLocal8Bit("Qt入门与提高-GUI产品开发"));
	writer.writeEndElement();  // 结束子元素 </lesson>
	// lesson
	writer.writeStartElement("lesson");  // 开始子元素 <lesson>
	writer.writeAttribute("url", "sorry, not ready");
	writer.writeAttribute("id", "4");
	writer.writeCharacters(QString::fromLocal8Bit("C++跨平台服务模块开发"));
	writer.writeEndElement();  // 结束子元素 </lesson>

	writer.writeEndElement();  // 结束子元素 </courses>

	writer.writeEndElement();  // 结束根元素 </doc>
	writer.writeEndDocument();  // 结束文档
	file.close();
}

/**
* @brief 读取xml格式文件示例代码
*/
void example02() {

	QString strPath = ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_20/");
	if (!strPath.endsWith("/")) {
		strPath += "/";
	}

	QString strFileName = strPath + "test04_20.xml"; // 程序运行目录下的xml文件
	QFile file(strFileName);
	if (!file.open(QFile::ReadOnly | QFile::Text))	{
		return;
	}

	QXmlStreamReader reader(&file);
	QString strVersion;
	QString strEncoding;
	while (!reader.atEnd()) {
		// 读取下一个元素
		QXmlStreamReader::TokenType nType = reader.tokenType();
		switch (nType) {
		case QXmlStreamReader::StartDocument: {  // 文档开始
			qDebug() << QString::fromLocal8Bit("============= 开始文档（XML 声明） ============= ");
			// XML 声明
			strVersion = reader.documentVersion().toString();
			strEncoding = reader.documentEncoding().toString();
			bool bAlone = reader.isStandaloneDocument();
			qDebug() << QString::fromLocal8Bit("XML版本：%1  XML编码：%2  Standalone：%3")
				.arg(strVersion).arg(strEncoding).arg(bAlone) << "\r\n";
			break;
		}
		case QXmlStreamReader::Comment: {  // 注释
			qDebug() << QString::fromLocal8Bit("============= XML注释 ============= ");
			QString strComment = reader.text().toString();
			qDebug() << strComment << "\r\n";
			break;
		}
		case QXmlStreamReader::ProcessingInstruction: {  // 处理指令
			qDebug() << QString::fromLocal8Bit("============= 处理指令 ============= ");
			QString strProcInstr = reader.processingInstructionData().toString();
			qDebug() << strProcInstr << "\r\n";
			break;
		}
		case QXmlStreamReader::DTD: {   // DTD
			qDebug() << QString::fromLocal8Bit("============= DTD ============= ");
			QString strDTD = reader.text().toString();
			QXmlStreamNotationDeclarations notationDeclarations = reader.notationDeclarations();  // 符号声明
			QXmlStreamEntityDeclarations entityDeclarations = reader.entityDeclarations();  // 实体声明
																							// DTD 声明
			QString strDTDName = reader.dtdName().toString();
			QString strDTDPublicId = reader.dtdPublicId().toString();  // DTD 公开标识符
			QString strDTDSystemId = reader.dtdSystemId().toString();  // DTD 系统标识符
			qDebug() << QString::fromLocal8Bit("DTD : %1").arg(strDTD);
			qDebug() << QString::fromLocal8Bit("DTD 名称 : %1").arg(strDTDName);
			qDebug() << QString::fromLocal8Bit("DTD 公开标识符 : %1").arg(strDTDPublicId);
			qDebug() << QString::fromLocal8Bit("DTD 系统标识符 : %1").arg(strDTDSystemId);
			qDebug() << "\r\n";

			break;
		}
		case QXmlStreamReader::StartElement: {  // 开始元素
			QString strElementName = reader.name().toString();
			if (QString::compare(strElementName, "doc") == 0) {  // 根元素
				qDebug() << QString::fromLocal8Bit("============= 开始元素<doc> ============= ");
				parseDoc(reader);
			}
			break;
		}
		case QXmlStreamReader::EndElement: {  // 结束元素
			QString strElementName = reader.name().toString();
			if (QString::compare(strElementName, "doc") == 0) {  // 根元素
				qDebug() << QString::fromLocal8Bit("============= 结束元素<doc> ============= ");
			}
			break;
		}
		case QXmlStreamReader::EndDocument: {  // 文档结束
			qDebug() << QString::fromLocal8Bit("============= 文档结束 ============= ");
		}
			break;
		default:
			break;
		}
		reader.readNext();
	}
	if (reader.hasError()) {
		// 做错误处理
	}

	file.close();
}
void parseDoc(QXmlStreamReader &reader) {
	while (!reader.atEnd()) {
		QXmlStreamReader::TokenType nType = reader.readNext();
		switch (nType) {
		case QXmlStreamReader::StartElement: {  // 开始元素
			QString strElementName = reader.name().toString();
			if (QString::compare(strElementName, "courses") == 0) {
				qDebug() << QString::fromLocal8Bit("============= 开始元素<courses> ============= ");
				parseCourse(reader);
			}
		}
			break;
		case QXmlStreamReader::Characters: {  // 字符元素
			QString strName = reader.name().toString();
			QString strText = reader.text().toString();
			qDebug() << QString("Characters: %1(%2)").arg(strName).arg(strText);
 		}
			break;
		case QXmlStreamReader::EndElement: {  // 结束元素
			QString strElementName = reader.name().toString();
			if (QString::compare(strElementName, "doc") == 0) {
				qDebug() << QString::fromLocal8Bit("============= 结束元素<doc> ============= ");
			}
			return;
		}
		default:
			break;
		}
	}
}

void parseCourse(QXmlStreamReader &reader) {
	while (!reader.atEnd()) {
		QXmlStreamReader::TokenType nType = reader.readNext();
		switch (nType) {
		case QXmlStreamReader::StartElement: {  // 开始元素
			QString strElementName = reader.name().toString();
			if (QString::compare(strElementName, "lesson") == 0) {
				qDebug() << QString::fromLocal8Bit("============= 开始元素<lesson> ============= ");
				parseLesson(reader);
			}
		}
			break;
		case QXmlStreamReader::EndElement: {  // 结束元素
			QString strElementName = reader.name().toString();
			if (QString::compare(strElementName, "courses") == 0) {
				qDebug() << QString::fromLocal8Bit("============= 结束元素<courses> ============= ");
			}
		}
			return;
		default:
			break;
		}
	}
}

void parseLesson(QXmlStreamReader &reader) {
	while (!reader.atEnd()) {
		QXmlStreamReader::TokenType nType = reader.tokenType();
		switch (nType) {
		case QXmlStreamReader::StartElement: {  // 开始元素
			QString strElementName = reader.name().toString();
			QXmlStreamAttributes attributes = reader.attributes();
			QXmlStreamAttributes::iterator ite = attributes.begin();
			for (ite = attributes.begin(); ite != attributes.end(); ite++) {
				qDebug()<< (*ite).name() <<"=" << (*ite).value();
			}
		}
			break;
		case QXmlStreamReader::Characters: {  // 字符元素
			QString strName = reader.name().toString();
			QString strText = reader.text().toString();
			qDebug() << QString("Characters: %1(%2)").arg(strName).arg(strText);
		}
			break;
		case QXmlStreamReader::EndElement: {  // 结束元素
			QString strName = reader.name().toString();
			QString strText = reader.text().toString();
			qDebug() << QString("EndElement: %1(%2)").arg(strName).arg(strText);
		}
			return;
			break;
		default:
			break;
		}
		reader.readNext();
	}
}