#pragma once
#include "CppUnit\TestCase.h"

class DetTrackImp;
class DetTrackTest : public CppUnit::TestCase 
{
public:
	DetTrackTest(const std::string& name);
	~DetTrackTest(void);

	static void RunTest();
	virtual void setUp();
	virtual void tearDown();

protected:
	static CppUnit::Test* suite();
	void TestFaceDetect();

private:
	DetTrackImp* _imp;
};


