#pragma once
#include "CppUnit\TestCase.h"

class FeatureImp;
class FeatureTest : public CppUnit::TestCase 
{
public:
	FeatureTest(const std::string& name);
	~FeatureTest(void);

	//支持并发测试提取特征
	static void RunTest();	
	//提取特征并保持
	static void RunSave();	

	virtual void setUp();
	virtual void tearDown();

protected:
	void GetFeature();
	void GetFeatureSave();
	void TestGetFeatureSave();

private:
	FeatureImp* _imp;
};

