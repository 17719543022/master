#include "stdafx.h"
#include "common.h"
#include <iostream>
#include "sdk_error_code.h"
#include "log_format.h"
#include "opencv.hpp"
#include <gtest/gtest.h>

using namespace std;
using namespace cv;

bool viewSwitch = true;

namespace{
	char *getFilename(char *p)
	{
		char ch = '\\';
		char *q = strrchr(p, ch) + 1;
 
		return q;
	}

	void getFeatureWithFacePosRgb(char *imgData, int imgLen, int imgWidth, int imgHeight, int param[][4], int faceNum, char *outFeature)
	{
		int defaultFeatureChannel = DEFAULT_FEATURE_CHANNEL();
		//如果有多张人脸，超出了给outFeature分配的大小，这个地方可能不安全。
		EXPECT_TRUE(SUCC == ISGetFeatureWithFacePosRgb(defaultFeatureChannel, imgData, imgLen, imgWidth, imgHeight, param, faceNum, outFeature));
		DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);
	}
}

void switchShow(char *name, Mat image)
{
	if(viewSwitch)
	{
		imshow(name, image);
	}
}

void faceDetectRgb(char *imgData, int imgLen, int imgWidth, int imgHeight, int outRst[][4], int *outLen)
{
	int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
	EXPECT_TRUE(SUCC == ISFaceDetectRgb(defaultDetTrackChannel, imgData, imgLen, imgWidth, imgHeight, outRst, outLen));
	DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);
}

void calFaceInfoRgb(char *imgData, int imgLen, int imgWidth, int imgHeight, int outRst[][4], int *outLen, int keyPoint[][6], float angle[][3], float kScore[])
{
	int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
	int nRet = ISFaceDetectRgb(defaultDetTrackChannel, imgData, imgLen, imgWidth, imgHeight, outRst, outLen);
	int ret = ISCalFaceInfoRgb(defaultDetTrackChannel, imgData, imgLen, imgWidth, imgHeight, outRst, *outLen, keyPoint, angle, kScore);
	DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);
}

void imCommonShow(char *name, Mat image, int outRst[][4], int len, int thickness, int delay)
{
	if(len < 1) 
	{
		switchShow(name, image);
		waitKey(3000);
		return;
	}

	for(int i=0; i<len; i++)
	{
		Rect rect = Rect(outRst[i][0],outRst[i][1],outRst[i][2]-outRst[i][0]+1,outRst[i][3]-outRst[i][1]+1);
		rectangle(image, rect, Scalar(0,0,255), thickness);

		switchShow(name, image);
		waitKey(delay);
	}
}

void imReadAndShow(char *imgPath)
{
	int outRst[50][4];
	int len;
	Mat image = imread(imgPath);

	faceDetectRgb((char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &len);

	switchShow(getFilename(imgPath), image);
	waitKey();
}

void imCommonReadAndShow(char *imgPath, int thickness, int delay)
{
	int outRst[50][4];
	int len;
	Mat image = imread(imgPath);

	faceDetectRgb((char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &len);

	imCommonShow(getFilename(imgPath), image, outRst, len, thickness, delay);
}

void faceDetectPath(char *imgPath,int outRst[][4],int *outLen)
{
	int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
	EXPECT_TRUE(SUCC == ISFaceDetectPath(defaultDetTrackChannel, imgPath, outRst, outLen));
	DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);
}

int getFeatureWithFacePosRgb(const char *imgPath, char *outFeature, int outRst[][4], int *outLen)
{
	int rst[50][4];
	int len = 0;
	Mat image = imread(imgPath);

	faceDetectRgb((char*)image.data, image.rows*image.cols*3, image.cols, image.rows, rst, &len);

	if(outLen != NULL){
		*outLen = len;
	}
	if(outRst != NULL){
		memcpy(outRst, rst, len*4*4);
	}

	if(len < 1){
		return DETECT_NO_FACE;
	}
	if(len != 1)
	{
		DBG_LOG("%s detect %d face!\n", imgPath, len);
	}

	getFeatureWithFacePosRgb((char*)image.data, image.rows*image.cols*3, image.cols, image.rows, rst, len, outFeature);
	return SUCC;
}

void getFeatureRgb(char *imgData, int imgLen, int imgWidth, int imgHeight, char *outFeature, float KPtScore)
{
	int defaultFeatureChannel = DEFAULT_FEATURE_CHANNEL();
	EXPECT_TRUE(SUCC == ISGetFeatureRgb(defaultFeatureChannel, imgData, imgLen, imgWidth, imgHeight, outFeature, KPtScore));
	DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);
}

void getPcaFea(char* fea_Org,char* fea_Pca)
{
	int defaultFeatureChannel = DEFAULT_FEATURE_CHANNEL();
	EXPECT_TRUE(SUCC == ISGetPcaFea(defaultFeatureChannel, fea_Org, fea_Pca));
	DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);
}

void getFeatureAndPredict(char *imgData
						  , int imgLen
						  , int imgWidth
						  , int imgHeight
						  , char *expression
						  , char *glasses
						  , char *smile
						  , float *age
						  , char *gender
						  , float *beauty
						  , float kScore)
{
	vector<char> vec(8192);
	int defaultFeatureChannel = PREDICT_FEATURE_CHANNEL();
	EXPECT_TRUE_EX(ISGetFeatureRgb(defaultFeatureChannel, imgData, imgLen, imgWidth, imgHeight, vec.data()));
	EXPECT_TRUE_EX(ISpredictExpression(defaultFeatureChannel, vec.data(), expression));
	EXPECT_TRUE_EX(ISpredictGlasses(defaultFeatureChannel, vec.data(), glasses));
	EXPECT_TRUE_EX(ISpredictSmile(defaultFeatureChannel, vec.data(), smile));
	EXPECT_TRUE_EX(ISpredictAgeGender(defaultFeatureChannel, vec.data(), age, gender));
	EXPECT_TRUE_EX(ISpredictBeauty(defaultFeatureChannel, vec.data(), beauty));
	DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);
}

void compare(char *feature1, char *feature2, float *outScore)
{
	int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
	ISCompare(defaultCompareChannel, feature1, feature2, outScore);
	DESTROY_COMPARE_CHANNEL(defaultCompareChannel);
}

void compareMN(char **featureM, int numM, char **featureN, int numN, float **outScore)
{
	int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
	EXPECT_TRUE(SUCC == ISCompareMN(defaultCompareChannel, featureM, numM, featureN, numN, outScore));
	DESTROY_COMPARE_CHANNEL(defaultCompareChannel);
}

void compareMNfaster(char **featureM, int numM, char **featureN, int numN, float **outScore)
{
	int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
	EXPECT_TRUE(SUCC == ISCompareMNfasterprep(defaultCompareChannel, featureM, numM));
	EXPECT_TRUE(SUCC == ISCompareMNfaster(defaultCompareChannel, featureN, numN, outScore));
	DESTROY_COMPARE_CHANNEL(defaultCompareChannel);
}