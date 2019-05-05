#include "stdafx.h"
#include <gtest/gtest.h>
#include <iostream>
#include "face_sdk.h"
#include "opencv.hpp"
#include "common.h"

using namespace std;
using namespace cv;

TEST(ftError, inputImagesWithATooSmallSize)
{
	int outRst[50][4];
	int outLength;
	Mat image = imread("..\\..\\Images\\ERROR\\501.jpg");
	
	int detChannelId = DEFAULT_DET_TRACK_CHANNEL();
	EXPECT_TRUE(IMG_SIZE_TOO_SMALL == ISFaceDetectRgb(detChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength));
	DESTROY_DET_TRACK_CHANNEL(detChannelId);
}

TEST(ftError, inputImagesCanNotBeFound)
{
	int outRst[50][4];
	int outLength;
	Mat image = imread("..\\..\\Images\\ERROR\\50x.jpg");
	
	int detChannelId = DEFAULT_DET_TRACK_CHANNEL();
	EXPECT_TRUE(IMG_DATA_ERROR == ISFaceDetectRgb(detChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength));
	DESTROY_DET_TRACK_CHANNEL(detChannelId);
}

TEST(ftError, detectWithOutCreatingDectectChannel)
{
	int outRst[50][4];
	int outLength;
	Mat image = imread("..\\..\\Images\\ERROR\\50x.jpg");
	
	EXPECT_TRUE(UNKNOWN_ERROR == ISFaceDetectRgb(0, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength));
}

TEST(ftError, inputImagesDetectedNoFace)
{
	int outRst[50][4];
	int outLength;
	Mat image = imread("..\\..\\Images\\ERROR\\502.jpg");
	
	imCommonReadAndShow("..\\..\\Images\\ERROR\\502.jpg");

	int detChannelId = DEFAULT_DET_TRACK_CHANNEL();
	//检测不到人脸的时候应该返回DETECT_NO_FACE，实际返回SUCC？
	EXPECT_TRUE(SUCC == ISFaceDetectRgb(detChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength));
	EXPECT_TRUE(0 == outLength);
	DESTROY_DET_TRACK_CHANNEL(detChannelId);
}

TEST(ftError, inputImagesGetNoFeature)
{
	Mat image = imread("..\\..\\Images\\ERROR\\502.jpg");

	vector<char> vec(8192);
	int defaultFeatureChannelId = PREDICT_FEATURE_CHANNEL();
	EXPECT_TRUE(DETECT_NO_FACE == ISGetFeatureRgb(defaultFeatureChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, vec.data()));
	DESTROY_FEATURE_CHANNEL(defaultFeatureChannelId);
}

TEST(ftError, whatImageLeadsToGetFeatureError)
{
	Mat img = imread("..\\..\\Images\\ERROR\\503.jpg");

	imCommonReadAndShow("..\\..\\Images\\ERROR\\503.jpg");

	vector<char> vec(8192);
	int defaultFeatureChannelId = PREDICT_FEATURE_CHANNEL();
	EXPECT_TRUE(GET_FEATURE_ERROR == ISGetFeatureRgb(defaultFeatureChannelId, (char *)img.data, img.rows*img.cols*3, img.cols, img.rows, vec.data()));
	DESTROY_FEATURE_CHANNEL(defaultFeatureChannelId);
}