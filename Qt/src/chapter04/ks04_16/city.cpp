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
