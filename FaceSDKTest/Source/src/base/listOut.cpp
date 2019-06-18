#include "listOut.h"
#include <gtest/gtest.h>

void listOutDirectoryFiles(string& path, vector<string>& list)
{
	_finddata_t tFolder;
	intptr_t hFolder = _findfirst((path + "\\*.*").data(), &tFolder);
	EXPECT_TRUE(hFolder != -1);

	do{
		if (strcmp(tFolder.name, ".") == 0 || strcmp(tFolder.name, "..") == 0)
		{
			continue;
		}

		list.push_back(path + "\\" + tFolder.name);
	}while (_findnext(hFolder, &tFolder) == 0);

	_findclose(hFolder);
}

void listOutSubdirectoryFiles(string& path, string& fileName, vector<string>& list)
{
	_finddata_t tFolder;
	intptr_t hFolder = _findfirst((path + "\\*.*").data(), &tFolder);
	EXPECT_TRUE(hFolder != -1);

	do{
		if (strcmp(tFolder.name, ".") == 0 || strcmp(tFolder.name, "..") == 0)
		{
			continue;
		}

		list.push_back(path + "\\" + tFolder.name + "\\" + fileName);
	}while (_findnext(hFolder, &tFolder) == 0);

	_findclose(hFolder);
}