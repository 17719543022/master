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
	printMsg("====��ʼ����������, �߳�����:%d ====", nThreadNum);
	
	Poco::RunnableAdapter<MultiThreadTest> ra(*this, &MultiThreadTest::TestDetTrack);
	for(int i = 0; i < nThreadNum; i++)
	{
		try
		{
			_thPool.start(ra);
		}
		catch(Poco::NoThreadAvailableException&)
		{
			std::cout<<"û�п����߳�����"<<std::endl;
		}
	}

	_thPool.joinAll();
	printMsg("�������������\n");
}

void MultiThreadTest::MultiTestGetFeature(int nThreadNum /*= 1*/)
{
	nThreadNum = nThreadNum > MAXTHREADNUM ? MAXTHREADNUM : nThreadNum;
	printMsg("====��ʼ������ȡ����, �߳�����:%d ====", nThreadNum);

	Poco::RunnableAdapter<MultiThreadTest> ra(*this, &MultiThreadTest::TestGetFeature);
	
	for(int i = 0; i < nThreadNum; i++)
	{
		try
		{
			_thPool.start(ra);
		}
		catch(Poco::NoThreadAvailableException&)
		{
			std::cout<<"û�п����߳�����"<<std::endl;
		}
	}

	_thPool.joinAll();
	printMsg("������ȡ�������\n");
}

void MultiThreadTest::TestGetFeatureAndSave()
{
	printMsg("====��ʼ������ȡ��ά���ر��棬�߳����� 1 ====");
	FeatureTest::RunSave();
	
	//��ȡ����·��
	int ret = help.getAllFile(config._strFeaPath, help._vecFeaFile, config._nMaxImgNum);
	if(ret != 0)
	{
		printErrMsg("ö��%s·��ʧ��", config._strImgPath);
	}
	//��ȡPCA����·��
	ret = help.getAllFile(config._strPcaFeaPath, help._vecPcaFeaFile, config._nMaxImgNum);
	if(ret != 0)
	{
		printErrMsg("ö��%s·��ʧ��", config._strImgPath);
	}

	printMsg("������ȡ��ά���ر������\n");
}

void MultiThreadTest::MultiTestCompare(int nThreadNum /*= 1*/)
{
	nThreadNum = nThreadNum > MAXTHREADNUM ? MAXTHREADNUM : nThreadNum;
	printMsg("====��ʼ1:1����, �߳�����:%d ====", nThreadNum);

	Poco::RunnableAdapter<MultiThreadTest> ra(*this, &MultiThreadTest::TestCompare);
	
	for(int i = 0; i < nThreadNum; i++)
	{
		try
		{
			_thPool.start(ra);
		}
		catch(Poco::NoThreadAvailableException&)
		{
			std::cout<<"û�п����߳�����"<<std::endl;
		}
	}

	_thPool.joinAll();
	printMsg("1:1�������\n");
}

void MultiThreadTest::MultiTestRecognise(int nThreadNum /*= 1*/)
{
	nThreadNum = nThreadNum > MAXTHREADNUM ? MAXTHREADNUM : nThreadNum;
	printMsg("====��ʼʶ����� �߳�����:%d ====", nThreadNum);

	Poco::RunnableAdapter<MultiThreadTest> ra(*this, &MultiThreadTest::TestRecognise);
	
	for(int i = 0; i < nThreadNum; i++)
	{
		try
		{
			_thPool.start(ra);
		}
		catch(Poco::NoThreadAvailableException&)
		{
			std::cout<<"û�п����߳�����"<<std::endl;
		}
	}

	_thPool.joinAll();
	printMsg("ʶ��������\n");
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