/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: logevt.h
\brief 日志事项类定义文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2019/01
*/

#ifndef GPLOGEVT_H
#define GPLOGEVT_H

#include <QEvent>
#include <QTime>


/// 日志级别枚举
enum ELogLevel
{
	ELogLevel_Error = 1,	/// 错误
	ELogLevel_Warning,		/// 警告
	ELogLevel_Normal,		/// 一般
};

/// 日志结构
struct SLog
{
	ELogLevel level;		/// 日志级别
	QString		msg;		/// 日志内容
	QTime		time;		/// 接收日志时间
	static QString translateLevel(ELogLevel level);
};

enum ELogEvt
{
	ELogEvt_LogOut = QEvent::User + 1,
};

class CLogEvt : public QEvent
{
public:
	/**
	* @brief 构造函数
	* @param[in] nType 事件类型
	*/
	CLogEvt(ELogEvt nType = ELogEvt_LogOut);
	
	/// 析构函数
	virtual ~CLogEvt();

	/**
	* @brief 获取日志
	* @return 日志
	*/
	SLog getLog() const;

	/**
	* @brief 设置日志
	* @param[in] log 日志
	*/
	void setLog(const SLog& log);
private:
	SLog m_log;
};

#endif //GPLOGEVT_H