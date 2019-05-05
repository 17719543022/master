#ifndef INCL_COMMON_H
#define INCL_COMMON_H

#include "face_sdk.h"
#include "opencv.hpp"
#include <vector>

using namespace cv;

#define DEFAULT_DET_TRACK_CHANNEL() ISCreateDetTrackChannel(46, 1000, 0);
#define DESTROY_DET_TRACK_CHANNEL(x) ISDestroyDetTrackChannel(x);
#define DEFAULT_FEATURE_CHANNEL() ISCreateFeatureChannel(0, 0, 0, 0, 0);
#define PREDICT_FEATURE_CHANNEL() ISCreateFeatureChannel(1, 1, 1, 1, 1);
#define DESTROY_FEATURE_CHANNEL(x) ISDestroyFeatureChannel(x);
#define DEFAULT_COMPARE_CHANNEL() ISCreateCompareChannel();
#define DESTROY_COMPARE_CHANNEL(x) ISDestroyCompareChannel(x);

#define ALLOC_DOUBLE_STAR(m, n, type, star, tag) \
	vector<type*> target##tag(m);\
	vector<type> vec1##tag(n);\
	vector<vector<type>> vec2##tag;\
	for(int i=0; i<m; i++)\
	{\
		vec2##tag.push_back(vec1##tag);\
	}\
	for(int i=0; i<m; i++)\
	{\
		target##tag[i] = &*vec2##tag[i].begin();\
	}\
	star = target##tag.data();

void imCommonShow(char *name, Mat img, int outRst[][4], int len, int thickness = 2, int delay = 1000);
void imReadAndShow(char *imgPath);
void imCommonReadAndShow(char *imgPath, int thickness = 2, int delay = 1000);
void switchShow(char *name, Mat image);

void faceDetectPath(char *imgPath, int outRst[][4], int *outLen);
void faceDetectRgb(char *imgData, int imgLen, int imgWidth, int imgHeight, int outRst[][4], int *outLen);
void calFaceInfoRgb(char *imgData, int imgLen, int imgWidth, int imgHeight, int outRst[][4], int *outLen, int keyPoint[][6], float angle[][3], float kScore[]);

int getFeatureWithFacePosRgb(const char *imgPath, char *outFeature, int outRst[][4] = NULL, int *outLen = NULL);
void getFeatureRgb(char *imgData, int imgLen, int imgWidth, int imgHeight, char *outFeature, float KPtScore=0.5);
void getPcaFea(char* fea_Org, char* fea_Pca);
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
						  , float kScore=0.5);

void compare(char *feature1, char *feature2, float *outScore);
void compareMN(char **featureM, int numM, char **featureN, int numN, float **outScore);
void compareMNfaster(char **featureM, int numM, char **featureN, int numN, float **outScore);

#endif
