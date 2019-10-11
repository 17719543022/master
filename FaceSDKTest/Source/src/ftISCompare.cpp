#ifdef WIN32
#include "opencv.hpp"
#endif
#ifdef LINUX
#include "opencv2/opencv.hpp"
#include "rmDir.h"
#endif
#include <gtest/gtest.h>
#include "testSuits.h"
#include "config.h"
#include "listOut.h"
#include "common.h"
#include <pthread.h>
#include <fstream>
#include "log_format.h"
#include <iostream>
#include "timer.h"

using namespace cv;
using namespace std;

extern pthread_mutex_t mutex;
extern int featureNumA;
extern int featureNumB;
extern string serial;
extern bool isFlow;
extern double cost;
pthread_mutex_t mutex2;
int valueCountsSmall;
int valueCountsBig;

namespace{
	void *faceFeature(void *ptr){
		vector<string> images = *(vector<string> *)ptr;
		int defaultFeatureChannel = DEFAULT_FEATURE_CHANNEL();
		char feature[5][8192];
		char pca[2048];
		string saveFeaPath_m, savePcaPath_m;
		string saveFeaPath_s, savePcaPath_s;
#ifdef WIN32
		fstream f_m, f_s;
#endif
#ifdef LINUX
		FILE *f_m, *f_s;
#endif
		for(unsigned int i=0; i<images.size(); i++){
			if(SUCC != ISGetFeaturePath(defaultFeatureChannel, const_cast<char *>(images[i].data()), feature[0])){
				continue;
			}
			else{
				pthread_mutex_lock(&mutex);
				if(serial[serial.size() - 1] == 'A')
				{
					featureNumA++;
				}
				if(serial[serial.size() - 1] == 'B')
				{
					featureNumB++;
				}
				pthread_mutex_unlock(&mutex);

				ISGetPcaFea(defaultFeatureChannel, feature[0], pca);
#ifdef WIN32
				if(serial[serial.size() - 1] == 'A')
				{
					saveFeaPath_m = upperDirectory(serial) + "\\" + "feaMA" + "\\" + getFileHeader(images[i].data()) + ".fea";
					savePcaPath_m = upperDirectory(serial) + "\\" + "pcaMA" + "\\" + getFileHeader(images[i].data()) + ".pca";
					saveFeaPath_s = upperDirectory(serial) + "\\" + "feaSA" + "\\" + getFileHeader(images[i].data()) + ".fea";
					savePcaPath_s = upperDirectory(serial) + "\\" + "pcaSA" + "\\" + getFileHeader(images[i].data()) + ".pca";
				}
				if(serial[serial.size() - 1] == 'B')
				{
					saveFeaPath_m = upperDirectory(serial) + "\\" + "feaMB" + "\\" + getFileHeader(images[i].data()) + ".fea";
					savePcaPath_m = upperDirectory(serial) + "\\" + "pcaMB" + "\\" + getFileHeader(images[i].data()) + ".pca";
					saveFeaPath_s = upperDirectory(serial) + "\\" + "feaSB" + "\\" + getFileHeader(images[i].data()) + ".fea";
					savePcaPath_s = upperDirectory(serial) + "\\" + "pcaSB" + "\\" + getFileHeader(images[i].data()) + ".pca";
				}
				f_m.open(saveFeaPath_m, ios::out | ios::binary);
				f_m.write(feature[0], sizeof(feature[0]));
				f_m.close();
				f_m.clear();

				f_m.open(savePcaPath_m, ios::out | ios::binary);
				f_m.write(pca, sizeof(pca));
				f_m.close();
				f_m.clear();

				f_s.open(saveFeaPath_s, ios::out | ios::binary);
				f_s.write(feature[0], sizeof(feature[0]));
				f_s.close();
				f_s.clear();

				f_s.open(savePcaPath_s, ios::out | ios::binary);
				f_s.write(pca, sizeof(pca));
				f_s.close();
				f_s.clear();
#endif
#ifdef LINUX
				if(serial[serial.size() - 1] == 'A')
				{
					saveFeaPath_m = upperDirectory(serial) + "/" + "feaMA" + "/" + getFileHeader(images[i].data()) + ".fea";
					savePcaPath_m = upperDirectory(serial) + "/" + "pcaMA" + "/" + getFileHeader(images[i].data()) + ".pca";
					saveFeaPath_s = upperDirectory(serial) + "/" + "feaSA" + "/" + getFileHeader(images[i].data()) + ".fea";
					savePcaPath_s = upperDirectory(serial) + "/" + "pcaSA" + "/" + getFileHeader(images[i].data()) + ".pca";
				}
				if(serial[serial.size() - 1] == 'B')
				{
					saveFeaPath_m = upperDirectory(serial) + "/" + "feaMB" + "/" + getFileHeader(images[i].data()) + ".fea";
					savePcaPath_m = upperDirectory(serial) + "/" + "pcaMB" + "/" + getFileHeader(images[i].data()) + ".pca";
					saveFeaPath_s = upperDirectory(serial) + "/" + "feaSB" + "/" + getFileHeader(images[i].data()) + ".fea";
					savePcaPath_s = upperDirectory(serial) + "/" + "pcaSB" + "/" + getFileHeader(images[i].data()) + ".pca";
				}
				f_m = fopen(saveFeaPath_m.data(), "wb");
				fwrite(feature, 8192, 1, f_m);
				fclose(f_m);

				f_m = fopen(savePcaPath_m.data(), "wb");
				fwrite(pca, 2048, 1, f_m);
				fclose(f_m);

				f_s = fopen(saveFeaPath_s.data(), "wb");
				fwrite(feature, 8192, 1, f_s);
				fclose(f_s);

				f_s = fopen(savePcaPath_s.data(), "wb");
				fwrite(pca, 2048, 1, f_s);
				fclose(f_s);
#endif
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

		string feaPathA;
		if(isFlow){
			feaPathA = upperDirectory(GConfig::getInstance().getAppliancePathA()) + "/" + "feaMA";
		}else{
			feaPathA = upperDirectory(GConfig::getInstance().getCompareImgPathA()) + "/" + "feaMA";
		}
		vector<string> featureAs;
		listOutDirectoryFiles(feaPathA, featureAs);
		int featureNumPerThread = int(featureAs.size()/pThreads_size);
		vector<string> featureAsOfCurrentThread;
		if(currentThreadIndex == pThreads_size-1){
			featureAsOfCurrentThread.assign(featureAs.begin()+currentThreadIndex*featureNumPerThread, featureAs.end());
		}
		else{
			featureAsOfCurrentThread.assign(featureAs.begin()+currentThreadIndex*featureNumPerThread, featureAs.begin()+(currentThreadIndex+1)*featureNumPerThread);
		}

		string feaPathB;
		if(isFlow){
			feaPathB = upperDirectory(GConfig::getInstance().getAppliancePathB()) + "/" + "feaMB";
		}else{
			feaPathB = upperDirectory(GConfig::getInstance().getCompareImgPathB()) + "/" + "feaMB";
		}
		vector<string> featureBs;
		listOutDirectoryFiles(feaPathB, featureBs);
		float score;
		char featureA[8192];
		char featureB[8192];
		Timer timer;
#ifdef WIN32
		fstream fileA, fileB;
#endif
#ifdef LINUX
		FILE *fileA, *fileB;
#endif

		int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
		float recongiseFaceValue = GConfig::getInstance().getRecogniseFaceValue();
		for(unsigned int i=0; i<featureAsOfCurrentThread.size(); i++){
#ifdef WIN32
			fileA.open(featureAsOfCurrentThread[i], ios::in | ios::binary);
			fileA.seekg(0, ios::beg);
			fileA.read(featureA, 8192);
			fileA.clear();
			fileA.close();
#endif
#ifdef LINUX
			fileA = fopen(featureAsOfCurrentThread[i].data(), "rb");
			fseek(fileA, 0, SEEK_SET);
			fread(featureA, 8192, 1, fileA);
			fclose(fileA);
#endif
			unsigned int start = i + currentThreadIndex*featureNumPerThread;
			unsigned int compareSamples = GConfig::getInstance().getCompareSamples();
			compareSamples = (compareSamples < featureBs.size()) ? compareSamples : featureBs.size();
			for(unsigned int k=0; k<featureBs.size(); k++){
				if(getFileHeader(featureAsOfCurrentThread[i].data()) == getFileHeader(featureBs[k].data())){
					start = k;
					break;
				}
			}

			for(unsigned int j=start; j<start+compareSamples; j++){
#ifdef WIN32
				fileB.open(featureBs[j%featureBs.size()], ios::in | ios::binary);
				fileB.seekg(0, ios::beg);
				fileB.read(featureB, 8192);
				fileB.clear();
				fileB.close();
#endif
#ifdef LINUX
				fileB = fopen(featureBs[j%featureBs.size()].data(), "rb");
				fseek(fileB, 0, SEEK_SET);
				fread(featureB, 8192, 1, fileB);
				fclose(fileB);
#endif

				timer.start();
				EXPECT_TRUE(SUCC == ISCompare( defaultCompareChannel
											 , featureA
											 , featureB
											 , &score));
				pthread_mutex_lock(&mutex);
				cost += timer.stop();
				pthread_mutex_unlock(&mutex);
				if(score < recongiseFaceValue
					&& 0 == strcmp(getFileHeader(featureAsOfCurrentThread[i].data()).data(), getFileHeader(featureBs[j%featureBs.size()].data()).data()))
				{
					pthread_mutex_lock(&mutex);
					valueCountsBig++;
					pthread_mutex_unlock(&mutex);
				}
				if(score >= recongiseFaceValue
					&& 0 != strcmp(getFileHeader(featureAsOfCurrentThread[i].data()).data(), getFileHeader(featureBs[j%featureBs.size()].data()).data()))
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

		string pcaPathA;
		if(isFlow){
			pcaPathA = upperDirectory(GConfig::getInstance().getAppliancePathA()) + "/" + "pcaMA";
		}else{
			pcaPathA = upperDirectory(GConfig::getInstance().getCompareImgPathA()) + "/" + "pcaMA";
		}
		vector<string> pcaAs;
		listOutDirectoryFiles(pcaPathA, pcaAs);
		int pcaNumPerThread = int(pcaAs.size()/pThreads_size);
		vector<string> pcaAsOfCurrentThread;
		if(currentThreadIndex == pThreads_size-1){
			pcaAsOfCurrentThread.assign(pcaAs.begin()+currentThreadIndex*pcaNumPerThread, pcaAs.end());
		}
		else{
			pcaAsOfCurrentThread.assign(pcaAs.begin()+currentThreadIndex*pcaNumPerThread, pcaAs.begin()+(currentThreadIndex+1)*pcaNumPerThread);
		}
		int pcaAsOfCurrentThread_size = pcaAsOfCurrentThread.size();

		string pcaPathB;
		if(isFlow){
			pcaPathB = upperDirectory(GConfig::getInstance().getAppliancePathB()) + "/" + "pcaMB";
		}else{
			pcaPathB = upperDirectory(GConfig::getInstance().getCompareImgPathB()) + "/" + "pcaMB";
		}
		vector<string> pcaBs;
		listOutDirectoryFiles(pcaPathB, pcaBs);
		int pcaBs_size = pcaBs.size();
		char pcaTemp[2048];
		Timer timer;
#ifdef WIN32
		fstream fileA, fileB;
#endif
#ifdef LINUX
		FILE *fileA, *fileB;
#endif

		int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
		float recongiseFaceValue = GConfig::getInstance().getRecogniseFaceValue();

		int compareSamples = GConfig::getInstance().getCompareSamples();
		compareSamples = (compareSamples < pcaBs_size) ? compareSamples : pcaBs_size;

		float **score;
		ALLOC_DOUBLE_STAR(1, compareSamples, float, score, S)

		char **pcaA;
		ALLOC_DOUBLE_STAR(1, 2048, char, pcaA, M)
		for(int s=0; s<pcaAsOfCurrentThread_size; s++){
#ifdef WIN32
			fileA.open(pcaAsOfCurrentThread[s], ios::in | ios::binary);
			fileA.seekg(0, ios::beg);
			fileA.read(pcaTemp, 2048);
			fileA.clear();
			fileA.close();
#endif
#ifdef LINUX
			fileA = fopen(pcaAsOfCurrentThread[s].data(), "rb");
			fseek(fileA, 0, SEEK_SET);
			fread(pcaTemp, 2048, 1, fileA);
			fclose(fileA);
#endif
			memcpy(pcaA[0], pcaTemp, 2048);

			int start = s;
			for(int k=0; k<pcaBs_size; k++){
					if(getFileHeader(pcaAsOfCurrentThread[s].data()) == getFileHeader(pcaBs[k].data())){
							start = k;
							break;
					}
			}
			char **pcaB;
			ALLOC_DOUBLE_STAR(compareSamples, 2048, char, pcaB, N)
			for(int i=start; i<start+compareSamples; i++)
			{
#ifdef WIN32
				fileB.open(pcaBs[i%pcaBs_size], ios::in | ios::binary);
				fileB.seekg(0, ios::beg);
				fileB.read(pcaTemp, 2048);
				fileB.clear();
				fileB.close();
#endif
#ifdef LINUX
				fileB = fopen(pcaBs[i%pcaBs_size].data(), "rb");
				fseek(fileB, 0, SEEK_SET);
				fread(pcaTemp, 2048, 1, fileB);
				fclose(fileB);
#endif
				memcpy(pcaB[i-start], pcaTemp, 2048);
			}

			timer.start();
			EXPECT_TRUE(SUCC == ISCompareMN(defaultCompareChannel, pcaA, 1, pcaB, compareSamples, score));
			pthread_mutex_lock(&mutex);
			cost += timer.stop();
			pthread_mutex_unlock(&mutex);
			for(int t=0; t<compareSamples; t++){
				if(score[0][t]<recongiseFaceValue && getFileHeader(pcaAsOfCurrentThread[s].data())==getFileHeader(pcaBs[(start + t)%pcaBs_size].data()))
				{
					pthread_mutex_lock(&mutex);
					valueCountsBig++;
					pthread_mutex_unlock(&mutex);
				}
				if(score[0][t]>=recongiseFaceValue && getFileHeader(pcaAsOfCurrentThread[s].data())!=getFileHeader(pcaBs[(start + t)%pcaBs_size].data()))
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

		string pcaPathA;
		if(isFlow){
			pcaPathA = upperDirectory(GConfig::getInstance().getAppliancePathA()) + "/" + "pcaMA";
		}else{
			pcaPathA = upperDirectory(GConfig::getInstance().getCompareImgPathA()) + "/" + "pcaMA";
		}
		vector<string> pcaAs;
		listOutDirectoryFiles(pcaPathA, pcaAs);
		int pcaNumPerThread = int(pcaAs.size()/pThreads_size);
		vector<string> pcaAsOfCurrentThread;
		if(currentThreadIndex == pThreads_size-1){
			pcaAsOfCurrentThread.assign(pcaAs.begin()+currentThreadIndex*pcaNumPerThread, pcaAs.end());
		}
		else{
			pcaAsOfCurrentThread.assign(pcaAs.begin()+currentThreadIndex*pcaNumPerThread, pcaAs.begin()+(currentThreadIndex+1)*pcaNumPerThread);
		}
		int pcaAsOfCurrentThread_size = pcaAsOfCurrentThread.size();

		string pcaPathB;
		if(isFlow){
			pcaPathB = upperDirectory(GConfig::getInstance().getAppliancePathB()) + "/" + "pcaMB";
		}else{
			pcaPathB = upperDirectory(GConfig::getInstance().getCompareImgPathB()) + "/" + "pcaMB";
		}
		vector<string> pcaBs;
		listOutDirectoryFiles(pcaPathB, pcaBs);
		int pcaBs_size = pcaBs.size();
		char pcaTemp[2048];
		Timer timer;
#ifdef WIN32
		fstream fileA, fileB;
#endif
#ifdef LINUX
		FILE *fileA, *fileB;
#endif

		int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
		float recongiseFaceValue = GConfig::getInstance().getRecogniseFaceValue();
		
		int compareSamples = GConfig::getInstance().getCompareSamples();
		compareSamples = (compareSamples < pcaBs_size) ? compareSamples : pcaBs_size;

		float **score;
		ALLOC_DOUBLE_STAR(1, compareSamples, float, score, S)

		char **pcaA;
		ALLOC_DOUBLE_STAR(1, 2048, char, pcaA, M)
		for(int s=0; s<pcaAsOfCurrentThread_size; s++){
#ifdef WIN32
			fileA.open(pcaAsOfCurrentThread[s], ios::in | ios::binary);
			fileA.seekg(0, ios::beg);
			fileA.read(pcaTemp, 2048);
			fileA.clear();
			fileA.close();
#endif
#ifdef LINUX
			fileA = fopen(pcaAsOfCurrentThread[s].data(), "rb");
			fseek(fileA, 0, SEEK_SET);
			fread(pcaTemp, 2048, 1, fileA);
			fclose(fileA);
#endif
			memcpy(pcaA[0], pcaTemp, 2048);

			int start = s;
			for(int k=0; k<pcaBs_size; k++){
					if(getFileHeader(pcaAsOfCurrentThread[s].data()) == getFileHeader(pcaBs[k].data())){
							start = k;
							break;
					}
			}

			char **pcaB;
			ALLOC_DOUBLE_STAR(compareSamples, 2048, char, pcaB, N)
			for(int i=start; i<start+compareSamples; i++)
			{
#ifdef WIN32
				fileB.open(pcaBs[i%pcaBs_size], ios::in | ios::binary);
				fileB.seekg(0, ios::beg);
				fileB.read(pcaTemp, 2048);
				fileB.clear();
				fileB.close();
#endif
#ifdef LINUX
				fileB = fopen(pcaBs[i%pcaBs_size].data(), "rb");
				fseek(fileB, 0, SEEK_SET);
				fread(pcaTemp, 2048, 1, fileB);
				fclose(fileB);
#endif
				memcpy(pcaB[i-start], pcaTemp, 2048);
			}

			EXPECT_TRUE(SUCC == ISCompareMNfasterprep(defaultCompareChannel, pcaB, compareSamples));
			timer.start();
			EXPECT_TRUE(SUCC == ISCompareMNfaster(defaultCompareChannel, pcaA, 1, score));
			pthread_mutex_lock(&mutex);
			cost += timer.stop();
			pthread_mutex_unlock(&mutex);
			for(int t=0; t<compareSamples; t++){
				if(score[0][t]<recongiseFaceValue && getFileHeader(pcaAsOfCurrentThread[s].data())==getFileHeader(pcaBs[(t+start)%pcaBs_size].data()))
				{
					pthread_mutex_lock(&mutex);
					valueCountsBig++;
					pthread_mutex_unlock(&mutex);
				}
				if(score[0][t]>=recongiseFaceValue && getFileHeader(pcaAsOfCurrentThread[s].data())!=getFileHeader(pcaBs[(t+start)%pcaBs_size].data()))
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
	string imgPathA = GConfig::getInstance().getCompareImgPathA();
	string imgPathB = GConfig::getInstance().getCompareImgPathB();

	vector<string> imageAs;
	listOutDirectoryFiles(imgPathA, imageAs);
	int imageAs_size = imageAs.size();
	vector<string> imageBs;
	listOutDirectoryFiles(imgPathB, imageBs);
	int imageBs_size = imageBs.size();

	vector<string> pathm(4), paths(4);
	pathm[0] = upperDirectory(imgPathA) + "/" + "feaMA";
	pathm[1] = upperDirectory(imgPathA) + "/" + "feaMB";
	pathm[2] = upperDirectory(imgPathB) + "/" + "pcaMA";
	pathm[3] = upperDirectory(imgPathB) + "/" + "pcaMB";
	paths[0] = upperDirectory(imgPathA) + "/" + "feaSA";
	paths[1] = upperDirectory(imgPathA) + "/" + "feaSB";
	paths[2] = upperDirectory(imgPathB) + "/" + "pcaSA";
	paths[3] = upperDirectory(imgPathB) + "/" + "pcaSB";

	string command;
	for(unsigned int i=0; i<pathm.size(); i++){
#ifdef WIN32
		pathm[i] = slashConvert(pathm[i], '/', '\\');
		command = "rd /s /q " + pathm[i];
		system(command.c_str());
		command = "mkdir " + pathm[i];
		system(command.c_str());
		paths[i] = slashConvert(paths[i], '/', '\\');
		command = "rd /s /q " + paths[i];
		system(command.c_str());
		command = "mkdir " + paths[i];
		system(command.c_str());
#endif
#ifdef LINUX
		rmDir(pathm[i]);
		mkdir(pathm[i].data(), 0775);
		rmDir(paths[i]);
		mkdir(paths[i].data(), 0775);
#endif
	}

	featureNumA = 0;
	featureNumB = 0;

	unsigned int detectThreadNum = GConfig::getInstance().getGetFeaThreadNum();
	int imgANumPerThread = int(imageAs_size/detectThreadNum);
	int imgBNumPerThread = int(imageBs_size/detectThreadNum);

	cout << "Please invoke this case first!!!" << endl;
	cout << "This case provides feature and pca for other cases" << endl;
	cout << ">>Inputs <<" << endl;
	cout << "Image directory A: " << GConfig::getInstance().getCompareImgPathA() << endl;
	cout << "Image directory B: " << GConfig::getInstance().getCompareImgPathB() << endl;
	cout << "Threads Num: " << GConfig::getInstance().getGetFeaThreadNum() << endl;
	cout << ">>Outputs<<" << endl;

	vector<vector<string> > imageA, imageB;
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
	serial = imgPathA;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceFeature, (void *)&imageA[i]));
	}

	void *retVal;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

	serial = imgPathB;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceFeature, (void *)&imageB[i]));
	}

	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

	cout << "picture num of image directory A: " << imageAs_size << endl;
	cout << "picture num got feature succ of image directory A: " << featureNumA << endl;
	float percent = float(featureNumA)/imageAs_size*100;
	cout << "success rate: " << setiosflags(ios::fixed) << setprecision(4) << percent << "%" << endl;
	cout << "picture num of image directory B: " << imageBs_size << endl;
	cout << "picture num got feature succ of image directory B: " << featureNumB << endl;
	percent = float(featureNumB)/imageBs_size*100;
	cout << "success rate: " << setiosflags(ios::fixed) << setprecision(4) << percent << "%" << endl;
	cout << "output feature of image directory A to: " << pathm[0] << endl;
	cout << "output feature of image directory B to: " << pathm[1] << endl;
	cout << "output pca of image directory A to: " << pathm[2] << endl;
	cout << "output pca of image directory B to: " << pathm[3] << endl;
}

//ISCompare only supports feature with length of 8192
TEST_F(ftISCompare, ISCompare_SingleThread){
	string imgPathA, imgPathB;
	if(isFlow){
		imgPathA = GConfig::getInstance().getAppliancePathA();
		imgPathB = GConfig::getInstance().getAppliancePathB();
	}else{
		imgPathA = GConfig::getInstance().getCompareImgPathA();
		imgPathB = GConfig::getInstance().getCompareImgPathB();
	}

#ifdef WIN32
	fstream f;
#endif
#ifdef LINUX
	FILE *f;
#endif
	char featureB[8192];
	char featureA[8192];

	string featurePathA = upperDirectory(imgPathA) + "/" + "feaSA";
	vector<string> feaAFiles;
	listOutDirectoryFiles(featurePathA, feaAFiles);
	int feaAFiles_size = feaAFiles.size();
	string featurePathB = upperDirectory(imgPathA) + "/" + "feaSB";
	vector<string> feaBFiles;
	listOutDirectoryFiles(featurePathB, feaBFiles);
	int feaBFiles_size = feaBFiles.size();
	int compareSamples = GConfig::getInstance().getCompareSamples();
	compareSamples = (compareSamples < feaBFiles_size) ? compareSamples : feaBFiles_size;

	valueCountsSmall = 0;
	valueCountsBig = 0;
	Timer timer;
	cost = 0;

	cout << ">>Inputs <<" << endl;
	cout << "Feature directory A: " << featurePathA << endl;
	cout << "Feature directory B: " << featurePathB << endl;
	cout << "Threads Num: " << "1" << endl;
	cout << ">>Outputs<<" << endl;

	int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
	float recongiseFaceValue = GConfig::getInstance().getRecogniseFaceValue();
	float score;
	for(int i=0; i<feaAFiles_size; i++){
#ifdef WIN32
		f.open(feaAFiles[i], ios::in | ios::binary);
		f.seekg(0, ios::beg);
		f.read(featureA, 8192);
		f.clear();
		f.close();
#endif
#ifdef LINUX
		f = fopen(feaAFiles[i].data(), "rb");
		fseek(f, 0, SEEK_SET);
		fread(featureA, 8192, 1, f);
		fclose(f);
#endif
		int start = i;
		for(int k=0; k<feaBFiles_size; k++){
			if(getFileHeader(feaAFiles[i].data()) == getFileHeader(feaBFiles[k].data())){
				start = k;
				break;
			}
		}
		for(int j=start; j<start+compareSamples; j++){
#ifdef WIN32
			f.open(feaBFiles[j%feaBFiles_size], ios::in | ios::binary);
			f.seekg(0, ios::beg);
			f.read(featureB, 8192);
			f.clear();
			f.close();
#endif
#ifdef LINUX
			f = fopen(feaBFiles[j%feaBFiles_size].data(), "rb");
			fseek(f, 0, SEEK_SET);
			fread(featureB, 8192, 1, f);
			fclose(f);
#endif
			timer.start();
			EXPECT_TRUE(SUCC == ISCompare(defaultCompareChannel, featureA, featureB, &score));
			cost += timer.stop();
			if(score < recongiseFaceValue
				&& 0 == strcmp(getFileHeader(feaAFiles[i].data()).data(), getFileHeader(feaBFiles[j%feaBFiles_size].data()).data()))
			{
				valueCountsBig++;
			}
			if(score >= recongiseFaceValue
				&& 0 != strcmp(getFileHeader(feaAFiles[i].data()).data(), getFileHeader(feaBFiles[j%feaBFiles_size].data()).data()))
			{
				valueCountsSmall++;
			}
		}
	}
	DESTROY_COMPARE_CHANNEL(defaultCompareChannel);

	cout << "feature num of feature directory A: " << feaAFiles_size << endl;
	cout << "feature num of feature directory B: " << feaBFiles_size << endl;
	cout << "samples: " << compareSamples << endl;
	cout << "for an identical person, but score less than compareFaceValue: " << valueCountsBig << endl;
	float percent = float(valueCountsBig)/(feaAFiles_size*compareSamples)*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(4) << percent << "%" << endl;
	cout << "for two different persons, but score more than compareFaceValue: " << valueCountsSmall << endl;
	percent = float(valueCountsSmall)/(feaAFiles_size*compareSamples)*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(4) << percent << "%" << endl;
	cout << "compare times: " << feaAFiles_size*compareSamples << endl;
	float timePerPic = float(cost)/(feaAFiles_size*compareSamples);
	cout << "whole cost: " << cost << "ms" << endl;
	cout << "average time cost: " << setiosflags(ios::fixed) << setprecision(4) << timePerPic << "ms" << endl;
}

TEST_F(ftISCompare, ISCompare_MultiThread){
	string imgPathA, imgPathB;
	if(isFlow){
		imgPathA = GConfig::getInstance().getAppliancePathA();
		imgPathB = GConfig::getInstance().getAppliancePathB();
	}else{
		imgPathA = GConfig::getInstance().getCompareImgPathA();
		imgPathB = GConfig::getInstance().getCompareImgPathB();
	}

	string featurePathA = upperDirectory(imgPathA) + "/" + "feaMA";
	vector<string> feaAs;
	listOutDirectoryFiles(featurePathA, feaAs);
	int feaAs_size = feaAs.size();
	string featurePathB = upperDirectory(imgPathA) + "/" + "feaMB";
	vector<string> feaBs;
	listOutDirectoryFiles(featurePathB, feaBs);
	int feaBs_size = feaBs.size();

	valueCountsSmall = 0;
	valueCountsBig = 0;
	cost = 0;

	cout << ">>Inputs <<" << endl;
	cout << "Feature directory A: " << featurePathA << endl;
	cout << "Feature directory B: " << featurePathB << endl;
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

	int compareSamples = GConfig::getInstance().getCompareSamples();
	compareSamples = (compareSamples < feaBs_size) ? compareSamples : feaBs_size;
	cout << "feature num of feature directory A: " << feaAs_size << endl;
	cout << "feature num of feature directory B: " << feaBs_size << endl;
	cout << "samples: " << compareSamples << endl;
	cout << "for an identical person, but score less than compareFaceValue: " << valueCountsBig << endl;
	float percent = float(valueCountsBig)/(feaAs_size*compareSamples)*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(4) << percent << "%" << endl;
	cout << "for two different persons, but score more than compareFaceValue: " << valueCountsSmall << endl;
	percent = float(valueCountsSmall)/(feaAs_size*compareSamples)*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(4) << percent << "%" << endl;
	cout << "compare times: " << feaAs_size*compareSamples << endl;
	cost = cost/compareThreadNum;
	float timePerPic = float(cost)/(feaAs_size*compareSamples);
	cout << "whole cost: " << cost << "ms" << endl;
	cout << "average time cost: " << setiosflags(ios::fixed) << setprecision(4) << timePerPic << "ms" << endl;
}

//ISCompareMN/ISCompareMNfaster only support pca with length of 2048
TEST_F(ftISCompare, ISCompareMN_SingleThread){
	string imgPathA, imgPathB;
	if(isFlow){
		imgPathA = GConfig::getInstance().getAppliancePathA();
		imgPathB = GConfig::getInstance().getAppliancePathB();
	}else{
		imgPathA = GConfig::getInstance().getCompareImgPathA();
		imgPathB = GConfig::getInstance().getCompareImgPathB();
	}
	string pcaPathA = upperDirectory(imgPathA) + "/" + "pcaSA";
	vector<string> pcaAs;
	listOutDirectoryFiles(pcaPathA, pcaAs);
	int pcaAs_size = pcaAs.size();
	string pcaPathB = upperDirectory(imgPathB) + "/" + "pcaSB";
	vector<string> pcaBs;
	listOutDirectoryFiles(pcaPathB, pcaBs);
	int pcaBs_size = pcaBs.size();

#ifdef WIN32
	fstream fileA, fileB;
#endif
#ifdef LINUX
	FILE *fileA, *fileB;
#endif
	char pcaTemp[2048];
	Timer timer;
	cost = 0;

	int compareSamples = GConfig::getInstance().getCompareSamples();
	compareSamples = (compareSamples < pcaBs_size) ? compareSamples : pcaBs_size;

	float **score;
	ALLOC_DOUBLE_STAR(1, compareSamples, float, score, S)

	cout << ">>Inputs <<" << endl;
	cout << "Pca directory A: " << pcaPathA << endl;
	cout << "Pca directory B: " << pcaPathB << endl;
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
#ifdef WIN32
		fileA.open(pcaAs[s], ios::in | ios::binary);
		fileA.seekg(0, ios::beg);
		fileA.read(pcaTemp, 2048);
		fileA.clear();
		fileA.close();
#endif
#ifdef LINUX
		fileA = fopen(pcaAs[s].data(), "rb");
		fseek(fileA, 0, SEEK_SET);
		fread(pcaTemp, 2048, 1, fileA);
		fclose(fileA);
#endif
		memcpy(pcaA[0], pcaTemp, 2048);

		int start = s;
		for(int k=0; k<pcaBs_size; k++){
			if(getFileHeader(pcaAs[s].data()) == getFileHeader(pcaBs[k].data())){
				start = k;
				break;
			}
		}
		char **pcaB;
		ALLOC_DOUBLE_STAR(compareSamples, 2048, char, pcaB, N)
		for(int i=start; i<start+compareSamples; i++)
		{
#ifdef WIN32
			fileB.open(pcaBs[i%pcaBs_size], ios::in | ios::binary);
			fileB.seekg(0, ios::beg);
			fileB.read(pcaTemp, 2048);
			fileB.clear();
			fileB.close();
#endif
#ifdef LINUX
			fileB = fopen(pcaBs[i%pcaBs_size].data(), "rb");
			fseek(fileB, 0, SEEK_SET);
			fread(pcaTemp, 2048, 1, fileB);
			fclose(fileB);
#endif
			memcpy(pcaB[i-start], pcaTemp, 2048);
		}

		timer.start();
		EXPECT_TRUE(SUCC == ISCompareMN(defaultCompareChannel, pcaA, 1, pcaB, compareSamples, score));
		cost += timer.stop();
		for(int t=0; t<compareSamples; t++){
			if(score[0][t]<recongiseFaceValue && getFileHeader(pcaAs[s].data())==getFileHeader(pcaBs[(start + t)%pcaBs_size].data()))
			{
				valueCountsBig++;
			}
			if(score[0][t]>=recongiseFaceValue && getFileHeader(pcaAs[s].data())!=getFileHeader(pcaBs[(start + t)%pcaBs_size].data()))
			{
				valueCountsSmall++;
			}
		}
	}

	DESTROY_COMPARE_CHANNEL(defaultCompareChannel);

	cout << "pca num of pca directory A: " << pcaAs_size << endl;
	cout << "pca num of pca directory B: " << pcaBs_size << endl;
	cout << "samples: " << compareSamples << endl;
	cout << "for an identical person, but score less than recongiseFaceValue: " << valueCountsBig << endl;
	float percent = float(valueCountsBig)/(pcaAs_size*compareSamples)*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(4) << percent << "%" << endl;
	cout << "for two different persons, but score more than compareFaceValue: " << valueCountsSmall << endl;
	percent = float(valueCountsSmall)/(pcaAs_size*compareSamples)*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(4) << percent << "%" << endl;
	cout << "compare times: " << pcaAs_size*compareSamples << endl;
	float timePerPic = float(cost)/(pcaAs_size*compareSamples);
	cout << "whole cost: " << cost << "ms" << endl;
	cout << "average time cost: " << setiosflags(ios::fixed) << setprecision(4) << timePerPic << "ms" << endl;
}

TEST_F(ftISCompare, ISCompareMN_MultiThread){
	string imgPathA, imgPathB;
	if(isFlow){
		imgPathA = GConfig::getInstance().getAppliancePathA();
		imgPathB = GConfig::getInstance().getAppliancePathB();
	}else{
		imgPathA = GConfig::getInstance().getCompareImgPathA();
		imgPathB = GConfig::getInstance().getCompareImgPathB();
	}
	string pcaPathA = upperDirectory(imgPathA) + "/" + "pcaMA";
	vector<string> pcaAs;
	listOutDirectoryFiles(pcaPathA, pcaAs);
	int pcaAs_size = pcaAs.size();
	string pcaPathB = upperDirectory(imgPathB) + "/" + "pcaMB";
	vector<string> pcaBs;
	listOutDirectoryFiles(pcaPathB, pcaBs);
	int pcaBs_size = pcaBs.size();

	valueCountsSmall = 0;
	valueCountsBig = 0;
	cost = 0;

	cout << ">>Inputs <<" << endl;
	cout << "Pca directory A: " << pcaPathA << endl;
	cout << "Pca directory B: " << pcaPathB << endl;
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

	int compareSamples = GConfig::getInstance().getCompareSamples();
	compareSamples = (compareSamples < pcaBs_size) ? compareSamples : pcaBs_size;

	cout << "pca num of pca directory A: " << pcaAs_size << endl;
	cout << "pca num of pca directory B: " << pcaBs_size << endl;
	cout << "compareSamples: " << compareSamples << endl;
	cout << "for an identical person, but score less than recongiseFaceValue: " << valueCountsBig << endl;
	float percent = float(valueCountsBig)/(pcaAs_size*compareSamples)*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(4) << percent << "%" << endl;
	cout << "for two different persons, but score more than compareFaceValue: " << valueCountsSmall << endl;
	percent = float(valueCountsSmall)/(pcaAs_size*compareSamples)*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(4) << percent << "%" << endl;
	cout << "compare times: " << pcaAs_size*compareSamples << endl;
	cost = cost/recogniseThreadNum;
	float timePerPic = float(cost)/(pcaAs_size*compareSamples);
	cout << "whole cost: " << cost << "ms" << endl;
	cout << "average time cost: " << setiosflags(ios::fixed) << setprecision(4) << timePerPic << "ms" << endl;
}

TEST_F(ftISCompare, ISCompareMNfaster_SingleThread){
	string imgPathA, imgPathB;
	if(isFlow){
		imgPathA = GConfig::getInstance().getAppliancePathA();
		imgPathB = GConfig::getInstance().getAppliancePathB();
	}else{
		imgPathA = GConfig::getInstance().getCompareImgPathA();
		imgPathB = GConfig::getInstance().getCompareImgPathB();
	}

#ifdef WIN32
	fstream fileA, fileB;
#endif
#ifdef LINUX
	FILE *fileA, *fileB;
#endif

	string pcaPathA = upperDirectory(imgPathA) + "/" + "pcaSA";
	vector<string> pcaAs;
	listOutDirectoryFiles(pcaPathA, pcaAs);
	int pcaAs_size = pcaAs.size();
	string pcaPathB = upperDirectory(imgPathB) + "/" + "pcaSB";
	vector<string> pcaBs;
	listOutDirectoryFiles(pcaPathB, pcaBs);
	int pcaBs_size = pcaBs.size();
	char pcaTemp[2048];
	Timer timer;
	cost = 0;

    int compareSamples = GConfig::getInstance().getCompareSamples();
    compareSamples = (compareSamples < pcaBs_size) ? compareSamples : pcaBs_size;
	int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();

	float **score;
	ALLOC_DOUBLE_STAR(1, compareSamples, float, score, S)

	cout << ">>Inputs <<" << endl;
	cout << "Pca directory A: " << pcaPathA << endl;
	cout << "Pca directory B: " << pcaPathB << endl;
	cout << "Threads Num: " << "1" << endl;
	cout << ">>Outputs<<" << endl;

	valueCountsSmall = 0;
	valueCountsBig = 0;

	float recongiseFaceValue = GConfig::getInstance().getRecogniseFaceValue();
	char **pcaA;
	ALLOC_DOUBLE_STAR(1, 2048, char, pcaA, M)
	for(int s=0; s<pcaAs_size; s++){
#ifdef WIN32
		fileA.open(pcaAs[s], ios::in | ios::binary);
		fileA.seekg(0, ios::beg);
		fileA.read(pcaTemp, 2048);
		fileA.clear();
		fileA.close();
#endif
#ifdef LINUX
		fileA = fopen(pcaAs[s].data(), "rb");
		fseek(fileA, 0, SEEK_SET);
		fread(pcaTemp, 2048, 1, fileA);
		fclose(fileA);
#endif
		memcpy(pcaA[0], pcaTemp, 2048);

        int start = s;
        for(int k=0; k<pcaBs_size; k++){
                if(getFileHeader(pcaAs[s].data()) == getFileHeader(pcaBs[k].data())){
                        start = k;
                        break;
                }
        }

		char **pcaB;
		ALLOC_DOUBLE_STAR(compareSamples, 2048, char, pcaB, N)
		for(int i=start; i<start+compareSamples; i++)
		{
#ifdef WIN32
			fileB.open(pcaBs[i%pcaBs_size], ios::in | ios::binary);
			fileB.seekg(0, ios::beg);
			fileB.read(pcaTemp, 2048);
			fileB.clear();
			fileB.close();
#endif
#ifdef LINUX
			fileB = fopen(pcaBs[i%pcaBs_size].data(), "rb");
			fseek(fileB, 0, SEEK_SET);
			fread(pcaTemp, 2048, 1, fileB);
			fclose(fileB);
#endif
			memcpy(pcaB[i-start], pcaTemp, 2048);
		}
		EXPECT_TRUE(SUCC == ISCompareMNfasterprep(defaultCompareChannel, pcaB, compareSamples));

		timer.start();
		EXPECT_TRUE(SUCC == ISCompareMNfaster(defaultCompareChannel, pcaA, 1, score));
		cost += timer.stop();
		for(int t=0; t<compareSamples; t++){
			if(score[0][t]<recongiseFaceValue && getFileHeader(pcaAs[s].data())==getFileHeader(pcaBs[(t+start)%pcaBs_size].data()))
			{
				valueCountsBig++;
			}
			if(score[0][t]>=recongiseFaceValue && getFileHeader(pcaAs[s].data())!=getFileHeader(pcaBs[(t+start)%pcaBs_size].data()))
			{
				valueCountsSmall++;
			}
		}
	}

	DESTROY_COMPARE_CHANNEL(defaultCompareChannel);

	cout << "pca num of pca directory A: " << pcaAs_size << endl;
	cout << "pca num of pca directory B: " << pcaBs_size << endl;
	cout << "samples: " << compareSamples << endl;
	cout << "for an identical person, but score less than recongiseFaceValue: " << valueCountsBig << endl;
	float percent = float(valueCountsBig)/(pcaAs_size*compareSamples)*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(4) << percent << "%" << endl;
	cout << "for two different persons, but score more than compareFaceValue: " << valueCountsSmall << endl;
	percent = float(valueCountsSmall)/(pcaAs_size*compareSamples)*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(4) << percent << "%" << endl;
	cout << "compare times: " << pcaAs_size*compareSamples << endl;
	float timePerPic = float(cost)/(pcaAs_size*compareSamples);
	cout << "whole cost: " << cost << "ms" << endl;
	cout << "average time cost: " << setiosflags(ios::fixed) << setprecision(4) << timePerPic << "ms" << endl;
}

TEST_F(ftISCompare, ISCompareMNfaster_MultiThread){
	string imgPathA, imgPathB;
	if(isFlow){
		imgPathA = GConfig::getInstance().getAppliancePathA();
		imgPathB = GConfig::getInstance().getAppliancePathB();
	}else{
		imgPathA = GConfig::getInstance().getCompareImgPathA();
		imgPathB = GConfig::getInstance().getCompareImgPathB();
	}

	string pcaPathA = upperDirectory(imgPathA) + "/" + "pcaMA";
	vector<string> pcaAs;
	listOutDirectoryFiles(pcaPathA, pcaAs);
	int pcaAs_size = pcaAs.size();

	string pcaPathB = upperDirectory(imgPathB) + "/" + "pcaMB";
	vector<string> pcaBs;
	listOutDirectoryFiles(pcaPathB, pcaBs);
	int pcaBs_size = pcaBs.size();

	valueCountsSmall = 0;
	valueCountsBig = 0;
	cost = 0;

	cout << ">>Inputs <<" << endl;
	cout << "Pca directory A: " << pcaPathA << endl;
	cout << "Pca directory B: " << pcaPathB << endl;
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

    int compareSamples = GConfig::getInstance().getCompareSamples();
    compareSamples = (compareSamples < pcaBs_size) ? compareSamples : pcaBs_size;

	cout << "pca num of pca directory A: " << pcaAs_size << endl;
	cout << "pca num of pca directory B: " << pcaBs_size << endl;
	cout << "samples: " << compareSamples << endl;
	cout << "for an identical person, but score less than recongiseFaceValue: " << valueCountsBig << endl;
	float percent = float(valueCountsBig)/(pcaAs_size*compareSamples)*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(4) << percent << "%" << endl;
	cout << "for two different persons, but score more than compareFaceValue: " << valueCountsSmall << endl;
	percent = float(valueCountsSmall)/(pcaAs_size*compareSamples)*100;
	cout << "error rate: " << setiosflags(ios::fixed) << setprecision(4) << percent << "%" << endl;
	cout << "compare times: " << pcaAs_size*compareSamples << endl;
	float timePerPic = float(cost)/(pcaAs_size*compareSamples);
	cost = cost/recogniseThreadNum;
	cout << "whole cost: " << cost << "ms" << endl;
	cout << "average time cost: " << setiosflags(ios::fixed) << setprecision(4) << timePerPic << "ms" << endl;
}
