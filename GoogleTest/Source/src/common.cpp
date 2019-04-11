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
	if(outLength==0)
	{
		return;
	}
	EXPECT_TRUE(SUCC == ISGetFeatureWithFacePosRgb(featureChannelId,(char*)image.data,image.rows*image.cols*3,image.cols,image.rows,outRst,1,outFeature));

	Rect rect = Rect(outRst[0][0],outRst[0][1],outRst[0][2]-outRst[0][0]+1,outRst[0][3]-outRst[0][1]+1);
	rectangle(image,rect,Scalar(0,0,255));
	imshow(imgPath,image);
	waitKey(10);

	ISDestroyDetTrackChannel(detChannelId);
	ISDestroyFeatureChannel(featureChannelId);
}

void traverseDirectory(const char *dir,char *idCard,char *live,bool *over)
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
