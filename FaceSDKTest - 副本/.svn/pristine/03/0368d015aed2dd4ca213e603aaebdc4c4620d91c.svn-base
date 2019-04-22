#pragma once
#include "CppUnit\TestCase.h"

class CompareImp;
class CompareTest : public CppUnit::TestCase
{
public:
	CompareTest(const std::string& Name);
	~CompareTest(void);

	static void RunTestCompare();
	static void RunTestRecognise();
	virtual void setUp();
	virtual void tearDown();

protected:
	void TestCompare();
	void TestRecognise();
	int  ReadFeature();
	int  ReadPcaFeature();

private:
	CompareImp* _imp;
};

