/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���

\file: city.cpp
\brief ������ʵ���ļ�

\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
\Date 2018/10
*/

#include "city.h"

// attribute name
static const char* c_attribute_name = "name";
static const char* c_attribute_card = "card";


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
		if (NULL != m_pCard) {
			delete m_pCard;
			m_pCard = new CCard();
			m_pCard->deSerializeBinary(ds, pError);
		}
	}
	return retcode;
}


ESerializeCode CCity::serializeXML(QDomDocument& doc, QDomElement& eleCity, QString* pError) const
{
    Q_UNUSED(doc);
    Q_UNUSED(pError);

    eleCity.setAttribute(c_attribute_name, m_strName);

    ESerializeCode ret = ESERIALIZECODE_OK;
    if (NULL != m_pCard) {
        eleCity.setAttribute(c_attribute_card, m_pCard->getString());
    }

    return ret;
}

ESerializeCode CCity::deSerializeXML(const QDomElement& eleCity, QString* pError)
{
    Q_UNUSED(pError);

    m_strName = eleCity.attribute(c_attribute_name);
    if (eleCity.hasAttribute(c_attribute_card)) {
        if (NULL == m_pCard) {
            m_pCard = new CCard;
        }
        m_pCard->setString(eleCity.attribute(c_attribute_card));
    }
    return ESERIALIZECODE_OK;
}
