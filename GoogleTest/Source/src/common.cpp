#include "stdafx.h"
#include "common.h"
#include <iostream>
#include "sdk_error_code.h"
#include "log_format.h"
#include "opencv.hpp"
#include <gtest/gtest.h>
using namespace std;
using namespace cv;

void getFeature(char *imgPath,char *outFeature)
{
	int detChannelId = ISCreateDetTrackChannel(46,1000,0);
	int featureChannelId = ISCreateFeatureChannel(0,0,0,0,0);
	int outRst[50][4];
	int outLength;

	Mat image = imread(imgPath,1);
	EXPECT_TRUE(SUCC == ISFaceDetectRgb(detChannelId,(char*)image.data,image.rows*image.cols*3,image.cols,image.rows,outRst,&outLength));
	EXPECT_TRUE(SUCC == ISGetFeatureWithFacePosRgb(featureChannelId,(char*)image.data,image.rows*image.cols*3,image.cols,image.rows,outRst,1,outFeature));

	Rect rect = Rect(outRst[0][0],outRst[0][1],outRst[0][2]-outRst[0][0]+1,outRst[0][3]-outRst[0][1]+1);
	rectangle(image,rect,Scalar(0,0,255));
	imshow(imgPath,image);
	waitKey(10);
}