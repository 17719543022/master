/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: country.cpp
\brief 省类实现文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/10
*/

#include "city.h"
#include "province.h"


// dom元素标签定义区
static const char* c_tag_city = "city";

// dom元素属性名定义区
static const char* c_attribute_name = "name";


CProvince::CProvince() {
	;
}

CProvince::~CProvince() {
	QList<CCity*>::iterator iteLst = m_lstCities.begin();
	while (iteLst != m_lstCities.end()) {
		if (NULL != *iteLst) {
			delete *iteLst;
		}
		iteLst++;
	}

	m_lstCities.clear();
}

int CProvince::addCity(CCity* pCity) {
	if ((NULL == pCity) || (m_lstCities.contains(pCity))) {
		return m_lstCities.size();
	}

	m_lstCities.push_back(pCity);
	return m_lstCities.size();
}

ESerializeCode  CProvince::serializeBinary(QDataStream& ds, QString* pError) const {
	ds << m_strName;
	quint16 nCount = m_lstCities.size(); // 需要明确指定数据类型，否则跨平台时可能出问题。比如int在各个平台上可能长度不一样。
	ds << nCount;
	QList<CCity*>::ConstIterator iteLst = m_lstCities.constBegin(); // 因为本函数为const，所以需要调用const类型的接口
	while (iteLst != m_lstCities.end()) {
		(*iteLst)->serializeBinary(ds, pError);
		iteLst++;
	}

	return ESERIALIZECODE_OK;
}


ESerializeCode CProvince::deSerializeBinary(QDataStream& ds, const ns_train::SFileHead* pFileHead, QString* pError) {
	ds.setByteOrder(QDataStream::LittleEndian);
	ESerializeCode retcode = ESERIALIZECODE_OK;
	ds >> m_strName;
	quint16 nCount = 0; // 需要明确指定数据类型，否则跨平台时可能出问题。比如int在各个平台上可能长度不一样。
	ds >> nCount;
	quint16 idx = 0;
	CCity* pCity = NULL;

	for (idx = 0; idx < nCount; idx++) {
		pCity = new CCity();
		pCity->deSerializeBinary(ds, pFileHead, pError);
		addCity(pCity);
	}

	return retcode;
}


ESerializeCode CProvince::serializeXML(QDomDocument& doc, QDomElement& eleProvince, QString* pError) const {

	eleProvince.setAttribute(c_attribute_name, m_strName);

	QList<CCity*>::ConstIterator iteLst = m_lstCities.constBegin(); // 因为本函数为const，所以需要调用const类型的接口
	ESerializeCode ret = ESERIALIZECODE_OK;
	while (iteLst != m_lstCities.end()) {
		QDomElement eleCity = doc.createElement(c_tag_city);
		ESerializeCode retcode = (*iteLst)->serializeXML(doc, eleCity, pError);
		if (ESERIALIZECODE_OK != retcode) {
			ret = retcode;
		}
		eleProvince.appendChild(eleCity);
		iteLst++;
	}


	return ESERIALIZECODE_OK;
}

ESerializeCode CProvince::deSerializeXML(const QDomElement& eleProvince, const ns_train::SFileHead* pFileHead, QString* pError) {
	ESerializeCode ret = ESERIALIZECODE_OK;
	ESerializeCode retcode = ESERIALIZECODE_OK;
	m_strName = eleProvince.attribute(c_attribute_name);
	// 
	QDomElement eleCity = eleProvince.firstChildElement();
	CCity* pCity = NULL;
	while (eleCity.isElement()) {
		if (eleCity.tagName() == c_tag_city) {
			pCity = new CCity();
			retcode = pCity->deSerializeXML(eleCity, pFileHead, pError);
			if (ESERIALIZECODE_OK != retcode) {
				ret = retcode;
			}
		}
		eleCity = eleCity.nextSiblingElement();
	}

	return ret;
}