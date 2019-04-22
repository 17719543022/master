/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: country.cpp
\brief 国家类实现文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/10
*/
#include <QDir>
#include <QTextStream>

#include "base/basedll/baseapi.h"
#include "country.h"
#include "province.h"

// tag name
static const char* c_tag_doc       = "doc";
static const char* c_tag_content   = "content";
static const char* c_tag_province  = "province";

// attribute name
static const char* c_attribute_name = "name";
static const char* c_attribute_continent = "continent";


CCountry::CCountry() {
	;
}

CCountry::~CCountry() {
	QList<CProvince*>::iterator iteLst = m_lstProvinces.begin();
	while (iteLst != m_lstProvinces.end()) {
		if (NULL != *iteLst) {
			delete *iteLst;
		}
		iteLst++;
	}

	m_lstProvinces.clear();
}

int CCountry::addProvince(CProvince* pProvince) {
	if ((NULL == pProvince) || (m_lstProvinces.contains(pProvince))) {
		return m_lstProvinces.size();
	}

	m_lstProvinces.push_back(pProvince);
	return m_lstProvinces.size();
}

ESerializeCode CCountry::serializeBinary(const QString& strFileName, QString* pError) const {
	if (0 == strFileName.length()) {
		if (NULL != pError) {
			pError->append(QString::fromLocal8Bit("\n文件名为空"));
		}
		return ESERIALIZECODE_FILENOTFOND;
	}
	QFile file(strFileName);
	QString strDirectory = ns_train::getDirectory(strFileName);
	
	QDir dir;
	dir.mkpath(strDirectory);

	if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
		return ESERIALIZECODE_FILENOTFOND;
	}

	QDataStream ds(&file);
	ds.setByteOrder(QDataStream::LittleEndian);
	ESerializeCode ret = serializeBinary(ds, pError);
	file.close();

	return ret;
}

ESerializeCode  CCountry::serializeBinary(QDataStream& ds, QString* pError) const {
	ds << m_strName;
	ds << m_strContinent;
	quint16 nCount = m_lstProvinces.size(); // 需要明确指定数据类型，否则跨平台时可能出问题。比如int在各个平台上可能长度不一样。
	ds << nCount; 
	QList<CProvince*>::ConstIterator iteLst = m_lstProvinces.constBegin(); // 因为本函数为const，所以需要调用const类型的接口
	ESerializeCode ret = ESERIALIZECODE_OK;
	while (iteLst != m_lstProvinces.end()) {
		ESerializeCode retcode = (*iteLst)->serializeBinary(ds, pError);
		if (ESERIALIZECODE_OK != retcode) {
			ret = retcode;
		}
		iteLst++;
	}
	return ret;
}

ESerializeCode CCountry::deSerializeBinary(const QString& strFileName, QString* pError) {
	Q_UNUSED(pError);

	if (strFileName.isEmpty())
	{
		return ESERIALIZECODE_FILENOTFOND;
	}

	QFile file(strFileName);
	if (!file.open(QFile::ReadOnly))
	{
		return ESERIALIZECODE_FILENOTFOND;
	}

	QDataStream ds(&file);
	ds.setByteOrder(QDataStream::LittleEndian);
	QString strError;
	ESerializeCode ret = deSerializeBinary(ds, &strError);
	file.close();

	return ret;
}

ESerializeCode CCountry::deSerializeBinary(QDataStream& ds, QString* pError) {
	ds.setByteOrder(QDataStream::LittleEndian);
	ESerializeCode retcode = ESERIALIZECODE_OK;
	ds >> m_strName;
	ds >> m_strContinent;
	quint16 nCount = 0; // 需要明确指定数据类型，否则跨平台时可能出问题。比如int在各个平台上可能长度不一样。
	ds >> nCount;
	quint16 idx = 0;
	CProvince* pProvince = NULL;

	for (idx = 0; idx < nCount; idx++) {
		pProvince = new CProvince();
		pProvince->deSerializeBinary(ds, pError);
		addProvince(pProvince);
	}

	return retcode;
}
ESerializeCode CCountry::serializeXML(const QString& fileName, QString* pError) const
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        return ESERIALIZECODE_FILENOTFOND;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    QDomDocument document;
    ESerializeCode ret = serializeXML(document, pError);
    if (ESERIALIZECODE_OK == ret)
    {
        document.save(out, 4, QDomNode::EncodingFromTextStream);
    }
    file.close();
    return ret;
}

ESerializeCode CCountry::serializeXML(QDomDocument& doc, QString* pError) const
{
    QDomElement rootDoc = doc.createElement(c_tag_doc);

    // 开始组织文件内容
    QDomElement eleContent = doc.createElement(c_tag_content);
    eleContent.setAttribute(c_attribute_name, m_strName);
    eleContent.setAttribute(c_attribute_continent, m_strContinent);

    ESerializeCode ret = ESERIALIZECODE_OK;

    // 因为本函数为const，所以需要对成员变量调用const类型的接口
    QList<CProvince*>::ConstIterator iteList = m_lstProvinces.constBegin();
    for (; iteList != m_lstProvinces.constEnd(); iteList++) {
        QDomElement eleProvince = doc.createElement(c_tag_province);
        ESerializeCode retcode = (*iteList)->serializeXML(doc, eleProvince, pError);
        if (ESERIALIZECODE_OK != retcode) {
            ret = retcode;
        }
        eleContent.appendChild(eleProvince);
    }

    rootDoc.appendChild(eleContent);
    doc.appendChild(rootDoc);
    return ret;
}

ESerializeCode CCountry::deSerializeXML(const QString& strFileName, QString* pError)
{
    Q_UNUSED(pError);
    if (strFileName.isEmpty()) {
        return ESERIALIZECODE_FILENOTFOND;
    }
    QFile file(strFileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return ESERIALIZECODE_FILENOTFOND;
    }
    QDomDocument document;
    QString strError;
    int row = 0, column = 0;
    if (!document.setContent(&file, false, &strError, &row, &column)) {
        return ESERIALIZECODE_SETCONTENT_ERROR;
    }
    ESerializeCode ret = deSerializeXML(document, &strError);
    file.close();
    return ret;
}


ESerializeCode CCountry::deSerializeXML(const QDomDocument& doc, QString* pError)
{
    ESerializeCode ret = ESERIALIZECODE_OK;
    ESerializeCode retcode = ESERIALIZECODE_OK;
    QDomElement rootDoc = doc.firstChildElement();
    if (rootDoc.nodeName() != c_tag_doc) {
        //setInSerializing(false);
        if (NULL != pError)
        {
            *pError = QObject::tr("Unrecognized graphics files!");
        }
        return ESERIALIZECODE_DOC_ELEMENT_NOTFOUND;
    }
    QDomElement eleContent = rootDoc.firstChildElement();
    if (eleContent.nodeName() != c_tag_content) {
        return ESERIALIZECODE_CONTENT_ELEMENT_NOTFOUND;
    }
    m_strName = eleContent.attribute(c_attribute_name);
    m_strContinent = eleContent.attribute(c_attribute_continent);

    QDomElement eleProvince = eleContent.firstChildElement();
    CProvince* pProvince = NULL;
    while (!eleProvince.isNull()) {
        if (eleProvince.tagName() != c_tag_province) {
            eleProvince = eleProvince.nextSiblingElement();
            continue;
        }
        pProvince = new CProvince();
        
        addProvince(pProvince);

        retcode = pProvince->deSerializeXML(eleProvince, pError);
        if (ESERIALIZECODE_OK != retcode) {
            return retcode;
        }
        eleProvince = eleProvince.nextSiblingElement();
    }
    return ret;
}