#ifndef _INCL_TEST_SUITS_H_
#define _INCL_TEST_SUITS_H_

#include <gtest/gtest.h>
#include "opencv.hpp"
#include "processMemory.h"

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