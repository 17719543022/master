﻿/*!
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: sendthread.h
\brief  CSendThread

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/
#pragma once

#include <QThread>

class CSendThread : public QThread {
public:
    CSendThread();
	~CSendThread();

	virtual void run();

private:
};