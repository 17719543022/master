#include "stdafx.h"
#include <gtest/gtest.h>
#include <iostream>
#include "face_sdk.h"
#include "common.h"
#include "opencv.hpp"

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
	int outResult[50][4] = {0};

	faceDetectPath(imgPath, outResult, &len);
	
	EXPECT_TRUE(len >= 15);
}

TEST(ftInterface, whatFaceReturnsEarlierInOutResultAndWhatLater)
{
	char *imgPath = "..\\..\\Images\\beauty.jpg";
	int len = 0;
	int outResult[50][4] = {0};
	Mat image = imread(imgPath);

	char outFeature1[50][8192];
	getFeatureWithFacePosRgb(imgPath, outFeature1[0], outResult, &len);

	imShowWithRect("beauty.jpg", image, outResult, len);
}

TEST(ftInterface, convolutionOfAllFacesInOnePicture)
{
	char *imgPath = "..\\..\\Images\\beauty.jpg";
	int len = 0;
	int outResult[50][4] = {0};
	Mat image = imread(imgPath);

	char outFeature[50][8192];
	getFeatureWithFacePosRgb(imgPath, outFeature[0], outResult, &len);

	char **featureM;
	ALLOC_DOUBLE_STAR(len, 8192, char, featureM, M)
	for(int i=0; i<len; i++)
	{
		featureM[i] = outFeature[i];
		getPcaFea(featureM[0],featureM[0]);
	}

	char **featureN;
	ALLOC_DOUBLE_STAR(len, 8192, char, featureN, N)
	for(int i=0; i<len; i++)
	{
		featureN[i] = outFeature[i];
		getPcaFea(featureN[i], featureN[i]);
	}

	float **outScoreMN;
	ALLOC_DOUBLE_STAR(len, len, float, outScoreMN, S)
	compareMN(featureM, len, featureN, len, outScoreMN);

	for(int i=0; i<len; i++)
	{
		for(int j=0;j<len;j++)
		{
			cout << setw(10) << setiosflags(ios::left) << outScoreMN[i][j];
		}
		cout<<endl;
	}
}

TEST(ftInterface, gotFeatureLengthBeCorrect)
{
	EXPECT_TRUE(8192 == ISGetFeatureLength());
}

