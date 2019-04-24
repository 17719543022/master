#ifndef INCL_COMMON_H
#define INCL_COMMON_H

#include "face_sdk.h"

void faceDetectPath(char *imgPath,int outResult[][4],int *outLen);

int getFeature(const char *imgPath,char *outFeature);

void compare(char *feature1, char *feature2, float *outScore);

#endif