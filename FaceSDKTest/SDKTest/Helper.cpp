#include "stdafx.h"
#include "Helper.h"
#include <fstream>
#include <io.h>

#ifdef WIN32
#include <Windows.h>
#include <psapi.h>
#pragma comment(lib,"Psapi.lib")
typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
#else
#include <pthread.h>
#endif

Helper help;

Helper::Helper(void)
{
}


Helper::~Helper(void)
{
}

int Helper::readFile(const char* path, char* buffer, int bufferLen)
{
	std::ifstream istr(path, std::ios::in|std::ios::binary);
	if(!istr.is_open())
	{
		return -1;
	}

	istr.seekg(0, std::ios::end);
	int pos = istr.tellg();
	if(pos > bufferLen)
	{
		istr.close();
		return -2;
	}

	istr.seekg(0,std::ios::beg);
	memset(buffer , 0, bufferLen);
	istr.read(buffer, pos);
	int count = istr.gcount();

	istr.close();
	return count;
}

int Helper::writeFile(const char* path, char* buffer, int bufferLen)
{
	std::ofstream ostr(path, std::ios::out | std::ios::binary);
	if(!ostr.is_open())
	{
		return -1;
	}

	ostr.write(buffer, bufferLen);
	return 0;
}

int Helper::makeDir(const char* path)
{
	int ret = -1;
#ifdef WIN32
	ret = CreateDirectoryA(path, NULL);
#endif
	return ret;
}

bool Helper::check64()
{
	bool b64 = true;
#ifdef WIN32
	BOOL bIsWow64 = FALSE;
	//IsWow64Process is not available on all supported versions of Windows.
	//Use GetModuleHandle to get a handle to the DLL that contains the function
	//and GetProcAddress to get a pointer to the function if available.
	LPFN_ISWOW64PROCESS fnIsWow64Process;
	fnIsWow64Process = (LPFN_ISWOW64PROCESS) GetProcAddress(
	GetModuleHandle(TEXT("kernel32")),"IsWow64Process");
	if(NULL != fnIsWow64Process)
	{
		if (!fnIsWow64Process(GetCurrentProcess(),&bIsWow64)){
			//handle error
		}
	}

	if(bIsWow64)
	{
		b64 = false;
	}
#endif
	return b64;
}

int Helper::getAllFile(std::string path, std::vector<std::string>& vecFile, int nMax)
{
	//文件句柄  
	intptr_t   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getAllFile(p.assign(path).append("\\").append(fileinfo.name), vecFile, nMax);
			}
			else
			{
				vecFile.push_back(p.assign(path).append("\\").append(fileinfo.name));
				if(vecFile.size() >= nMax)
				{
					break;
				}
			}

		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}
	else
	{
		return -1;
	}

	return 0;
}

uint32_t Helper::getCurrentThreadId()
{
	uint32_t id = -1;
#ifdef WIN32
	id = GetCurrentThreadId();
#endif
	return id;
}

uint64_t Helper::getCurrentMemUse()
{
	uint64_t mm = 0;
#ifdef WIN32
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
#endif
	return mm;
}
