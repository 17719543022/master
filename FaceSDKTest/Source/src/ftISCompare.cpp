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
		// 计算得出当前线程在线程数组中的index，以便后面拿到对应的入参
		vector<pthread_t> pThreads = *(vector<pthread_t> *)ptr;
		int pThreads_size = pThreads.size();

		unsigned int currentThreadIndex;
		for(int i=0; i<pThreads_size; i++){
			if(0 != pthread_equal(pthread_self(), pThreads[i])){
				currentThreadIndex = i;
			}
		}

		// 计算得出当前线程需要处理的featureNumPerThread张图片的Feature的地址，并存在featureAsOfCurrentThread中
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
		// 计算得出当前线程在线程数组中的index，以便后面拿到对应的入参
		vector<pthread_t> pThreads = *(vector<pthread_t> *)ptr;
		int pThreads_size = pThreads.size();

		unsigned int currentThreadIndex;
		for(int i=0; i<pThreads_size; i++){
			if(0 != pthread_equal(pthread_self(), pThreads[i])){
				currentThreadIndex = i;
			}
		}

		// 计算得出当前线程需要处理的pcaNumPerThread张图片的Pca的地址，并存在pcaAsOfCurrentThread中
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

		char **pcaA;
		ALLOC_DOUBLE_STAR(pcaAsOfCurrentThread_size, 2048, char, pcaA, M)
		for(int j=0; j<pcaAsOfCurrentThread_size; j++){
			fileA.open(pcaAsOfCurrentThread[j], ios::in | ios::binary);
			fileA.seekg(0, ios::beg);
			fileA.read(pcaTemp, 2048);
			fileA.clear();
			fileA.close();

			memcpy(pcaA[j], pcaTemp, 2048);
		}

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
		ALLOC_DOUBLE_STAR(pcaAsOfCurrentThread_size, pcaBs_size, float, score, S)

		EXPECT_TRUE(SUCC == ISCompareMN(defaultCompareChannel, pcaA, pcaAsOfCurrentThread_size, pcaB, pcaBs_size, score));
		for(int s=0; s<pcaAsOfCurrentThread_size; s++){
			for(int t=0; t<pcaBs_size; t++){
				if(score[s][t]<recongiseFaceValue && s+currentThreadIndex*pcaNumPerThread==t)
				{
					pthread_mutex_lock(&mutex);
					valueCountsBig++;
					pthread_mutex_unlock(&mutex);
				}
				if(score[s][t]>=recongiseFaceValue && s+currentThreadIndex*pcaNumPerThread!=t)
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
		// 计算得出当前线程在线程数组中的index，以便后面拿到对应的入参
		vector<pthread_t> pThreads = *(vector<pthread_t> *)ptr;
		int pThreads_size = pThreads.size();

		unsigned int currentThreadIndex;
		for(int i=0; i<pThreads_size; i++){
			if(0 != pthread_equal(pthread_self(), pThreads[i])){
				currentThreadIndex = i;
			}
		}

		// 计算得出当前线程需要处理的pcaNumPerThread张图片的Pca的地址，并存在pcaAsOfCurrentThread中
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

		// ISCompareMNfasterprep
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
	
		// ISCompareMNfaster
		char **pcaA;
		ALLOC_DOUBLE_STAR(pcaAsOfCurrentThread_size, 2048, char, pcaA, M)
		for(int j=0; j<pcaAsOfCurrentThread_size; j++){
			fileA.open(pcaAsOfCurrentThread[j], ios::in | ios::binary);
			fileA.seekg(0, ios::beg);
			fileA.read(pcaTemp, 2048);
			fileA.clear();
			fileA.close();

			memcpy(pcaA[j], pcaTemp, 2048);
		}

		float **score;
		ALLOC_DOUBLE_STAR(pcaAsOfCurrentThread_size, pcaBs_size, float, score, S)

		EXPECT_TRUE(SUCC == ISCompareMNfaster(defaultCompareChannel, pcaA, pcaAsOfCurrentThread_size, score));
		for(int s=0; s<pcaAsOfCurrentThread_size; s++){
			for(int t=0; t<pcaBs_size; t++){
				if(score[s][t]<recongiseFaceValue && s+currentThreadIndex*pcaNumPerThread==t)
				{
					pthread_mutex_lock(&mutex);
					valueCountsBig++;
					pthread_mutex_unlock(&mutex);
				}
				if(score[s][t]>=recongiseFaceValue && s+currentThreadIndex*pcaNumPerThread!=t)
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

	cout << "进行特征对比之前，请先调用此测试用例" << endl;
	cout << "\t——使用多线程快速提取待对比两个文件夹的特征和PCA" << endl;
	cout << ">>Inputs <<" << endl;
	cout << "待对比图片目录A：" << GConfig::getInstance().getCompareImgAPath() << endl;
	cout << "待对比图片目录B：" << GConfig::getInstance().getCompareImgBPath() << endl;
	cout << "线程数：" << GConfig::getInstance().getGetFeaThreadNum() << endl;
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
	cout << "目录A图片张数：" << imageAs_size << endl;
	cout << "目录A提取到人脸特征张数：" << featureNumA << endl;
	float percent = float(featureNumA)/imageAs_size*100;
	cout << "特征提取成功率：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "目录B图片张数：" << imageBs_size << endl;
	cout << "目录B提取到人脸特征张数：" << featureNumB << endl;
	percent = float(featureNumB)/imageBs_size*100;
	cout << "特征提取成功率：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "输出目录A降维前的特征到：" << GConfig::getInstance().getFeatureAPath() << endl;
	cout << "输出目录A降维后的特征到：" << GConfig::getInstance().getPcaAPath() << endl;
	cout << "输出目录B降维前的特征到：" << GConfig::getInstance().getFeatureBPath() << endl;
	cout << "输出目录B降维后的特征到：" << GConfig::getInstance().getPcaBPath() << endl;
	cout << "总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
	float timePerPic = float(getGap(tStart, tStop))/(imageAs_size+imageBs_size);
	cout << "单张图片耗时：" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "毫秒" << endl;
}

//ISCompare只支持8192的feature
TEST_F(ftISCompare, ISCompare_SingleThread)
{
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

	cout << "进行特征对比之前，请先确保待对比两个图片文件夹的特征已经准备就绪！！" << endl;
	cout << ">>Inputs <<" << endl;
	cout << "待对比图片目录A的特征：" << featureAPath << endl;
	cout << "待对比图片目录B的特征：" << featureBPath << endl;
	cout << "线程数：" << "单线程" << endl;
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

	cout << "特征目录A文件数：" << feaAFiles_size << endl;
	cout << "特征目录B文件数：" << feaBFiles_size << endl;
	cout << "是本人，但算出来的score值小于\"人脸对比分数阈值\"发生次数：" << valueCountsBig << endl;
	float percent = float(valueCountsBig)/feaAFiles_size*100;
	cout << "是本人但score值达不到\"人脸对比分数阈值\"的误识率（此类错误次数/特征目录A文件数）：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "不是本人，但算出来的score值大于\"人脸对比分数阈值\"发生次数：" << valueCountsSmall << endl;
	percent = float(valueCountsSmall)/feaAFiles_size*100;
	cout << "不是本人但score值超过\"人脸对比分数阈值\"的误识率（此类错误次数/特征目录A文件数）：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "特征对比总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
	cout << "累计完成特征对比计算次数：" << feaAFiles_size*feaBFiles_size << endl;
	float timePerPic = float(getGap(tStart, tStop))/(feaAFiles_size*feaBFiles_size);
	cout << "单次特征对比耗时：" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "毫秒" << endl;
}

/* 无法在线程下同时创建特征提取通道和对比通道，故障修改中！！ 
 * 本例直接用提取好特征的两个特征目录进行对比，
 * 不涉及在线程下同时创建特征提取通道和对比通道
 */
TEST_F(ftISCompare, ISCompare_MultiThread)
{
	SYSTEMTIME tStart, tStop;
    GetSystemTime(&tStart);
	valueCountsSmall = 0;
	valueCountsBig = 0;

	cout << "进行特征对比之前，请先确保待对比两个图片文件夹的特征已经准备就绪！！" << endl;
	cout << ">>Inputs <<" << endl;
	cout << "待对比图片目录A的特征：" << GConfig::getInstance().getFeatureAPath() << endl;
	cout << "待对比图片目录B的特征：" << GConfig::getInstance().getFeatureBPath() << endl;
	unsigned int compareThreadNum = GConfig::getInstance().getCompareThreadNum();
	cout << "线程数：" << compareThreadNum << endl;
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

	cout << "特征目录A文件数：" << imageAs_size << endl;
	cout << "特征目录B文件数：" << imageBs_size << endl;
	cout << "是本人，但算出来的score值小于\"人脸对比分数阈值\"发生次数：" << valueCountsBig << endl;
	float percent = float(valueCountsBig)/imageAs_size*100;
	cout << "是本人但score值达不到\"人脸对比分数阈值\"的误识率（此类错误次数/特征目录A文件数）：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "不是本人，但算出来的score值大于\"人脸对比分数阈值\"发生次数：" << valueCountsSmall << endl;
	percent = float(valueCountsSmall)/imageAs_size*100;
	cout << "不是本人但score值超过\"人脸对比分数阈值\"的误识率（此类错误次数/特征目录A文件数）：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "特征对比总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
	cout << "累计完成特征对比计算次数：" << imageAs_size*imageBs_size << endl;
	float timePerPic = float(getGap(tStart, tStop))/(imageAs_size*imageBs_size);
	cout << "单次特征对比耗时：" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "毫秒" << endl;
}

/* ISCompareMN/ISCompareMNfaster只支持2048的feature */
TEST_F(ftISCompare, ISCompareMN_SingleThread)
{
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
	char **pcaA;
	ALLOC_DOUBLE_STAR(pcaAs_size, 2048, char, pcaA, M)
	for(int j=0; j<pcaAs_size; j++){
		fileA.open(pcaAs[j], ios::in | ios::binary);
		fileA.seekg(0, ios::beg);
		fileA.read(pcaTemp, 2048);
		fileA.clear();
		fileA.close();

		memcpy(pcaA[j], pcaTemp, 2048);
	}

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
	ALLOC_DOUBLE_STAR(pcaAs_size, pcaBs_size, float, score, S)

	cout << "进行CompareMN对比之前，请先确保待对比两个图片文件夹的PCA已经准备就绪！！" << endl;
	cout << ">>Inputs <<" << endl;
	cout << "待对比图片目录A的PCA：" << GConfig::getInstance().getPcaAPath() << endl;
	cout << "待对比图片目录B的PCA：" << GConfig::getInstance().getPcaBPath() << endl;
	cout << "线程数：" << "单线程" << endl;
	cout << ">>Outputs<<" << endl;

	valueCountsSmall = 0;
	valueCountsBig = 0;
	int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
	float recongiseFaceValue = GConfig::getInstance().getRecogniseFaceValue();

	EXPECT_TRUE(SUCC == ISCompareMN(defaultCompareChannel, pcaA, pcaAs_size, pcaB, pcaBs_size, score));
	for(int s=0; s<pcaAs_size; s++){
		for(int t=0; t<pcaBs_size; t++){
			if(score[s][t]<recongiseFaceValue && s==t)
			{
				valueCountsBig++;
			}
			if(score[s][t]>=recongiseFaceValue && s!=t)
			{
				valueCountsSmall++;
			}
		}
	}

	DESTROY_COMPARE_CHANNEL(defaultCompareChannel);
    GetSystemTime(&tStop);

	cout << "PCA目录A文件数：" << pcaAs_size << endl;
	cout << "PCA目录B文件数：" << pcaBs_size << endl;
	cout << "是本人，但算出来的score值小于\"人脸对比分数阈值\"发生次数：" << valueCountsBig << endl;
	float percent = float(valueCountsBig)/pcaAs_size*100;
	cout << "是本人但score值达不到\"人脸对比分数阈值\"的误识率（此类错误次数/特征目录A文件数）：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "不是本人，但算出来的score值大于\"人脸对比分数阈值\"发生次数：" << valueCountsSmall << endl;
	percent = float(valueCountsSmall)/pcaAs_size*100;
	cout << "不是本人但score值超过\"人脸对比分数阈值\"的误识率（此类错误次数/特征目录A文件数）：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "特征对比总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
	cout << "累计完成特征对比计算次数：" << pcaAs_size*pcaBs_size << endl;
	float timePerPic = float(getGap(tStart, tStop))/(pcaAs_size*pcaBs_size);
	cout << "单次特征对比耗时：" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "毫秒" << endl;
}

TEST_F(ftISCompare, ISCompareMN_MultiThread)
{
	SYSTEMTIME tStart, tStop;
    GetSystemTime(&tStart);
	valueCountsSmall = 0;
	valueCountsBig = 0;

	cout << "进行CompareMN对比之前，请先确保待对比两个图片文件夹的PCA已经准备就绪！！" << endl;
	cout << ">>Inputs <<" << endl;
	cout << "待对比图片目录A的PCA：" << GConfig::getInstance().getPcaAPath() << endl;
	cout << "待对比图片目录B的PCA：" << GConfig::getInstance().getPcaBPath() << endl;
	unsigned int recogniseThreadNum = GConfig::getInstance().getRecogniseThreadNum();
	cout << "线程数：" << recogniseThreadNum << endl;
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

	cout << "PCA目录A文件数：" << pcaAs_size << endl;
	cout << "PCA目录B文件数：" << pcaBs_size << endl;
	cout << "是本人，但算出来的score值小于\"人脸对比分数阈值\"发生次数：" << valueCountsBig << endl;
	float percent = float(valueCountsBig)/pcaAs_size*100;
	cout << "是本人但score值达不到\"人脸对比分数阈值\"的误识率（此类错误次数/特征目录A文件数）：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "不是本人，但算出来的score值大于\"人脸对比分数阈值\"发生次数：" << valueCountsSmall << endl;
	percent = float(valueCountsSmall)/pcaAs_size*100;
	cout << "不是本人但score值超过\"人脸对比分数阈值\"的误识率（此类错误次数/特征目录A文件数）：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "CompareMN对比总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
	cout << "累计完成CompareMN对比计算次数：" << pcaAs_size*pcaBs_size << endl;
	float timePerPic = float(getGap(tStart, tStop))/(pcaAs_size*pcaBs_size);
	cout << "单次PCA对比耗时：" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "毫秒" << endl;
}

TEST_F(ftISCompare, ISCompareMNfaster_SingleThread)
{
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
	int pcaBs_size = pcaAs.size();
	char pcaTemp[2048];

	char **pcaA;
	ALLOC_DOUBLE_STAR(pcaAs_size, 2048, char, pcaA, M)
	for(int i=0; i<pcaAs_size; i++){
		fileA.open(pcaAs[i], ios::in | ios::binary);
		fileA.seekg(0, ios::beg);
		fileA.read(pcaTemp, 2048);
		fileA.clear();
		fileA.close();

		memcpy(pcaA[i], pcaTemp, 2048);
	}

	char **pcaB;
	ALLOC_DOUBLE_STAR(pcaBs_size, 2048, char, pcaB, N)
	for(int j=0; j<pcaBs_size; j++)
	{
		fileB.open(pcaBs[j], ios::in | ios::binary);
		fileB.seekg(0, ios::beg);
		fileB.read(pcaTemp, 2048);
		fileB.clear();
		fileB.close();

		memcpy(pcaB[j], pcaTemp, 2048);
	}

	int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
	EXPECT_TRUE(SUCC == ISCompareMNfasterprep(defaultCompareChannel, pcaB, pcaBs_size));
	
	// ISCompareMNfaster
	float **score;
	ALLOC_DOUBLE_STAR(pcaAs_size, pcaBs_size, float, score, S)

	cout << "进行CompareMNfaster对比之前，请先确保待对比两个图片文件夹的PCA已经准备就绪！！" << endl;
	cout << ">>Inputs <<" << endl;
	cout << "待对比图片目录A的PCA：" << GConfig::getInstance().getPcaAPath() << endl;
	cout << "待对比图片目录B的PCA：" << GConfig::getInstance().getPcaBPath() << endl;
	cout << "线程数：" << "单线程" << endl;
	cout << ">>Outputs<<" << endl;
	
	valueCountsSmall = 0;
	valueCountsBig = 0;

	float recongiseFaceValue = GConfig::getInstance().getRecogniseFaceValue();
	EXPECT_TRUE(SUCC == ISCompareMNfaster(defaultCompareChannel, pcaA, pcaAs_size, score));
	for(int s=0; s<pcaAs_size; s++){
		for(int t=0; t<pcaBs_size; t++){
			if(score[s][t]<recongiseFaceValue && s==t)
			{
				valueCountsBig++;
			}
			if(score[s][t]>=recongiseFaceValue && s!=t)
			{
				valueCountsSmall++;
			}
		}
	}

	DESTROY_COMPARE_CHANNEL(defaultCompareChannel);
    GetSystemTime(&tStop);
	
	cout << "PCA目录A文件数：" << pcaAs_size << endl;
	cout << "PCA目录B文件数：" << pcaBs_size << endl;
	cout << "是本人，但算出来的score值小于\"人脸对比分数阈值\"发生次数：" << valueCountsBig << endl;
	float percent = float(valueCountsBig)/pcaAs_size*100;
	cout << "是本人但score值达不到\"人脸对比分数阈值\"的误识率（此类错误次数/特征目录A文件数）：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "不是本人，但算出来的score值大于\"人脸对比分数阈值\"发生次数：" << valueCountsSmall << endl;
	percent = float(valueCountsSmall)/pcaAs_size*100;
	cout << "不是本人但score值超过\"人脸对比分数阈值\"的误识率（此类错误次数/特征目录A文件数）：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "PCA对比总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
	cout << "累计完成PCA对比计算次数：" << pcaAs_size*pcaBs_size << endl;
	float timePerPic = float(getGap(tStart, tStop))/(pcaAs_size*pcaBs_size);
	cout << "单次PCA对比耗时：" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "毫秒" << endl;
}

TEST_F(ftISCompare, ISCompareMNfaster_MultiThread)
{
	SYSTEMTIME tStart, tStop;
    GetSystemTime(&tStart);
	valueCountsSmall = 0;
	valueCountsBig = 0;

	cout << "进行CompareMNfaster对比之前，请先确保待对比两个图片文件夹的PCA已经准备就绪！！" << endl;
	cout << ">>Inputs <<" << endl;
	cout << "待对比图片目录A的PCA：" << GConfig::getInstance().getPcaAPath() << endl;
	cout << "待对比图片目录B的PCA：" << GConfig::getInstance().getPcaBPath() << endl;
	unsigned int recogniseThreadNum = GConfig::getInstance().getRecogniseThreadNum();
	cout << "线程数：" << recogniseThreadNum << endl;
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

	cout << "PCA目录A文件数：" << pcaAs_size << endl;
	cout << "PCA目录B文件数：" << pcaBs_size << endl;
	cout << "是本人，但算出来的score值小于\"人脸对比分数阈值\"发生次数：" << valueCountsBig << endl;
	float percent = float(valueCountsBig)/pcaAs_size*100;
	cout << "是本人但score值达不到\"人脸对比分数阈值\"的误识率（此类错误次数/特征目录A文件数）：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "不是本人，但算出来的score值大于\"人脸对比分数阈值\"发生次数：" << valueCountsSmall << endl;
	percent = float(valueCountsSmall)/pcaAs_size*100;
	cout << "不是本人但score值超过\"人脸对比分数阈值\"的误识率（此类错误次数/特征目录A文件数）：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "CompareMN对比总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
	cout << "累计完成CompareMN对比计算次数：" << pcaAs_size*pcaBs_size << endl;
	float timePerPic = float(getGap(tStart, tStop))/(pcaAs_size*pcaBs_size);
	cout << "单次PCA对比耗时：" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "毫秒" << endl;
}
