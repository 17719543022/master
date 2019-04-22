#pragma once
#include <stdint.h>
#include <vector>
#include <string>

class Helper
{
public:
	Helper(void);
	~Helper(void);

	int readFile(const char* path, char* buffer, int bufferLen);

	int writeFile(const char* path, char* buffer, int bufferLen);

	int makeDir(const char* path);

	bool check64();

	int getAllFile(std::string path, std::vector<std::string>& vecFile, int nMax);

	uint32_t getCurrentThreadId();

	uint64_t getCurrentMemUse();

public:
	std::vector<std::string> _vecImgFile;
	std::vector<std::string> _vecFeaFile;
	std::vector<std::string> _vecPcaFeaFile;
};

extern Helper help;

