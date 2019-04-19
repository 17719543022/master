/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���

\file: city.h
\brief �����ඨ���ļ���
       
\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
\Date 2018/10
*/

#ifndef _CITY_H_
#define _CITY_H_

#include<QString>

#include "serialize.h"
#include "qdatastream.h"

class CProvince;

// ������
//-----------------------------------------
class CCity
{
public:
    /**
    * @brief ���ó�������.
    * @param[in] str ��������
    * @return void
    */
	//void  setName(const QString& str) {m_strName = str;}
	void  setName(const QString& str);

    /**
    * @brief ��ȡ��������.
    * @return ��������
    */
	//QString  getName(void)const {return m_strName;}
	QString  getName(void)const;
 
    /**
    * @brief ���ó�������ʡ(��)
    * @param[in] pProvince ��������ʡ(��)
    * @return void
    */
	//void  setProvince(CProvince* pProvince) { m_pProvince = pProvince;}
	void  setProvince(CProvince* pProvince);

    /**
    * @brief ��ȡ��������ʡ(��)
    * @return ��������ʡ(��)
    */
	//CProvince*  getProvince(void) const {return m_pProvince;}
	CProvince*  getProvince(void) const;

private:	
    QString	m_strName;
	CProvince*	m_pProvince;
};

#endif  // for _CITY_H_
