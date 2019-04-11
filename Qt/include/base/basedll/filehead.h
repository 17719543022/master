/*! \file: filehead.h
	\brief 文件头定义类
	\author 星点课堂
	\Date : 2018
* please import basedll.dll
*/
#ifndef _FILEHEAD_H
#define _FILEHEAD_H

#include "qglobal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 版本变更记录
// 1.0 初始版本
// 1.1 CCard增加了id值的序列化
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


namespace ns_train {


static const quint16 c_MainVersion= 1;		/// 当前文件的主版本号
static const quint16 c_SubVersion = 1;		/// 当前文件的次版本号

/// 获取当前文件的主版本号（使用本程序保存文件时的版本号）
static quint16 getMainVersion() {
	return c_MainVersion;
}
/// 获取当前文件的次版本号（使用本程序保存文件时的版本号）
static quint16 getSubVersion() {
	return c_SubVersion;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// 文件头类
class SFileHead
{
public:
	SFileHead()	{
		m_nMainVersion = c_MainVersion;
		m_nSubVersion = c_SubVersion;
	}

	SFileHead(quint16 nMainVersion, quint16 nSubVersion)	{
		m_nMainVersion = nMainVersion;
		m_nSubVersion = nSubVersion;
	}

	/// 是否有效
	bool isValid() const	{
		return (0 != m_nMainVersion) && (0 != m_nSubVersion);
	}

	/// 文件(程序)版本号是否比传入的版本号旧
	bool isEarliererVersion(quint16 nMainVersion, quint16 nSubVersion) const	{
		if ((m_nMainVersion < nMainVersion)
			|| (m_nMainVersion == nMainVersion && m_nSubVersion < nSubVersion))	{
			return true;
		}
		else	{
			return false;
		}
	}
	/// 文件版本号是否比传入的版本号新
	bool isLaterVersion(quint16 nMainVersion, quint16 nSubVersion) const	{
		if ((m_nMainVersion > nMainVersion)
			|| (m_nMainVersion == nMainVersion && m_nSubVersion >= nSubVersion))	{
			return true;
		}
		else	{
			return false;
		}
	}
	/// 文件主版本号是否比传入的主版本号新
	bool isLaterMainVersion(quint16 nMainVersion) const	{
		if (m_nMainVersion > nMainVersion)	{
			return true;
		}
		else	{
			return false;
		}
	}
	/// 文件版本号是否与传入的版本号相同
	bool isSameVersion(quint16 nMainVersion, quint16 nSubVersion) const	{
		if ((m_nMainVersion == nMainVersion)
			&& (m_nSubVersion == nSubVersion))
		{
			return true;
		}
		else	{
			return false;
		}
	}

	/// 将版本号转化为QString类型字符串，如版本1.0，转后为"1.0"
	QString toQString() const	{
		QString str = QString::number(m_nMainVersion).append(".").append(QString::number(m_nSubVersion));
		return str;
	}

	/// 将QString类型字符串转化为版本号，如字符串"1.0"，转后为版本1.0
	static SFileHead fromQString(QString str)	{
		SFileHead FileHead;
		if (str.contains('.'))	{
			qint32 index = str.indexOf('.');
			FileHead.m_nMainVersion = str.left(index).toUShort();
			FileHead.m_nSubVersion = str.right(str.length() - index - 1).toUShort();
		}
		else	{
			FileHead.m_nMainVersion = 0;
			FileHead.m_nSubVersion = 0;
		}
		return FileHead;
	}

	/// 赋值构造
	SFileHead& operator = (const SFileHead& fileHead)	{
		if (this != &fileHead)	{
			this->m_nMainVersion = fileHead.m_nMainVersion;
			this->m_nSubVersion = fileHead.m_nSubVersion;
		}
		return *this;
	}
	/// 判断两者是否相等
	bool operator == (const SFileHead& r)	{
		if ((this->m_nMainVersion == r.m_nMainVersion) && (this->m_nSubVersion == r.m_nSubVersion))		{
			return true;
		}
		else		{
			return false;
		}
	}
	/// 获取主版本号
	quint16 getMainVersion() const	{
		return m_nMainVersion;
	}

	/// 获取子版本号
	quint16 getSubVersion() const	{
		return m_nSubVersion;
	}

private:
	quint16	m_nMainVersion;		/// 主版本号
	quint16	m_nSubVersion;		/// 次版本号
};

} // namespace ns_train

#endif	//FILEHEAD_H