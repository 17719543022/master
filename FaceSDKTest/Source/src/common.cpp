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
	#define DEFAULT_DET_TRACK_CHANNEL() ISCreateDetTrackChannel(46,1000,0);
	#define DESTROY_DET_TRACK_CHANNEL(x) ISDestroyDetTrackChannel(x);
	#define DEFAULT_FEATURE_CHANNEL() ISCreateFeatureChannel(0,0,0,0,0);
	#define DESTROY_FEATURE_CHANNEL(x) ISDestroyFeatureChannel(x);
	#define DEFAULT_COMPARE_CHANNEL() ISCreateCompareChannel();
	#define DESTROY_COMPARE_CHANNEL(x) ISDestroyCompareChannel(x);

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

