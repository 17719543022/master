#include "stdafx.h"
#include "FeatureTest.h"
#include "FeatureImp.h"
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

FeatureTest::FeatureTest(const std::string& name):
	TestCase(name),
	_imp(nullptr)
{
}


FeatureTest::~FeatureTest(void)
{
}

void FeatureTest::setUp()
{
	_imp = FeatureImp::GetInstance();
	int ret = _imp->CreatureChannel();
	assert( ret >= 0);
}

void FeatureTest::tearDown()
{
	if(_imp != nullptr)
	{
		_imp->DestoryChannel(); 
		delete _imp;
	}
}

void FeatureTest::GetFeature()
{
	unsigned long t1, t2;
	unsigned long total = 0;
	int currect = 0, imgNum = 0;
	char* file = new char[1024*1024];
	char path[64] = {0};
		
	for(int i = 0; i < help._vecImgFile.size(); i++)
	{
		int len = help.readFile(help._vecImgFile[i].c_str(), file, 1024*1024);
		if( len > 0)
		{
			imgNum++;
#ifdef WIN32
			t1 = GetTickCount();
#endif
			int ret = _imp->GetFeature(file, len);
			
#ifdef WIN32
			t2 = GetTickCount();
#endif

			if(ret == 0)
			{
				currect++;
			}
			else
			{
				printErrMsg("ͼƬ:%d/1.jpg ��ȡ����ʧ��;������:%d", i, ret);
			}

			total += (t2 - t1);
		}
	}

	delete[] file;
	printMsg("��ȡͼƬ:%d�� ��ȷ��ȡ:%d�� ��ȷ��:%.2f%% �ܺ�ʱ:%dms ƽ����ʱ:%.3fms", imgNum, currect, ((float)currect*100)/imgNum, total, (float)total/imgNum);
}

void FeatureTest::GetFeatureSave()
{
	char* file = new char[1024*1024];
	char feaPath[64] = {0};
	char pcaPath[64] = {0};
	int currect = 0, currectPca = 0, imgNum = 0, saveNum = 0;
	
	for(int i = 0; i < help._vecImgFile.size(); i++)
	{
		int len = help.readFile(help._vecImgFile[i].c_str(), file, 1024*1024);
		if( len > 0)
		{
			imgNum++;
			int ret = _imp->GetFeature(file, len);
			if(ret == 0)
			{
				currect++;
				ret = _imp->GetPcaFeature();
				if(ret == 0)
				{
					currectPca++;
					sprintf(feaPath, "%s/%d.fea", config._strFeaPath.c_str(), i);
					sprintf(pcaPath, "%s/%d.fea", config._strPcaFeaPath.c_str(), i);
					ret = _imp->SaveFeature(feaPath, pcaPath);
					if(ret == 0)
					{
						saveNum++;
					}
					else
					{
						printErrMsg("����ͼ��%d.jpg ����ʧ��", i);
					}
				}
				else
				{
					printErrMsg("ͼƬ:%d.jpg ������ά����ʧ��;������:%d", i, ret);
				}
				
			}
			else
			{
				printErrMsg("ͼƬ:%d.jpg ��ȡ����ʧ��;������:%d", i, ret);
			}
		}
	}

	delete[] file;
	printMsg("��ȡͼƬ:%d�� ��ȷ��ȡ:%d�� ��ȷ��ά����:%d�� �ֱ𱣴�������PCA����:%d��", imgNum, currect, currectPca, saveNum);
}

void FeatureTest::TestGetFeatureSave()
{
	GetFeatureSave();
}

void FeatureTest::RunTest()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("FeatureTest");
	CppUnit_addTest(pSuite, FeatureTest, GetFeature);
	CppUnit::TestResult re;
	pSuite->run(&re);
	delete pSuite;
}

void FeatureTest::RunSave()
{
	CppUnit::TestResult re;
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("FeatureTest");
	CppUnit_addTest(pSuite, FeatureTest, TestGetFeatureSave);
	pSuite->run(&re);
	delete pSuite;
}