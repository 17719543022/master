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
	#define DEFAULT_FEATURE_CHANNEL() ISCreateFeatureChannel(0,0,0,0,0);
	#define DEFAULT_COMPARE_CHANNEL() ISCreateCompareChannel();
	#define DESTROY_DET_TRACK_CHANNEL(x) ISDestroyDetTrackChannel(x);
	#define DESTROY_FEATURE_CHANNEL(x) ISDestroyFeatureChannel(x);
	#define DESTROY_COMPARE_CHANNEL(x) ISDestroyCompareChannel(x);

	void faceDetectRgb(char *imgData, int imgLen, int imgWidth, int imgHeight, int outResult[][4],int *outLen)
	{
		int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
		EXPECT_TRUE(SUCC == ISFaceDetectRgb(defaultDetTrackChannel, imgData, imgLen, imgWidth, imgHeight, outResult, outLen));
		DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);
	}

	void getFeatureWithFacePosRgb(char *imgData, int imgLen, int imgWidth, int imgHeight, int param[][4], int faceNum, char *outFeature)
	{
		int defaultFeatureChannel = ISCreateFeatureChannel(0,0,0,0,0);
		EXPECT_TRUE(SUCC == ISGetFeatureWithFacePosRgb(defaultFeatureChannel, imgData, imgLen, imgWidth, imgHeight, param, faceNum, outFeature));
		DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);
	}
}

void getFeature(char *imgPath, char *outFeature)
{
	int outRst[50][4];
	int outLength = 0;

	Mat image = imread(imgPath, 1);

	faceDetectRgb((char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength);
	if(outLength == 0){
		ERR_LOG("%s detected no face!\n", imgPath);
		return;
	}

	getFeatureWithFacePosRgb((char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, outLength, outFeature);
}

//void forFiles(...);

void forFolders(const char *dir,char *idCard,char *live,bool *over)
{
	_finddata_t findData;

	intptr_t handle = _findfirst(dir, &findData);
	EXPECT_TRUE(handle != -1);

	do
	{
		if (findData.attrib & _A_SUBDIR
				&& (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0))
		{
			continue;
		}
		else
		{
			cout << findData.name << endl;
		}
	} while (_findnext(handle, &findData) == 0);

	_findclose(handle);
}
