#ifndef _INCL_TEST_SUITS_H_
#define _INCL_TEST_SUITS_H_

#ifdef WIN32
#include "opencv.hpp"
#endif
#ifdef LINUX
#include "opencv2/opencv.hpp"
#endif
#include <gtest/gtest.h>
#include "processMemory.h"
#include "common.h"

using namespace cv;
using namespace std;

class ftISDetTrack : public testing::Test{
protected:
	virtual void SetUp(){
		cout << "ProcessMemory::getProcessMemory(): " << ProcessMemory::getProcessMemory() << endl;
	}
	virtual void TearDown(){
		destroyAllWindows();
		cout << "ProcessMemory::getProcessMemory(): " << ProcessMemory::getProcessMemory() << endl;
	}
};

class ftISFeature : public testing::Test{
protected:
	virtual void SetUp(){
		cout << "ProcessMemory::getProcessMemory(): " << ProcessMemory::getProcessMemory() << endl;
	}
	virtual void TearDown(){
		destroyAllWindows();
		cout << "ProcessMemory::getProcessMemory(): " << ProcessMemory::getProcessMemory() << endl;
	}
};

class ftISCompare : public testing::Test{
protected:
	virtual void SetUp(){
		cout << "ProcessMemory::getProcessMemory(): " << ProcessMemory::getProcessMemory() << endl;
	}
	virtual void TearDown(){
		destroyAllWindows();
		cout << "ProcessMemory::getProcessMemory(): " << ProcessMemory::getProcessMemory() << endl;
	}
};

class ftError : public testing::Test{
protected:
	virtual void SetUp(){
		cout << "ProcessMemory::getProcessMemory(): " << ProcessMemory::getProcessMemory() << endl;
	}
	virtual void TearDown(){
		destroyAllWindows();
		cout << "ProcessMemory::getProcessMemory(): " << ProcessMemory::getProcessMemory() << endl;
	}
};

class ftAppliance : public testing::Test{
protected:
	virtual void SetUp(){
		cout << "ProcessMemory::getProcessMemory(): " << ProcessMemory::getProcessMemory() << endl;
	}
	virtual void TearDown(){
		destroyAllWindows();
		cout << "ProcessMemory::getProcessMemory(): " << ProcessMemory::getProcessMemory() << endl;
	}
};

#endif
