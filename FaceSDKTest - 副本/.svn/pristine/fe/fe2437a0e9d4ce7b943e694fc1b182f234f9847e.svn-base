#include "stdafx.h"
#include "MultiThreadTest.h"
#include "ParamDef.h"
#include "DetTrackTest.h"
#include "FeatureTest.h"
#include "CompareTest.h"
#include "ProgressBar.h"
#include "Poco\RunnableAdapter.h"
#include "LogHelper.h"
#include "Helper.h"
#include "ConFigHelper.h"
#include <iostream>

MultiThreadTest::MultiThreadTest(void):
	_thPool(1, MAXTHREADNUM)
{
}


MultiThreadTest::~MultiThreadTest(void)
{
}

void MultiThreadTest::MultiTestDetTrack(int nThreadNum/* = 1*/)
{
	nThreadNum = nThreadNum > MAXTHREADNUM ? MAXTHREADNUM : nThreadNum;
	printMsg("====开始人脸检测测试, 线程数量:%d ====", nThreadNum);
	
	Poco::RunnableAdapter<MultiThreadTest> ra(*this, &MultiThreadTest::TestDetTrack);
	for(int i = 0; i < nThreadNum; i++)
	{
		try
		{
			_thPool.start(ra);
		}
		catch(Poco::NoThreadAvailableException&)
		{
			std::cout<<"没有可用线程啦！"<<std::endl;
		}
	}

	_thPool.joinAll();
	printMsg("人脸检测测试完成\n");
}

void MultiThreadTest::MultiTestGetFeature(int nThreadNum /*= 1*/)
{
	nThreadNum = nThreadNum > MAXTHREADNUM ? MAXTHREADNUM : nThreadNum;
	printMsg("====开始特征提取测试, 线程数量:%d ====", nThreadNum);

	Poco::RunnableAdapter<MultiThreadTest> ra(*this, &MultiThreadTest::TestGetFeature);
	
	for(int i = 0; i < nThreadNum; i++)
	{
		try
		{
			_thPool.start(ra);
		}
		catch(Poco::NoThreadAvailableException&)
		{
			std::cout<<"没有可用线程啦！"<<std::endl;
		}
	}

	_thPool.joinAll();
	printMsg("特征提取测试完成\n");
}

void MultiThreadTest::TestGetFeatureAndSave()
{
	printMsg("====开始特征提取降维本地保存，线程数量 1 ====");
	FeatureTest::RunSave();
	
	//读取特征路径
	int ret = help.getAllFile(config._strFeaPath, help._vecFeaFile, config._nMaxImgNum);
	if(ret != 0)
	{
		printErrMsg("枚举%s路径失败", config._strImgPath);
	}
	//读取PCA特征路径
	ret = help.getAllFile(config._strPcaFeaPath, help._vecPcaFeaFile, config._nMaxImgNum);
	if(ret != 0)
	{
		printErrMsg("枚举%s路径失败", config._strImgPath);
	}

	printMsg("特征提取降维本地保存完成\n");
}

void MultiThreadTest::MultiTestCompare(int nThreadNum /*= 1*/)
{
	nThreadNum = nThreadNum > MAXTHREADNUM ? MAXTHREADNUM : nThreadNum;
	printMsg("====开始1:1测试, 线程数量:%d ====", nThreadNum);

	Poco::RunnableAdapter<MultiThreadTest> ra(*this, &MultiThreadTest::TestCompare);
	
	for(int i = 0; i < nThreadNum; i++)
	{
		try
		{
			_thPool.start(ra);
		}
		catch(Poco::NoThreadAvailableException&)
		{
			std::cout<<"没有可用线程啦！"<<std::endl;
		}
	}

	_thPool.joinAll();
	printMsg("1:1测试完成\n");
}

void MultiThreadTest::MultiTestRecognise(int nThreadNum /*= 1*/)
{
	nThreadNum = nThreadNum > MAXTHREADNUM ? MAXTHREADNUM : nThreadNum;
	printMsg("====开始识别测试 线程数量:%d ====", nThreadNum);

	Poco::RunnableAdapter<MultiThreadTest> ra(*this, &MultiThreadTest::TestRecognise);
	
	for(int i = 0; i < nThreadNum; i++)
	{
		try
		{
			_thPool.start(ra);
		}
		catch(Poco::NoThreadAvailableException&)
		{
			std::cout<<"没有可用线程啦！"<<std::endl;
		}
	}

	_thPool.joinAll();
	printMsg("识别测试完成\n");
}


void MultiThreadTest::TestDetTrack()
{
	DetTrackTest::RunTest();
}

void MultiThreadTest::TestGetFeature()
{
	FeatureTest::RunTest();
}

void MultiThreadTest::TestCompare()
{
	CompareTest::RunTestCompare();
}

void MultiThreadTest::TestRecognise()
{
	CompareTest::RunTestRecognise();
}