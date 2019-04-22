#include "stdafx.h"
#include "DetTrackTest.h"
#include "DetTrackImp.h"
#include "CppUnit\TestSuite.h"
#include "CppUnit\TestCaller.h"
#include "CppUnit\TestRunner.h"
#include "CppUnit\TestResult.h"
#include "Helper.h"
#include "LogHelper.h"
#include "ParamDef.h"
#include "ConFigHelper.h"
#include <iostream>

#ifdef WIN32
#include <Windows.h>
#endif

DetTrackTest::DetTrackTest(const std::string& name):
	CppUnit::TestCase(name),
	_imp(nullptr)
{
}

DetTrackTest::~DetTrackTest(void)
{
}

void DetTrackTest::setUp()
{
	_imp = DetTrackImp::GetInstance();
	int ret = _imp->CreateChannel();
	assert(ret >= 0);
}

void DetTrackTest::tearDown()
{
	if(_imp != nullptr)
	{
		_imp->DestoryChannel();
		delete _imp;
	}
}

void DetTrackTest::TestFaceDetect()
{
	unsigned long t1, t2;
	unsigned long total = 0;
	int faceNum = 0 , currect = 0, imgNum = 0;
	char* file = new char[1024*1024];

	for(int i = 0; i < help._vecImgFile.size(); i++)
	{
		int len = help.readFile(help._vecImgFile[i].c_str(), file, 1024*1024);
		if( len > 0)
		{
			imgNum++;
#ifdef WIN32
	t1 = GetTickCount();
#endif
			int ret = _imp->FaceDetect(file, len, faceNum);
			
#ifdef WIN32
	t2 = GetTickCount();
#endif
			assert(ret >= 0);
			if(faceNum == 1)
			{
				currect++;
			}

			total += (t2 - t1);
		}
	}

	delete[] file;
	printMsg("检测图片:%d张 正确识别:%d次 正确率:%.2f%% 总耗时:%dms 平均耗时:%.3fms", imgNum, currect, ((float)currect*100)/imgNum, total, (float)total/imgNum);
}

CppUnit::Test* DetTrackTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("DetTrackTest");
	CppUnit_addTest(pSuite, DetTrackTest, TestFaceDetect);
	return pSuite;
}

void DetTrackTest::RunTest()
{
	CppUnit::TestResult re;
	CppUnit::Test* pSuite = DetTrackTest::suite();
	pSuite->run(&re);
	delete pSuite;
}