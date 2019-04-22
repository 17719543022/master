#include "stdafx.h"
#include "CompareTest.h"
#include "CompareImp.h"
#include "Helper.h"
#include "ParamDef.h"
#include "CppUnit\TestSuite.h"
#include "CppUnit\TestCaller.h"
#include "CppUnit\TestRunner.h"
#include "CppUnit\TestResult.h"
#include "LogHelper.h"
#include "ConFigHelper.h"

#ifdef WIN32
#include <Windows.h>
#endif

CompareTest::CompareTest(const std::string& Name):
	TestCase(Name),
	_imp(nullptr)
{
}


CompareTest::~CompareTest(void)
{
}

void CompareTest::setUp()
{
	_imp = CompareImp::GetInstance();
	int ret = _imp->CreateChannel();
	assert(ret >= 0);
}

void CompareTest::tearDown()
{
	int ret = _imp->DestoryChannel();
	assert(ret == 0);
	delete _imp;
}

void CompareTest::TestCompare()
{
	int nSize = ReadFeature();
	
	unsigned long t1, t2, t = 0;
	int currect = 0, num = 0;

	for(int i = 0; i < nSize; i++)
	{
		for(int j = i; j < nSize; j++)
		{
			num++;
	#ifdef WIN32
			t1 = GetTickCount();
	#endif
			double s = 0;
			int ret = _imp->Compare(i, j, s);
			
	#ifdef WIN32
			t2 = GetTickCount();
	#endif
			if(ret != 0)
			{
				printErrMsg("1:1对比失败 特征序号：%s:%s 错误码:%d", help._vecFeaFile[i].c_str(), help._vecFeaFile[j].c_str(), ret);
			}
			else
			{
				if(i == j)
				{
					if(s - config._dCompareValue > 0.001)
					{
						currect++;
						t += (t2 - t1);
					}
					else
					{
						printErrMsg("1:1对比失败 特征序号：%s:%s source:%.3f < %.3f", help._vecFeaFile[i].c_str(), help._vecFeaFile[j].c_str(), s, config._dCompareValue);
					}
				}
				else if(i != j)
				{
					if(s - config._dCompareValue < 0.001)
					{
						currect++;
						t += (t2 - t1);
					}
					else
					{
						printErrMsg("1:1对比失败 特征序号：%s:%s source:%.3f > %.3f", help._vecFeaFile[i].c_str(), help._vecFeaFile[j].c_str(), s, config._dCompareValue);
					}
				}
			
			}
		}
	}

	_imp->releaseFeature();
	printMsg("对比次数:%d次 正确次数:%d次 正确率:%.2f%% 总耗时:%dms 平均耗时:%.3fms", num, currect, ((float)currect* 100)/num , t, (float)t/num);

}

int CompareTest::ReadPcaFeature()
{
	char* fea = new char[2*1024];
	int nSize = 0; 

	for(int i = 0; i < help._vecPcaFeaFile.size(); i++)
	{
		memset(fea, 0, 2*1024);
		int len = help.readFile(help._vecPcaFeaFile[i].c_str(), fea, 2*1024);
		if(len <= 0)
		{
			continue;
		}
	
		nSize = _imp->addFeature(fea, len);	
	}

	delete[] fea;
	return nSize;
}

int CompareTest::ReadFeature()
{
	char* fea = new char[8*1024];
	int nSize = 0; 

	for(int i = 0; i < help._vecFeaFile.size(); i++)
	{
		memset(fea, 0, 8*1024);
		int len = help.readFile(help._vecFeaFile[i].c_str(), fea, 8*1024);
		if(len <= 0)
		{
			continue;
		}
	
		nSize = _imp->addFeature(fea, len);	
	}

	delete[] fea;
	return nSize;
}

void CompareTest::TestRecognise()
{
	int nSize = ReadPcaFeature();
	int ret = _imp->importFeature();
	if(ret != 0)
	{
		printErrMsg("导入特征失败 错误码：%d", ret);
	}
	assert(ret == 0);

	unsigned long t1, t2, t = 0;
	int currect = 0, num = 0;
	int nIndex = -1;
	float fSource = 0.0;

	for(int i = 0; i < nSize; i++)
	{	
		num++;
#ifdef WIN32
		t1 = GetTickCount();
#endif
		ret = _imp->Recognise(i, nIndex, fSource);

#ifdef WIN32
		t2 = GetTickCount();
#endif


		if(ret != 0)
		{
			printErrMsg("识别失败 特征序号：%s 错误码:%d", help._vecPcaFeaFile[i].c_str(), ret);
		}
		else
		{
			if(nIndex == i && fSource - config._dRecogniseValue > 0.001)
			{
				currect++;
				t += (t2 - t1);
			}
			else
			{
				printErrMsg("识别失败 特征序号：%s 正确索引%d 返回索引%d 分数%.3f", help._vecPcaFeaFile[i].c_str(), i, nIndex, fSource);
			}
			
		}
	}

	_imp->releaseFeature();
	printMsg("识别次数:%d次 正确次数:%d次 正确率:%.2f%% 总耗时:%dms 平均耗时:%.3fms", num, currect, ((float)currect* 100)/num, t, (float)t/num);
}

void CompareTest::RunTestCompare()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("CompareTest");
	CppUnit_addTest(pSuite, CompareTest, TestCompare);
	
	CppUnit::TestResult re;
	pSuite->run(&re);
	delete pSuite;
}

void CompareTest::RunTestRecognise()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("RecogniseTest");
	CppUnit_addTest(pSuite, CompareTest, TestRecognise);
	
	CppUnit::TestResult re;
	pSuite->run(&re);
	delete pSuite;
}