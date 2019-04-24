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

void faceDetectPath(char *imgPath, int outResult[][4], int *outLen);

int getFeature(const char *imgPath,char *outFeature);

void compare(char *feature1, char *feature2, float *outScore);

#endif