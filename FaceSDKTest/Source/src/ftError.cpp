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
	Mat image = imread("..//..//Images//ERROR//501.jpg");
	
	int detChannelId = DEFAULT_DET_TRACK_CHANNEL();
	EXPECT_TRUE(IMG_SIZE_TOO_SMALL == ISFaceDetectRgb(detChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength));
	DESTROY_DET_TRACK_CHANNEL(detChannelId);
}

TEST(ftError, inputImagesCanNotBeFound)
{
	int outRst[50][4];
	int outLength;
	Mat image = imread("..//..//Images//ERROR//50x.jpg");
	
	int detChannelId = DEFAULT_DET_TRACK_CHANNEL();
	EXPECT_TRUE(IMG_DATA_ERROR == ISFaceDetectRgb(detChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength));
	DESTROY_DET_TRACK_CHANNEL(detChannelId);
}

TEST(ftError, inputImagesDetectedNoFace)
{
	int outRst[50][4];
	int outLength;
	Mat image = imread("..//..//Images//ERROR//502.jpg");
	
	imReadAndShowWithRect("..//..//Images//ERROR//502.jpg");

	int detChannelId = DEFAULT_DET_TRACK_CHANNEL();
	//检测不到人脸的时候应该返回DETECT_NO_FACE，实际返回SUCC？
	EXPECT_TRUE(SUCC == ISFaceDetectRgb(detChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength));
	EXPECT_TRUE(0 == outLength);
	DESTROY_DET_TRACK_CHANNEL(detChannelId);
}
