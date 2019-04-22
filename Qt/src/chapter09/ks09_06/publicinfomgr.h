
#ifndef _PUBLICINFOMGR_H_
#define _PUBLICINFOMGR_H_

#include "uitypedef.h"

class CPublicInfoMgr
{
public:
	//����Ĵ���������
	static CPublicInfoMgr* instance(void);
	void destroy();

	//! ��û����ĸ�·����ICCSHOMEָ����
	virtual QString getBasePath();

	//! ��û�����ͼ��Ŀ¼
	virtual QString getIconPath();

	//! ��ȡƤ�����·��
	virtual QString getConciseIconPath();

	//! ���ָ�����Ƶ���ʽ��Ϣ
	virtual QString getStyleSheet(const QString& name);

	// @method	: setIconPath
	// @comm	: ����ͼƬ·��
	virtual void setIconPath(const QString& strPath);

	// @method	: setConcisePath
	// @comm	: ����Ƥ�����·��
	virtual void setConciseIconPath(const QString& strPath = 0);

	//��ȡͼƬpathname
	virtual QString getUiIconPathName(const QString& strIcon, const EUIState& eState);

private:
	CPublicInfoMgr(void);
	CPublicInfoMgr(const CPublicInfoMgr&);
	CPublicInfoMgr& operator=(const CPublicInfoMgr&);
	~CPublicInfoMgr(void);

	static CPublicInfoMgr* pInstance;

private:
	QString m_strBasePath;			//��·��
	QString m_strIconPath;			//ͼ��·��
	QString m_strConciseIconPath;	//��Լ���ͼ��·��
};

#endif