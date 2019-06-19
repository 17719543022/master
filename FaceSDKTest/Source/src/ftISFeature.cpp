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

using namespace std;
using namespace cv;

extern pthread_mutex_t mutex;
extern int denominator;
int featureNum;

namespace{
	void *faceFeature(void *ptr){
		vector<string> images = *(vector<string> *)ptr;

		int defaultFeatureChannel = DEFAULT_FEATURE_CHANNEL();
		char feature[5][8192];
		char pca[2048];
#ifdef WIN32
		fstream fileF, fileP;
#endif
#ifdef LINUX
		FILE *fileF, *fileP;
#endif
		for(unsigned int i=0; i<images.size(); i++){
			if(SUCC != ISGetFeaturePath(defaultFeatureChannel, const_cast<char *>(images[i].data()), feature[0])){
				continue;
			}
			else{
				pthread_mutex_lock(&mutex);
				featureNum++;
				pthread_mutex_unlock(&mutex);
				ISGetPcaFea(defaultFeatureChannel, feature[0], pca);
#ifdef WIN32
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
#endif
#ifdef LINUX
				string saveFeaPath = GConfig::getInstance().getFeaMPath() + "/" + getFileHeader(images[i].data()) + ".fea";
				fileF = fopen(saveFeaPath.data(), "wb");
				fwrite(feature, 8192, 1, fileF);
				fclose(fileF);

				string savePcaPath = GConfig::getInstance().getPcaMPath() + "/" + getFileHeader(images[i].data()) + ".pca";
				fileP = fopen(savePcaPath.data(), "wb");
				fwrite(pca, 2048, 1, fileP);
				fclose(fileP);
#endif
			}
		}
		DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);

		return NULL;
	}
}

TEST_F(ftISFeature, ISGetFeaturePath_SingleThread){
	string imgPath = GConfig::getInstance().getFeatureImgPath();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);
	featureNum = 0;

	cout << ">>Inputs <<" << endl;
	cout << "image directory: " << imgPath << endl;
	cout << "threads num: " << "1" << endl;
	cout << ">>Outputs<<" << endl;

	char feature[5][8192];
	char pca[2048];
#ifdef WIN32
	fstream fileF, fileP;
#endif
#ifdef LINUX
	FILE *fileF, *fileP;
#endif
	string feaPath = GConfig::getInstance().getFeaSPath();
	string pcaPath = GConfig::getInstance().getPcaSPath();

#ifdef WIN32
	string command = "rd /s /q " + feaPath;
	system(command.c_str());
	command = "mkdir " + feaPath;
	system(command.c_str());
	command = "rd /s /q " + pcaPath;
	system(command.c_str());
	command = "mkdir " + pcaPath;
	system(command.c_str());
#endif
#ifdef LINUX
	rmDir(feaPath);
	mkdir(feaPath.data(), 0775);
	rmDir(pcaPath);
	mkdir(pcaPath.data(), 0775);
#endif

	int defaultFeatureChannel = DEFAULT_FEATURE_CHANNEL();
	for(unsigned int i=0; i<images.size(); i++){
		if(SUCC != ISGetFeaturePath(defaultFeatureChannel, const_cast<char *>(images[i].data()), feature[0])){
			continue;
		}

		ISGetPcaFea(defaultFeatureChannel, feature[0], pca);
		featureNum++;
#ifdef WIN32
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
#endif
#ifdef LINUX
		string saveFeaPath = feaPath + "/" + getFileHeader(images[i].data()) + ".fea";
		fileF = fopen(saveFeaPath.data(), "wb");
		fwrite(feature, 8192, 1, fileF);
		fclose(fileF);

		string savePcaPath = pcaPath + "/" + getFileHeader(images[i].data()) + ".pca";
		fileP = fopen(savePcaPath.data(), "wb");
		fwrite(pca, 2048, 1, fileP);
		fclose(fileP);
#endif
	}
	DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);

	cout << "picture num of image directory: " << images.size() << endl;
	cout << "picture num got feature succ of image directory: " << featureNum << endl;
	float percent = float(featureNum)/images.size()*100;
	cout << "success rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "output feature of image directory to: " << feaPath << endl;
	cout << "output pca of image directory to: " << pcaPath << endl;
	denominator = images.size();
}

TEST_F(ftISFeature, ISGetFeaturePath_MultiThread){
	string imgPath = GConfig::getInstance().getFeatureImgPath();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);
	featureNum = 0;

	unsigned int detectThreadNum = GConfig::getInstance().getGetFeaThreadNum();
	int imgNumPerThread = int(images.size()/detectThreadNum);

	cout << ">>Inputs <<" << endl;
	cout << "image directory: " << imgPath << endl;
	cout << "threads num: " << detectThreadNum << endl;
	cout << ">>Outputs<<" << endl;

#ifdef WIN32
	string command = "rd /s /q " + GConfig::getInstance().getFeaMPath();
	system(command.c_str());
	command = "mkdir " + GConfig::getInstance().getFeaMPath();
	system(command.c_str());
	command = "rd /s /q " + GConfig::getInstance().getPcaMPath();
	system(command.c_str());
	command = "mkdir " + GConfig::getInstance().getPcaMPath();
	system(command.c_str());
#endif
#ifdef LINUX
	rmDir(GConfig::getInstance().getFeaMPath());
	mkdir(GConfig::getInstance().getFeaMPath().data(), 0775);
	rmDir(GConfig::getInstance().getPcaMPath());
	mkdir(GConfig::getInstance().getPcaMPath().data(), 0775);
#endif

	vector<vector<string> > image;
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

	cout << "picture num of image directory: " << images.size() << endl;
	cout << "picture num got feature succ of image directory: " << featureNum << endl;
	float percent = float(featureNum)/images.size()*100;
	cout << "success rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "output feature of image directory to: " << GConfig::getInstance().getFeaMPath() << endl;
	cout << "output pca of image directory to: " << GConfig::getInstance().getPcaMPath() << endl;
	denominator = images.size();
}

TEST_F(ftISFeature, ISGetFeaturePath_OutResultCheck){
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

	cout << ">>Inputs <<" << endl;
	cout << "single thread feature path: " << feaS << endl;
	cout << "single thread pca path: " << pcaS << endl;
	cout << "multi thread feature path: " << feaM << endl;
	cout << "multi thread pca path: " << pcaM << endl;
	cout << ">>Outputs<<" << endl;

	EXPECT_TRUE(feaSNames.size()==feaMNames.size());
	EXPECT_TRUE(feaSNames.size()==pcaSNames.size());
	EXPECT_TRUE(pcaMNames.size()==feaMNames.size());

#ifdef WIN32
	fstream fFeaS;
	fstream fPcaS;
	fstream fFeaM;
	fstream fPcaM;
#endif
#ifdef LINUX
	FILE *fFeaS;
	FILE *fPcaS;
	FILE *fFeaM;
	FILE *fPcaM;
#endif
	int lenFea = 8192;
	int lenPca = 2048;
	char featureS[8192];
	char pcaFeatureS[8192];
	char featureM[8192];
	char pcaFeatureM[8192];

	for(unsigned int i=0; i<feaSNames.size(); i++){
#ifdef WIN32
		fFeaS.open(feaSNames[i], ios::in | ios::binary);
		fFeaS.read(featureS, 8192);
		fFeaS.clear();
		fFeaS.close();

		fFeaM.open(feaMNames[i], ios::in | ios::binary);
		fFeaM.read(featureM, 8192);
		fFeaM.clear();
		fFeaM.close();
#endif
#ifdef LINUX
		fFeaS = fopen(feaSNames[i].data(), "rb");
		fread(featureS, 8192, 1, fFeaS);
		fclose(fFeaS);

		fFeaM = fopen(feaMNames[i].data(), "rb");
		fread(featureM, 8192, 1, fFeaM);
		fclose(fFeaM);
#endif

		for(int j=0; j<8192; j++){
			EXPECT_TRUE(featureS[j]==featureM[j]);
		}

#ifdef WIN32
		fPcaS.open(pcaSNames[i], ios::in | ios::binary);
		fPcaS.read(pcaFeatureS, 2048);
		fPcaS.clear();
		fPcaS.close();

		fPcaM.open(pcaMNames[i], ios::in | ios::binary);
		fPcaM.read(pcaFeatureM, 2048);
		fPcaM.clear();
		fPcaM.close();
#endif
#ifdef LINUX
		fPcaS = fopen(pcaSNames[i].data(), "rb");
		fread(pcaFeatureS, 2048, 1, fPcaS);
		fclose(fPcaS);

		fPcaM = fopen(pcaMNames[i].data(), "rb");
		fread(pcaFeatureM, 2048, 1, fPcaM);
		fclose(fPcaM);
#endif

		for(int j=0; j<2048; j++){
			EXPECT_TRUE(pcaFeatureS[j]==pcaFeatureM[j]);
		}
	}

	cout << "whether single thread or multi thread, the got result(pca/feature) by ISGetFeaturePath are the same" << endl;
}
