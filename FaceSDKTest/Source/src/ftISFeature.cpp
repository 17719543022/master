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
#include "log_format.h"

using namespace std;
using namespace cv;

extern pthread_mutex_t mutex;
int featureNum;

namespace{
	void *faceFeature(void *ptr){
		vector<string> images = *(vector<string> *)ptr;

		int defaultFeatureChannel = DEFAULT_FEATURE_CHANNEL();
		char feature[5][8192];
		char pca[2048];
		fstream fileF, fileP;
		for(unsigned int i=0; i<images.size(); i++){
			if(SUCC != ISGetFeaturePath(defaultFeatureChannel, const_cast<char *>(images[i].data()), feature[0])){
				continue;
			}
			else{
				pthread_mutex_lock(&mutex);
				featureNum++;
				pthread_mutex_unlock(&mutex);
				ISGetPcaFea(defaultFeatureChannel, feature[0], pca);
				string saveFeaPath = GConfig::getInstance().getFeaMPath() + "\\" + getFileHeader(images[i].data()) + ".fea";
				fileF.open(saveFeaPath, ios::out | ios::binary);
				fileF.write(feature[0], sizeof(feature[0]));
				fileF.close();
				fileF.clear();

				string savePcaPath = GConfig::getInstance().getPcaMPath() + "\\" + getFileHeader(images[i].data()) + ".pca";
				fileP.open(savePcaPath, ios::out | ios::binary);
				fileP.write(pca, sizeof(pca));
				fileP.close();
				fileP.clear();
			}
		}
		DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);

		return NULL;
	}
}

TEST_F(ftISFeature, ISGetFeaturePath_SingleThread)
{
	SYSTEMTIME	tStart, tStop;
	GetSystemTime(&tStart);
	string imgPath = GConfig::getInstance().getFeatureImgPath();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);
	featureNum = 0;

	cout << ">>Inputs <<" << endl;
	cout << "待提取特征目录：" << imgPath << endl;
	cout << "线程数：" << "单线程" << endl;
	cout << ">>Outputs<<" << endl;

	char feature[5][8192];
	char pca[2048];
	fstream fileF, fileP;
	string feaPath = GConfig::getInstance().getFeaSPath();
	string pcaPath = GConfig::getInstance().getPcaSPath();

	int defaultFeatureChannel = DEFAULT_FEATURE_CHANNEL();
	for(unsigned int i=0; i<images.size(); i++){
		if(SUCC != ISGetFeaturePath(defaultFeatureChannel, const_cast<char *>(images[i].data()), feature[0])){
			continue;
		}

		ISGetPcaFea(defaultFeatureChannel, feature[0], pca);
		featureNum++;
		string saveFeaPath = feaPath + "\\" + getFileHeader(images[i].data()) + ".fea";
		fileF.open(saveFeaPath, ios::out | ios::binary);
		fileF.write(feature[0], sizeof(feature[0]));
		fileF.close();
		fileF.clear();

		string savePcaPath = pcaPath + "\\" + getFileHeader(images[i].data()) + ".pca";
		fileP.open(savePcaPath, ios::out | ios::binary);
		fileP.write(pca, sizeof(pca));
		fileP.close();
		fileP.clear();
	}
	DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);

	GetSystemTime(&tStop);

	cout << "输入图片张数：" << images.size() << endl;
	cout << "提取到人脸特征张数：" << featureNum << endl;
	float percent = float(featureNum)/images.size()*100;
	cout << "特征提取成功率：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "输出降维前的特征到目录：" << feaPath << endl;
	cout << "输出降维后的特征到目录：" << pcaPath << endl;
	cout << "总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
	float timePerPic = float(getGap(tStart, tStop))/images.size();
	cout << "单张图片耗时：" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "毫秒" << endl;
}

TEST_F(ftISFeature, ISGetFeaturePath_MultiThread)
{
	SYSTEMTIME tStart, tStop;
    GetSystemTime(&tStart);
	string imgPath = GConfig::getInstance().getFeatureImgPath();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);
	featureNum = 0;

	unsigned int detectThreadNum = GConfig::getInstance().getGetFeaThreadNum();
	int imgNumPerThread = int(images.size()/detectThreadNum);

	cout << ">>Inputs <<" << endl;
	cout << "待提取特征目录：" << imgPath << endl;
	cout << "线程数：" << detectThreadNum << endl;
	cout << ">>Outputs<<" << endl;

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

	vector<pthread_t> pThread(detectThreadNum);
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceFeature, (void *)&image[i]));
	}

	void *retVal;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

    GetSystemTime(&tStop);

	cout << "输入图片张数：" << images.size() << endl;
	cout << "提取到人脸特征张数：" << featureNum << endl;
	float percent = float(featureNum)/images.size()*100;
	cout << "特征提取成功率：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "输出降维前的特征到目录：" << GConfig::getInstance().getFeaMPath() << endl;
	cout << "输出降维后的特征到目录：" << GConfig::getInstance().getPcaMPath() << endl;
	cout << "总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
	float timePerPic = float(getGap(tStart, tStop))/images.size();
	cout << "单张图片耗时：" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "毫秒" << endl;
}

TEST_F(ftISFeature, ISGetFeaturePath_OutResultCheck)
{
	string feaS = GConfig::getInstance().getFeaSPath();
	vector<string> feaSNames;
	listOutDirectoryFiles(feaS, feaSNames);
	string pcaS = GConfig::getInstance().getPcaSPath();
	vector<string> pcaSNames;
	listOutDirectoryFiles(pcaS, pcaSNames);

	string feaM = GConfig::getInstance().getFeaMPath();
	vector<string> feaMNames;
	listOutDirectoryFiles(feaM, feaMNames);
	string pcaM = GConfig::getInstance().getPcaMPath();
	vector<string> pcaMNames;
	listOutDirectoryFiles(pcaM, pcaMNames);

	EXPECT_TRUE(feaSNames.size()==feaMNames.size());
	EXPECT_TRUE(feaSNames.size()==pcaSNames.size());
	EXPECT_TRUE(pcaMNames.size()==feaMNames.size());

	fstream fFeaS;
	fstream fPcaS;
	fstream fFeaM;
	fstream fPcaM;
	int lenFea = 8192;
	int lenPca = 2048;
	char featureS[8192];
	char pcaFeatureS[8192];
	char featureM[8192];
	char pcaFeatureM[8192];

	for(unsigned int i=0; i<feaSNames.size(); i++){
		fFeaS.open(feaSNames[i], ios::in | ios::binary);
		fFeaS.read(featureS, 8192);
		fFeaS.clear();
		fFeaS.close();

		fFeaM.open(feaMNames[i], ios::in | ios::binary);
		fFeaM.read(featureM, 8192);
		fFeaM.clear();
		fFeaM.close();

		for(int j=0; j<8192; j++){
			EXPECT_TRUE(featureS[j]==featureM[j]);
		}

		fPcaS.open(pcaSNames[i], ios::in | ios::binary);
		fPcaS.read(pcaFeatureS, 2048);
		fPcaS.clear();
		fPcaS.close();

		fPcaM.open(pcaMNames[i], ios::in | ios::binary);
		fPcaM.read(pcaFeatureM, 2048);
		fPcaM.clear();
		fPcaM.close();

		for(int j=0; j<2048; j++){
			EXPECT_TRUE(pcaFeatureS[j]==pcaFeatureM[j]);
		}
	}

	cout << "单线程和多线程ISGetFeaturePath函数返回的feature、pca完全一致！" << endl;
}