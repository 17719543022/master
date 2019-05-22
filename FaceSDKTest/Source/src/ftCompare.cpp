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
//	cout << "����ȡ����Ŀ¼��" << imgPath << endl;
//	cout << "�߳�����" << "���߳�" << endl;
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
//	cout << "����ͼƬ������" << images.size() << endl;
//	cout << "��ȡ����������������" << detectedNum << endl;
//	float percent = float(detectedNum)/images.size()*100;
//	cout << "������ȡ�ɹ��ʣ�" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
//	cout << "�����άǰ��������Ŀ¼��" << GConfig::getInstance().getFeaPath() << endl;
//	cout << "�ܹ���ʱ��" << getGap(tStart, tStop) << "����" << endl;
//	float timePerPic = float(getGap(tStart, tStop))/images.size();
//	cout << "����ͼƬ��ʱ��" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "����" << endl;
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
//	cout << "����ȡ����Ŀ¼��" << imgPath << endl;
//	cout << "�߳�����" << detectThreadNum << endl;
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
//	cout << "����ͼƬ������" << images.size() << endl;
//	cout << "�ܹ���ʱ��" << getGap(tStart, tStop) << "����" << endl;
//	float timePerPic = float(getGap(tStart, tStop))/images.size();
//	cout << "����ͼƬ��ʱ��" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "����" << endl;
//}
//
////ISCompareֻ֧��8192��feature
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
//	cout << "ISCompare AĿ¼��" << ISCompareA << endl;
//	cout << "ISCompare BĿ¼��" << ISCompareB << endl;
//	cout << "�����Աȷ�����ֵ��" << recongiseFaceValue << endl;
//	cout << "�߳�����" << "���߳�" << endl;
//	cout << ">>Outputs<<" << endl;
//
//	//�Ƚ�ISCompareBĿ¼��ͼƬ��ȡ�����������
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
//		/* ��feaĿ¼ */
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
//	//�ٽ�ISCompareAĿ¼�µ�ͼƬ��һ��ǰ�����������ļ��е������ļ�����ISCompare�Ա�
//	defaultFeatureChannel = DEFAULT_FEATURE_CHANNEL();
//	int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
//	fstream f;
//	char featureB[8192]; //���ʱ��ֻ����һ����������
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
//				cout << imageAs[i] << " + " << feaFiles[j] << " = �Ǳ��ˣ����������scoreֵС��\"�����Աȷ�����ֵ\"" << endl;
//			}
//			if(score >= recongiseFaceValue
//				&& 0 != strcmp(getFileHeader(imageAs[i].data()).data(), getFileHeader(feaFiles[j].data()).data()))
//			{
//				cout << imageAs[i] << " + " << feaFiles[j] << " = ���Ǳ��ˣ����������scoreֵ����\"�����Աȷ�����ֵ\"" << endl;
//			}
//		}
//	}
//	DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);
//	DESTROY_COMPARE_CHANNEL(defaultCompareChannel);
//
//	GetSystemTime(&tStop);
//
//	cout << "AĿ¼ͼƬ������" << imageAs.size() << endl;
//	cout << "AĿ¼��ȡ������������" << detectedNum << endl;
//	cout << "BĿ¼ͼƬ������" << imageBs.size() << endl;
//	cout << "BĿ¼��ȡ������������" << feaFiles.size() << endl;
//	cout << "�����Ա��ܹ���ʱ��" << getGap(tStart, tStop) << "����" << endl;
//	float timePerPic = float(getGap(tStart, tStop))/(detectedNum*feaFiles.size());
//	cout << "���������ԱȺ�ʱ��" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "����" << endl;
//}
