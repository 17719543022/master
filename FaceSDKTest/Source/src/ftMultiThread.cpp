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
#include <fstream>
using namespace std;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

namespace{
	string getFileHeader(const char *p){
		char slash = '\\';
		const char *q = strrchr(p, slash) + 1;
		char dot = '.';
		const char *t = strrchr(p, dot);

		return string(q, t);
	}

	int getGap(SYSTEMTIME tStart, SYSTEMTIME tStop){
		int gap = 0;

		gap += (tStop.wHour - tStart.wHour)*60*60*1000;
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

	void *faceFeature(void *ptr){
		vector<string> images = *(vector<string> *)ptr;

		int defaultFeatureChannelId = DEFAULT_FEATURE_CHANNEL();
		char feature[8192];
		for(unsigned int i=0; i<images.size(); i++){
			Mat image = imread(images[i]);
			EXPECT_TRUE(SUCC == ISGetFeatureRgb(defaultFeatureChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, feature));
		}
		DESTROY_FEATURE_CHANNEL(defaultFeatureChannelId);

		return NULL;
	}

	struct ThreadEssentials{
		pthread_t pThread;
		int featureChannel;
		int compareChannel;
	};

	void *faceCompare(void *ptr){
		// ����ó���ǰ�߳����߳������е�index���Ա�����õ���Ӧ�����
		vector<ThreadEssentials> essentials = *(vector<ThreadEssentials> *)ptr;
		unsigned int currentThreadIndex;
		for(unsigned int i=0; i<essentials.size(); i++){
			if(0 != pthread_equal(pthread_self(), essentials[i].pThread)){
				currentThreadIndex = i;
			}
		}

		// ����ó���ǰ�߳���Ҫ�����imgNumPerThread��ͼƬ�ĵ�ַ��������imagesOfCurrentThread��
		string imgPath = GConfig::getInstance().getImgPath();
		vector<string> images;
		listOutDirectoryFiles(imgPath, images);
		unsigned int imgNumPerThread = unsigned int(images.size()/essentials.size());
		vector<string> imagesOfCurrentThread;
		if(currentThreadIndex == essentials.size()-1){
			imagesOfCurrentThread.assign(images.begin()+currentThreadIndex*imgNumPerThread, images.end());
		}
		else{
			imagesOfCurrentThread.assign(images.begin()+currentThreadIndex*imgNumPerThread, images.begin()+(currentThreadIndex+1)*imgNumPerThread);
		}

		// ���������ǰ�̴߳����imgNumPerThread��ͼƬ����getFeaPath()�е�����feaFiles����Compare
		float recongiseFaceValue = GConfig::getInstance().getRecogniseFaceValue();
		vector<string> feaFiles;
		string feaPath = GConfig::getInstance().getFeaPath();
		listOutDirectoryFiles(feaPath, feaFiles);
		float score;
		char feaSaved[8192];
		char feature[8192];
		fstream f;

		// ��һ��ѭ����ȡ�ָ����̵߳�imagesOfCurrentThread��һ��ͼƬ������
		for(unsigned int i=0; i<imagesOfCurrentThread.size(); i++){
			Mat image = imread(imagesOfCurrentThread[i]);

			EXPECT_TRUE(SUCC == ISGetFeatureRgb( essentials[currentThreadIndex].featureChannel
											   , (char *)image.data
											   , image.rows*image.cols*3
											   , image.cols
											   , image.rows
											   , feature));
			// �ڶ��㽫��ȡ�����������ļ�Ŀ¼�е�ÿ�������ļ�����compare
			for(unsigned int j=0; j<feaFiles.size(); j++){
				f.open(feaFiles[j], ios::in | ios::binary);
				f.seekg(0, ios::beg);
				f.read(feaSaved, 8192);
				f.clear();
				f.close();

				EXPECT_TRUE(SUCC == ISCompare( essentials[currentThreadIndex].compareChannel
											 , feature
											 , feaSaved
											 , &score));
				//if(score < recongiseFaceValue 
				//	&& 0 == strcmp(getFileHeader(imagesOfCurrentThread[i].data()).data(), getFileHeader(feaFiles[j].data()).data()))
				//{
				//	pthread_mutex_lock(&mutex);
				//	cout << imagesOfCurrentThread[i] << " + " << feaFiles[j] << " = �Ǳ��ˣ����������scoreֵС��recongiseFaceValue" << endl;
				//	pthread_mutex_unlock(&mutex);
				//}
				//if(score >= recongiseFaceValue
				//	&& 0 != strcmp(getFileHeader(imagesOfCurrentThread[i].data()).data(), getFileHeader(feaFiles[j].data()).data()))
				//{
				//	pthread_mutex_lock(&mutex);
				//	cout << imagesOfCurrentThread[i] << " + " << feaFiles[j] << " = ���Ǳ��ˣ����������scoreֵ����recongiseFaceValue" << endl;
				//	pthread_mutex_unlock(&mutex);
				//}
			}
		}

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

	cout << "���̼߳��1000�������ܹ���ʱ��" << getGap(tStart, tStop) << "����" << endl;
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

	vector<pthread_t> pThread(detectThreadNum);
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceDetect, (void *)&image[i]));
	}

	void *retVal;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

    GetSystemTime(&tStop);
	cout << "���̼߳��1000�������ܹ���ʱ��" << getGap(tStart, tStop) << "����" << endl;
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

	cout << "���߳���ȡ1000�����������ܹ���ʱ��" << getGap(tStart, tStop) << "����" << endl;
}

TEST(ftMultiThread, get1000FacePcaFeaturesWithSingleThreadAndSave)
{
	string imgPath = GConfig::getInstance().getImgPath();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);

	fstream fileFea, filePca;
	string feaPath = GConfig::getInstance().getFeaPath();
	string pcaFeaPath = GConfig::getInstance().getPcaFeaPath();

	int defaultFeatureChannelId = DEFAULT_FEATURE_CHANNEL();
	for(unsigned int i=0; i<images.size(); i++){
		/* ��feaĿ¼ */
		Mat image = imread(images[i]);
		char feature[8192];
		EXPECT_TRUE(SUCC == ISGetFeatureRgb(defaultFeatureChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, feature));

		string saveFeaPath = feaPath + "\\" + getFileHeader(images[i].data()) + ".fea";
		cout << saveFeaPath << endl;

		fileFea.open(saveFeaPath, ios::out | ios::binary);
		fileFea.write(feature, sizeof(feature));
		fileFea.close();
		fileFea.clear();

		/* ��pcaĿ¼ */
		char pcaFeature[2048];
		EXPECT_TRUE(SUCC == ISGetPcaFea(defaultFeatureChannelId, feature, pcaFeature));

		string savePcaFeaPath = pcaFeaPath + "\\" + getFileHeader(images[i].data()) + ".pca";
		cout << savePcaFeaPath << endl;

		filePca.open(savePcaFeaPath, ios::out | ios::binary);
		filePca.write(pcaFeature, sizeof(pcaFeature));
		filePca.close();
		filePca.clear();
	}
	DESTROY_FEATURE_CHANNEL(defaultFeatureChannelId);
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

	vector<pthread_t> pThread(detectThreadNum);
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceFeature, (void *)&image[i]));
	}

	void *retVal;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

    GetSystemTime(&tStop);
	cout << "���߳���ȡ1000�����������ܹ���ʱ��" << getGap(tStart, tStop) << "����" << endl;
}

TEST(ftMultiThread, toPointOutTheRecogniseFaceValueStatisfiedFeaFileOfAGivenImage)
{
	string path = "..\\..\\Images\\image\\250.jpg";
	char feature[8192];
	Mat image = imread(path);
	
	getFeatureRgb((char *)image.data, image.rows*image.cols*3, image.cols, image.rows, feature);

	float recongiseFaceValue = GConfig::getInstance().getRecogniseFaceValue();
	vector<string> feaFiles;
	string feaPath = GConfig::getInstance().getFeaPath();
	listOutDirectoryFiles(feaPath, feaFiles);

	float score;
	char feaSaved[8192];
	fstream f;
	int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
	for(unsigned int i=0; i<feaFiles.size(); i++){
		f.open(feaFiles[i], ios::in | ios::binary);
		f.seekg(0, ios::beg);
		f.read(feaSaved, 8192);
		f.clear();
		f.close();

		EXPECT_TRUE(SUCC == ISCompare(defaultCompareChannel, feature, feaSaved, &score));
		if(score > recongiseFaceValue){
			cout << feaFiles[i] << endl;
		}
	}
	DESTROY_COMPARE_CHANNEL(defaultCompareChannel);
}

TEST(ftMultiThread, toCompareEachImageWithAllFeaFilesAccordingToCompareFaceValue_SingleThread)
{
	// ��һ��ѭ��ʹ�õ�����
	string imgPath = GConfig::getInstance().getImgPath();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);
	char feature[8192];
	int defaultFeatureChannel = DEFAULT_FEATURE_CHANNEL();

	// �ڶ���ѭ��ʹ�õ�����
	int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
	float recongiseFaceValue = GConfig::getInstance().getRecogniseFaceValue();
	vector<string> feaFiles;
	string feaPath = GConfig::getInstance().getFeaPath();
	listOutDirectoryFiles(feaPath, feaFiles);
	float score;
	char feaSaved[8192];
	fstream f;

	SYSTEMTIME tStart, tStop;
    GetSystemTime(&tStart);

	for(unsigned int i=0; i<images.size(); i++){
		Mat image = imread(images[i]);
		getFeatureRgb((char *)image.data, image.rows*image.cols*3, image.cols, image.rows, feature);
		EXPECT_TRUE(SUCC == ISGetFeatureRgb(defaultFeatureChannel, (char *)image.data, image.rows*image.cols*3, image.cols, image.rows, feature));

		for(unsigned int j=0; j<feaFiles.size(); j++){
			f.open(feaFiles[j], ios::in | ios::binary);
			f.seekg(0, ios::beg);
			f.read(feaSaved, 8192);
			f.clear();
			f.close();

			EXPECT_TRUE(SUCC == ISCompare(defaultCompareChannel, feature, feaSaved, &score));
			//if(score < recongiseFaceValue 
			//	&& 0 == strcmp(getFileHeader(images[i].data()).data(), getFileHeader(feaFiles[j].data()).data()))
			//{
			//	cout << images[i] << " + " << feaFiles[j] << " = �Ǳ��ˣ����������scoreֵС��recongiseFaceValue" << endl;
			//}
			//if(score >= recongiseFaceValue
			//	&& 0 != strcmp(getFileHeader(images[i].data()).data(), getFileHeader(feaFiles[j].data()).data()))
			//{
			//	cout << images[i] << " + " << feaFiles[j] << " = ���Ǳ��ˣ����������scoreֵ����recongiseFaceValue" << endl;
			//}
		}
	}
	DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);
	DESTROY_COMPARE_CHANNEL(defaultCompareChannel);

    GetSystemTime(&tStop);
	cout << "���߳��£�1000�������������Compare����ʱ��" << getGap(tStart, tStop) << "����" << endl;
}

TEST(ftMultiThread, toCompareEachImageWithAllFeaFilesAccordingToCompareFaceValue_MultiThread)
{
	string imgPath = GConfig::getInstance().getImgPath();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);

	unsigned int getFeaThreadNum = GConfig::getInstance().getGetFeaThreadNum();

	SYSTEMTIME tStart, tStop;
    GetSystemTime(&tStart);

	vector<ThreadEssentials> threadEssentials(getFeaThreadNum);
	for(unsigned int m=0; m<getFeaThreadNum; m++){
		threadEssentials[m].featureChannel = DEFAULT_FEATURE_CHANNEL();
		threadEssentials[m].compareChannel = DEFAULT_COMPARE_CHANNEL();
		EXPECT_TRUE(SUCC == pthread_create(&(threadEssentials[m].pThread), NULL, faceCompare, &threadEssentials));
	}

	void *retVal;
	for(unsigned int n=0; n<getFeaThreadNum; n++){
		EXPECT_TRUE(SUCC == pthread_join(threadEssentials[n].pThread, &retVal));
		DESTROY_FEATURE_CHANNEL(threadEssentials[n].featureChannel);
		DESTROY_COMPARE_CHANNEL(threadEssentials[n].compareChannel);
	}

	GetSystemTime(&tStop);
	cout << "5�߳��£�1000�������������Compare����ʱ��" << getGap(tStart, tStop) << "����" << endl;
}