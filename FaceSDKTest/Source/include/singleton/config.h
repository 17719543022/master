#ifndef _INCL_CONFIG_H_
#define _INCL_CONFIG_H_
#include "iniReader.h"
using namespace std;

struct Config{
	Config();
	
	int detectThreadNum;
	int getFeaThreadNum;
	int compareThreadNum;
	float compareFaceValue;
	int recogniseThreadNum;
	float recogniseFaceValue;
	int maxImgNum;
	string detectImgPath;
	string rectangleSPath;
	string rectangleMPath;
	string report;
	string log;
};

class GConfig{
public:
	static GConfig& getInstance();
	int getDetectThreadNum();
	int getGetFeaThreadNum();
	int getCompareThreadNum();
	float getCompareFaceValue();
	int getRecogniseThreadNum();
	float getRecogniseFaceValue();
	int getMaxImgNum();
	string getDetectImgPath();
	string getRectangleSPath();
	string getRectangleMPath();
	string getReport();
	string getLog();
	void dump();

private:
	GConfig();
	GConfig(const GConfig&);
	GConfig& operator=(const GConfig&);

private:
	Config config;
};

#endif
