
#ifndef _PUBLICINFOMGR_H_
#define _PUBLICINFOMGR_H_

#include "uitypedef.h"

class CPublicInfoMgr
{
public:
	//单体的创建与销毁
	static CPublicInfoMgr* instance(void);
	void destroy();

	//! 获得环境的根路径（ICCSHOME指定）
	virtual QString getBasePath();

	//! 获得环境的图标目录
	virtual QString getIconPath();

	//! 获取皮肤风格路径
	virtual QString getConciseIconPath();

	//! 获得指定名称的样式信息
	virtual QString getStyleSheet(const QString& name);

	// @method	: setIconPath
	// @comm	: 设置图片路径
	virtual void setIconPath(const QString& strPath);

	// @method	: setConcisePath
	// @comm	: 设置皮肤风格路径
	virtual void setConciseIconPath(const QString& strPath = 0);

	//获取图片pathname
	virtual QString getUiIconPathName(const QString& strIcon, const EUIState& eState);

private:
	CPublicInfoMgr(void);
	CPublicInfoMgr(const CPublicInfoMgr&);
	CPublicInfoMgr& operator=(const CPublicInfoMgr&);
	~CPublicInfoMgr(void);

	static CPublicInfoMgr* pInstance;

private:
	QString m_strBasePath;			//根路径
	QString m_strIconPath;			//图标路径
	QString m_strConciseIconPath;	//简约风格图标路径
};

#endif