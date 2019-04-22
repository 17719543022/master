
/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: customevent.h
\brief  CCustomEvent

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/

#pragma once

#include <QEvent>
#include <QString>

class CCustomEvent : public QEvent {
public:
	CCustomEvent() :QEvent(QEvent::Type(QEvent::User+1)){ ; }
	~CCustomEvent() { ; }

	/**
	* @brief 保存文件名，不带路径
	* @param[in] strFileName  文件名
	* @return void
	*/
	void setFileName(const QString & strFileName) { m_strFileName = strFileName; }
	/**
	* @brief 获取文件名，不带路径
	* @param[in] srFileName  文件名
	* @return 文件名
	*/
	QString getFileName() { return m_strFileName; }
private:
	QString m_strFileName;

};