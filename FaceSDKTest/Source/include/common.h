#ifndef INCL_COMMON_H
#define INCL_COMMON_H

#include "face_sdk.h"

void getFeature(char *imgPath,char *outFeature);
void traverseDirectory(const char *dir,char *idCard,char *live,bool *over);

#endif