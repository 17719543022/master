/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: province.h
\brief 省(州)类定义文件。
       
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/10
*/

#ifndef _PROVINCE_H_
#define _PROVINCE_H_

#include <QList>
#include <QString>

#include "serialize.h"

class CCity;
class CCountry;

// 省(州)类
//-----------------------------------------
class CProvince
{
public:
	CProvince();
	~CProvince();

    /**
    * @brief 设置省(州)名称.
    * @param[in] strName 省(州)名称
    * @return void
    */
	void  setName(const QString& str) {m_strName = str;}

    /**
    * @brief 获取省(州)名称.
    * @return 省(州)名称
    */
	QString  getName(void) const {return m_strName;}
   
   
    /**
    * @brief 设置省(州)所在国家
    * @param[in] pCountry 省(州)所在国家
    * @return void
    */
	void  setCountry(CCountry* pCountry) {m_pCountry = pCountry;}

    /**
    * @brief 获取省(州)所在国家
    * @return 省(州)所在国家
    */
	CCountry*  getCountry(void) const {return m_pCountry;}

    /**
    * @brief 添加城市
    * @param[in] pCity 城市
    * @return 添加后的城市个数
    */
	int addCity(CCity* pCity);

    /**
    * @brief 添加城市
    * @param[out] lstCities 城市列表
    * @return 已有城市个数
    */
	int getCities(QList<CCity*>& lstCities) const { lstCities = m_lstCities; return lstCities.size(); }

private:	
    QString	m_strName;
	CCountry* m_pCountry;
	QList<CCity*> m_lstCities;
};

#endif  // for _PROVINCE_H_
