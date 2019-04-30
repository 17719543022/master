#include "stdafx.h"
#include "timer.h"
#include <Windows.h>
#include <iostream>
using namespace std;

bool isTimeOut(int secondsSet)
{
	SYSTEMTIME stop;
    GetSystemTime(&stop);

	static SYSTEMTIME start = stop;

	if(stop.wMonth != start.wMonth)
	{
		return true;
	}

	if((stop.wDay    - start.wDay   )*24*60*60 \
	  +(stop.wHour   - start.wHour  )*60*60 \
	  +(stop.wMinute - start.wMinute)*60 \
	  +(stop.wSecond - start.wSecond)*1          > secondsSet)
	{
		return true;
	}

	return false;
}