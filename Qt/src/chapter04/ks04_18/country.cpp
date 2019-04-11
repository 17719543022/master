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
#include <QCryptographicHash>
#include <QDir>
#include <QTextStream>

#include "base/basedll/baseapi.h"
#include "base/basedll/fileattribute.h"
#include "base/basedll/filehead.h"
#include "country.h"
#include "province.h"

/////////////////////////////////////////////////////////////////////////
// dom元素标签定义区
static const char* c_tag_doc = "doc";
static const char* c_tag_content = "content";
static const char* c_tag_customdata = "customdata";
static const char* c_tag_province = "province";
static const char* c_tag_provinces = "provinces";

// dom元素属性名定义区
static const char* c_attribute_name = "name";
static const char* c_attribute_continent = "continent";

/////////////////////////////////////////////////////////////////////////
// CCountry
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

	if (!file.open(QFile::ReadWrite | QFile::Truncate)) {
		return ESERIALIZECODE_FILENOTFOND;
	}

	QDataStream ds(&file);
	ds.setByteOrder(QDataStream::LittleEndian);
	ESerializeCode ret = serializeBinary(ds, pError);
	file.close();

	return ret;
}

ESerializeCode  CCountry::serializeBinary(QDataStream& ds, QString* pError) const {
	ns_train::SFileAttr attrs;
	// 保存文件头信息(保存时总是保存为当前程序版本所对应的文件格式)
	attrs.mainVer = ns_train::getMainVersion();
	attrs.subVer = ns_train::getSubVersion();
	ds << attrs;

	ds << m_strName;
	ds << m_strContinent;
    quint16 nCount = 0;
    
    // 自定义属性的存储
    nCount = m_mapCustomData.size();
    ds << nCount;
    QMap<QString, QVariant>::ConstIterator iteMap = m_mapCustomData.constBegin();
    while (iteMap != m_mapCustomData.constEnd()) {
        ds << iteMap.key();
        ds << iteMap.value();
        iteMap++;
    }

    // 保存province
    m_lstProvinces.size(); // 需要明确指定数据类型，否则跨平台时可能出问题。比如int在各个平台上可能长度不一样。
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

	// 保存MD5码
	QCryptographicHash cghash(QCryptographicHash::Md5);
	qint64 nOffsetOfMd5 = offsetof(ns_train::SFileAttr, md5);		// md5码在文件中的位置
	//qint64 nOffsetOfMd5 = sizeof(quint16) + sizeof(quint16);		// md5码在文件中的位置
	qint64 nLengthMd5 = ds.device()->size() - ns_train::c_MD5_Length;	// 需要进行md5计算的数据总长度
	qint64 nLengthContent = nLengthMd5 - nOffsetOfMd5;		// 除了版本和md5之外的文件内容长度
	char* buf = new char[nLengthMd5];
	ds.device()->seek(0);	// 先定位到文件头
	ds.device()->read(buf, nOffsetOfMd5);
	ds.device()->seek(nOffsetOfMd5 + ns_train::c_MD5_Length);		// 先定位到md5码之后的数据区
	ds.device()->read(buf + nOffsetOfMd5, nLengthContent);
	cghash.addData(buf, nLengthMd5);
	QByteArray bydata = cghash.result();
	qint64 nPos = ds.device()->pos();
	ds.device()->seek(nOffsetOfMd5);
	ds.device()->write(bydata.data(), ns_train::c_MD5_Length);
	ds.device()->seek(nPos);
	delete buf;

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

    ns_train::SFileAttr attr;
    ds >> attr;
    ns_train::SFileHead fileHead(attr.mainVer, attr.subVer);

    ds >> m_strName;
    ds >> m_strContinent;
    quint16 nCount = 0; // 需要明确指定数据类型(长度)，否则跨平台时可能出问题。比如int在各个平台上可能长度不一样。
    if (fileHead.isLaterVersion(1, 1)) {
        ds >> nCount;
        QString strName;
        QVariant var;
        quint16 idx = 0;
        for (; idx < nCount; idx++) {
            ds >> strName;
            ds >> var;
            addCustomData(strName, var);
        }
    }

	ds >> nCount;
	quint16 idx = 0;
	CProvince* pProvince = NULL;

	for (idx = 0; idx < nCount; idx++) {
		pProvince = new CProvince();
		pProvince->deSerializeBinary(ds, &fileHead, pError);
		addProvince(pProvince);
	}

	return retcode;
}

ESerializeCode CCountry::serializeXML(const QString& fileName, QString* pError) const {
	
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		return ESERIALIZECODE_FILENOTFOND;
	}

	QTextStream out(&file);
	out.setCodec("UTF-8");
	QDomDocument document;
	int ret = serializeXML(document, pError);
	if (ret == ESERIALIZECODE_OK)
	{
		document.save(out, 4, QDomNode::EncodingFromTextStream);
	}
	file.close();
	return ESERIALIZECODE_OK;
}

ESerializeCode CCountry::serializeXML(QDomDocument& doc, QString* pError) const {
	QDomElement rootDoc = doc.createElement(c_tag_doc);
	doc.appendChild(rootDoc);

	// 图形属性
	ns_train::SFileAttr attrs;
	// 保存文件头信息(保存时总是保存为当前程序版本所对应的文件格式)
	attrs.mainVer = ns_train::getMainVersion();
	attrs.subVer = ns_train::getSubVersion();
	rootDoc << attrs;

	// 文件内容
	QDomElement eleContent = doc.createElement(c_tag_content);

	eleContent.setAttribute(c_attribute_name, m_strName);
	eleContent.setAttribute(c_attribute_continent, m_strContinent);
	
	// 自定义属性
	QDomElement eleCustomData = doc.createElement(c_tag_customdata);
    QMap<QString, QVariant>::ConstIterator iteMap = m_mapCustomData.constBegin();
    while (iteMap != m_mapCustomData.constEnd()) {
        eleCustomData.setAttribute(iteMap.key(), iteMap.value().toString());
        iteMap++;
    }
	eleContent.appendChild(eleCustomData);

	// provinces
	QDomElement eleProvinces = doc.createElement(c_tag_provinces);
	QList<CProvince*>::ConstIterator iteLst = m_lstProvinces.constBegin(); // 因为本函数为const，所以需要调用const类型的接口
	ESerializeCode ret = ESERIALIZECODE_OK;
	while (iteLst != m_lstProvinces.end()) {
		QDomElement eleProvince = doc.createElement(c_tag_province);
		ESerializeCode retcode = (*iteLst)->serializeXML(doc, eleProvince, pError);
		if (ESERIALIZECODE_OK != retcode) {
			ret = retcode;
		}
        eleProvinces.appendChild(eleProvince);
		iteLst++;
	}
	rootDoc.appendChild(eleContent);


	return ESERIALIZECODE_OK;
}



ESerializeCode CCountry::deSerializeXML(const QString& strFileName, QString* /*pError*/) {
	if (strFileName.isEmpty())
	{
		return ESERIALIZECODE_FILENOTFOND;
	}

	QFile file(strFileName);
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{		
		return ESERIALIZECODE_FILENOTFOND;
	}

	QDomDocument document;
	QString error;
	int row = 0, column = 0;

	if (!document.setContent(&file, false, &error, &row, &column))
	{
		return ESERIALIZECODE_SETCONTENT_ERROR;
	}

	deSerializeXML(document);

	file.close();

	return ESERIALIZECODE_OK;
}


ESerializeCode CCountry::deSerializeXML(const QDomDocument& doc, QString* pError) {
	
	ESerializeCode ret = ESERIALIZECODE_OK;
	ESerializeCode retcode = ESERIALIZECODE_OK;

	QDomElement rootDoc = doc.firstChildElement();
	if (rootDoc.nodeName() != c_tag_doc)
	{
		//setInSerializing(false);
		if (NULL != pError)	{
			*pError = QObject::tr("Unrecognized graphics files!");
		}
		return ESERIALIZECODE_DOC_ELEMENT_NOTFOUND;
	}

	ns_train::SFileAttr attrs;
	rootDoc >> attrs;
	ns_train::SFileHead fileHead(attrs.mainVer, attrs.subVer);
	if (fileHead.isLaterMainVersion(ns_train::getMainVersion())) 	{
		if (NULL != pError)		{
			*pError = QObject::tr("Unable to open higher version graphics files!");
		}
		return ESERIALIZECODE_VERSION_NOTRECOGNIZE;
	}
	// 
	QDomElement ele = rootDoc.firstChildElement();
	CProvince* pProvince = NULL;
	QDomElement eleProvince;
	while (ele.isElement()) {
		if (ele.tagName() == c_tag_provinces) {
            eleProvince = ele.firstChildElement();
            while (eleProvince.isElement()) {
		        pProvince = new CProvince();
		        retcode = pProvince->deSerializeXML(eleProvince, &fileHead, pError);
		        if (ESERIALIZECODE_OK != retcode) {
			        ret = retcode;
		        }		
            }
		}
        else if (ele.tagName() == c_tag_customdata) {
            QDomNamedNodeMap attrs = ele.attributes();
            int nC = attrs.count();
            for (int i = 0; i < nC; ++i)
            {
                QDomAttr  attrEle = attrs.item(i).toAttr();
                if (!attrEle.isNull())
                {
                    QString szName = attrEle.name();
                    setCustomData(attrEle.name(), attrEle.value());
                }
            }
        }
		eleProvince = eleProvince.nextSiblingElement();
	}
	return ret;
}

bool CCountry::addCustomData(const QString& name) {
    QMap<QString, QVariant>::Iterator iteMap = m_mapCustomData.find(name);
    if (iteMap == m_mapCustomData.constEnd()) {
        m_mapCustomData[name] = QVariant();
        return true;
    }
    return false;

}

int CCountry::getAllCustomDataName(QStringList& lst) const {
    lst.clear();
    QMap<QString, QVariant>::ConstIterator iteMap = m_mapCustomData.constBegin();
    while (iteMap != m_mapCustomData.constEnd()) {
        lst.push_back(iteMap.key());
        iteMap++;
    }
    return m_mapCustomData.size();
}

QVariant CCountry::getCustomData(const QString& name) const {
    QMap<QString, QVariant>::ConstIterator iteMap = m_mapCustomData.constFind(name);
    if (iteMap != m_mapCustomData.constEnd()) {
        return iteMap.value();
    }
    return QVariant();
}

void CCountry::addCustomData(const QString& name, const QVariant& data) {
    m_mapCustomData[name] = data;
}

bool CCountry::setCustomData(const QString& name, const QVariant& data) {
    QMap<QString, QVariant>::Iterator iteMap = m_mapCustomData.find(name);
    if (iteMap != m_mapCustomData.end()) {
        m_mapCustomData[name] = data;
        return true;
    }
    return false;

}

