#include "stdafx.h"
#include <gtest/gtest.h>
#include "opencv.hpp"
#include "testSuits.h"
#include "config.h"
#include "listOut.h"
#include <Windows.h>
#include "common.h"
#include <pthread.h>
#include <fstream>

using namespace std;
using namespace cv;

//
//TEST_F(ft, getFaceFeaturesOfAWholeDirectory_SingleThread)
//{
//	string imgPath = GConfig::getInstance().getImgPath();
//	vector<string> images;
//	listOutDirectoryFiles(imgPath, images);
//	detectedNum = 0;
//
//	cout << ">>Inputs <<" << endl;
//	cout << "待提取特征目录：" << imgPath << endl;
//	cout << "线程数：" << "单线程" << endl;
//	cout << ">>Outputs<<" << endl;
//
//	SYSTEMTIME	tStart, tStop;
//	GetSystemTime(&tStart);
//	char feature[5][8192];
//	fstream f;
//	string feaPath = GConfig::getInstance().getFeaPath();
//
//	int defaultFeatureChannelId = DEFAULT_FEATURE_CHANNEL();
//	for(unsigned int i=0; i<images.size(); i++){
//		if(SUCC != ISGetFeaturePath(defaultFeatureChannelId, const_cast<char *>(images[i].data()), feature[0])){
//			continue;
//		}
//
//		detectedNum++;
//		string saveFeaPath = feaPath + "\\" + getFileHeader(images[i].data()) + ".fea";
//		f.open(saveFeaPath, ios::out | ios::binary);
//		f.write(feature[0], sizeof(feature[0]));
//		f.close();
//		f.clear();
//	}
//	DESTROY_FEATURE_CHANNEL(defaultFeatureChannelId);
//
//	GetSystemTime(&tStop);
//
//	cout << "输入图片张数：" << images.size() << endl;
//	cout << "提取到人脸特征张数：" << detectedNum << endl;
//	float percent = float(detectedNum)/images.size()*100;
//	cout << "特征提取成功率：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
//	cout << "输出降维前的特征到目录：" << GConfig::getInstance().getFeaPath() << endl;
//	cout << "总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
//	float timePerPic = float(getGap(tStart, tStop))/images.size();
//	cout << "单张图片耗时：" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "毫秒" << endl;
//}
//
//TEST_F(ft, getFaceFeaturesOfAWholeDirectory_MultiThread)
//{
//	string imgPath = GConfig::getInstance().getImgPath();
//	vector<string> images;
//	listOutDirectoryFiles(imgPath, images);
//
//	unsigned int detectThreadNum = GConfig::getInstance().getGetFeaThreadNum();
//	int imgNumPerThread = int(images.size()/detectThreadNum);
//
//	cout << ">>Inputs <<" << endl;
//	cout << "待提取特征目录：" << imgPath << endl;
//	cout << "线程数：" << detectThreadNum << endl;
//	cout << ">>Outputs<<" << endl;
//
//	vector<vector<string>> image;
//	for(unsigned int i=0; i<detectThreadNum; i++){
//		image.push_back(vector<string>());
//		if(i == detectThreadNum-1){
//			image[i].assign(images.begin()+i*imgNumPerThread, images.end());
//		}
//		else{
//			image[i].assign(images.begin()+i*imgNumPerThread, images.begin()+(i+1)*imgNumPerThread);
//		}
//	}
//
//	SYSTEMTIME tStart, tStop;
//    GetSystemTime(&tStart);
//
//	vector<pthread_t> pThread(detectThreadNum);
//	for(unsigned int i=0; i<detectThreadNum; i++){
//		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceFeature, (void *)&image[i]));
//	}
//
//	void *retVal;
//	for(unsigned int i=0; i<detectThreadNum; i++){
//		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
//	}
//
//    GetSystemTime(&tStop);
//
//	cout << "输入图片张数：" << images.size() << endl;
//	cout << "总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
//	float timePerPic = float(getGap(tStart, tStop))/images.size();
//	cout << "单张图片耗时：" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "毫秒" << endl;
//}
//
////ISCompare只支持8192的feature
//TEST_F(ft, toISCompareBetweenTwoDirectoriesAccordingToCompareFaceValue_SingleThread)
//{
//	string ISCompareA = GConfig::getInstance().getISCompareA();
//	string ISCompareB = GConfig::getInstance().getISCompareB();
//	float recongiseFaceValue = GConfig::getInstance().getRecogniseFaceValue();
//	vector<string> imageAs;
//	vector<string> imageBs;
//	listOutDirectoryFiles(ISCompareA, imageAs);
//	listOutDirectoryFiles(ISCompareB, imageBs);
//	detectedNum = 0;
//
//	cout << ">>Inputs <<" << endl;
//	cout << "ISCompare A目录：" << ISCompareA << endl;
//	cout << "ISCompare B目录：" << ISCompareB << endl;
//	cout << "人脸对比分数阈值：" << recongiseFaceValue << endl;
//	cout << "线程数：" << "单线程" << endl;
//	cout << ">>Outputs<<" << endl;
//
//	//先将ISCompareB目录下图片提取特征后存起来
//	fstream fileFea;
//	string feaPath = GConfig::getInstance().getFeaPath();
//	string command = "rd /s /q " + feaPath;
//	system(command.c_str());
//	command = "mkdir " + feaPath;
//	system(command.c_str());
//
//	SYSTEMTIME tStart, tStop;
//    GetSystemTime(&tStart);
//
//	int defaultFeatureChannel = DEFAULT_FEATURE_CHANNEL();
//	for(unsigned int i=0; i<imageBs.size(); i++){
//		/* 存fea目录 */
//		char featureTemp[5][8192];
//		if(SUCC != ISGetFeaturePath(defaultFeatureChannel, const_cast<char *>(imageBs[i].data()), featureTemp[0])){
//			continue;
//		}
//
//		string saveFeaPath = feaPath + "\\" + getFileHeader(imageBs[i].data()) + ".fea";
//		fileFea.open(saveFeaPath, ios::out | ios::binary);
//		fileFea.write(featureTemp[0], sizeof(featureTemp[0]));
//		fileFea.close();
//		fileFea.clear();
//	}
//	DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);
//
//	//再将ISCompareA目录下的图片逐一与前面所存特征文件夹的特征文件进行ISCompare对比
//	defaultFeatureChannel = DEFAULT_FEATURE_CHANNEL();
//	int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
//	fstream f;
//	char featureB[8192]; //存的时候只存了一张人脸特征
//	char featureA[5][8192];
//	float score;
//
//	vector<string> feaFiles;
//	listOutDirectoryFiles(feaPath, feaFiles);
//
//	for(unsigned int i=0; i<imageAs.size(); i++){
//		if(SUCC != ISGetFeaturePath(defaultFeatureChannel, const_cast<char *>(imageAs[i].data()), featureA[0])){
//			continue;
//		}
//
//		detectedNum++;
//		for(unsigned int j=0; j<feaFiles.size(); j++){
//			f.open(feaFiles[j], ios::in | ios::binary);
//			f.seekg(0, ios::beg);
//			f.read(featureB, 8192);
//			f.clear();
//			f.close();
//
//			EXPECT_TRUE(SUCC == ISCompare(defaultCompareChannel, featureA[0], featureB, &score));
//			if(score < recongiseFaceValue 
//				&& 0 == strcmp(getFileHeader(imageAs[i].data()).data(), getFileHeader(feaFiles[j].data()).data()))
//			{
//				cout << imageAs[i] << " + " << feaFiles[j] << " = 是本人，但算出来的score值小于\"人脸对比分数阈值\"" << endl;
//			}
//			if(score >= recongiseFaceValue
//				&& 0 != strcmp(getFileHeader(imageAs[i].data()).data(), getFileHeader(feaFiles[j].data()).data()))
//			{
//				cout << imageAs[i] << " + " << feaFiles[j] << " = 不是本人，但算出来的score值大于\"人脸对比分数阈值\"" << endl;
//			}
//		}
//	}
//	DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);
//	DESTROY_COMPARE_CHANNEL(defaultCompareChannel);
//
//	GetSystemTime(&tStop);
//
//	cout << "A目录图片张数：" << imageAs.size() << endl;
//	cout << "A目录提取到特征张数：" << detectedNum << endl;
//	cout << "B目录图片张数：" << imageBs.size() << endl;
//	cout << "B目录提取到特征张数：" << feaFiles.size() << endl;
//	cout << "特征对比总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
//	float timePerPic = float(getGap(tStart, tStop))/(detectedNum*feaFiles.size());
//	cout << "单次特征对比耗时：" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "毫秒" << endl;
//}
