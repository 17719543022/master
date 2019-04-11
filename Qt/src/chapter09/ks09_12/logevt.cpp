/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: logevt.cpp
\brief 日志事项类实现文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2019/01
*/

#include "logevt.h"
#include <QObject>


CLogEvt::CLogEvt(ELogEvt nType) : QEvent((QEvent::Type)nType)
{
}

CLogEvt::~CLogEvt()
{
}

SLog CLogEvt::getLog() const
{
	return m_log;
}

void CLogEvt::setLog(const SLog& log)
{
	m_log = log;
}

////////////////////////////////////////////////////////
QString SLog::translateLevel(ELogLevel level)
{
	switch (level)
	{
	case ELogLevel_Error:
		return QObject::tr("Error");
		break;
	case ELogLevel_Warning:
		return QObject::tr("Warning");
		break;
	case ELogLevel_Normal:
		return QObject::tr("Normal");
		break;
	default:
		break;
	}

	return QString::null;
}