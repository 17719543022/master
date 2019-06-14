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
#include <iostream>

using namespace cv;
using namespace std;

extern pthread_mutex_t mutex;
pthread_mutex_t mutex2;
int featureNumA;
int featureNumB;
int valueCountsSmall;
int valueCountsBig;

namespace{
	void *faceFeatureA(void *ptr){
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
				featureNumA++;
				pthread_mutex_unlock(&mutex);

				ISGetPcaFea(defaultFeatureChannel, feature[0], pca);
				string saveFeaPath = GConfig::getInstance().getFeatureAPath() + "\\" + getFileHeader(images[i].data()) + ".fea";
				fileF.open(saveFeaPath, ios::out | ios::binary);
				fileF.write(feature[0], sizeof(feature[0]));
				fileF.close();
				fileF.clear();

				string savePcaPath = GConfig::getInstance().getPcaAPath() + "\\" + getFileHeader(images[i].data()) + ".pca";
				fileP.open(savePcaPath, ios::out | ios::binary);
				fileP.write(pca, sizeof(pca));
				fileP.close();
				fileP.clear();
			}
		}
		DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);

		return NULL;
	}

	void *faceFeatureB(void *ptr){
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
				featureNumB++;
				pthread_mutex_unlock(&mutex);

				ISGetPcaFea(defaultFeatureChannel, feature[0], pca);
				string saveFeaPath = GConfig::getInstance().getFeatureBPath() + "\\" + getFileHeader(images[i].data()) + ".fea";
				fileF.open(saveFeaPath, ios::out | ios::binary);
				fileF.write(feature[0], sizeof(feature[0]));
				fileF.close();
				fileF.clear();

				string savePcaPath = GConfig::getInstance().getPcaBPath() + "\\" + getFileHeader(images[i].data()) + ".pca";
				fileP.open(savePcaPath, ios::out | ios::binary);
				fileP.write(pca, sizeof(pca));
				fileP.close();
				fileP.clear();
			}
		}
		DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);

		return NULL;
	}

	void *compare(void *ptr){
		vector<pthread_t> pThreads = *(vector<pthread_t> *)ptr;
		int pThreads_size = pThreads.size();

		unsigned int currentThreadIndex;
		for(int i=0; i<pThreads_size; i++){
			if(0 != pthread_equal(pthread_self(), pThreads[i])){
				currentThreadIndex = i;
			}
		}

		string feaAPath = GConfig::getInstance().getFeatureAPath();
		vector<string> featureAs;
		listOutDirectoryFiles(feaAPath, featureAs);
		unsigned int featureNumPerThread = unsigned int(featureAs.size()/pThreads_size);
		vector<string> featureAsOfCurrentThread;
		if(currentThreadIndex == pThreads_size-1){
			featureAsOfCurrentThread.assign(featureAs.begin()+currentThreadIndex*featureNumPerThread, featureAs.end());
		}
		else{
			featureAsOfCurrentThread.assign(featureAs.begin()+currentThreadIndex*featureNumPerThread, featureAs.begin()+(currentThreadIndex+1)*featureNumPerThread);
		}

		string featureBPath = GConfig::getInstance().getFeatureBPath();
		vector<string> featureBs;
		listOutDirectoryFiles(featureBPath, featureBs);
		float score;
		char featureA[8192];
		char featureB[8192];
		fstream fileA, fileB;

		int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
		float recongiseFaceValue = GConfig::getInstance().getRecogniseFaceValue();
		for(unsigned int i=0; i<featureAsOfCurrentThread.size(); i++){
			fileA.open(featureAsOfCurrentThread[i], ios::in | ios::binary);
			fileA.seekg(0, ios::beg);
			fileA.read(featureA, 8192);
			fileA.clear();
			fileA.close();
			for(unsigned int j=0; j<featureBs.size(); j++){
				fileB.open(featureBs[j], ios::in | ios::binary);
				fileB.seekg(0, ios::beg);
				fileB.read(featureB, 8192);
				fileB.clear();
				fileB.close();

				EXPECT_TRUE(SUCC == ISCompare( defaultCompareChannel
											 , featureA
											 , featureB
											 , &score));
				if(score < recongiseFaceValue 
					&& 0 == strcmp(getFileHeader(featureAsOfCurrentThread[i].data()).data(), getFileHeader(featureBs[j].data()).data()))
				{
					pthread_mutex_lock(&mutex);
					valueCountsBig++;
					pthread_mutex_unlock(&mutex);
				}
				if(score >= recongiseFaceValue
					&& 0 != strcmp(getFileHeader(featureAsOfCurrentThread[i].data()).data(), getFileHeader(featureBs[j].data()).data()))
				{
					pthread_mutex_lock(&mutex);
					valueCountsSmall++;
					pthread_mutex_unlock(&mutex);
				}
			}
		}

		DESTROY_COMPARE_CHANNEL(defaultCompareChannel);
		return NULL;
	}

	void *compareMN(void *ptr){
		vector<pthread_t> pThreads = *(vector<pthread_t> *)ptr;
		int pThreads_size = pThreads.size();

		unsigned int currentThreadIndex;
		for(int i=0; i<pThreads_size; i++){
			if(0 != pthread_equal(pthread_self(), pThreads[i])){
				currentThreadIndex = i;
			}
		}

		string pcaAPath = GConfig::getInstance().getPcaAPath();
		vector<string> pcaAs;
		listOutDirectoryFiles(pcaAPath, pcaAs);
		unsigned int pcaNumPerThread = unsigned int(pcaAs.size()/pThreads_size);
		vector<string> pcaAsOfCurrentThread;
		if(currentThreadIndex == pThreads_size-1){
			pcaAsOfCurrentThread.assign(pcaAs.begin()+currentThreadIndex*pcaNumPerThread, pcaAs.end());
		}
		else{
			pcaAsOfCurrentThread.assign(pcaAs.begin()+currentThreadIndex*pcaNumPerThread, pcaAs.begin()+(currentThreadIndex+1)*pcaNumPerThread);
		}
		int pcaAsOfCurrentThread_size = pcaAsOfCurrentThread.size();

		string pcaBPath = GConfig::getInstance().getPcaBPath();
		vector<string> pcaBs;
		listOutDirectoryFiles(pcaBPath, pcaBs);
		int pcaBs_size = pcaBs.size();
		char pcaTemp[2048];
		fstream fileA, fileB;

		int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
		float recongiseFaceValue = GConfig::getInstance().getRecogniseFaceValue();

		char **pcaB;
		ALLOC_DOUBLE_STAR(pcaBs_size, 2048, char, pcaB, N)
		for(int i=0; i<pcaBs_size; i++)
		{
			fileB.open(pcaBs[i], ios::in | ios::binary);
			fileB.seekg(0, ios::beg);
			fileB.read(pcaTemp, 2048);
			fileB.clear();
			fileB.close();

			memcpy(pcaB[i], pcaTemp, 2048);
		}

		float **score;
		ALLOC_DOUBLE_STAR(1, pcaBs_size, float, score, S)

		char **pcaA;
		ALLOC_DOUBLE_STAR(1, 2048, char, pcaA, M)
		for(int s=0; s<pcaAsOfCurrentThread_size; s++){
			fileA.open(pcaAsOfCurrentThread[s], ios::in | ios::binary);
			fileA.seekg(0, ios::beg);
			fileA.read(pcaTemp, 2048);
			fileA.clear();
			fileA.close();
			pcaA[0] = pcaTemp;

			EXPECT_TRUE(SUCC == ISCompareMN(defaultCompareChannel, pcaA, 1, pcaB, pcaBs_size, score));
			for(int t=0; t<pcaBs_size; t++){
				if(score[0][t]<recongiseFaceValue && getFileHeader(pcaAsOfCurrentThread[s].data())==getFileHeader(pcaBs[t].data()))
				{
					pthread_mutex_lock(&mutex);
					valueCountsBig++;
					pthread_mutex_unlock(&mutex);
				}
				if(score[0][t]>=recongiseFaceValue && getFileHeader(pcaAsOfCurrentThread[s].data())!=getFileHeader(pcaBs[t].data()))
				{
					pthread_mutex_lock(&mutex);
					valueCountsSmall++;
					pthread_mutex_unlock(&mutex);
				}
			}
		}

		DESTROY_COMPARE_CHANNEL(defaultCompareChannel);
		return NULL;
	}

	void *compareMNfaster(void *ptr){
		vector<pthread_t> pThreads = *(vector<pthread_t> *)ptr;
		int pThreads_size = pThreads.size();

		unsigned int currentThreadIndex;
		for(int i=0; i<pThreads_size; i++){
			if(0 != pthread_equal(pthread_self(), pThreads[i])){
				currentThreadIndex = i;
			}
		}

		string pcaAPath = GConfig::getInstance().getPcaAPath();
		vector<string> pcaAs;
		listOutDirectoryFiles(pcaAPath, pcaAs);
		unsigned int pcaNumPerThread = unsigned int(pcaAs.size()/pThreads_size);
		vector<string> pcaAsOfCurrentThread;
		if(currentThreadIndex == pThreads_size-1){
			pcaAsOfCurrentThread.assign(pcaAs.begin()+currentThreadIndex*pcaNumPerThread, pcaAs.end());
		}
		else{
			pcaAsOfCurrentThread.assign(pcaAs.begin()+currentThreadIndex*pcaNumPerThread, pcaAs.begin()+(currentThreadIndex+1)*pcaNumPerThread);
		}
		int pcaAsOfCurrentThread_size = pcaAsOfCurrentThread.size();

		//ISCompareMNfasterprep
		string pcaBPath = GConfig::getInstance().getPcaBPath();
		vector<string> pcaBs;
		listOutDirectoryFiles(pcaBPath, pcaBs);
		int pcaBs_size = pcaBs.size();
		char pcaTemp[2048];
		fstream fileA, fileB;

		int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
		float recongiseFaceValue = GConfig::getInstance().getRecogniseFaceValue();

		char **pcaB;
		ALLOC_DOUBLE_STAR(pcaBs_size, 2048, char, pcaB, N)
		for(int i=0; i<pcaBs_size; i++)
		{
			fileB.open(pcaBs[i], ios::in | ios::binary);
			fileB.seekg(0, ios::beg);
			fileB.read(pcaTemp, 2048);
			fileB.clear();
			fileB.close();

			memcpy(pcaB[i], pcaTemp, 2048);
		}

		EXPECT_TRUE(SUCC == ISCompareMNfasterprep(defaultCompareChannel, pcaB, pcaBs_size));
	
		//ISCompareMNfaster
		float **score;
		ALLOC_DOUBLE_STAR(1, pcaBs_size, float, score, S)

		char **pcaA;
		ALLOC_DOUBLE_STAR(1, 2048, char, pcaA, M)
		for(int s=0; s<pcaAsOfCurrentThread_size; s++){
			fileA.open(pcaAsOfCurrentThread[s], ios::in | ios::binary);
			fileA.seekg(0, ios::beg);
			fileA.read(pcaTemp, 2048);
			fileA.clear();
			fileA.close();
			pcaA[0] = pcaTemp;

			EXPECT_TRUE(SUCC == ISCompareMNfaster(defaultCompareChannel, pcaA, 1, score));
			for(int t=0; t<pcaBs_size; t++){
				if(score[0][t]<recongiseFaceValue && getFileHeader(pcaAsOfCurrentThread[s].data())==getFileHeader(pcaBs[t].data()))
				{
					pthread_mutex_lock(&mutex);
					valueCountsBig++;
					pthread_mutex_unlock(&mutex);
				}
				if(score[0][t]>=recongiseFaceValue && getFileHeader(pcaAsOfCurrentThread[s].data())!=getFileHeader(pcaBs[t].data()))
				{
					pthread_mutex_lock(&mutex);
					valueCountsSmall++;
					pthread_mutex_unlock(&mutex);
				}
			}
		}

		DESTROY_COMPARE_CHANNEL(defaultCompareChannel);
		return NULL;
	}
}

TEST_F(ftISCompare, prepareFeatureAndPcaRapidlyUsingMultiThread){
	SYSTEMTIME	tStart, tStop;
	GetSystemTime(&tStart);

	vector<string>paths(4);
	paths[0] = GConfig::getInstance().getFeatureAPath();
	paths[1] = GConfig::getInstance().getFeatureBPath();
	paths[2] = GConfig::getInstance().getPcaAPath();
	paths[3] = GConfig::getInstance().getPcaBPath();

	for(unsigned int i=0; i<paths.size(); i++){
		string command = "rd /s /q " + paths[i];
		system(command.c_str());
		command = "mkdir " + paths[i];
		system(command.c_str());
	}
	
	featureNumA = 0;
	featureNumB = 0;

	string imgAPath = GConfig::getInstance().getCompareImgAPath();
	vector<string> imageAs;
	listOutDirectoryFiles(imgAPath, imageAs);
	int imageAs_size = imageAs.size();
	string imgBPath = GConfig::getInstance().getCompareImgBPath();
	vector<string> imageBs;
	listOutDirectoryFiles(imgBPath, imageBs);
	int imageBs_size = imageBs.size();

	unsigned int detectThreadNum = GConfig::getInstance().getGetFeaThreadNum();
	int imgANumPerThread = int(imageAs_size/detectThreadNum);
	int imgBNumPerThread = int(imageBs_size/detectThreadNum);

	cout << "Please invoke this case first!!!" << endl;
	cout << "This case provides feature and pca for other cases" << endl;
	cout << ">>Inputs <<" << endl;
	cout << "Image directory A: " << GConfig::getInstance().getCompareImgAPath() << endl;
	cout << "Image directory B: " << GConfig::getInstance().getCompareImgBPath() << endl;
	cout << "Threads Num: " << GConfig::getInstance().getGetFeaThreadNum() << endl;
	cout << ">>Outputs<<" << endl;

	vector<vector<string>> imageA, imageB;
	for(unsigned int i=0; i<detectThreadNum; i++){
		imageA.push_back(vector<string>());
		imageB.push_back(vector<string>());
		if(i == detectThreadNum-1){
			imageA[i].assign(imageAs.begin()+i*imgANumPerThread, imageAs.end());
			imageB[i].assign(imageBs.begin()+i*imgBNumPerThread, imageBs.end());
		}
		else{
			imageA[i].assign(imageAs.begin()+i*imgANumPerThread, imageAs.begin()+(i+1)*imgANumPerThread);
			imageB[i].assign(imageBs.begin()+i*imgBNumPerThread, imageBs.begin()+(i+1)*imgBNumPerThread);
		}
	}

	vector<pthread_t> pThread(detectThreadNum);
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceFeatureA, (void *)&imageA[i]));
	}

	void *retVal;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceFeatureB, (void *)&imageB[i]));
	}

	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

	GetSystemTime(&tStop);
	cout << "picture num of image directory A: " << imageAs_size << endl;
	cout << "picture num got feature succ of image directory A: " << featureNumA << endl;
	float percent = float(featureNumA)/imageAs_size*100;
	cout << "success rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "picture num of image directory B: " << imageBs_size << endl;
	cout << "picture num got feature succ of image directory B: " << featureNumB << endl;
	percent = float(featureNumB)/imageBs_size*100;
	cout << "success rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "output feature of image directory A to: " << GConfig::getInstance().getFeatureAPath() << endl;
	cout << "output pca of image directory A to: " << GConfig::getInstance().getPcaAPath() << endl;
	cout << "output feature of image directory B to: " << GConfig::getInstance().getFeatureBPath() << endl;
	cout << "output pca of image directory B to: " << GConfig::getInstance().getPcaBPath() << endl;
	cout << "time cost: " << getGap(tStart, tStop) << "ms" << endl;
	float timePerPic = float(getGap(tStart, tStop))/(imageAs_size+imageBs_size);
	cout << "time cost per picture: " << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "ms" << endl;
}

//ISCompare only supports feature with length of 8192
TEST_F(ftISCompare, ISCompare_SingleThread){
	SYSTEMTIME tStart, tStop;
    GetSystemTime(&tStart);

	fstream f;
	char featureB[8192];
	char featureA[8192];

	string featureAPath = GConfig::getInstance().getFeatureAPath();
	vector<string> feaAFiles;
	listOutDirectoryFiles(featureAPath, feaAFiles);
	int feaAFiles_size = feaAFiles.size();
	string featureBPath = GConfig::getInstance().getFeatureBPath();
	vector<string> feaBFiles;
	listOutDirectoryFiles(featureBPath, feaBFiles);
	int feaBFiles_size = feaBFiles.size();

	valueCountsSmall = 0;
	valueCountsBig = 0;

	cout << ">>Inputs <<" << endl;
	cout << "Feature directory A: " << featureAPath << endl;
	cout << "Feature directory B: " << featureBPath << endl;
	cout << "Threads Num: " << "1" << endl;
	cout << ">>Outputs<<" << endl;

	int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
	float recongiseFaceValue = GConfig::getInstance().getRecogniseFaceValue();
	float score;
	for(int i=0; i<feaAFiles_size; i++){
		f.open(feaAFiles[i], ios::in | ios::binary);
		f.seekg(0, ios::beg);
		f.read(featureA, 8192);
		f.clear();
		f.close();
		for(int j=0; j<feaBFiles_size; j++){
			f.open(feaBFiles[j], ios::in | ios::binary);
			f.seekg(0, ios::beg);
			f.read(featureB, 8192);
			f.clear();
			f.close();
			EXPECT_TRUE(SUCC == ISCompare(defaultCompareChannel, featureA, featureB, &score));
			if(score < recongiseFaceValue 
				&& 0 == strcmp(getFileHeader(feaAFiles[i].data()).data(), getFileHeader(feaBFiles[j].data()).data()))
			{
				valueCountsBig++;
			}
			if(score >= recongiseFaceValue
				&& 0 != strcmp(getFileHeader(feaAFiles[i].data()).data(), getFileHeader(feaBFiles[j].data()).data()))
			{
				valueCountsSmall++;
			}
		}
	}
	DESTROY_COMPARE_CHANNEL(defaultCompareChannel);

	GetSystemTime(&tStop);

	cout << "feature num of feature directory A: " << feaAFiles_size << endl;
	cout << "feature num of feature directory B: " << feaBFiles_size << endl;
	cout << "for an identical person, but score less than compareFaceValue: " << valueCountsBig << endl;
	float percent = float(valueCountsBig)/feaAFiles_size*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "for two different persons, but score more than compareFaceValue: " << valueCountsSmall << endl;
	percent = float(valueCountsSmall)/feaAFiles_size*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "time cost: " << getGap(tStart, tStop) << "ms" << endl;
	cout << "compare times: " << feaAFiles_size*feaBFiles_size << endl;
	float timePerPic = float(getGap(tStart, tStop))/(feaAFiles_size*feaBFiles_size);
	cout << "time cost per compare: " << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "ms" << endl;
}

TEST_F(ftISCompare, ISCompare_MultiThread){
	SYSTEMTIME tStart, tStop;
    GetSystemTime(&tStart);
	valueCountsSmall = 0;
	valueCountsBig = 0;

	cout << ">>Inputs <<" << endl;
	cout << "Feature directory A: " << GConfig::getInstance().getFeatureAPath() << endl;
	cout << "Feature directory B: " << GConfig::getInstance().getFeatureBPath() << endl;
	unsigned int compareThreadNum = GConfig::getInstance().getCompareThreadNum();
	cout << "Threads Num: " << compareThreadNum << endl;
	cout << ">>Outputs<<" << endl;

	vector<pthread_t> pThreads(compareThreadNum);
	for(unsigned int m=0; m<compareThreadNum; m++){
		EXPECT_TRUE(SUCC == pthread_create(&pThreads[m], NULL, compare, &pThreads));
	}

	void *retVal;
	for(unsigned int n=0; n<compareThreadNum; n++){
		EXPECT_TRUE(SUCC == pthread_join(pThreads[n], &retVal));
	}

	GetSystemTime(&tStop);

	string imgAPath = GConfig::getInstance().getCompareImgAPath();
	vector<string> imageAs;
	listOutDirectoryFiles(imgAPath, imageAs);
	int imageAs_size = imageAs.size();

	string imgBPath = GConfig::getInstance().getCompareImgBPath();
	vector<string> imageBs;
	listOutDirectoryFiles(imgBPath, imageBs);
	int imageBs_size = imageBs.size();

	cout << "feature num of feature directory A: " << imageAs_size << endl;
	cout << "feature num of feature directory B: " << imageBs_size << endl;
	cout << "for an identical person, but score less than compareFaceValue: " << valueCountsBig << endl;
	float percent = float(valueCountsBig)/imageAs_size*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "for two different persons, but score more than compareFaceValue: " << valueCountsSmall << endl;
	percent = float(valueCountsSmall)/imageAs_size*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "time cost: " << getGap(tStart, tStop) << "ms" << endl;
	cout << "compare times: " << imageAs_size*imageBs_size << endl;
	float timePerPic = float(getGap(tStart, tStop))/(imageAs_size*imageBs_size);
	cout << "time cost per compare: " << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "ms" << endl;
}

//ISCompareMN/ISCompareMNfaster only support pca with length of 2048
TEST_F(ftISCompare, ISCompareMN_SingleThread){
	SYSTEMTIME tStart, tStop;
    GetSystemTime(&tStart);

	string pcaAPath = GConfig::getInstance().getPcaAPath();
	vector<string> pcaAs;
	listOutDirectoryFiles(pcaAPath, pcaAs);
	int pcaAs_size = pcaAs.size();
	string pcaBPath = GConfig::getInstance().getPcaBPath();
	vector<string> pcaBs;
	listOutDirectoryFiles(pcaBPath, pcaBs);
	int pcaBs_size = pcaBs.size();

	fstream fileA, fileB;
	char pcaTemp[2048];

	char **pcaB;
	ALLOC_DOUBLE_STAR(pcaBs_size, 2048, char, pcaB, N)
	for(int i=0; i<pcaBs_size; i++)
	{
		fileB.open(pcaBs[i], ios::in | ios::binary);
		fileB.seekg(0, ios::beg);
		fileB.read(pcaTemp, 2048);
		fileB.clear();
		fileB.close();

		memcpy(pcaB[i], pcaTemp, 2048);
	}

	float **score;
	ALLOC_DOUBLE_STAR(1, pcaBs_size, float, score, S)

	cout << ">>Inputs <<" << endl;
	cout << "Pca directory A: " << GConfig::getInstance().getPcaAPath() << endl;
	cout << "Pca directory B: " << GConfig::getInstance().getPcaBPath() << endl;
	cout << "Threads Num: " << "1" << endl;
	cout << ">>Outputs<<" << endl;

	valueCountsSmall = 0;
	valueCountsBig = 0;
	int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
	float recongiseFaceValue = GConfig::getInstance().getRecogniseFaceValue();

	//fill pcaA with just one fileA to prevent COMPARE_MN_ERROR
	char **pcaA;
	ALLOC_DOUBLE_STAR(1, 2048, char, pcaA, M)
	for(int s=0; s<pcaAs_size; s++){
		fileA.open(pcaAs[s], ios::in | ios::binary);
		fileA.seekg(0, ios::beg);
		fileA.read(pcaTemp, 2048);
		fileA.clear();
		fileA.close();

		pcaA[0] = pcaTemp;
		EXPECT_TRUE(SUCC == ISCompareMN(defaultCompareChannel, pcaA, 1, pcaB, pcaBs_size, score));
		for(int t=0; t<pcaBs_size; t++){
			if(score[0][t]<recongiseFaceValue && getFileHeader(pcaAs[s].data())==getFileHeader(pcaBs[t].data()))
			{
				valueCountsBig++;
			}
			if(score[0][t]>=recongiseFaceValue && getFileHeader(pcaAs[s].data())!=getFileHeader(pcaBs[t].data()))
			{
				valueCountsSmall++;
			}
		}
	}

	DESTROY_COMPARE_CHANNEL(defaultCompareChannel);
    GetSystemTime(&tStop);

	cout << "pca num of pca directory A: " << pcaAs_size << endl;
	cout << "pca num of pca directory B: " << pcaBs_size << endl;
	cout << "for an identical person, but score less than recongiseFaceValue: " << valueCountsBig << endl;
	float percent = float(valueCountsBig)/pcaAs_size*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "for two different persons, but score more than compareFaceValue: " << valueCountsSmall << endl;
	percent = float(valueCountsSmall)/pcaAs_size*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "time cost: " << getGap(tStart, tStop) << "ms" << endl;
	cout << "compare times: " << pcaAs_size*pcaBs_size << endl;
	float timePerPic = float(getGap(tStart, tStop))/(pcaAs_size*pcaBs_size);
	cout << "time cost per compare: " << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "ms" << endl;
}

TEST_F(ftISCompare, ISCompareMN_MultiThread){
	SYSTEMTIME tStart, tStop;
    GetSystemTime(&tStart);
	valueCountsSmall = 0;
	valueCountsBig = 0;

	cout << ">>Inputs <<" << endl;
	cout << "Pca directory A: " << GConfig::getInstance().getPcaAPath() << endl;
	cout << "Pca directory B: " << GConfig::getInstance().getPcaBPath() << endl;
	unsigned int recogniseThreadNum = GConfig::getInstance().getRecogniseThreadNum();
	cout << "Threads Num: " << recogniseThreadNum << endl;
	cout << ">>Outputs<<" << endl;

	vector<pthread_t> pThreads(recogniseThreadNum);
	for(unsigned int m=0; m<recogniseThreadNum; m++){
		EXPECT_TRUE(SUCC == pthread_create(&pThreads[m], NULL, compareMN, &pThreads));
	}

	void *retVal;
	for(unsigned int n=0; n<recogniseThreadNum; n++){
		EXPECT_TRUE(SUCC == pthread_join(pThreads[n], &retVal));
	}

	GetSystemTime(&tStop);

	string pcaAPath = GConfig::getInstance().getPcaAPath();
	vector<string> pcaAs;
	listOutDirectoryFiles(pcaAPath, pcaAs);
	int pcaAs_size = pcaAs.size();

	string pcaBPath = GConfig::getInstance().getPcaBPath();
	vector<string> pcaBs;
	listOutDirectoryFiles(pcaBPath, pcaBs);
	int pcaBs_size = pcaBs.size();

	cout << "pca num of pca directory A: " << pcaAs_size << endl;
	cout << "pca num of pca directory B: " << pcaBs_size << endl;
	cout << "for an identical person, but score less than recongiseFaceValue: " << valueCountsBig << endl;
	float percent = float(valueCountsBig)/pcaAs_size*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "for two different persons, but score more than compareFaceValue: " << valueCountsSmall << endl;
	percent = float(valueCountsSmall)/pcaAs_size*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "time cost: " << getGap(tStart, tStop) << "ms" << endl;
	cout << "compare times: " << pcaAs_size*pcaBs_size << endl;
	float timePerPic = float(getGap(tStart, tStop))/(pcaAs_size*pcaBs_size);
	cout << "time cost per compare: " << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "ms" << endl;
}

TEST_F(ftISCompare, ISCompareMNfaster_SingleThread){
	SYSTEMTIME tStart, tStop;
    GetSystemTime(&tStart);
	fstream fileA, fileB;

	// ISCompareMNfasterprep
	string pcaAPath = GConfig::getInstance().getPcaAPath();
	vector<string> pcaAs;
	listOutDirectoryFiles(pcaAPath, pcaAs);
	int pcaAs_size = pcaAs.size();
	string pcaBPath = GConfig::getInstance().getPcaBPath();
	vector<string> pcaBs;
	listOutDirectoryFiles(pcaBPath, pcaBs);
	int pcaBs_size = pcaBs.size();
	char pcaTemp[2048];

	char **pcaB;
	ALLOC_DOUBLE_STAR(pcaBs_size, 2048, char, pcaB, N)
	for(int i=0; i<pcaBs_size; i++)
	{
		fileB.open(pcaBs[i], ios::in | ios::binary);
		fileB.seekg(0, ios::beg);
		fileB.read(pcaTemp, 2048);
		fileB.clear();
		fileB.close();

		memcpy(pcaB[i], pcaTemp, 2048);
	}

	int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
	EXPECT_TRUE(SUCC == ISCompareMNfasterprep(defaultCompareChannel, pcaB, pcaBs_size));
	
	// ISCompareMNfaster
	float **score;
	ALLOC_DOUBLE_STAR(1, pcaBs_size, float, score, S)

	cout << ">>Inputs <<" << endl;
	cout << "Pca directory A: " << GConfig::getInstance().getPcaAPath() << endl;
	cout << "Pca directory B: " << GConfig::getInstance().getPcaBPath() << endl;
	cout << "Threads Num: " << "1" << endl;
	cout << ">>Outputs<<" << endl;
	
	valueCountsSmall = 0;
	valueCountsBig = 0;

	float recongiseFaceValue = GConfig::getInstance().getRecogniseFaceValue();
	char **pcaA;
	ALLOC_DOUBLE_STAR(1, 2048, char, pcaA, M)
	for(int s=0; s<pcaAs_size; s++){
		fileA.open(pcaAs[s], ios::in | ios::binary);
		fileA.seekg(0, ios::beg);
		fileA.read(pcaTemp, 2048);
		fileA.clear();
		fileA.close();

		pcaA[0] = pcaTemp;
		EXPECT_TRUE(SUCC == ISCompareMNfaster(defaultCompareChannel, pcaA, 1, score));
		for(int t=0; t<pcaBs_size; t++){
			if(score[0][t]<recongiseFaceValue && getFileHeader(pcaAs[s].data())==getFileHeader(pcaBs[t].data()))
			{
				valueCountsBig++;
			}
			if(score[0][t]>=recongiseFaceValue && getFileHeader(pcaAs[s].data())!=getFileHeader(pcaBs[t].data()))
			{
				valueCountsSmall++;
			}
		}
	}

	DESTROY_COMPARE_CHANNEL(defaultCompareChannel);
    GetSystemTime(&tStop);
	
	cout << "pca num of pca directory A: " << pcaAs_size << endl;
	cout << "pca num of pca directory B: " << pcaBs_size << endl;
	cout << "for an identical person, but score less than recongiseFaceValue: " << valueCountsBig << endl;
	float percent = float(valueCountsBig)/pcaAs_size*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "for two different persons, but score more than compareFaceValue: " << valueCountsSmall << endl;
	percent = float(valueCountsSmall)/pcaAs_size*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "time cost: " << getGap(tStart, tStop) << "ms" << endl;
	cout << "compare times: " << pcaAs_size*pcaBs_size << endl;
	float timePerPic = float(getGap(tStart, tStop))/(pcaAs_size*pcaBs_size);
	cout << "time cost per compare: " << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "ºÁÃë" << endl;
}

TEST_F(ftISCompare, ISCompareMNfaster_MultiThread){
	SYSTEMTIME tStart, tStop;
    GetSystemTime(&tStart);
	valueCountsSmall = 0;
	valueCountsBig = 0;

	cout << ">>Inputs <<" << endl;
	cout << "Pca directory A: " << GConfig::getInstance().getPcaAPath() << endl;
	cout << "Pca directory B: " << GConfig::getInstance().getPcaBPath() << endl;
	unsigned int recogniseThreadNum = GConfig::getInstance().getRecogniseThreadNum();
	cout << "Threads Num: " << recogniseThreadNum << endl;
	cout << ">>Outputs<<" << endl;

	vector<pthread_t> pThreads(recogniseThreadNum);
	for(unsigned int m=0; m<recogniseThreadNum; m++){
		EXPECT_TRUE(SUCC == pthread_create(&pThreads[m], NULL, compareMNfaster, &pThreads));
	}

	void *retVal;
	for(unsigned int n=0; n<recogniseThreadNum; n++){
		EXPECT_TRUE(SUCC == pthread_join(pThreads[n], &retVal));
	}

	GetSystemTime(&tStop);

	string pcaAPath = GConfig::getInstance().getPcaAPath();
	vector<string> pcaAs;
	listOutDirectoryFiles(pcaAPath, pcaAs);
	int pcaAs_size = pcaAs.size();

	string pcaBPath = GConfig::getInstance().getPcaBPath();
	vector<string> pcaBs;
	listOutDirectoryFiles(pcaBPath, pcaBs);
	int pcaBs_size = pcaBs.size();

	cout << "pca num of pca directory A: " << pcaAs_size << endl;
	cout << "pca num of pca directory B: " << pcaBs_size << endl;
	cout << "for an identical person, but score less than recongiseFaceValue: " << valueCountsBig << endl;
	float percent = float(valueCountsBig)/pcaAs_size*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "for two different persons, but score more than compareFaceValue: " << valueCountsSmall << endl;
	percent = float(valueCountsSmall)/pcaAs_size*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "time cost: " << getGap(tStart, tStop) << "ms" << endl;
	cout << "compare times: " << pcaAs_size*pcaBs_size << endl;
	float timePerPic = float(getGap(tStart, tStop))/(pcaAs_size*pcaBs_size);
	cout << "time cost per compare: " << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "ms" << endl;
}
