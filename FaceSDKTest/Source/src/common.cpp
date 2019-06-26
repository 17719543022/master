#ifdef WIN32
#include "opencv.hpp"
#endif
#ifdef LINUX
#include "opencv2/opencv.hpp"
#endif
#include "common.h"
#include <iostream>
#include "sdk_error_code.h"
#include "log_format.h"
#include <gtest/gtest.h>

using namespace std;
using namespace cv;

bool viewSwitch = true;

namespace{
	char *getFilename(char *p)
	{
		char ch = '/';
		char *q = strrchr(p, ch) + 1;
 
		return q;
	}

	void switchShow(char *name, Mat image)
	{
		if(viewSwitch)
		{
			imshow(name, image);
		}
	}
}

#ifdef WIN32
int getGap(SYSTEMTIME tStart, SYSTEMTIME tStop){
	int gap = 0;

	gap += (tStop.wHour - tStart.wHour)*60*60*1000;
	gap += (tStop.wMinute - tStart.wMinute)*60*1000;
	gap += (tStop.wSecond - tStart.wSecond)*1000;
	gap += tStop.wMilliseconds - tStart.wMilliseconds;

	return gap;
}
#endif

#ifdef WIN32
string getFileHeader(const char *p){
	char slash = '\\';
	const char *q = strrchr(p, slash) + 1;
	char dot = '.';
	const char *t = strrchr(p, dot);

	return string(q, t);
}

string slashConvert(string& str, char beReplaced, char toReplace){
	string strTemp = str;

	for(unsigned int i=0; i<strTemp.length(); i++){
		if (strTemp[i] == beReplaced)
			strTemp[i] = toReplace;
	}

	return strTemp;
}
#endif

string upperDirectory(string& str){
	char slash = '/';
	const char *q = strrchr(str.data(), slash);

	return string(str.data(), q);
}

#ifdef LINUX
string getFileHeader(const char *p){
	char slash ='/';
	const char *q = strrchr(p, slash) + 1;
	char dot = '.';
	const char *t = strrchr(p, dot);

	return string(q, t);
}

string slashConvert(string& str, char toReplace, char beReplaced){
	string strTemp = str;

	return strTemp;
}
#endif

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
	Mat image = imread(imgPath);

	switchShow(getFilename(imgPath), image);
	waitKey();
}

void imCommonReadAndShow(char *imgPath, int thickness, int delay)
{
	int outRst[50][4];
	int len;
	Mat image = imread(imgPath);

	int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
	EXPECT_TRUE(SUCC == ISFaceDetectRgb(defaultDetTrackChannel, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &len));
	DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);

	imCommonShow(getFilename(imgPath), image, outRst, len, thickness, delay);
}

void getFeatureAndPredict(int defaultFeatureChannel
						  , char *imgData
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
	EXPECT_TRUE_EX(ISGetFeatureRgb(defaultFeatureChannel, imgData, imgLen, imgWidth, imgHeight, vec.data()));
#ifdef WIN32
	EXPECT_TRUE_EX(ISpredictExpression(defaultFeatureChannel, vec.data(), expression));
	EXPECT_TRUE_EX(ISpredictGlasses(defaultFeatureChannel, vec.data(), glasses));
	EXPECT_TRUE_EX(ISpredictSmile(defaultFeatureChannel, vec.data(), smile));
	EXPECT_TRUE_EX(ISpredictAgeGender(defaultFeatureChannel, vec.data(), age, gender));
	EXPECT_TRUE_EX(ISpredictBeauty(defaultFeatureChannel, vec.data(), beauty));
#endif
}
