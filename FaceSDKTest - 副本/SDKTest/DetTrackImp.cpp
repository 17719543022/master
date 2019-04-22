#include "stdafx.h"
#include "DetTrackImp.h"
#include "ParamDef.h"
#include "SDK\ISDetTrack.h"


DetTrackImp::DetTrackImp(void):
	_detTrackChannel(-1)
{
}


DetTrackImp::~DetTrackImp(void)
{
}

DetTrackImp* DetTrackImp::GetInstance()
{
	return new DetTrackImp();
}

int DetTrackImp::CreateChannel()
{
	_detTrackChannel = ISCreateDetTrackChannelEx(MINFACESIZE, MAXFACESIZE, 2);
	return _detTrackChannel;
}

int DetTrackImp::DestoryChannel()
{
	return ISDestroyDetTrackChannel(_detTrackChannel);
}

int DetTrackImp::FaceDetect(char* img, int imgLen, int& faceNum)
{
	int outResult[20][4] = {0};
	int ret = ISFaceDetect(_detTrackChannel, img, imgLen, outResult, &faceNum);
	return ret;
}

int DetTrackImp::FaceDetectByPath(const char* path, int& faceNum)
{
	int outResult[20][4] = {0};
	int ret = ISFaceDetectPath(_detTrackChannel, (char*)path, outResult, &faceNum);
	return ret;
}


