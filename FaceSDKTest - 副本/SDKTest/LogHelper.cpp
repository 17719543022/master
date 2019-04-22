#include "stdafx.h"
#include "Helper.h"
#include "LogHelper.h"
#include "SDK\ISCompare.h"
#include "SDK\ISDetTrack.h"
#include "SDK\ISFeature.h"
#include "ConFigHelper.h"
#include <stdarg.h>
#include <iostream>
#include <iomanip>
#include <fstream>

void initLogFile()
{
	std::ofstream ostr(config._strTextReport.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
	ostr.close();

	if(config._strErrLog.length() > 0)
	{
		ostr.open(config._strErrLog.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
		ostr.close();
	}

	if(help.check64())
	{
		printMsg("64位程序");
	}
	else
	{
		printMsg("32位程序");
	}
	
	printMsg("Compare  Version:%s", ISGetCompareVersionInfo());
	printMsg("DetTrack Version:%s", ISGetDetTrackVersionInfo());
	printMsg("Feature  Version:%s", ISGetFeatureVersionInfo());
}

void printMsg(const char* format, ...)
{
	char buf[1024] = {0};
	va_list ap;
	va_start(ap, format);
	vsprintf(buf, format, ap);
	int thId = help.getCurrentThreadId();
	
	//输出到控制台
	std::cout<<"线程["<< std::setw(5)<< thId <<"]"<<"  "
		<< buf <<std::endl;

	//输出到文件
	std::ofstream ostr(config._strTextReport.c_str(), std::ios::out | std::ios::binary | std::ios::app);
	if(ostr.is_open())
	{
		ostr<<"线程["<< std::setw(5)<< thId <<"]" <<"  "
		<< buf <<std::endl;
	}
}

void printErrMsg(const char* format, ...)
{
	if(config._strErrLog.length() <= 0)
	{
		return ;
	}

	char buf[1024] = {0};
	va_list ap;
	va_start(ap, format);
	vsprintf(buf, format, ap);
	int thId = help.getCurrentThreadId();

	//输出到文件
	std::ofstream ostr(config._strErrLog.c_str(), std::ios::out | std::ios::binary | std::ios::app);
	if(ostr.is_open())
	{
		ostr<<"线程["<< std::setw(5)<< thId <<"]" <<"  "
		<< buf <<std::endl;
	}
}
