#ifndef _INCL_LIST_OUT_H_
#define _INCL_LIST_OUT_H_

#include <vector>
#include <string>
using namespace std;

void listOutDirectoryFiles(string& path, vector<string>& list);
void listOutSubdirectoryFiles(string& path, string& fileName, vector<string>& list);

#endif