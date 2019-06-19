#ifdef WIN32
#include <windows.h>
#include <Psapi.h>
#endif
#include "processMemory.h"

#ifdef WIN32
unsigned long long ProcessMemory::getProcessMemory(){
	unsigned long long mm = 0;

	HANDLE handle=GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS_EX pmc = {0};
	int a = sizeof(pmc);
	if (!GetProcessMemoryInfo(handle,(PROCESS_MEMORY_COUNTERS*)&pmc,sizeof(pmc)))
	{
		DWORD errCode = GetLastError();
	}
	else
	{
		mm = pmc.PrivateUsage/1024;
	}

	return mm;
}
#endif

#ifdef LINUX
unsigned long long ProcessMemory::getProcessMemory(){
	return -1;
}
#endif
