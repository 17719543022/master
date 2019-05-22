#include "stdafx.h"
#include "config.h"
#include <iostream>
using namespace std;

Config::Config(){
	iniReader reader;
	reader.readConfig("../../config.ini");

	detectThreadNum = reader.readInt("PARAM", "detectThreadNum", 0);
	getFeaThreadNum = reader.readInt("PARAM", "getFeaThreadNum", 0);
	compareThreadNum = reader.readInt("PARAM", "compareThreadNum", 0);
	compareFaceValue = reader.readFloat("PARAM", "compareFaceValue", 0);
	recogniseThreadNum = reader.readInt("PARAM", "recogniseThreadNum", 0);
	recogniseFaceValue = reader.readFloat("PARAM", "recogniseFaceValue", 0);
	maxImgNum = reader.readInt("PARAM", "maxImgNum", 0);
	detectImgPath = reader.readString("ISFaceDetectPath", "detectImgPath", "");
	recDetectSPath = reader.readString("ISFaceDetectPath", "recDetectSPath", "");
	recDetectMPath = reader.readString("ISFaceDetectPath", "recDetectMPath", "");
	trackImgPath = reader.readString("ISFaceDetTrackRgb", "trackImgPath", "");
	recTrackSPath = reader.readString("ISFaceDetTrackRgb", "recTrackSPath", "");
	recTrackMPath = reader.readString("ISFaceDetTrackRgb", "recTrackMPath", "");
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

string GConfig::getDetectImgPath(){
	return config.detectImgPath;
}

string GConfig::getRecDetectSPath(){
	return config.recDetectSPath;
}

string GConfig::getRecDetectMPath(){
	return config.recDetectMPath;
}

string GConfig::getTrackImgPath(){
	return config.trackImgPath;
}

string GConfig::getRecTrackSPath(){
	return config.recTrackSPath;
}

string GConfig::getRecTrackMPath(){
	return config.recTrackMPath;
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
	cout << "detectImgPath" << getDetectImgPath() << endl;
	cout << "recDetectSPath" << getRecDetectSPath() << endl;
	cout << "recDetectMPath" << getRecDetectMPath() << endl;
	cout << "trackImgPath" << getTrackImgPath() << endl;
	cout << "recTrackSPath" << getRecTrackSPath() << endl;
	cout << "recTrackMPath" << getRecTrackMPath() << endl;
	cout << "report = " << getReport() << endl;
	cout << "log = " << getLog() << endl;
}