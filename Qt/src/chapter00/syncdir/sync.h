/*! \file: sync.h
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\brief 文件同步类定义头文件
\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/

#ifndef _SYNC_H
#define _SYNC_H

#include <QString>
#include <QList>

class CSyncConfig {
public:
	CSyncConfig();
	CSyncConfig(const CSyncConfig& right);
	~CSyncConfig();

	CSyncConfig& operator=(const CSyncConfig& right);

	/**
	* @brief 设置源路径
	* @param[in] strSrc 源路径
	* @return void
	*/
	void setSourceDirectory(const QString& strSrc) { m_strSrcDir = strSrc; }
	/**
	* @brief 获取源路径, 已经转换为unix风格（/xx/xx/xx.txt），且不带最后的斜杠"/"
	* @return 源路径
	*/	
	QString getSourceDirectory() const { return m_strSrcDir; }

	/**
	* @brief 设置目标路径
	* @param[in] strDst 目标路径
	* @return void
	*/
	void setDestDirectory(const QString& strDst) { m_strDstDir = strDst; }
	/**
	* @brief 获取源路径, 已经转换为unix风格（/xx/xx/xx.txt），且不带最后的斜杠"/"
	* @return 目标路径
	*/
	QString getDestDirectory() const { return m_strDstDir; }

	/**
	* @brief 设置路径过滤列表
	* @param[in] lstDirFilter 路径过滤列表
	* @return void
	*/
	void setDirectoryFilters(const QStringList& lstDirFilter) { m_lstDirFilter = lstDirFilter; }
	/**
	* @brief 获取路径过滤列表
	* @return 路径过滤列表
	*/
	QStringList getDirectoryFilters()  const { return m_lstDirFilter; }

	/**
	* @brief 设置文件过滤列表
	* @param[in] lstFileFilter 文件过滤列表
	* @return void
	*/
	void setFileFilters(const QStringList& lstFileFilter) { m_lstFileFilter = lstFileFilter; }

	/**
	* @brief 获取文件过滤列表
	* @return 文件过滤列表
	*/
	QStringList getFileFilters() const { return m_lstFileFilter; }

	/**
	* @brief 指定路径是否被过滤
	* @param[in] strDirectory 指定路径(绝对路径)
	* @param[in] bSource true:源路径中的路径，false:目标路径中的路径
	* @return true:路径被过滤。 false:路径未过滤，需要正常处理
	*/	
	bool isFilteredDirectory(const QString& strDirectory, bool bSource) const;
	/**
	* @brief 指定文件是否被过滤
	* @param[in] strFileName 指定文件（带绝对路径）
	* @param[in] bSource true:源路径中的文件，false:目标路径中的文件
	* @return true:文件被过滤。 false:文件未过滤，需要正常处理
	*/		
	bool isFilteredFile(const QString& strFileName, bool bSource) const;
private:
	QString m_strSrcDir;
	QString m_strDstDir;
	QStringList m_lstDirFilter;
	QStringList m_lstFileFilter;
};

class CSync {
public:
	CSync();
	~CSync();

public:
	/**
	* @brief 执行同步
	* @return true:成功，false:失败
	*/
	bool exec();

private:
	/**
	* @brief 读取配置
	* @return void
	*/
	void readConfig();
	
	/**
	* @brief 清空配置
	* @return void
	*/	
	void clear();

	/**
	* @brief 获取指定根目录的待传输文件列表，该列表已经经过过滤，把跳过的目录和文件排除在外。
	* @param[in] strDirectory 指定路径
	* @param[in]  syncConfig 同步配置项
	* @param[in] bSource true:指定路径是源路径，false:指定路径是目标路径
	* @return 待传输文件列表
	*/	
	QStringList getSyncFileList(const QString& strDirectory, const CSyncConfig& syncConfig, bool bSource);

private:
	QList<CSyncConfig> m_lst;
};

#endif  // _MYCLASS_DLL_H