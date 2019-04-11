/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: iniconfig.h
\brief ini格式配置文件定义头文件, 请注意：保存的配置文件采用GB2312编码。
       
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
* please import basedll.dll
*/

#ifndef _INICONFIG_H_
#define _INICONFIG_H_

#include <QFile>
#include <QString>
#include <QVector>

#include "base_export.h"

namespace ns_train {

// ini格式配置文件处理类
//-----------------------------------------


class BASE_API CIniConfig
{
public:
	CIniConfig();
	~CIniConfig();

    /**
    * @brief 设置配置文件的文件名，使用全路径，不支持环境变量.
    * @param[in] strFileName 文件名
    * @return true:成功,false:失败
    */
	bool  setFileName(const QString& strFileName);

    /**
    * @brief 删除指定子键
    * @param[in] strKey 主键
    * @param[in] strSubKey 子键
    * @return true:成功,false:失败
    */
	bool  deleteSubKey(const QString& strKey, const QString& strSubKey);
    /**
    * @brief 删除指定主键
    * @param[in] strKey 主键
    * @return true:成功,false:失败
    */
	bool  deleteKey(const QString& strKey);
    /**
    * @brief 删除全部键值
    * @return true:成功,false:失败
    */
	bool  deleteAll();

    /**
    * @brief 读取bool类型的键值
    * @param[in] strKey 主键
    * @param[in] strSubKey 子键
    * @param[in] i_nDefault 默认值
    * @param[out] o_bRet true:成功, false:失败
    * @return 数据
    */
	bool  getBool(const QString& strKey, const QString& strSubKey, bool i_nDefault, bool* o_bRet=NULL);
    /**
    * @brief 读取int类型的键值
    * @param[in] strKey 主键
    * @param[in] strSubKey 子键
    * @param[in] i_nDefault 默认值
    * @param[out] o_bRet true:成功, false:失败
    * @return 数据
    */
	int  getInt(const QString& strKey, const QString& strSubKey, int i_nDefault, bool* o_bRet=NULL);
    /**
    * @brief 读取浮点类型的键值
    * @param[in] strKey 主键
    * @param[in] strSubKey 子键
    * @param[in] i_fDefault 默认值
    * @param[out] o_bRet true:成功, false:失败
    * @return 数据
    */
	double  getReal(const QString& strKey, const QString& strSubKey, double i_fDefault, bool* o_bRet=NULL);
    /**
    * @brief 读取string类型的键值
    * @param[in] strKey 主键
    * @param[in] strSubKey 子键
    * @param[in] strDefault 默认值
    * @param[out] o_bRet true:成功, false:失败
    * @return 数据
    */
    QString getString(const QString& strKey, const QString& strSubKey, const QString& strDefault, bool* o_bRet=NULL);
    /**
    * @brief 读取string类型的键值(扩展接口),支持多行读取
    * @param[in] strKey 主键
    * @param[in] strSubKey 子键
    * @param[in] strDefault 默认值
    * @param[out] o_bRet true:成功, false:失败
    * @return 数据
    */
    QString getStringExt(const QString& strKey, const QString& strSubKey, const QString& strDefault, bool* o_bRet=NULL);
    /**
    * @brief 设置bool类型的键值
    * @param[in] strKey 主键
    * @param[in] strSubKey 子键
    * @param[in] i_nValue 子键的值
     * @return true:成功, false:失败
    */	
    bool  setBool(const QString& strKey, const QString& strSubKey, bool i_nValue);
    /**
    * @brief 设置int类型的键值
    * @param[in] strKey 主键
    * @param[in] strSubKey 子键
    * @param[in] i_nValue 子键的值
     * @return true:成功, false:失败
    */	
    bool  setInt(const QString& strKey, const QString& strSubKey, int i_nValue);
    /**
    * @brief 设置浮点类型的键值
    * @param[in] strKey 主键
    * @param[in] strSubKey 子键
    * @param[in] i_fValue 子键的值
     * @return true:成功, false:失败
    */	
	bool  setReal(const QString& strKey, const QString& strSubKey, double i_fValue);
    /**
    * @brief 设置字符串类型的键值, 比如，配置文件内容如下:
    *           [config]
    *           x=xx
    *           y=yy
    *           z=zz
    * @param[in] strKey 主键=config
    * @param[in] strSubKey 子键=x
    * @param[in] strValue 子键的值, 为""表示删除该子健。
     * @return true:成功, false:失败
    */	
    bool  setString(const QString& strKey, const QString& strSubKey, const QString& strValue);

    /**
    * @brief 读取键值列表, ，比如传入("config"")，得到, "x=xx\ny=yy\nz=zz"
    * @param[in] strKey 主键
    * @return 键值列表
    */
    QString getKeyList(const QString& strKey);

    /**
    * @brief 设置键值列表, ，比如传入("config", "x=xx\ny=yy\nz=zz")
    *           执行后的结果:
    *           [config]
    *           x=xx
    *           y=yy
    *           z=zz
    * @param[in] strKey 主键
    * @param[in] str 子键值值列表,\n分隔。比如: "x=xx\ny=yy\nz=zz"  
    * @return 结果，true:成功, false:失败
    */	
    bool setKeyList(const QString& strKey, const QString& Str);

private:
	int searchLine(const QString& strKey, const QString& strSubKey);
	bool writeToFile();

	bool getValueString(int i_nIndex, QString& o_pValue);
	bool setValueString(int i_nIndex, const QString& strValue);
	void addValueString(const QString& strKey, const QString& strSubKey, const QString& strValue, int i_nRet);

	QFile				m_yFile;    // 文件对象
	QVector<QString>	m_arString;
	bool				m_bIsOpen;  // 配置文件是否已打开
    QString				m_szTmp;
};

}

#endif  // for _INICONFIG_H_
