#include "stdafx.h"
#include <gtest/gtest.h>
#include "testSuits.h"
#include "common.h"
#include "face_sdk.h"

TEST_F(ftError, inputImagesWithATooSmallSize){
	int outRst[50][4];
	int outLength;
	Mat image = imread("..\\..\\Data\\Error\\501.jpg");
	
	int detChannelId = DEFAULT_DET_TRACK_CHANNEL();
	EXPECT_TRUE(IMG_SIZE_TOO_SMALL == ISFaceDetectRgb(detChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength));
	DESTROY_DET_TRACK_CHANNEL(detChannelId);
}

TEST_F(ftError, inputImagesCanNotBeFound){
	int outRst[50][4];
	int outLength;
	Mat image = imread("..\\..\\Data\\Error\\50x.jpg");
	
	int detChannelId = DEFAULT_DET_TRACK_CHANNEL();
	EXPECT_TRUE(IMG_DATA_ERROR == ISFaceDetectRgb(detChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength));
	DESTROY_DET_TRACK_CHANNEL(detChannelId);
}

TEST_F(ftError, detectWithOutCreatingDectectChannel){
	int outRst[50][4];
	int outLength;
	Mat image = imread("..\\..\\Data\\Error\\50x.jpg");
	
	EXPECT_TRUE(UNKNOWN_ERROR == ISFaceDetectRgb(0, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength));
}

TEST_F(ftError, inputImagesDetectedNoFace){
	int outRst[50][4];
	int outLength;
	Mat image = imread("..\\..\\Data\\Error\\502.jpg");
	
	imCommonReadAndShow("..\\..\\Data\\Error\\502.jpg");

	int detChannelId = DEFAULT_DET_TRACK_CHANNEL();
	//ISFaceDetect return SUCC when the picture has no face, however, ISGetFeature returns DETECT_NO_FACE.
	EXPECT_TRUE(SUCC == ISFaceDetectRgb(detChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength));
	EXPECT_TRUE(0 == outLength);
	DESTROY_DET_TRACK_CHANNEL(detChannelId);
}

TEST_F(ftError, inputImagesGetNoFeature){
	Mat image = imread("..\\..\\Data\\Error\\502.jpg");

	vector<char> vec(8192);
	int defaultFeatureChannelId = PREDICT_FEATURE_CHANNEL();
	EXPECT_TRUE(DETECT_NO_FACE == ISGetFeatureRgb(defaultFeatureChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, vec.data()));
	DESTROY_FEATURE_CHANNEL(defaultFeatureChannelId);
}

TEST_F(ftError, whatImageLeadsToGetFeatureError){
	Mat img = imread("..\\..\\Data\\Error\\503.jpg");

	imCommonReadAndShow("..\\..\\Data\\Error\\503.jpg");

	vector<char> vec(8192);
	int defaultFeatureChannelId = PREDICT_FEATURE_CHANNEL();
	EXPECT_TRUE(GET_FEATURE_ERROR == ISGetFeatureRgb(defaultFeatureChannelId, (char *)img.data, img.rows*img.cols*3, img.cols, img.rows, vec.data()));
	DESTROY_FEATURE_CHANNEL(defaultFeatureChannelId);
}