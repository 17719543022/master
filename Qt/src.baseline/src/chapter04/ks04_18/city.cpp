/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: city.cpp
\brief 城市类实现文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/10
*/

#include "city.h"

// dom元素标签定义区
static const char* c_tag_card = "card";

// dom元素属性名定义区
static const char* c_attribute_name = "name";
static const char* c_attribute_string = "string";

////////////////////////////////////////////////////////////////////////////////////
// CCard
ESerializeCode CCard::serializeXML(QDomDocument& /*doc*/, QDomElement& eleCard, QString* /*pError*/) const {
	eleCard.setAttribute(c_attribute_name, m_str);

	return ESERIALIZECODE_OK;
}

/**
* @brief 用来把类对象进行文本方式序列化的函数。
* @param[in] eleCity 城市元素对象
* @param[in] pError 错误信息。
* @return ESerializeCode枚举值。
*/
ESerializeCode CCard::deSerializeXML(const QDomElement& eleCard, QString* /*pError*/) {
	m_str = eleCard.attribute(c_attribute_name);
	return ESERIALIZECODE_OK;
}

////////////////////////////////////////////////////////////////////////////////////
// CCity
CCity::CCity() :m_pCard(NULL) {
	;
}

CCity::~CCity() {
	if (NULL != m_pCard) {
		delete m_pCard;
	}
}

ESerializeCode  CCity::serializeBinary(QDataStream& ds, QString* pError) const {
	Q_UNUSED(pError);

	ds << m_strName;
	quint8 byValue = ((NULL != m_pCard) ? true : false);
	ds << byValue;
	if (NULL != m_pCard) {
		m_pCard->serializeBinary(ds, pError);
	}
	return ESERIALIZECODE_OK;
}

ESerializeCode CCity::deSerializeBinary(QDataStream& ds, QString* pError) {
	Q_UNUSED(pError);
	ds.setByteOrder(QDataStream::LittleEndian);
	ESerializeCode retcode = ESERIALIZECODE_OK;
	ds >> m_strName;
	
	quint8 byValue = 0;
	ds >> byValue;

	if (byValue) {
		if (NULL == m_pCard) {
			m_pCard = new CCard();
		}
		m_pCard->deSerializeBinary(ds, pError);
	}
	return retcode;
}


ESerializeCode CCity::serializeXML(QDomDocument& doc, QDomElement& eleCity, QString* pError) const {

	eleCity.setAttribute(c_attribute_name, m_strName);

	ESerializeCode ret = ESERIALIZECODE_OK;
	if (NULL != m_pCard) {
		QDomElement eleCard = doc.createElement(c_tag_card);
		ret = m_pCard->serializeXML(doc, eleCard, pError);
		eleCity.appendChild(eleCard);
	}


	return ret;
}

ESerializeCode CCity::deSerializeXML(const QDomElement& eleCity, QString* pError) {
	
	ESerializeCode ret = ESERIALIZECODE_OK;
	m_strName = eleCity.attribute(c_attribute_name);
	// 
	QDomElement eleCard = eleCity.firstChildElement();
	if (eleCard.isElement()) {
		if (eleCard.tagName() == c_tag_card) {
			if (NULL == m_pCard) {
				m_pCard = new CCard();
			}
			ret = m_pCard->deSerializeXML(eleCard, pError);
		}
	}
	return ret;
}