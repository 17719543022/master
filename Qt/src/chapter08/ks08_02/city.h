/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: city.h
\brief 城市类定义文件。
       
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/10
*/

#ifndef _CITY_H_
#define _CITY_H_

#include<QString>

#include "serialize.h"
#include "qdatastream.h"

class CProvince;

// 城市类
//-----------------------------------------
class CCity
{
public:
    /**
    * @brief 设置城市名称.
    * @param[in] str 城市名称
    * @return void
    */
	//void  setName(const QString& str) {m_strName = str;}
	void  setName(const QString& str);

    /**
    * @brief 获取城市名称.
    * @return 城市名称
    */
	//QString  getName(void)const {return m_strName;}
	QString  getName(void)const;
 
    /**
    * @brief 设置城市所在省(州)
    * @param[in] pProvince 城市所在省(州)
    * @return void
    */
	//void  setProvince(CProvince* pProvince) { m_pProvince = pProvince;}
	void  setProvince(CProvince* pProvince);

    /**
    * @brief 获取城市所在省(州)
    * @return 城市所在省(州)
    */
	//CProvince*  getProvince(void) const {return m_pProvince;}
	CProvince*  getProvince(void) const;

private:	
    QString	m_strName;
	CProvince*	m_pProvince;
};

#endif  // for _CITY_H_
