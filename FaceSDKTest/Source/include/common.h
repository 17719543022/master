#ifndef INCL_COMMON_H
#define INCL_COMMON_H

#include "face_sdk.h"
#include "opencv.hpp"

using namespace cv;

#define DEFAULT_DET_TRACK_CHANNEL() ISCreateDetTrackChannel(46,1000,0);
#define DESTROY_DET_TRACK_CHANNEL(x) ISDestroyDetTrackChannel(x);
#define DEFAULT_FEATURE_CHANNEL() ISCreateFeatureChannel(0,0,0,0,0);
#define DESTROY_FEATURE_CHANNEL(x) ISDestroyFeatureChannel(x);
#define DEFAULT_COMPARE_CHANNEL() ISCreateCompareChannel();
#define DESTROY_COMPARE_CHANNEL(x) ISDestroyCompareChannel(x);

void imShowWithRect(char *name, Mat img, int outRst[][4], int len);
void imReadAndShow(char *imgPath);
void imReadAndShowWithRect(char *imgPath);
void switchShow(char *name, Mat image);

void faceDetectPath(char *imgPath, int outResult[][4], int *outLen);
void faceDetectRgb(char *imgData, int imgLen, int imgWidth, int imgHeight, int outResult[][4],int *outLen);

int getFeatureWithFacePosRgb(const char *imgPath, char *outFeature, int outResult[][4] = NULL, int *outLen = NULL);
void getFeatureRgb(char *imgData, int imgLen, int imgWidth, int imgHeight, char *outFeature, float KPtScore=0.5);
void getPcaFea(char* fea_Org,char* fea_Pca);

void compare(char *feature1, char *feature2, float *outScore);
void compareMN(char **featureM, int numM, char **featureN, int numN, float **outScore);

#endif
