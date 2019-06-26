#ifndef INCL_COMMON_H
#define INCL_COMMON_H

#ifdef WIN32
#include <Windows.h>
#include "opencv.hpp"
#endif
#ifdef LINUX
#include "opencv2/opencv.hpp"
#endif
#include "face_sdk.h"
#include <vector>

using namespace cv;

#define DEFAULT_DET_TRACK_CHANNEL() ISCreateDetTrackChannel(46, 1000);
#define DESTROY_DET_TRACK_CHANNEL(x) ISDestroyDetTrackChannel(x);
#define DEFAULT_FEATURE_CHANNEL() ISCreateFeatureChannel();
#define DESTROY_FEATURE_CHANNEL(x) ISDestroyFeatureChannel(x);
#define DEFAULT_COMPARE_CHANNEL() ISCreateCompareChannel();
#define DESTROY_COMPARE_CHANNEL(x) ISDestroyCompareChannel(x);

#define ALLOC_DOUBLE_STAR(m, n, type, star, tag) \
	vector<type*> target##tag(m);\
	vector<type> vec1##tag(n);\
	vector<vector<type> > vec2##tag;\
	for(int i=0; i<m; i++)\
	{\
		vec2##tag.push_back(vec1##tag);\
	}\
	for(int i=0; i<m; i++)\
	{\
		target##tag[i] = &*vec2##tag[i].begin();\
	}\
	star = target##tag.data();

#ifdef WIN32
int getGap(SYSTEMTIME tStart, SYSTEMTIME tStop);
#endif
string slashConvert(string& str, char beReplaced, char toReplace);
string upperDirectory(string& str);
string getFileHeader(const char *p);

void imCommonShow(char *name, Mat img, int outRst[][4], int len, int thickness = 2, int delay = 1000);
void imReadAndShow(char *imgPath);
void imCommonReadAndShow(char *imgPath, int thickness = 2, int delay = 1000);

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
						  , float kScore=0.5);

#endif
