#ifndef _INCL_TEST_SUITS_H_
#define _INCL_TEST_SUITS_H_

#include <gtest/gtest.h>
#include "opencv.hpp"

using namespace cv;

class ftDetect : public testing::Test{
protected:
	virtual void SetUp(){

	}
	virtual void TearDown(){
		destroyAllWindows();
	}
};

class ftFeature : public testing::Test{
protected:
	virtual void SetUp(){

	}
	virtual void TearDown(){
		destroyAllWindows();
	}
};

class ftCompare : public testing::Test{
protected:
	virtual void SetUp(){

	}
	virtual void TearDown(){
		destroyAllWindows();
	}
};

#endif