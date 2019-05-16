#include "stdafx.h"
#include <gtest/gtest.h>
#include <iostream>
#include "face_sdk.h"
#include "common.h"
#include "opencv.hpp"
#include "log_format.h"
#include "config.h"
#include <fstream>
#include "testSuits.h"

using namespace std;
using namespace cv;

TEST_F(ftInterface, displayVersionNo)
{
	cout<<"ISGetDetTrackVersionInfo(): "<<ISGetDetTrackVersionInfo()<<endl;
	cout<<"ISGetFeatureVersionInfo(): "<<ISGetFeatureVersionInfo()<<endl;
	cout<<"ISGetCompareVersionInfo(): "<<ISGetCompareVersionInfo()<<endl;
}

TEST_F(ftInterface, theGivenPictureHasMoreThan15FacesBeDetected)
{
	char *imgPath = "..\\..\\Images\\beauty.jpg";
	int len = 0;
	int outRst[50][4] = {0};

	faceDetectPath(imgPath, outRst, &len);
	
	EXPECT_TRUE(len >= 15);
}

TEST_F(ftInterface, gotFeatureLengthBeCorrect)
{
	EXPECT_TRUE(8192 == ISGetFeatureLength());
}

TEST_F(ftInterface, getAFacePcaFeatureAndSave)
{
	char *imgPath = "..\\..\\Images\\image\\1.jpg";
	Mat image = imread(imgPath);
	char feature[8192];
	char pcaFeature[2048];

	getFeatureRgb((char*)image.data, image.rows*image.cols*3, image.cols, image.rows, feature);
	getPcaFea(feature, pcaFeature);

	fstream f;

	string path = GConfig::getInstance().getPcaFeaPath();
	path = path + "\\1.pca";
	f.open(path, ios::out | ios::binary);
	f.write(pcaFeature, sizeof(pcaFeature));

	f.close();
	f.clear();
}
