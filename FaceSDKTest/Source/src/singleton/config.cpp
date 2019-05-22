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
	rectangleSPath = reader.readString("ISFaceDetectPath", "rectangleSPath", "");
	rectangleMPath = reader.readString("ISFaceDetectPath", "rectangleMPath", "");
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

//string GConfig::getImgPath(){
//	return config.imgPath;
//}
//
//string GConfig::getISCompareA(){
//	return config.ISCompareA;
//}
//
//string GConfig::getISCompareB(){
//	return config.ISCompareB;
//}
//
//string GConfig::getISCompareMNA(){
//	return config.ISCompareMNA;
//}
//
//string GConfig::getISCompareMNB(){
//	return config.ISCompareMNB;
//}
//
//string GConfig::getFeaPath(){
//	return config.feaPath;
//}
//
//string GConfig::getPcaFeaPath(){
//	return config.pcaFeaPath;
//}

string GConfig::getDetectImgPath(){
	return config.detectImgPath;
}

string GConfig::getRectangleSPath(){
	return config.rectangleSPath;
}

string GConfig::getRectangleMPath(){
	return config.rectangleMPath;
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
	cout << "rectangleSPath" << getRectangleSPath() << endl;
	cout << "rectangleMPath" << getRectangleMPath() << endl;
	cout << "report = " << getReport() << endl;
	cout << "log = " << getLog() << endl;
}