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

		gap += (tStop.wMinute - tStart.wMinute)*60*1000;
		gap += (tStop.wSecond - tStart.wSecond)*1000;
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

	void *faceFeature(void *ptr1){
		vector<string> images = *(vector<string> *)ptr1;

		int defaultFeatureChannelId = DEFAULT_FEATURE_CHANNEL();
		char feature[8192];
		for(unsigned int i=0; i<images.size(); i++){
			Mat image = imread(images[i]);
			EXPECT_TRUE(SUCC == ISGetFeatureRgb(defaultFeatureChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, feature));
		}
		DESTROY_FEATURE_CHANNEL(defaultFeatureChannelId);

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

TEST(ftMultiThread, get1000FaceFeaturesWithSingleThreadAndDetermineCost)
{
	string imgPath = GConfig::getInstance().getImgPath();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);

	SYSTEMTIME	tStart, tStop;
	GetSystemTime(&tStart);

	int defaultFeatureChannelId = DEFAULT_FEATURE_CHANNEL();
	for(unsigned int i=0; i<images.size(); i++){
		Mat image = imread(images[i]);
		char feature[8192];
		EXPECT_TRUE(SUCC == ISGetFeatureRgb(defaultFeatureChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, feature));
	}
	DESTROY_FEATURE_CHANNEL(defaultFeatureChannelId);

	GetSystemTime(&tStop);

	cout << "单线程提取1000张人脸特征总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
}

TEST(ftMultiThread, get1000FaceFeaturesWithMultiThreadAndDetermineCost)
{
	string imgPath = GConfig::getInstance().getImgPath();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);

	unsigned int detectThreadNum = GConfig::getInstance().getGetFeaThreadNum();
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
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceFeature, (void *)&image[i]));
	}

	void *retVal;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

    GetSystemTime(&tStop);
	cout << "多线程提取1000张人脸特征总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
}
