#include "stdafx.h"
#include <gtest/gtest.h>
#include <iostream>
#include "face_sdk.h"
#include "common.h"
#include "opencv.hpp"
#include "log_format.h"
#include "config.h"
#include <fstream>
using namespace std;
using namespace cv;

TEST(ftInterface, displayVersionNo)
{
	cout<<"ISGetDetTrackVersionInfo(): "<<ISGetDetTrackVersionInfo()<<endl;
	cout<<"ISGetFeatureVersionInfo(): "<<ISGetFeatureVersionInfo()<<endl;
	cout<<"ISGetCompareVersionInfo(): "<<ISGetCompareVersionInfo()<<endl;
}

TEST(ftInterface, theGivenPictureHasMoreThan15FacesBeDetected)
{
	char *imgPath = "..\\..\\Images\\beauty.jpg";
	int len = 0;
	int outRst[50][4] = {0};

	faceDetectPath(imgPath, outRst, &len);
	
	EXPECT_TRUE(len >= 15);
}

TEST(ftInterface, gotFeatureLengthBeCorrect)
{
	EXPECT_TRUE(8192 == ISGetFeatureLength());
}

//TEST(ftInterface, getAFacePcaFeatureAndSave)
//{
//	char *imgPath = "..\\..\\Images\\image\\1.jpg";
//	Mat image = imread(imgPath);
//	char feature[8192];
//	char pcaFeature[2048];
//
//	getFeatureRgb((char*)image.data, image.rows*image.cols*3, image.cols, image.rows, feature);
//	getPcaFea(feature, pcaFeature);
//
//	fstream f;
//
//	string path = GConfig::getInstance().getPcaFeaPath();
//	path = path + "\\1.fea";
//	f.open(path, ios::out | ios::binary);
//	f.write(pcaFeature, sizeof(pcaFeature));
//
//	f.close();
//	f.clear();
//
//	f.open(path, ios::in | ios::binary);
//	f.seekg(0, ios::end);
//	streampos size = f.tellg();
//
//	f.seekg(0, ios::beg);
//
//	char pcaRead[2048];
//	f.read(pcaRead, size);
//	for(unsigned int i=0; i<size; i++){
//		cout << int(pcaRead[i]) << endl;
//	}
//
//	f.close();
//	f.clear();
//}
