/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���

\file: country.cpp
\brief ʡ��ʵ���ļ�

\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
\Date 2018/10
*/

#include "city.h"
#include "province.h"

CProvince::CProvince() {
	;
}

CProvince::~CProvince() {
	clear();
}
void CProvince::clear(void)
{
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
	ds.setByteOrder(QDataStream::LittleEndian); 
	ds << m_strName;
	quint16 nCount = m_lstCities.size(); // ��Ҫ��ȷָ���������ͣ������ƽ̨ʱ���ܳ����⡣����int�ڸ���ƽ̨�Ͽ��ܳ��Ȳ�һ����
	ds << nCount;
	QList<CCity*>::ConstIterator iteLst = m_lstCities.constBegin(); // ��Ϊ������Ϊconst��������Ҫ����const���͵Ľӿ�
	while (iteLst != m_lstCities.end()) {
		(*iteLst)->serializeBinary(ds, pError);
		iteLst++;
	}

	return ESERIALIZECODE_OK;
}


ESerializeCode CProvince::deSerializeBinary(QDataStream& ds, QString* pError) {
	clear();

	ds.setByteOrder(QDataStream::LittleEndian);
	ESerializeCode retcode = ESERIALIZECODE_OK;
	ds >> m_strName;
	quint16 nCount = 0; // ��Ҫ��ȷָ���������ͣ������ƽ̨ʱ���ܳ����⡣����int�ڸ���ƽ̨�Ͽ��ܳ��Ȳ�һ����
	ds >> nCount;
	quint16 idx = 0;
	CCity* pCity = NULL;

	for (idx = 0; idx < nCount; idx++) {
		pCity = new CCity();
		pCity->deSerializeBinary(ds, pError);
		addCity(pCity);
		pCity->setProvince(this);
	}

	return retcode;
}
