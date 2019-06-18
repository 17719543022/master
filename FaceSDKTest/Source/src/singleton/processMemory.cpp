#include "processMemory.h"
#include <windows.h>
#include <Psapi.h>

unsigned long long ProcessMemory::getProcessMemory(){
	unsigned long long mm = 0;
//#ifdef WIN32
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
//#endif
	return mm;
}