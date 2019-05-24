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

extern pthread_mutex_t mutex;
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

	void *faceCompare(void *ptr){
		// ����ó���ǰ�߳����߳������е�index���Ա�����õ���Ӧ�����
		vector<pthread_t> pThreads = *(vector<pthread_t> *)ptr;

		unsigned int currentThreadIndex;
		for(unsigned int i=0; i<pThreads.size(); i++){
			if(0 != pthread_equal(pthread_self(), pThreads[i])){
				currentThreadIndex = i;
			}
		}

		// ����ó���ǰ�߳���Ҫ�����imgNumPerThread��ͼƬ��Feature�ĵ�ַ��������featureAsOfCurrentThread��
		string feaAPath = GConfig::getInstance().getFeatureAPath();
		vector<string> featureAs;
		listOutDirectoryFiles(feaAPath, featureAs);
		unsigned int featureNumPerThread = unsigned int(featureAs.size()/pThreads.size());
		vector<string> featureAsOfCurrentThread;
		if(currentThreadIndex == pThreads.size()-1){
			featureAsOfCurrentThread.assign(featureAs.begin()+currentThreadIndex*featureNumPerThread, featureAs.end());
		}
		else{
			featureAsOfCurrentThread.assign(featureAs.begin()+currentThreadIndex*featureNumPerThread, featureAs.begin()+(currentThreadIndex+1)*featureNumPerThread);
		}

		string feaBPath = GConfig::getInstance().getFeatureBPath();
		vector<string> featureBs;
		listOutDirectoryFiles(feaBPath, featureBs);
		float score;
		char featureA[8192];
		char featureB[8192];
		fstream fileA, fileB;

		int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
		float recongiseFaceValue = GConfig::getInstance().getRecogniseFaceValue();
		for(unsigned int i=0; i<featureAsOfCurrentThread.size(); i++){
			fileA.open(featureAs[i], ios::in | ios::binary);
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
}

TEST_F(ftISCompare, prepareFeatureAndPcaRapidlyUsingMultiThread)
{
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
	string imgBPath = GConfig::getInstance().getCompareImgBPath();
	vector<string> imageBs;
	listOutDirectoryFiles(imgBPath, imageBs);

	unsigned int detectThreadNum = GConfig::getInstance().getGetFeaThreadNum();
	int imgANumPerThread = int(imageAs.size()/detectThreadNum);
	int imgBNumPerThread = int(imageBs.size()/detectThreadNum);

	cout << "���������Ա�֮ǰ�����ȵ��ô˲�������" << endl;
	cout << "\t����ʹ�ö��߳̿�����ȡ���Ա������ļ��е�������PCA" << endl;
	cout << ">>Inputs <<" << endl;
	cout << "���Ա�ͼƬĿ¼A��" << GConfig::getInstance().getCompareImgAPath() << endl;
	cout << "���Ա�ͼƬĿ¼B��" << GConfig::getInstance().getCompareImgBPath() << endl;
	cout << "�߳�����" << GConfig::getInstance().getGetFeaThreadNum() << endl;
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

	SYSTEMTIME	tStart, tStop;
	GetSystemTime(&tStart);

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
	cout << "Ŀ¼AͼƬ������" << imageAs.size() << endl;
	cout << "Ŀ¼A��ȡ����������������" << featureNumA << endl;
	float percent = float(featureNumA)/imageAs.size()*100;
	cout << "������ȡ�ɹ��ʣ�" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "Ŀ¼BͼƬ������" << imageBs.size() << endl;
	cout << "Ŀ¼B��ȡ����������������" << featureNumB << endl;
	percent = float(featureNumB)/imageBs.size()*100;
	cout << "������ȡ�ɹ��ʣ�" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "���Ŀ¼A��άǰ����������" << GConfig::getInstance().getFeatureAPath() << endl;
	cout << "���Ŀ¼A��ά�����������" << GConfig::getInstance().getPcaAPath() << endl;
	cout << "���Ŀ¼B��άǰ����������" << GConfig::getInstance().getFeatureBPath() << endl;
	cout << "���Ŀ¼B��ά�����������" << GConfig::getInstance().getPcaBPath() << endl;
	cout << "�ܹ���ʱ��" << getGap(tStart, tStop) << "����" << endl;
	float timePerPic = float(getGap(tStart, tStop))/(imageAs.size()+imageBs.size());
	cout << "����ͼƬ��ʱ��" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "����" << endl;
}

//ISCompareֻ֧��8192��feature
TEST_F(ftISCompare, ISCompare_SingleThread)
{
	fstream f;
	char featureB[8192];
	char featureA[8192];

	string featureAPath = GConfig::getInstance().getFeatureAPath();
	vector<string> feaAFiles;
	listOutDirectoryFiles(featureAPath, feaAFiles);
	string featureBPath = GConfig::getInstance().getFeatureBPath();
	vector<string> feaBFiles;
	listOutDirectoryFiles(featureBPath, feaBFiles);

	SYSTEMTIME tStart, tStop;
    GetSystemTime(&tStart);

	valueCountsSmall = 0;
	valueCountsBig = 0;

	cout << "���������Ա�֮ǰ������ȷ�����Ա�����ͼƬ�ļ��е�������PCA�Ѿ�׼����������" << endl;
	cout << ">>Inputs <<" << endl;
	cout << "���Ա�ͼƬĿ¼A��������" << featureAPath << endl;
	cout << "���Ա�ͼƬĿ¼B��������" << featureBPath << endl;
	cout << "�߳�����" << "���߳�" << endl;
	cout << ">>Outputs<<" << endl;

	int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
	float recongiseFaceValue = GConfig::getInstance().getRecogniseFaceValue();
	float score;
	for(unsigned int i=0; i<feaAFiles.size(); i++){
		f.open(feaAFiles[i], ios::in | ios::binary);
		f.seekg(0, ios::beg);
		f.read(featureA, 8192);
		f.clear();
		f.close();
		for(unsigned int j=0; j<feaBFiles.size(); j++){
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

	cout << "����Ŀ¼A�ļ�����" << feaAFiles.size() << endl;
	cout << "����Ŀ¼B�ļ�����" << feaBFiles.size() << endl;
	cout << "�Ǳ��ˣ����������scoreֵС��\"�����Աȷ�����ֵ\"����������" << valueCountsBig << endl;
	float percent = float(valueCountsBig)/feaAFiles.size()*100;
	cout << "�Ǳ��˵�scoreֵ�ﲻ��\"�����Աȷ�����ֵ\"����ʶ�ʣ�����������/����Ŀ¼A�ļ�������" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "���Ǳ��ˣ����������scoreֵ����\"�����Աȷ�����ֵ\"����������" << valueCountsSmall << endl;
	percent = float(valueCountsSmall)/feaAFiles.size()*100;
	cout << "���Ǳ��˵�scoreֵ����\"�����Աȷ�����ֵ\"����ʶ�ʣ�����������/����Ŀ¼A�ļ�������" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "�����Ա��ܹ���ʱ��" << getGap(tStart, tStop) << "����" << endl;
	cout << "�ۼ���������Աȼ��������" << feaAFiles.size()*feaBFiles.size() << endl;
	float timePerPic = float(getGap(tStart, tStop))/(feaAFiles.size()*feaBFiles.size());
	cout << "���������ԱȺ�ʱ��" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "����" << endl;
}

/* �޷����߳���ͬʱ����������ȡͨ���ͶԱ�ͨ���������޸��У��� 
 * ����ֱ������ȡ����������������Ŀ¼���жԱȣ�
 * ���漰���߳���ͬʱ����������ȡͨ���ͶԱ�ͨ��
 */
TEST_F(ftISCompare, ISCompare_MultiThread)
{
	SYSTEMTIME tStart, tStop;
    GetSystemTime(&tStart);
	cout << "���������Ա�֮ǰ������ȷ�����Ա�����ͼƬ�ļ��е�������PCA�Ѿ�׼����������" << endl;
	cout << ">>Inputs <<" << endl;
	cout << "���Ա�ͼƬĿ¼A��������" << GConfig::getInstance().getFeatureAPath() << endl;
	cout << "���Ա�ͼƬĿ¼B��������" << GConfig::getInstance().getFeatureBPath() << endl;
	unsigned int getFeaThreadNum = GConfig::getInstance().getGetFeaThreadNum();
	cout << "�߳�����" << getFeaThreadNum << endl;
	cout << ">>Outputs<<" << endl;

	valueCountsSmall = 0;
	valueCountsBig = 0;

	vector<pthread_t> pThreads(getFeaThreadNum);
	for(unsigned int m=0; m<getFeaThreadNum; m++){
		EXPECT_TRUE(SUCC == pthread_create(&pThreads[m], NULL, faceCompare, &pThreads));
	}

	void *retVal;
	for(unsigned int n=0; n<getFeaThreadNum; n++){
		EXPECT_TRUE(SUCC == pthread_join(pThreads[n], &retVal));
	}

	GetSystemTime(&tStop);

	string imgAPath = GConfig::getInstance().getCompareImgAPath();
	vector<string> imageAs;
	listOutDirectoryFiles(imgAPath, imageAs);

	string imgBPath = GConfig::getInstance().getCompareImgBPath();
	vector<string> imageBs;
	listOutDirectoryFiles(imgBPath, imageBs);

	cout << "����Ŀ¼A�ļ�����" << imageAs.size() << endl;
	cout << "����Ŀ¼B�ļ�����" << imageBs.size() << endl;
	cout << "�Ǳ��ˣ����������scoreֵС��\"�����Աȷ�����ֵ\"����������" << valueCountsBig << endl;
	float percent = float(valueCountsBig)/imageAs.size()*100;
	cout << "�Ǳ��˵�scoreֵ�ﲻ��\"�����Աȷ�����ֵ\"����ʶ�ʣ�����������/����Ŀ¼A�ļ�������" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "���Ǳ��ˣ����������scoreֵ����\"�����Աȷ�����ֵ\"����������" << valueCountsSmall << endl;
	percent = float(valueCountsSmall)/imageAs.size()*100;
	cout << "���Ǳ��˵�scoreֵ����\"�����Աȷ�����ֵ\"����ʶ�ʣ�����������/����Ŀ¼A�ļ�������" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "�����Ա��ܹ���ʱ��" << getGap(tStart, tStop) << "����" << endl;
	cout << "�ۼ���������Աȼ��������" << imageAs.size()*imageBs.size() << endl;
	float timePerPic = float(getGap(tStart, tStop))/(imageAs.size()*imageBs.size());
	cout << "���������ԱȺ�ʱ��" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "����" << endl;
}

//ISCompareMNֻ֧��2048��pca
