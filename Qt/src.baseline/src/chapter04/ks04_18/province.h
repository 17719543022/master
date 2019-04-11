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

#include <QDomDocument>
#include <QList>
#include <QString>

#include "base/basedll/serialize.h"

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
	
	/**
	* @brief 用来把类对象进行二进制方式序列化的函数。
	* @param[in] ds 文件流对象。
	* @param[in|out] pError 错误信息。
	* @return ESerializeCode枚举值。
	*/
	ESerializeCode serializeBinary(QDataStream& ds, QString* pError) const;
	/**
	* @brief 用来把类对象进行二进制方式序列化的函数。
	*        打开的文件与保存时采用相同的ByteOrder(本接口内部已经调用QDataStream::setByteOrder)。
	* @param[in] ds 文件流对象。
	* @param[in|out] pError 错误信息。
	* @return ESerializeCode枚举值。
	*/
	ESerializeCode deSerializeBinary(QDataStream& ds, QString* pError);
	/**
	* @brief 用来把类对象进行文本方式序列化的函数。
	* @param[in|out] doc QDomDocument对象，需要外部构建
	* @param[in] eleProvince 省元素对象
	* @return ESerializeCode枚举值。
	*/
	ESerializeCode serializeXML(QDomDocument& doc, QDomElement& eleProvince, QString* pError) const;

	/**
	* @brief 用来把类对象进行文本方式序列化的函数。
	* @param[in] eleProvince 省元素对象
	* @return ESerializeCode枚举值。
	*/
	ESerializeCode deSerializeXML(const QDomElement& eleProvince, QString* pError = NULL);
private:	
    QString	m_strName;
	CCountry* m_pCountry;
	QList<CCity*> m_lstCities;
};



#endif  // for _PROVINCE_H_
