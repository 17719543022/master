/*! 
* Copyright (C) 2018 Ů�����ϰ�
* ��Ȩ���С�
* ��������ڿγ̡�Qt���������-GUI��Ʒ��������ѧϰ�����𴫲���
* ��������:���벻��֤�ȶ��ԣ�����������ҵ��;���������Ը���

\file: province.h
\brief ʡ(��)�ඨ���ļ���
       
\author Ů�����ϰ�  �ǵ����: http://xingdianketang.cn/
\Date 2018/10
*/

#ifndef _PROVINCE_H_
#define _PROVINCE_H_

#include <QList>
#include <QString>

#include "serialize.h"

class CCity;
class CCountry;

// ʡ(��)��
//-----------------------------------------
class CProvince
{
public:
	CProvince();
	~CProvince();

    /**
    * @brief ����ʡ(��)����.
    * @param[in] strName ʡ(��)����
    * @return void
    */
	void  setName(const QString& str) {m_strName = str;}

    /**
    * @brief ��ȡʡ(��)����.
    * @return ʡ(��)����
    */
	QString  getName(void) const {return m_strName;}
   
   
    /**
    * @brief ����ʡ(��)���ڹ���
    * @param[in] pCountry ʡ(��)���ڹ���
    * @return void
    */
	void  setCountry(CCountry* pCountry) {m_pCountry = pCountry;}

    /**
    * @brief ��ȡʡ(��)���ڹ���
    * @return ʡ(��)���ڹ���
    */
	CCountry*  getCountry(void) const {return m_pCountry;}

    /**
    * @brief ��ӳ���
    * @param[in] pCity ����
    * @return ��Ӻ�ĳ��и���
    */
	int addCity(CCity* pCity);

    /**
    * @brief ��ӳ���
    * @param[out] lstCities �����б�
    * @return ���г��и���
    */
	int getCities(QList<CCity*>& lstCities) const { lstCities = m_lstCities; return lstCities.size(); }

private:	
    QString	m_strName;
	CCountry* m_pCountry;
	QList<CCity*> m_lstCities;
};

#endif  // for _PROVINCE_H_
