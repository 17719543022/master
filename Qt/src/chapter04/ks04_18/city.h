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

#include <QDomDocument>
#include <QDataStream>
#include <QString>

#include "base/basedll/serialize.h"

namespace ns_train {
	class SFileHead;
}
class CProvince;

// 名片类
class CCard {
public:
	CCard():m_id(0) {}
	~CCard() {}

	/**
	* @brief 设置名片字符串.
	* @param[in] str 名片字符串.
	* @return void
	*/
	void  setString(const QString& str) { m_str = str; }

	/**
	* @brief 获取名片字符串.
	* @return 名片字符串.
	*/
	QString  getString(void) const { return m_str; }
	/**
	* @brief 设置名片id.
	* @param[in] str 名片id.
	* @return void
	*/
	void  setId(quint32 id) { m_id = id; }

	/**
	* @brief 获取名片id.
	* @return 名片id.
	*/
	quint32  getId(void) const { return m_id; }
	/**
	* @brief 用来把类对象进行二进制方式序列化的函数。
	* @param[in] ds 文件流对象。
	* @param[in|out] pError 错误信息。
	* @return ESerializeCode枚举值。
	*/
    ESerializeCode serializeBinary(QDataStream& ds, QString* /*pError*/) const;

	/**
	* @brief 用来把类对象进行二进制方式序列化的函数。
	*        打开的文件与保存时采用相同的ByteOrder(本接口内部已经调用QDataStream::setByteOrder)。
	* @param[in] ds 文件流对象。
	* @param[in|out] pError 错误信息。
	* @return ESerializeCode枚举值。
	*/
    ESerializeCode deSerializeBinary(QDataStream& ds, const ns_train::SFileHead* /*pFileHead*/, QString* /*pError*/);
	/**
	* @brief 用来把类对象进行文本方式序列化的函数。
	* @param[in|out] doc QDomDocument对象，需要外部构建
	* @param[in|out] eleCity 城市元素对象
	* @param[in|out] pError 错误信息。
	* @return ESerializeCode枚举值。
	*/
	ESerializeCode serializeXML(QDomDocument& doc, QDomElement& eleCard, QString* pError) const;

	/**
	* @brief 用来把类对象进行文本方式序列化的函数。
	* @param[in] eleCity 城市元素对象
	* @param[in] pError 错误信息。
	* @return ESerializeCode枚举值。
	*/
	ESerializeCode deSerializeXML(const QDomElement& eleCard, const ns_train::SFileHead* pFileHead, QString* pError = NULL);
private:
	QString m_str;
    quint32 m_id;
};
// 城市类
//-----------------------------------------
class CCity
{
public:
	CCity();
	~CCity();

    /**
    * @brief 设置城市名称.
    * @param[in] strName 城市名称
    * @return void
    */
	void  setName(const QString& str) {m_strName = str;}

    /**
    * @brief 获取城市名称.
    * @return 城市名称
    */
	QString  getName(void)const {return m_strName;}
 
    /**
    * @brief 设置城市所在省(州)
    * @param[in] pProvince 城市所在省(州)
    * @return void
    */
	void  setProvince(CProvince* pProvince) { m_pProvince = pProvince;}

    /**
    * @brief 获取城市所在省(州)
    * @return 城市所在省(州)
    */
	CProvince*  getProvince(void) const {return m_pProvince;}
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
	ESerializeCode deSerializeBinary(QDataStream& ds, const ns_train::SFileHead* pFileHead, QString* pError);
	/**
	* @brief 用来把类对象进行文本方式序列化的函数。
	* @param[in|out] doc QDomDocument对象，需要外部构建
	* @param[in|out] eleCity 城市元素对象
	* @param[in|out] pError 错误信息。
	* @return ESerializeCode枚举值。
	*/
	ESerializeCode serializeXML(QDomDocument& doc, QDomElement& eleCity, QString* pError) const;

	/**
	* @brief 用来把类对象进行文本方式序列化的函数。
	* @param[in] eleCity 城市元素对象
	* @param[in] pError 错误信息。
	* @return ESerializeCode枚举值。
	*/
	ESerializeCode deSerializeXML(const QDomElement& eleCity, const ns_train::SFileHead* pFileHead, QString* pError = NULL);


	/**
	* @brief 设置城市名片
	* @param[in] pCard 城市市名片
	* @return void
	*/
	void  setCard(CCard* pCard) { m_pCard = pCard; }

	/**
	* @brief 获取城市名片
	* @return 城市名片
	*/
	CCard*  getCard(void) const { return m_pCard; }

private:
	QString	m_strName;
	CProvince*	m_pProvince;
	CCard* m_pCard;

};



#endif  // for _CITY_H_
