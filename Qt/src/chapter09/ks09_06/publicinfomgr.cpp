
#include <qfile.h>
#include <QTextStream>

#include "publicinfomgr.h"

//�ྲ̬��Ա������ʼ��
CPublicInfoMgr* CPublicInfoMgr::pInstance = NULL;

CPublicInfoMgr* CPublicInfoMgr::instance(void)
{
	if (NULL == pInstance)
	{
		pInstance = new CPublicInfoMgr;
	}
	return pInstance;
}

void CPublicInfoMgr::destroy()
{
	if (NULL != pInstance)
	{
		delete pInstance;
		pInstance = NULL;
	}
}

CPublicInfoMgr::CPublicInfoMgr(void)
{
}

CPublicInfoMgr::~CPublicInfoMgr(void)
{
}

//��û����ĸ�·����ICCSHOMEָ����
QString CPublicInfoMgr::getBasePath()
{
	if (m_strBasePath.isEmpty())
	{
		m_strBasePath = qgetenv("ICCSHOME");
		m_strBasePath.replace('\\', '/');
	}
	return m_strBasePath;
}

//��û�����ͼ���Ŀ¼
QString CPublicInfoMgr::getIconPath()
{

	if (m_strIconPath.isEmpty())
		m_strIconPath = getBasePath() + "/system/icons/";

	return m_strIconPath;
}

QString CPublicInfoMgr::getConciseIconPath()
{
	return m_strConciseIconPath;
}

QString CPublicInfoMgr::getStyleSheet(const QString& name)
{
	QString strContent;
	QString fileName = getBasePath() + QString("/system/drawqss/%1.qss").arg(name);
	QFile file(fileName);
	if (file.open(QIODevice::ReadOnly))
	{
		QTextStream ts(&file);
		strContent = ts.readAll();
		file.close();
	}
	return strContent;
}

void CPublicInfoMgr::setIconPath(const QString& strPath)
{
	m_strIconPath = getBasePath() + "/system/icons/" + strPath + "/";
}

void CPublicInfoMgr::setConciseIconPath(const QString& strPath)
{
	m_strConciseIconPath = getIconPath() + strPath + "/";
}

//��ȡͼƬpathname
QString CPublicInfoMgr::getUiIconPathName(const QString& strIcon, const EUIState& eState)
{
	QString retString;
	QString suffixString;
	switch (eState)
	{
	case eState_SingleState:
		suffixString = SingleStateIcon;
		break;
	case eState_Normal:
		suffixString = NormalIcon;
		break;
	case eState_Over:
		suffixString = OverIcon;
		break;
	case eState_Down:
		suffixString = DownIcon;
		break;
	case eState_Unable:
		suffixString = UnableIcon;
		break;
	default:
		break;
	}
	retString = getIconPath() + strIcon + suffixString;
	return retString;
}