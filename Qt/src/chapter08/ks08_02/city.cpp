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

void  CCity::setName(const QString& str)
{
	m_strName = str;
}

QString  CCity::getName(void)const 
{
	return m_strName;
}

void  CCity::setProvince(CProvince* pProvince) 
{
	m_pProvince = pProvince;
}

CProvince*  CCity::getProvince(void) const 
{
	return m_pProvince;
}