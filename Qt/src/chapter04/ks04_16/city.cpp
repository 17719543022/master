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

CCity::CCity() :m_pCard(NULL) {
	;
}

CCity::~CCity() {
	clear();
}
void CCity::clear(void)
{
	if (NULL != m_pCard) {
		delete m_pCard;
	}
	m_pCard = NULL;
}
ESerializeCode  CCity::serializeBinary(QDataStream& ds, QString* pError) const {
	Q_UNUSED(pError);
	ds.setByteOrder(QDataStream::LittleEndian);
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
	clear();

	ds.setByteOrder(QDataStream::LittleEndian);
	ESerializeCode retcode = ESERIALIZECODE_OK;
	ds >> m_strName;
	
	quint8 byValue = 0;
	ds >> byValue;

	if (byValue) {
		m_pCard = new CCard();
		m_pCard->deSerializeBinary(ds, pError);
	}
	return retcode;
}
