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
#include <QDomDocument>
#include <QFile>
#include "qglobal.h"
#include <QString>
#include <QTextStream>
#include "myclass.h"

void example01();
void example02();


int main(int argc, char * argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);

	QCoreApplication app(argc, argv);
   

	if (false) {
		example01();
	}

	if (true) {
		example02();
	}
	
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
	QString strPath = QCoreApplication::applicationDirPath();
	strPath = ns_train::getPath(strPath);
	if (!strPath.endsWith("/")) {
		strPath += "/";
	}

	QString strFileName = strPath + "test04_13.xml"; // 程序运行目录下的xml文件
	QFile file(strFileName);
	if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate))	{ // QFile::Truncate,需要清空原来的内容
		return ;
	}

	QTextStream out(&file);
	out.setCodec("GB2312");

	QDomDocument document;
    QDomProcessingInstruction instruction;  //添加处理指令
    instruction = document.createProcessingInstruction("xml",
        "version=\"1.0\" encoding=\"GB2312\""); // 请注意此处的编码必须和您的源代码文件的编码保持一致。

    document.appendChild(instruction);
	// doc
	QDomElement rootDoc = document.createElement("doc");
	document.appendChild(rootDoc);
	
	// 添加扰乱项目，用来测试example02()。
	QDomElement eleConfig = document.createElement("config");
	eleConfig.setAttribute("id", 5);
	rootDoc.appendChild(eleConfig);

	QString strName;
	QString strValue;
	// courses
	QDomElement eleCourses = document.createElement("courses");
	rootDoc.appendChild(eleCourses);

	strName = "institution";
	strValue = QString::fromLocal8Bit("星点课堂");
    eleCourses.setAttribute(strName, strValue);

	strName = "teacher";
	strValue = QString::fromLocal8Bit("女儿叫老白");
    eleCourses.setAttribute(strName, strValue);

	strName = "count";
	strValue = QString("%1").arg(4);
    eleCourses.setAttribute(strName, strValue);

	// lesson
	QDomElement eleLesson = document.createElement("lesson"); 

	strName = "id";
	strValue = QString("%1").arg(1);
    eleLesson.setAttribute(strName, strValue);

	strName = "url";
	strValue = "https://study.163.com/instructor/1143174933.htm";
    eleLesson.setAttribute(strName, strValue);

    strName = "fee";
    strValue = QString::fromLocal8Bit("免费");
    eleLesson.setAttribute(strName, strValue);

    QDomText dtText = document.createTextNode(QString::fromLocal8Bit("C++老鸟日记"));
    eleLesson.appendChild(dtText);
    eleCourses.appendChild(eleLesson);

    // lesson
    eleLesson = document.createElement("lesson"); 
    
    strName = "id";
    strValue = QString("%1").arg(2);
    eleLesson.setAttribute(strName, strValue);

    strName = "url";
    strValue = "https://study.163.com/instructor/1143174933.htm";
    eleLesson.setAttribute(strName, strValue);

    strName = "fee";
    strValue = QString::fromLocal8Bit("免费");
    eleLesson.setAttribute(strName, strValue);

    dtText = document.createTextNode(QString::fromLocal8Bit("C++跨平台开发中的编译错误"));
    eleLesson.appendChild(dtText);
    eleCourses.appendChild(eleLesson);  

    // lesson
    eleLesson = document.createElement("lesson");
    
    strName = "id";
    strValue = QString("%1").arg(3);
    eleLesson.setAttribute(strName, strValue);

    strName = "url";
    strValue = "https://study.163.com/instructor/1143174933.htm";
    eleLesson.setAttribute(strName, strValue);


    dtText = document.createTextNode(QString::fromLocal8Bit("Qt入门与提高-GUI产品开发"));
    eleLesson.appendChild(dtText);
    eleCourses.appendChild(eleLesson);


    // lesson
    eleLesson = document.createElement("lesson");

    strName = "id";
    strValue = QString("%1").arg(4);
    eleLesson.setAttribute(strName, strValue);

    strName = "url";
    strValue = "sorry, not ready";
    eleLesson.setAttribute(strName, strValue);
	 
    dtText = document.createTextNode(QString::fromLocal8Bit("C++跨平台服务模块开发"));
    eleLesson.appendChild(dtText);
    eleCourses.appendChild(eleLesson);
    
    document.save(out, 4, QDomNode::EncodingFromTextStream);    // 4:缩进值
	
	// 将信息输出到终端
	qDebug() << "XML to write";		
	qDebug() << document.toString(4);

	file.close();
}

/**
* @brief 读取xml格式文件示例代码
*/
void example02() {
	/*
	理解二者的区别：
	QDomElement QDomNode::firstChildElement(const QString & tagName = QString()) const
	QDomNode QDomNode::firstChild() const
	*/
	QString strPath = QCoreApplication::applicationDirPath();
	strPath = ns_train::getPath(strPath);
	if (!strPath.endsWith("/")) {
		strPath += "/";
	}

	QString strFileName = strPath + "test04_13.xml"; // 程序运行目录下的xml文件
	QFile file(strFileName);
	if (!file.open(QFile::ReadOnly | QFile::Text))	{
		return;
	}

	QDomDocument document;
	QString error;
	int row = 0, column = 0;

	if (!document.setContent(&file, false, &error, &row, &column))	{
		return;
	}
	QDomElement rootDoc = document.firstChildElement();

	if (rootDoc.nodeName() != "doc") {
		return;
	}
	QString strName;
	QString strValue;
	QDomElement eleCourses = rootDoc.firstChildElement();
	while (eleCourses.isElement()) { //拥有属性的节点才是元素，
									 //因为我们写XML时就知道“courses”节点是有属性的，
									 //所以这里我们可以对它进行这样的判断。
		strName = eleCourses.tagName();
		if (strName != "courses") {
            eleCourses = eleCourses.nextSiblingElement();
			continue;
		}
		strName = "institution";
		strValue = eleCourses.attribute(strName);

		strName = "teacher";
		strValue = eleCourses.attribute(strName);

		strName = "serie";
		strValue = eleCourses.attribute(strName);


		strName = "count";
		strValue = eleCourses.attribute(strName);

		QDomElement eleLesson = eleCourses.firstChildElement();
		while (eleLesson.isElement()) {
			strName = eleLesson.tagName();
			if (strName == "lesson") {
				QDomNamedNodeMap attrs = eleLesson.attributes();
				int nC = attrs.count();
				for (int i = 0; i < nC; ++i) {
					QDomAttr  attrEle = attrs.item(i).toAttr();
					if (!attrEle.isNull()) {
						strName = attrEle.name();
						strValue = attrEle.value();
					}
				}
				if (!eleLesson.firstChild().isNull()) {
					//eleLesson.firstChild()可以获取到第一个子节点，
					//因为我们保存XML文件时，“lesson”元素的第一个子节点就是文本，
					//所以我们对应这样编码是可以的。
					QDomCharacterData dtText = eleLesson.firstChild().toCharacterData();
					if (!dtText.isNull()) {
						strValue = dtText.data();
					}
				}
			}			
            eleLesson = eleLesson.nextSiblingElement();
		}
        eleCourses = eleCourses.nextSiblingElement();
	}

	file.close();
}


