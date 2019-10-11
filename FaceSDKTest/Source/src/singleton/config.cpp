#include "config.h"
#include <iostream>
using namespace std;

Config::Config(){
	iniReader reader;
	reader.readConfig("../../../config.ini");

	detectThreadNum = reader.readInt("PARAM", "detectThreadNum", 0);
	getFeaThreadNum = reader.readInt("PARAM", "getFeaThreadNum", 0);
	compareThreadNum = reader.readInt("PARAM", "compareThreadNum", 0);
	compareFaceValue = reader.readFloat("PARAM", "compareFaceValue", 0);
	recogniseThreadNum = reader.readInt("PARAM", "recogniseThreadNum", 0);
	recogniseFaceValue = reader.readFloat("PARAM", "recogniseFaceValue", 0);
	maxImgNum = reader.readInt("PARAM", "maxImgNum", 0);
	compareSamples = reader.readInt("PARAM", "compareSamples", 0);
	detectImgPathA = reader.readString("ISFaceDetectPath", "detectImgPathA", "");
	detectImgPathB = reader.readString("ISFaceDetectPath", "detectImgPathB", "");
	detectRgbImgPathA = reader.readString("ISFaceDetectRgb", "detectRgbImgPathA", "");
	detectRgbImgPathB = reader.readString("ISFaceDetectRgb", "detectRgbImgPathB", "");
	trackImgPathA = reader.readString("ISFaceDetTrackRgb", "trackImgPathA", "");
	trackImgPathB = reader.readString("ISFaceDetTrackRgb", "trackImgPathB", "");
	faceInfoImgPathA = reader.readString("ISCalFaceInfoPath", "faceInfoImgPathA", "");
	faceInfoImgPathB = reader.readString("ISCalFaceInfoPath", "faceInfoImgPathB", "");
	featureImgPathA = reader.readString("ISGetFeaturePath", "featureImgPathA", "");
	featureImgPathB = reader.readString("ISGetFeaturePath", "featureImgPathB", "");
	compareImgPathA = reader.readString("ISCompare", "compareImgPathA", "");
	compareImgPathB = reader.readString("ISCompare", "compareImgPathB", "");
	appliancePathA = reader.readString("Appliance", "appliancePathA", "");
	appliancePathB = reader.readString("Appliance", "appliancePathB", "");
	report = reader.readString("RESULT", "report", "");
	log = reader.readString("RESULT", "log", "");
}

GConfig::GConfig(){
	
}

GConfig::GConfig(const GConfig&){

}

GConfig& GConfig::operator=(const GConfig& gConfig){
	return *this;
}

GConfig& GConfig::getInstance(){
	static GConfig instance;
	return instance;
}

int GConfig::getDetectThreadNum(){
	return config.detectThreadNum;
}

int GConfig::getGetFeaThreadNum(){
	return config.getFeaThreadNum;
}

int GConfig::getCompareThreadNum(){
	return config.compareThreadNum;
}

float GConfig::getCompareFaceValue(){
	return config.compareFaceValue;
}

int GConfig::getRecogniseThreadNum(){
	return config.recogniseThreadNum;
}

float GConfig::getRecogniseFaceValue(){
	return config.recogniseFaceValue;
}

int GConfig::getMaxImgNum(){
	return config.maxImgNum;
}

int GConfig::getCompareSamples(){
	return config.compareSamples;
}

string GConfig::getDetectImgPathA(){
	return config.detectImgPathA;
}

string GConfig::getDetectImgPathB(){
	return config.detectImgPathB;
}

string GConfig::getDetectRgbImgPathA(){
	return config.detectRgbImgPathA;
}

string GConfig::getDetectRgbImgPathB(){
	return config.detectRgbImgPathB;
}

string GConfig::getTrackImgPathA(){
	return config.trackImgPathA;
}

string GConfig::getTrackImgPathB(){
	return config.trackImgPathB;
}

string GConfig::getFaceInfoImgPathA(){
	return config.faceInfoImgPathA;
}

string GConfig::getFaceInfoImgPathB(){
	return config.faceInfoImgPathB;
}

string GConfig::getFeatureImgPathA(){
	return config.featureImgPathA;
}

string GConfig::getFeatureImgPathB(){
	return config.featureImgPathB;
}

string GConfig::getCompareImgPathA(){
	return config.compareImgPathA;
}

string GConfig::getCompareImgPathB(){
	return config.compareImgPathB;
}

string GConfig::getAppliancePathA(){
	return config.appliancePathA;
}

string GConfig::getAppliancePathB(){
	return config.appliancePathB;
}

string GConfig::getReport(){
	return config.report;
}

string GConfig::getLog(){
	return config.log;
}

void GConfig::dump(){
	cout << "detectThreadNum = " << getDetectThreadNum() << endl;
	cout << "getFeaThreadNum = " << getGetFeaThreadNum() << endl;
	cout << "compareThreadNum = " << getCompareThreadNum() << endl;
	cout << "compareFaceValue = " << getCompareFaceValue() << endl;
	cout << "recogniseThreadNum = " << getRecogniseThreadNum() << endl;
	cout << "recogniseFaceValue = " << getRecogniseFaceValue() << endl;
	cout << "maxImgNum = " << getMaxImgNum() << endl;
	cout << "compareSamples = " << getCompareSamples() << endl;
	cout << "detectImgPathA = " << getDetectImgPathA() << endl;
	cout << "detectImgPathB = " << getDetectImgPathB() << endl;
	cout << "detectRgbImgPathA = " << getDetectRgbImgPathA() << endl;
	cout << "detectRgbImgPathB = " << getDetectRgbImgPathB() << endl;
	cout << "trackImgPathA = " << getTrackImgPathA() << endl;
	cout << "trackImgPathB = " << getTrackImgPathB() << endl;
	cout << "faceInfoImgPathA = " << getFaceInfoImgPathA() << endl;
	cout << "faceInfoImgPathB = " << getFaceInfoImgPathB() << endl;
	cout << "featureImgPathA = " << getFeatureImgPathA() << endl;
	cout << "featureImgPathB = " << getFeatureImgPathB() << endl;
	cout << "compareImgPathA = " << getCompareImgPathA() << endl;
	cout << "compareImgPathB = " << getCompareImgPathB() << endl;
	cout << "appliancePathA = " << getAppliancePathA() << endl;
	cout << "appliancePathB = " << getAppliancePathB() << endl;
	cout << "report = " << getReport() << endl;
	cout << "log = " << getLog() << endl;
}
