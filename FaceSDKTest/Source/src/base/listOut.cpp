#ifdef LINUX
#include <dirent.h>
#endif
#include "listOut.h"
#include <gtest/gtest.h>
#include "listOut.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <vector>
#include "log_format.h"

#ifdef WIN32
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
#endif

#ifdef LINUX
void listOutDirectoryFiles(string& path, vector<string>& list)
{
	DIR *dir;
	if (NULL == (dir = opendir(path.data())))
	{
		ERR_LOG("opendir directory fail.");
		return;
	}

	struct dirent *d_ent;
	char fullpath[128];

	while ((d_ent = readdir(dir)) != NULL)
	{
		if(strcmp(d_ent->d_name, ".")==0 || strcmp(d_ent->d_name, "..")==0){
			continue;
		}

		list.push_back(path + "/" + d_ent->d_name);
	}

	closedir(dir);
}

void listOutSubdirectoryFiles(string& path, string& fileName, vector<string>& list)
{
	DIR *dir;
	if (NULL == (dir = opendir(path.data())))
	{
		ERR_LOG("opendir directory fail.");
		return;
	}

	struct dirent *d_ent;
	char fullpath[128];

	while ((d_ent = readdir(dir)) != NULL)
	{
		if(strcmp(d_ent->d_name, ".")==0 || strcmp(d_ent->d_name, "..")==0){
			continue;
		}

		list.push_back(path + "/" + d_ent->d_name + "/" + fileName);
	}

	closedir(dir);
}
#endif

