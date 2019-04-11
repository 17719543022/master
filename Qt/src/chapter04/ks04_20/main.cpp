/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���

\file: main.cpp
\brief mian()������ʵ���ļ�

\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
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
* @brief ����xml��ʽ�ļ�ʾ������
*        xml�ļ�����
*        <doc>
*           <courses institution="�ǵ����"  teacher="Ů�����ϰ�" serie="C++��ƽ̨�����ɻ�ϵ��" count="7">
*               <lesson id="1" url="" fee="���" >C++�����ռ�<lesson/>
*               <lesson id="2" url="" fee="���" >C++��ƽ̨�����еı������<lesson/>
*               <lesson id="3" url="" >Qt���������-GUI��Ʒ����<lesson/>
*               <lesson id="4" url=""  >C++��ƽ̨����ģ�鿪��<lesson/>
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
	QString strFileName = strPath + "test04_20.xml"; // ��������Ŀ¼�µ�xml�ļ�
	QFile file(strFileName);
	if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate))	{ // QFile::Truncate,��Ҫ���ԭ��������
		return ;
	}

	QXmlStreamWriter writer(&file);
	writer.setCodec("GB2312");  // XML ����
	writer.setAutoFormatting(true); // �Զ���ʽ��
	writer.writeStartDocument("1.0", true);  // ��ʼ�ĵ���XML ������
	writer.writeComment(QString::fromLocal8Bit("�ǵ����"));  // ע��
//	writer.writeProcessingInstruction("version=\"1.0\" encoding=\"GB2312\"");  // ����ָ��
																								   // DTD
//	writer.writeDTD(QString::fromLocal8Bit("<!DOCTYPE Blogs [ <!ENTITY Copyright \"Copyright 2016��Qtʵսһ������\"> <!ELEMENT Blogs (Blog)> <!ELEMENT Blog (����,��ҳ,����˵��)> <!ELEMENT ����     (#PCDATA)> <!ELEMENT ��ҳ     (#PCDATA)> <!ELEMENT ����˵��  (#PCDATA)> ]>"));

	writer.writeStartElement("doc");  // ��ʼ��Ԫ�� <doc>

	writer.writeStartElement("courses");  // ��ʼ��Ԫ�� <courses>
	writer.writeAttribute("count", "4");
	writer.writeAttribute("institution", QString::fromLocal8Bit("�ǵ����"));
	writer.writeAttribute("teacher", QString::fromLocal8Bit("Ů�����ϰ�"));

	// lesson
	writer.writeStartElement("lesson");  // ��ʼ��Ԫ�� <lesson>
	writer.writeAttribute("url", "https://study.163.com/instructor/1143174933.htm");
	writer.writeAttribute("id", "1");
	writer.writeAttribute("fee", QString::fromLocal8Bit("���"));
	writer.writeCharacters(QString::fromLocal8Bit("C++�����ռ�"));
	writer.writeEndElement();  // ������Ԫ�� </lesson>
	// lesson
	writer.writeStartElement("lesson");  // ��ʼ��Ԫ�� <lesson>
	writer.writeAttribute("url", "https://study.163.com/instructor/1143174933.htm");
	writer.writeAttribute("id", "2");
	writer.writeAttribute("fee", QString::fromLocal8Bit("���"));
	writer.writeCharacters(QString::fromLocal8Bit("C++��ƽ̨�����еı������"));
	writer.writeEndElement();  // ������Ԫ�� </lesson>
	// lesson
	writer.writeStartElement("lesson");  // ��ʼ��Ԫ�� <lesson>
	writer.writeAttribute("url", "https://study.163.com/instructor/1143174933.htm");
	writer.writeAttribute("id", "3");
	writer.writeCharacters(QString::fromLocal8Bit("Qt���������-GUI��Ʒ����"));
	writer.writeEndElement();  // ������Ԫ�� </lesson>
	// lesson
	writer.writeStartElement("lesson");  // ��ʼ��Ԫ�� <lesson>
	writer.writeAttribute("url", "sorry, not ready");
	writer.writeAttribute("id", "4");
	writer.writeCharacters(QString::fromLocal8Bit("C++��ƽ̨����ģ�鿪��"));
	writer.writeEndElement();  // ������Ԫ�� </lesson>

	writer.writeEndElement();  // ������Ԫ�� </courses>

	writer.writeEndElement();  // ������Ԫ�� </doc>
	writer.writeEndDocument();  // �����ĵ�
	file.close();
}

/**
* @brief ��ȡxml��ʽ�ļ�ʾ������
*/
void example02() {

	QString strPath = ns_train::getPath("$TRAINDEVHOME/test/chapter04/ks04_20/");
	if (!strPath.endsWith("/")) {
		strPath += "/";
	}

	QString strFileName = strPath + "test04_20.xml"; // ��������Ŀ¼�µ�xml�ļ�
	QFile file(strFileName);
	if (!file.open(QFile::ReadOnly | QFile::Text))	{
		return;
	}

	QXmlStreamReader reader(&file);
	QString strVersion;
	QString strEncoding;
	while (!reader.atEnd()) {
		// ��ȡ��һ��Ԫ��
		QXmlStreamReader::TokenType nType = reader.tokenType();
		switch (nType) {
		case QXmlStreamReader::StartDocument: {  // �ĵ���ʼ
			qDebug() << QString::fromLocal8Bit("============= ��ʼ�ĵ���XML ������ ============= ");
			// XML ����
			strVersion = reader.documentVersion().toString();
			strEncoding = reader.documentEncoding().toString();
			bool bAlone = reader.isStandaloneDocument();
			qDebug() << QString::fromLocal8Bit("XML�汾��%1  XML���룺%2  Standalone��%3")
				.arg(strVersion).arg(strEncoding).arg(bAlone) << "\r\n";
			break;
		}
		case QXmlStreamReader::Comment: {  // ע��
			qDebug() << QString::fromLocal8Bit("============= XMLע�� ============= ");
			QString strComment = reader.text().toString();
			qDebug() << strComment << "\r\n";
			break;
		}
		case QXmlStreamReader::ProcessingInstruction: {  // ����ָ��
			qDebug() << QString::fromLocal8Bit("============= ����ָ�� ============= ");
			QString strProcInstr = reader.processingInstructionData().toString();
			qDebug() << strProcInstr << "\r\n";
			break;
		}
		case QXmlStreamReader::DTD: {   // DTD
			qDebug() << QString::fromLocal8Bit("============= DTD ============= ");
			QString strDTD = reader.text().toString();
			QXmlStreamNotationDeclarations notationDeclarations = reader.notationDeclarations();  // ��������
			QXmlStreamEntityDeclarations entityDeclarations = reader.entityDeclarations();  // ʵ������
																							// DTD ����
			QString strDTDName = reader.dtdName().toString();
			QString strDTDPublicId = reader.dtdPublicId().toString();  // DTD ������ʶ��
			QString strDTDSystemId = reader.dtdSystemId().toString();  // DTD ϵͳ��ʶ��
			qDebug() << QString::fromLocal8Bit("DTD : %1").arg(strDTD);
			qDebug() << QString::fromLocal8Bit("DTD ���� : %1").arg(strDTDName);
			qDebug() << QString::fromLocal8Bit("DTD ������ʶ�� : %1").arg(strDTDPublicId);
			qDebug() << QString::fromLocal8Bit("DTD ϵͳ��ʶ�� : %1").arg(strDTDSystemId);
			qDebug() << "\r\n";

			break;
		}
		case QXmlStreamReader::StartElement: {  // ��ʼԪ��
			QString strElementName = reader.name().toString();
			if (QString::compare(strElementName, "doc") == 0) {  // ��Ԫ��
				qDebug() << QString::fromLocal8Bit("============= ��ʼԪ��<doc> ============= ");
				parseDoc(reader);
			}
			break;
		}
		case QXmlStreamReader::EndElement: {  // ����Ԫ��
			QString strElementName = reader.name().toString();
			if (QString::compare(strElementName, "doc") == 0) {  // ��Ԫ��
				qDebug() << QString::fromLocal8Bit("============= ����Ԫ��<doc> ============= ");
			}
			break;
		}
		case QXmlStreamReader::EndDocument: {  // �ĵ�����
			qDebug() << QString::fromLocal8Bit("============= �ĵ����� ============= ");
		}
			break;
		default:
			break;
		}
		reader.readNext();
	}
	if (reader.hasError()) {
		// ��������
	}

	file.close();
}
void parseDoc(QXmlStreamReader &reader) {
	while (!reader.atEnd()) {
		QXmlStreamReader::TokenType nType = reader.readNext();
		switch (nType) {
		case QXmlStreamReader::StartElement: {  // ��ʼԪ��
			QString strElementName = reader.name().toString();
			if (QString::compare(strElementName, "courses") == 0) {
				qDebug() << QString::fromLocal8Bit("============= ��ʼԪ��<courses> ============= ");
				parseCourse(reader);
			}
		}
			break;
		case QXmlStreamReader::Characters: {  // �ַ�Ԫ��
			QString strName = reader.name().toString();
			QString strText = reader.text().toString();
			qDebug() << QString("Characters: %1(%2)").arg(strName).arg(strText);
 		}
			break;
		case QXmlStreamReader::EndElement: {  // ����Ԫ��
			QString strElementName = reader.name().toString();
			if (QString::compare(strElementName, "doc") == 0) {
				qDebug() << QString::fromLocal8Bit("============= ����Ԫ��<doc> ============= ");
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
		case QXmlStreamReader::StartElement: {  // ��ʼԪ��
			QString strElementName = reader.name().toString();
			if (QString::compare(strElementName, "lesson") == 0) {
				qDebug() << QString::fromLocal8Bit("============= ��ʼԪ��<lesson> ============= ");
				parseLesson(reader);
			}
		}
			break;
		case QXmlStreamReader::EndElement: {  // ����Ԫ��
			QString strElementName = reader.name().toString();
			if (QString::compare(strElementName, "courses") == 0) {
				qDebug() << QString::fromLocal8Bit("============= ����Ԫ��<courses> ============= ");
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
		case QXmlStreamReader::StartElement: {  // ��ʼԪ��
			QString strElementName = reader.name().toString();
			QXmlStreamAttributes attributes = reader.attributes();
			QXmlStreamAttributes::iterator ite = attributes.begin();
			for (ite = attributes.begin(); ite != attributes.end(); ite++) {
				qDebug()<< (*ite).name() <<"=" << (*ite).value();
			}
		}
			break;
		case QXmlStreamReader::Characters: {  // �ַ�Ԫ��
			QString strName = reader.name().toString();
			QString strText = reader.text().toString();
			qDebug() << QString("Characters: %1(%2)").arg(strName).arg(strText);
		}
			break;
		case QXmlStreamReader::EndElement: {  // ����Ԫ��
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