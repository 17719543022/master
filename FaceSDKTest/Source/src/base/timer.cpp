#ifdef WIN32
#include <Windows.h>
#endif
#include "timer.h"
#include <iostream>
using namespace std;

#ifdef WIN32
bool isTimeOut(int secondsSet)
{
	SYSTEMTIME stop;
    GetSystemTime(&stop);

	static SYSTEMTIME start = stop;

	if(stop.wMonth != start.wMonth)
	{
		return true;
	}

	if((stop.wDay - start.wDay)*24*60*60 \
	  +(stop.wHour - start.wHour)*60*60 \
	  +(stop.wMinute - start.wMinute)*60 \
	  +(stop.wSecond - start.wSecond)*1 > secondsSet)
	{
		return true;
	}

	return false;
}
#endif

#ifdef LINUX
bool isTimeOut(int secondsSet)
{
	static time_t tStart = time((time_t *)NULL);

	if(time((time_t *)NULL) - tStart > secondsSet)
	{
		return true;
	}

	return false;
}
#endif
