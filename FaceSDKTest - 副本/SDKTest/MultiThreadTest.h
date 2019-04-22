#pragma once
#include "Poco\ThreadPool.h"

class MultiThreadTest
{
public:
	MultiThreadTest(void);
	~MultiThreadTest(void);

	void MultiTestDetTrack(int nThreadNum = 1);

	void MultiTestGetFeature(int nThreadNum = 1);

	void TestGetFeatureAndSave();

	void MultiTestCompare(int nThreadNum = 1);

	void MultiTestRecognise(int nThreadNum = 1);
	

protected:
	void TestDetTrack();
	void TestGetFeature();
	void TestRecognise();
	void TestCompare();

private:
	Poco::ThreadPool _thPool;
};

