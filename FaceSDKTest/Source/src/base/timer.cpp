#include "timer.h"
#include <stddef.h> 
#ifdef  WIN32
	#include <Windows.h>
#elif  linux
	#include <sys/time.h>
#endif
#include <iostream>
using namespace std;
 
#ifdef WIN32
Timer::Timer()
{
	LARGE_INTEGER sysFreq;
	flag = QueryPerformanceFrequency( &sysFreq );
	if ( flag )
	{
		dSystemFreq = (double)sysFreq.QuadPart;
	}
}
 
void Timer::start()
{
	LARGE_INTEGER t;
	flag &= QueryPerformanceCounter( &t );
	if ( !flag )
		return;
	dStartTime = (double)t.QuadPart;
}
 
double Timer::stop()
{
	LARGE_INTEGER t;
	flag &= QueryPerformanceCounter( &t );
 
	if ( !flag )
		return -1.0;
	
	dStopTime = (double)t.QuadPart;
	return 1000.0 * ( dStopTime - dStartTime ) / dSystemFreq;
}
 
#elif  linux
 
Timer::Timer(){}
 
void Timer::start()
{
	gettimeofday( &tvStart, NULL );
}
 
double Timer::stop()
{
	gettimeofday( &tvStop, NULL );
	return 1000.0 * (double)(tvStop.tv_sec - tvStart.tv_sec)
		+ (double)(tvStop.tv_usec - tvStart.tv_usec)/1000.0;
}
 
#endif

