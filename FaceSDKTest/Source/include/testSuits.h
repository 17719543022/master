#ifndef _INCL_TEST_SUITS_H_
#define _INCL_TEST_SUITS_H_

#include <gtest/gtest.h>
#include "opencv.hpp"

using namespace cv;

class ftISDetTrack : public testing::Test{
protected:
	virtual void SetUp(){

	}
	virtual void TearDown(){
		destroyAllWindows();
	}
};

class ftISFeature : public testing::Test{
protected:
	virtual void SetUp(){

	}
	virtual void TearDown(){
		destroyAllWindows();
	}
};

class ftISCompare : public testing::Test{
protected:
	virtual void SetUp(){

	}
	virtual void TearDown(){
		destroyAllWindows();
	}
};

class ftError : public testing::Test{
protected:
	virtual void SetUp(){

	}
	virtual void TearDown(){
		destroyAllWindows();
	}
};

class ftAppliance : public testing::Test{
protected:
	virtual void SetUp(){

	}
	virtual void TearDown(){
		destroyAllWindows();
	}
};

#endif