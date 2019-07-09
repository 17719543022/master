/*
 * Linux/Windows 系统高精度计时器
 */
 
#ifndef __LINUX_WINDOWS_TIMER_H__
#define __LINUX_WINDOWS_TIMER_H__
 
#ifdef WIN32
	#include <Windows.h>
#elif linux
	#include <sys/time.h>
#endif
 
class Timer
{
public:
	Timer();
	void   start();
	double stop();
 
private:
#ifdef  WIN32
	double dSystemFreq; 
	BOOL   flag;
	double dStartTime;
	double dStopTime;
#elif  linux
	struct timeval tvStart;
	struct timeval tvStop;
#endif
};

#endif
