/*
 * rmDir.cpp
 *
 *  Created on: Jun 17, 2019
 *      Author: liuyong
 */

#ifdef LINUX

#include "rmDir.h"
#include <dirent.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

using namespace std;

int rmDir(string path)
{
	DIR* dirp = opendir(path.c_str());
	if(!dirp)
	{
		return -1;
	}
	struct dirent *dir;
	struct stat st;
	while((dir = readdir(dirp)) != NULL)
	{
		if(strcmp(dir->d_name,".") == 0
				|| strcmp(dir->d_name,"..") == 0)
		{
			continue;
		}
		string sub_path = path + '/' + dir->d_name;
		if(lstat(sub_path.c_str(),&st) == -1)
		{
			continue;
		}
		if(S_ISDIR(st.st_mode))
		{
			if(rmDir(sub_path) == -1)
			{
				closedir(dirp);
				return -1;
			}
			rmdir(sub_path.c_str());
		}
		else if(S_ISREG(st.st_mode))
		{
			unlink(sub_path.c_str());
		}
		else
		{
			continue;
		}
	}
	if(rmdir(path.c_str()) == -1)
	{
		closedir(dirp);
		return -1;
	}
	closedir(dirp);

	return 0;
}

#endif
