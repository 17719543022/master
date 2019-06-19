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

extern int denominator;

#ifdef WIN32
	extern SYSTEMTIME tStart, tStop;
#endif
#ifdef LINUX
	extern time_t tStart, tStop;
#endif

class ftISDetTrack : public testing::Test{
protected:
	virtual void SetUp(){
		cout << "ProcessMemory::getProcessMemory(): " << ProcessMemory::getProcessMemory() << endl;
#ifdef WIN32
		GetSystemTime(&tStart);
#endif
#ifdef LINUX
		tStart = time((time_t *)NULL);
#endif
	}
	virtual void TearDown(){
		destroyAllWindows();
#ifdef WIN32
		GetSystemTime(&tStop);
		cout << "time cost: " << getGap(tStart, tStop) << "ms" << endl;
		float timePerPic = float(getGap(tStart, tStop))/denominator;
#endif
#ifdef LINUX
		tStop = time((time_t *)NULL);
		cout << "time cost: " << 1000*(tStop - tStart) << "ms" << endl;
		float timePerPic = float(1000*(tStop - tStart))/denominator;
#endif
		cout << "average time cost: " << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "ms" << endl;
		cout << "ProcessMemory::getProcessMemory(): " << ProcessMemory::getProcessMemory() << endl;
	}
};

class ftISFeature : public testing::Test{
protected:
	virtual void SetUp(){
		cout << "ProcessMemory::getProcessMemory(): " << ProcessMemory::getProcessMemory() << endl;
#ifdef WIN32
		GetSystemTime(&tStart);
#endif
#ifdef LINUX
		tStart = time((time_t *)NULL);
#endif
	}
	virtual void TearDown(){
		destroyAllWindows();
#ifdef WIN32
		GetSystemTime(&tStop);
		cout << "time cost: " << getGap(tStart, tStop) << "ms" << endl;
		float timePerPic = float(getGap(tStart, tStop))/denominator;
#endif
#ifdef LINUX
		tStop = time((time_t *)NULL);
		cout << "time cost: " << 1000*(tStop - tStart) << "ms" << endl;
		float timePerPic = float(1000*(tStop - tStart))/denominator;
#endif
		cout << "average time cost: " << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "ms" << endl;
		cout << "ProcessMemory::getProcessMemory(): " << ProcessMemory::getProcessMemory() << endl;
	}
};

class ftISCompare : public testing::Test{
protected:
	virtual void SetUp(){
		cout << "ProcessMemory::getProcessMemory(): " << ProcessMemory::getProcessMemory() << endl;
#ifdef WIN32
		GetSystemTime(&tStart);
#endif
#ifdef LINUX
		tStart = time((time_t *)NULL);
#endif
	}
	virtual void TearDown(){
		destroyAllWindows();
#ifdef WIN32
		GetSystemTime(&tStop);
		cout << "time cost: " << getGap(tStart, tStop) << "ms" << endl;
		float timePerPic = float(getGap(tStart, tStop))/denominator;
#endif
#ifdef LINUX
		tStop = time((time_t *)NULL);
		cout << "time cost: " << 1000*(tStop - tStart) << "ms" << endl;
		float timePerPic = float(1000*(tStop - tStart))/denominator;
#endif
		cout << "average time cost: " << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "ms" << endl;
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
