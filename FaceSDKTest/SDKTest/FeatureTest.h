#pragma once
#include "CppUnit\TestCase.h"

class FeatureImp;
class FeatureTest : public CppUnit::TestCase 
{
public:
	FeatureTest(const std::string& name);
	~FeatureTest(void);

	//֧�ֲ���������ȡ����
	static void RunTest();	
	//��ȡ����������
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

