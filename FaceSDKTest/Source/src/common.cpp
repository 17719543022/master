#include "stdafx.h"
#include "common.h"
#include <iostream>
#include "sdk_error_code.h"
#include "log_format.h"
#include "opencv.hpp"
#include <gtest/gtest.h>

using namespace std;
using namespace cv;

namespace{
	void faceDetectRgb(char *imgData, int imgLen, int imgWidth, int imgHeight, int outResult[][4],int *outLen)
	{
		int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
		EXPECT_TRUE(SUCC == ISFaceDetectRgb(defaultDetTrackChannel, imgData, imgLen, imgWidth, imgHeight, outResult, outLen));
		DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);
	}

	void getFeatureWithFacePosRgb(char *imgData, int imgLen, int imgWidth, int imgHeight, int param[][4], int faceNum, char *outFeature)
	{
		int defaultFeatureChannel = DEFAULT_FEATURE_CHANNEL();
		//如果有多张人脸，超出了给outFeature分配的大小，这个地方可能不安全。
		EXPECT_TRUE(SUCC == ISGetFeatureWithFacePosRgb(defaultFeatureChannel, imgData, imgLen, imgWidth, imgHeight, param, 1, outFeature));
		DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);
	}

	char *getFilename(char *p)
	{
		char ch = '\\';
		char *q = strrchr(p, ch) + 1;
 
		return q;
	}
}

void imShowWithRect(char *name, Mat image, int outRst[][4], int len)
{
	if(len < 1) return;

	for(int i=0; i<len; i++)
	{
		Rect rect = Rect(outRst[i][0],outRst[i][1],outRst[i][2]-outRst[i][0]+1,outRst[i][3]-outRst[i][1]+1);
		rectangle(image, rect, Scalar(0,0,255));
	}

	imshow(name, image);
	waitKey();
}

void imReadAndShow(char *imgPath)
{
	int outRst[50][4];
	int len;
	Mat image = imread(imgPath);

	faceDetectRgb((char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &len);

	imshow(getFilename(imgPath), image);
	waitKey();
}

void imReadAndShowWithRect(char *imgPath)
{
	int outRst[50][4];
	int len;
	Mat image = imread(imgPath);

	faceDetectRgb((char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &len);

	imShowWithRect(getFilename(imgPath), image, outRst, len);
}

void faceDetectPath(char *imgPath,int outResult[][4],int *outLen)
{
	int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
	EXPECT_TRUE(SUCC == ISFaceDetectPath(defaultDetTrackChannel, imgPath, outResult, outLen));
	DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);
}

int getFeature(const char *imgPath, char *outFeature)
{
	int outRst[50][4];
	int outLength = 0;

	Mat image = imread(imgPath, 1);

	faceDetectRgb((char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength);
	if(outLength < 1){
		DBG_LOG("%s detect no face!\n", imgPath);
		return DETECT_NO_FACE;
	}
	else if(outLength > 1){
		DBG_LOG("%s detect more than one face.\n", imgPath);
	}

	getFeatureWithFacePosRgb((char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, outLength, outFeature);

	return SUCC;
}

void compare(char *feature1, char *feature2, float *outScore)
{
	int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
	ISCompare(defaultCompareChannel, feature1, feature2, outScore);
	DESTROY_COMPARE_CHANNEL(defaultCompareChannel);
}

