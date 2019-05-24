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
	faceInfoImgPath = reader.readString("ISCalFaceInfoPath", "faceInfoImgPath", "");
	faceInfoSPath = reader.readString("ISCalFaceInfoPath", "faceInfoSPath", "");
	faceInfoMPath = reader.readString("ISCalFaceInfoPath", "faceInfoMPath", "");
	featureImgPath = reader.readString("ISGetFeaturePath", "featureImgPath", "");
	feaSPath = reader.readString("ISGetFeaturePath", "feaSPath", "");
	pcaSPath = reader.readString("ISGetFeaturePath", "pcaSPath", "");
	feaMPath = reader.readString("ISGetFeaturePath", "feaMPath", "");
	pcaMPath = reader.readString("ISGetFeaturePath", "pcaMPath", "");
	compareImgAPath = reader.readString("ISCompare", "compareImgAPath", "");
	compareImgBPath = reader.readString("ISCompare", "compareImgBPath", "");
	featureAPath = reader.readString("ISCompare", "featureAPath", "");
	featureBPath = reader.readString("ISCompare", "featureBPath", "");
	pcaAPath = reader.readString("ISCompare", "pcaAPath", "");
	pcaBPath = reader.readString("ISCompare", "pcaBPath", "");
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

string GConfig::getFaceInfoImgPath(){
	return config.faceInfoImgPath;
}

string GConfig::getFaceInfoSPath(){
	return config.faceInfoSPath;
}

string GConfig::getFaceInfoMPath(){
	return config.faceInfoMPath;
}

string GConfig::getFeatureImgPath(){
	return config.featureImgPath;
}

string GConfig::getFeaSPath(){
	return config.feaSPath;
}

string GConfig::getPcaSPath(){
	return config.pcaSPath;
}

string GConfig::getFeaMPath(){
	return config.feaMPath;
}

string GConfig::getPcaMPath(){
	return config.pcaMPath;
}

string GConfig::getCompareImgAPath(){
	return config.compareImgAPath;
}

string GConfig::getCompareImgBPath(){
	return config.compareImgBPath;
}

string GConfig::getFeatureAPath(){
	return config.featureAPath;
}

string GConfig::getFeatureBPath(){
	return config.featureBPath;
}

string GConfig::getPcaAPath(){
	return config.pcaAPath;
}

string GConfig::getPcaBPath(){
	return config.pcaBPath;
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
	cout << "faceInfoImgPath" << getFaceInfoImgPath() << endl;
	cout << "faceInfoSPath" << getFaceInfoSPath() << endl;
	cout << "faceInfoMPath" << getFaceInfoMPath() << endl;
	cout << "featureImgPath" << getFeatureImgPath() << endl;
	cout << "feaSPath" << getFeaSPath() << endl;
	cout << "pcaSPath" << getPcaSPath() << endl;
	cout << "feaMPath" << getFeaMPath() << endl;
	cout << "pcaMPath" << getPcaMPath() << endl;
	cout << "compareImgAPath" << getCompareImgAPath() << endl;
	cout << "compareImgBPath" << getCompareImgBPath() << endl;
	cout << "featureAPath" << getFeatureAPath() << endl;
	cout << "featureBPath" << getFeatureBPath() << endl;
	cout << "pcaAPath" << getPcaAPath() << endl;
	cout << "pcaBPath" << getPcaBPath() << endl;
	cout << "report = " << getReport() << endl;
	cout << "log = " << getLog() << endl;
}
