/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: country.h
\brief 国家类定义文件。
       
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/10
*/

#ifndef _COUNTRY_H_
#define _COUNTRY_H_

#include <QList>
#include <QString>

#include "serialize.h"

class CProvince;



// 国家类
//-----------------------------------------
class CCountry
{
public:
	CCountry();
	explicit CCountry(const QString& str) :m_strName(str) { ; }
	~CCountry();

    /**
    * @brief 设置国家名称.
    * @param[in] strName 国家名称
    * @return void
    */
	void  setName(const QString& str) {m_strName = str;}

    /**
    * @brief 获取国家名称.
    * @return 国家名称
    */
	QString  getName(void) const {return m_strName;}   
   
    /**
    * @brief 设置国家所在大洲名称
    * @param[in] str 国家所在大洲名称
    * @return void
    */
	void  setContinent(const QString& str) {m_strContinent = str;}

    /**
    * @brief 获取国家所在大洲名称
    * @return 国家所在大洲名称
    */
	QString  getContinent(void) const {return m_strContinent;}

	/**
	* @brief 添加省
	* @param[in] pProvince 省
	* @return 添加后的省个数
	*/
	int addProvince(CProvince* pProvince);

	/**
	* @brief 获取省列表
	* @param[out] lstProvinces 省列表
	* @return 已有省个数
	*/
	int getProvinces(QList<CProvince*>& lstProvinces) const { lstProvinces = m_lstProvinces; return lstProvinces.size(); }

private:
    QString	m_strName;
    QString	m_strContinent;	
	QList<CProvince*> m_lstProvinces;
};


#endif  // for _COUNTRY_H_
