#include "stdafx.h"
#include <stdlib.h>
#include <pthread.h>
#include <gtest/gtest.h>
#include "config.h"
#include "listOut.h"
#include "common.h"
#include "face_sdk.h"
#include <iostream>
#include <Windows.h>
using namespace std;

namespace{
	int getGap(SYSTEMTIME tStart, SYSTEMTIME tStop){
		int gap = 0;
		
		gap += (tStop.wSecond - tStart.wSecond)*1000;
		if(tStop.wSecond < tStart.wSecond){
			gap += 60*1000;
		}

		gap += tStop.wMilliseconds - tStart.wMilliseconds;

		return gap;
	}

	void *faceDetect(void *ptr){
		vector<string> images = *(vector<string> *)ptr;
		int len = 0;
		int outRst[50][4] = {0};

		int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
		for(unsigned int i=0; i<images.size(); i++){
			char* image = const_cast<char*>(images[i].data());
			EXPECT_TRUE(SUCC == ISFaceDetectPath(defaultDetTrackChannel, image, outRst, &len));
		}
		DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);

		return NULL;
	}
}

TEST(ftMultiThread, dumpConfigFileOfIniFormat)
{
	GConfig::getInstance().dump();
}

TEST(ftMultiThread, detect1000FacesWithSingleThreadAndDetermineCost)
{
	string imgPath = GConfig::getInstance().getImgPath();
	vector<string> images;
	int len = 0;
	int outRst[50][4] = {0};

	listOutDirectoryFiles(imgPath, images);

	SYSTEMTIME tStart, tStop;
    GetSystemTime(&tStart);
	
	int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
	for(unsigned int i=0; i<images.size(); i++){
		char* image = const_cast<char*>(images[i].data());
		EXPECT_TRUE(SUCC == ISFaceDetectPath(defaultDetTrackChannel, image, outRst, &len));
	}
	DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);

	GetSystemTime(&tStop);

	cout << "单线程检测1000张人脸总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
}

TEST(ftMultiThread, detect1000FacesWithMultiThreadAndDetermineCost)
{
	string imgPath = GConfig::getInstance().getImgPath();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);

	unsigned int detectThreadNum = GConfig::getInstance().getDetectThreadNum();
	int imgNumPerThread = int(images.size()/detectThreadNum);

	vector<vector<string>> image;
	for(unsigned int i=0; i<detectThreadNum; i++){
		image.push_back(vector<string>());
		if(i == detectThreadNum-1){
			image[i].assign(images.begin()+i*imgNumPerThread, images.end());
		}
		else{
			image[i].assign(images.begin()+i*imgNumPerThread, images.begin()+(i+1)*imgNumPerThread);
		}
	}

	SYSTEMTIME tStart, tStop;
    GetSystemTime(&tStart);

	pthread_t pThread[10];
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceDetect, (void *)&image[i]));
	}

	void *retVal;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

    GetSystemTime(&tStop);
	cout << "多线程检测1000张人脸总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
}
