// SDKTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MultiThreadTest.h"
#include "LogHelper.h"
#include "ConFigHelper.h"
#include "Helper.h"
#include <stdio.h>

int init()
{
	config.init();
	initLogFile();
	help.makeDir(config._strFeaPath.c_str());
	help.makeDir(config._strPcaFeaPath.c_str());
	int ret = help.getAllFile(config._strImgPath, help._vecImgFile, config._nMaxImgNum);
	if(ret != 0)
	{
		printErrMsg("枚举%s路径失败", config._strImgPath);
	}
	return 0;
}

int unInit()
{
	help._vecFeaFile.clear();
	help._vecImgFile.clear();
	help._vecPcaFeaFile.clear();
	return 0;
}
 
int _tmain(int argc, _TCHAR* argv[])
{
	init();
	uint64_t mm1 = help.getCurrentMemUse();
	
	MultiThreadTest t;
	t.MultiTestDetTrack(config._nDetectThreadNum);
	t.MultiTestGetFeature(config._nGetFeaThreadNum);
	t.TestGetFeatureAndSave();
	t.MultiTestCompare(config._nCompareThreadNum);
	t.MultiTestRecognise(config._nRecogniseThreadNum);

	unInit();
	uint64_t mm2 = help.getCurrentMemUse();
	printMsg("测试完成内存变化%lluKB", (mm2 - mm1));
	system("pause");
	return 0;
}

