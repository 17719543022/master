#ifdef WIN32
#include <Windows.h>
#endif
#include "log_format.h"
#include "common.h"

bool logSwitch = false;

int switchPrintf(const char* format, ...)
{
	return 0;
}

int denominator = 0;

#ifdef WIN32
	SYSTEMTIME	tStart, tStop;
#endif
#ifdef LINUX
	time_t tStart, tStop;
#endif
