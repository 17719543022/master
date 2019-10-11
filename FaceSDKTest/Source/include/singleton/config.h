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
	int compareSamples;
	string detectImgPathA;
	string detectImgPathB;
	string detectRgbImgPathA;
	string detectRgbImgPathB;
	string trackImgPathA;
	string trackImgPathB;
	string faceInfoImgPathA;
	string faceInfoImgPathB;
	string featureImgPathA;
	string featureImgPathB;
	string compareImgPathA;
	string compareImgPathB;
	string appliancePathA;
	string appliancePathB;
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
	int getCompareSamples();
	string getDetectImgPathA();
	string getDetectImgPathB();
	string getDetectRgbImgPathA();
	string getDetectRgbImgPathB();
	string getTrackImgPathA();
	string getTrackImgPathB();
	string getFaceInfoImgPathA();
	string getFaceInfoImgPathB();
	string getFeatureImgPathA();
	string getFeatureImgPathB();
	string getCompareImgPathA();
	string getCompareImgPathB();
	string getAppliancePathA();
	string getAppliancePathB();
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
