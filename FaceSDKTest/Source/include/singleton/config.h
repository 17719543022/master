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
	string recDetectSPath;
	string recDetectMPath;
	string trackImgPath;
	string recTrackSPath;
	string recTrackMPath;
	string faceInfoImgPath;
	string faceInfoSPath;
	string faceInfoMPath;
	string featureImgPath;
	string feaSPath;
	string pcaSPath;
	string feaMPath;
	string pcaMPath;
	string compareImgAPath;
	string compareImgBPath;
	string featureAPath;
	string featureBPath;
	string pcaAPath;
	string pcaBPath;
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
	string getRecDetectSPath();
	string getRecDetectMPath();
	string getTrackImgPath();
	string getRecTrackSPath();
	string getRecTrackMPath();
	string getFaceInfoImgPath();
	string getFaceInfoSPath();
	string getFaceInfoMPath();
	string getFeatureImgPath();
	string getFeaSPath();
	string getPcaSPath();
	string getFeaMPath();
	string getPcaMPath();
	string getCompareImgAPath();
	string getCompareImgBPath();
	string getFeatureAPath();
	string getFeatureBPath();
	string getPcaAPath();
	string getPcaBPath();
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
