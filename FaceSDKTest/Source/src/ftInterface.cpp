#include "stdafx.h"
#include <gtest/gtest.h>
#include <iostream>
#include "face_sdk.h"
#include "common.h"
#include "opencv.hpp"
#include "log_format.h"

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
	int outRst[50][4] = {0};

	faceDetectPath(imgPath, outRst, &len);
	
	EXPECT_TRUE(len >= 15);
}

TEST(ftInterface, gotFeatureLengthBeCorrect)
{
	EXPECT_TRUE(8192 == ISGetFeatureLength());
}
