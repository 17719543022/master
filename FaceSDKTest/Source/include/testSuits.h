#ifndef _INCL_TEST_SUITS_H_
#define _INCL_TEST_SUITS_H_

#include <gtest/gtest.h>
#include "opencv.hpp"

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

class ftInterface : public testing::Test{
protected:
	virtual void SetUp(){

	}
	virtual void TearDown(){
		destroyAllWindows();
	}
};

class ftMultiThread : public testing::Test{
protected:
	virtual void SetUp(){

	}
	virtual void TearDown(){
		destroyAllWindows();
	}
};

#endif