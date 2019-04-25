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

TEST(ftInterface, drawsTheMostKptScoreFace)
{
	char *imgPath = "..\\..\\Images\\beauty.jpg";
	int len = 0;
	int outResult[50][4] = {0};
	Mat image = imread(imgPath);

	char outFeature2[8192];
	getFeatureRgb((char *)image.data, image.rows*image.cols*3, image.cols, image.rows, outFeature2);

	char outFeature1[50][8192];
	getFeatureWithFacePosRgb(imgPath, outFeature1[0], outResult, &len);

	int numM = len;
	int numN = 1;
	char **featureM = new char*[numM];
	char **featureN = new char*[numN];
	float **outScoreMN = new float*[numN];
	for(int i=0;i<numN;i++)
	{
		outScoreMN[i] = new float[numM];
	}
	for(int m=0; m<numM; m++)
	{
		featureM[m] = outFeature1[m];
		getPcaFea(featureM[m], featureM[m]);
	}
	featureN[0] = outFeature2;
	getPcaFea(featureN[0],featureN[0]);

	compareMN(featureN, numN, featureM, numM, outScoreMN);

	cout<<"M:N"<<endl;
	for(int i=0;i<numN;i++)
	{
		for(int j=0;j<numM;j++)
		{
			cout<<outScoreMN[i][j]<<" ";
		}
		cout<<endl;
	}

	Rect rect = Rect(outResult[0][0],outResult[0][1],outResult[0][2]-outResult[0][0]+1,outResult[0][3]-outResult[0][1]+1);
	rectangle(image, rect, Scalar(0,0,255));

	switchShow("beauty.jpg", image);
	waitKey();
}

TEST(ftInterface, gotFeatureLengthBeCorrect)
{
	EXPECT_TRUE(8192 == ISGetFeatureLength());
}

