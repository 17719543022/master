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
extern bool isFlow;
int featureNumA;
int featureNumB;
extern string serial;

namespace{
	void *faceFeature(void *ptr){
		vector<string> images = *(vector<string> *)ptr;
		string saveFeaPath, savePcaPath;

		int defaultFeatureChannel = DEFAULT_FEATURE_CHANNEL();
		char feature[5][8192];
		char pca[2048];
#ifdef WIN32
		fstream f;
#endif
#ifdef LINUX
		FILE *f;
#endif
		for(unsigned int i=0; i<images.size(); i++){
			if(SUCC != ISGetFeaturePath(defaultFeatureChannel, const_cast<char *>(images[i].data()), feature[0])){
				continue;
			}
			else{
				pthread_mutex_lock(&mutex);
				if(serial[serial.size() - 1] == 'A')
				{
					featureNumA += 1;
				}
				if(serial[serial.size() - 1] == 'B')
				{
					featureNumB += 1;
				}
				pthread_mutex_unlock(&mutex);

				ISGetPcaFea(defaultFeatureChannel, feature[0], pca);
#ifdef WIN32
				string saveFeaPath = serial + "\\" + getFileHeader(images[i].data()) + ".fea";
				f.open(saveFeaPath, ios::out | ios::binary);
				f.write(feature[0], sizeof(feature[0]));
				f.close();
				f.clear();

				if(serial[serial.size() - 1] == 'A'){
					savePcaPath = upperDirectory(serial) + "\\" + "pcaMA" + "\\" + getFileHeader(images[i].data()) + ".pca";
				}
				if(serial[serial.size() - 1] == 'B'){
					savePcaPath = upperDirectory(serial) + "\\" + "pcaMB" + "\\" + getFileHeader(images[i].data()) + ".pca";
				}
				f.open(savePcaPath, ios::out | ios::binary);
				f.write(pca, sizeof(pca));
				f.close();
				f.clear();
#endif
#ifdef LINUX
				saveFeaPath = serial + "/" + getFileHeader(images[i].data()) + ".fea";
				f = fopen(saveFeaPath.data(), "wb");
				fwrite(feature, 8192, 1, f);
				fclose(f);

				if(serial[serial.size() - 1] == 'A'){
					savePcaPath = upperDirectory(serial) + "/" + "pcaMA" + getFileHeader(images[i].data()) + ".pca";
				}
				if(serial[serial.size() - 1] == 'B'){
					savePcaPath = upperDirectory(serial) + "/" + "pcaMB" + getFileHeader(images[i].data()) + ".pca";
				}
				f = fopen(savePcaPath.data(), "wb");
				fwrite(pca, 2048, 1, f);
				fclose(f);
#endif
			}
		}
		DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);

		return NULL;
	}

	void *faceFeatureWithPos(void *ptr){
		vector<string> facePos = *(vector<string> *)ptr;
		string imgPath, saveFeaPath, savePcaPath;

		int defaultFeatureChannel = DEFAULT_FEATURE_CHANNEL();
		char feature[5][8192];
		char pca[2048];
		int len = 0;
		int outRst[50][4];
#ifdef WIN32
		fstream f;
#endif
#ifdef LINUX
		FILE *f;
#endif
		for(unsigned int i=0; i<facePos.size(); i++){
#ifdef WIN32
			f.open(facePos[i], ios::in | ios::binary);
			f.read((char *)&len, sizeof(len));
			f.read((char *)outRst[0], sizeof(outRst[0])*len);
			f.clear();
			f.close();
#endif
#ifdef LINUX
			f = fopen(facePos[i].data(), "rb");
			fseek(f, 0, SEEK_SET);
			fread(&len, sizeof(int), 1, f);
			fread(outRst, 4*sizeof(int)*len, 1, f);
			fclose(f);
#endif
			if(serial[serial.size() - 1] == 'A'){
				imgPath = upperDirectory(serial) + "/" + "detectImgA" + "/" + getFileHeader(facePos[i].data()) + ".jpg";
			}
			if(serial[serial.size() - 1] == 'B'){
				imgPath = upperDirectory(serial) + "/" + "detectImgB" + "/" + getFileHeader(facePos[i].data()) + ".jpg";
			}
			if(SUCC == ISGetFeatureWithFacePosPath(defaultFeatureChannel, const_cast<char *>(imgPath.data()), outRst, len, feature[0])){
				pthread_mutex_lock(&mutex);
				if(serial[serial.size() - 1] == 'A')
				{
					featureNumA += 1;
				}
				if(serial[serial.size() - 1] == 'B')
				{
					featureNumB += 1;
				}
				pthread_mutex_unlock(&mutex);

				ISGetPcaFea(defaultFeatureChannel, feature[0], pca);
#ifdef WIN32
				if(serial[serial.size() - 1] == 'A'){
					saveFeaPath = upperDirectory(serial) + "/" + "feaMA" + "/" + getFileHeader(facePos[i].data()) + ".fea";
				}
				if(serial[serial.size() - 1] == 'B'){
					saveFeaPath = upperDirectory(serial) + "/" + "feaMB" + "/" + getFileHeader(facePos[i].data()) + ".fea";
				}
				f.open(saveFeaPath, ios::out | ios::binary);
				f.write(feature[0], sizeof(feature[0]));
				f.close();
				f.clear();

				if(serial[serial.size() - 1] == 'A'){
					savePcaPath = upperDirectory(serial) + "/" + "pcaMA" + "/" + getFileHeader(facePos[i].data()) + ".pca";
				}
				if(serial[serial.size() - 1] == 'B'){
					savePcaPath = upperDirectory(serial) + "/" + "pcaMB" + "/" + getFileHeader(facePos[i].data()) + ".pca";
				}
				f.open(savePcaPath, ios::out | ios::binary);
				f.write(pca, sizeof(pca));
				f.close();
				f.clear();
#endif
#ifdef LINUX
				if(serial[serial.size() - 1] == 'A'){
					saveFeaPath = upperDirectory(serial) + "/" + "feaMA" + getFileHeader(facePos[i].data()) + ".fea";
				}
				if(serial[serial.size() - 1] == 'B'){
					saveFeaPath = upperDirectory(serial) + "/" + "feaMB" + getFileHeader(facePos[i].data()) + ".fea";
				}
				f = fopen(saveFeaPath.data(), "wb");
				fwrite(feature, 8192, 1, f);
				fclose(f);

				if(serial[serial.size() - 1] == 'A'){
					savePcaPath = upperDirectory(serial) + "/" + "pcaMA" + getFileHeader(facePos[i].data()) + ".pca";
				}
				if(serial[serial.size() - 1] == 'B'){
					savePcaPath = upperDirectory(serial) + "/" + "pcaMB" + getFileHeader(facePos[i].data()) + ".pca";
				}
				f = fopen(savePcaPath.data(), "wb");
				fwrite(pca, 2048, 1, f);
				fclose(f);
#endif
			}
		}
		DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);

		return NULL;
	}
}

TEST_F(ftISFeature, ISGetFeaturePath_SingleThread){
	string imgPathA = GConfig::getInstance().getFeatureImgPathA();
	vector<string> imageAs;
	listOutDirectoryFiles(imgPathA, imageAs);
	string imgPathB = GConfig::getInstance().getFeatureImgPathB();
	vector<string> imageBs;
	listOutDirectoryFiles(imgPathB, imageBs);
	featureNumA = 0;
	featureNumB = 0;

	cout << ">>Inputs <<" << endl;
	cout << "image directory A: " << imgPathA << endl;
	cout << "image directory B: " << imgPathB << endl;
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
	string feaPathA = upperDirectory(imgPathA) + "/" + "feaSA";
	string pcaPathA = upperDirectory(imgPathA) + "/" + "pcaSA";
	string feaPathB = upperDirectory(imgPathB) + "/" + "feaSB";
	string pcaPathB = upperDirectory(imgPathB) + "/" + "pcaSB";

#ifdef WIN32
	feaPathA = slashConvert(feaPathA, '/', '\\');
	pcaPathA = slashConvert(pcaPathA, '/', '\\');
	feaPathB = slashConvert(feaPathB, '/', '\\');
	pcaPathB = slashConvert(pcaPathB, '/', '\\');
	string command = "rd /s /q " + feaPathA;
	system(command.c_str());
	command = "mkdir " + feaPathA;
	system(command.c_str());
	command = "rd /s /q " + pcaPathA;
	system(command.c_str());
	command = "mkdir " + pcaPathA;
	system(command.c_str());
	command = "rd /s /q " + feaPathB;
	system(command.c_str());
	command = "mkdir " + feaPathB;
	system(command.c_str());
	command = "rd /s /q " + pcaPathB;
	system(command.c_str());
	command = "mkdir " + pcaPathB;
	system(command.c_str());
#endif
#ifdef LINUX
	rmDir(feaPathA);
	mkdir(feaPathA.data(), 0775);
	rmDir(pcaPathA);
	mkdir(pcaPathA.data(), 0775);
	rmDir(feaPathB);
	mkdir(feaPathB.data(), 0775);
	rmDir(pcaPathB);
	mkdir(pcaPathB.data(), 0775);
#endif

	int defaultFeatureChannel = DEFAULT_FEATURE_CHANNEL();
	for(unsigned int i=0; i<imageAs.size(); i++){
		if(SUCC != ISGetFeaturePath(defaultFeatureChannel, const_cast<char *>(imageAs[i].data()), feature[0])){
			continue;
		}

		ISGetPcaFea(defaultFeatureChannel, feature[0], pca);
		featureNumA++;
#ifdef WIN32
		string saveFeaPath = feaPathA + "\\" + getFileHeader(imageAs[i].data()) + ".fea";
		fileF.open(saveFeaPath, ios::out | ios::binary);
		fileF.write(feature[0], sizeof(feature[0]));
		fileF.close();
		fileF.clear();

		string savePcaPath = pcaPathA + "\\" + getFileHeader(imageAs[i].data()) + ".pca";
		fileP.open(savePcaPath, ios::out | ios::binary);
		fileP.write(pca, sizeof(pca));
		fileP.close();
		fileP.clear();
#endif
#ifdef LINUX
		string saveFeaPath = feaPathA + "/" + getFileHeader(imageAs[i].data()) + ".fea";
		fileF = fopen(saveFeaPath.data(), "wb");
		fwrite(feature, 8192, 1, fileF);
		fclose(fileF);

		string savePcaPath = pcaPathA + "/" + getFileHeader(imageAs[i].data()) + ".pca";
		fileP = fopen(savePcaPath.data(), "wb");
		fwrite(pca, 2048, 1, fileP);
		fclose(fileP);
#endif
	}
	for(unsigned int i=0; i<imageBs.size(); i++){
		if(SUCC != ISGetFeaturePath(defaultFeatureChannel, const_cast<char *>(imageBs[i].data()), feature[0])){
			continue;
		}

		ISGetPcaFea(defaultFeatureChannel, feature[0], pca);
		featureNumB++;
#ifdef WIN32
		string saveFeaPath = feaPathB + "\\" + getFileHeader(imageBs[i].data()) + ".fea";
		fileF.open(saveFeaPath, ios::out | ios::binary);
		fileF.write(feature[0], sizeof(feature[0]));
		fileF.close();
		fileF.clear();

		string savePcaPath = pcaPathB + "\\" + getFileHeader(imageBs[i].data()) + ".pca";
		fileP.open(savePcaPath, ios::out | ios::binary);
		fileP.write(pca, sizeof(pca));
		fileP.close();
		fileP.clear();
#endif
#ifdef LINUX
		string saveFeaPath = feaPathB + "/" + getFileHeader(imageBs[i].data()) + ".fea";
		fileF = fopen(saveFeaPath.data(), "wb");
		fwrite(feature, 8192, 1, fileF);
		fclose(fileF);

		string savePcaPath = pcaPathB + "/" + getFileHeader(imageBs[i].data()) + ".pca";
		fileP = fopen(savePcaPath.data(), "wb");
		fwrite(pca, 2048, 1, fileP);
		fclose(fileP);
#endif
	}
	DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);

	cout << "picture num of image directory A: " << imageAs.size() << endl;
	cout << "picture num of image directory B: " << imageBs.size() << endl;
	cout << "picture num got feature succ of image directory A: " << featureNumA << endl;
	cout << "picture num got feature succ of image directory B: " << featureNumB << endl;
	double percentA = double(featureNumA)/(imageAs.size() + 0.01)*100;
	cout << "success rate A: " << setiosflags(ios::fixed) << setprecision(2) << percentA << "%" << endl;
	double percentB = double(featureNumB)/(imageBs.size() + 0.01)*100;
	cout << "success rate B: " << setiosflags(ios::fixed) << setprecision(2) << percentB << "%" << endl;
	cout << "output feature of image directory to A: " << feaPathA << endl;
	cout << "output feature of image directory to B: " << feaPathB << endl;
	cout << "output pca of image directory to A: " << pcaPathA << endl;
	cout << "output pca of image directory to B: " << pcaPathB << endl;
	denominator = imageAs.size() + imageBs.size();
}

TEST_F(ftISFeature, ISGetFeaturePath_MultiThread){
	string imgPathA = GConfig::getInstance().getFeatureImgPathA();
	vector<string> imageAs;
	listOutDirectoryFiles(imgPathA, imageAs);
	string imgPathB = GConfig::getInstance().getFeatureImgPathB();
	vector<string> imageBs;
	listOutDirectoryFiles(imgPathB, imageBs);
	featureNumA = 0;
	featureNumB = 0;

	unsigned int detectThreadNum = GConfig::getInstance().getGetFeaThreadNum();
	int imgNumPerThreadA = int(imageAs.size()/detectThreadNum);
	int imgNumPerThreadB = int(imageBs.size()/detectThreadNum);

	cout << ">>Inputs <<" << endl;
	cout << "image directory A: " << imgPathA << endl;
	cout << "image directory B: " << imgPathB << endl;
	cout << "threads num: " << detectThreadNum << endl;
	cout << ">>Outputs<<" << endl;

	string feaPathA = upperDirectory(imgPathA) + "/" + "feaMA";
	string pcaPathA = upperDirectory(imgPathA) + "/" + "pcaMA";
	string feaPathB = upperDirectory(imgPathB) + "/" + "feaMB";
	string pcaPathB = upperDirectory(imgPathB) + "/" + "pcaMB";

#ifdef WIN32
	feaPathA = slashConvert(feaPathA, '/', '\\');
	pcaPathA = slashConvert(pcaPathA, '/', '\\');
	feaPathB = slashConvert(feaPathB, '/', '\\');
	pcaPathB = slashConvert(pcaPathB, '/', '\\');
	string command = "rd /s /q " + feaPathA;
	system(command.c_str());
	command = "mkdir " + feaPathA;
	system(command.c_str());
	command = "rd /s /q " + pcaPathA;
	system(command.c_str());
	command = "mkdir " + pcaPathA;
	system(command.c_str());
	command = "rd /s /q " + feaPathB;
	system(command.c_str());
	command = "mkdir " + feaPathB;
	system(command.c_str());
	command = "rd /s /q " + pcaPathB;
	system(command.c_str());
	command = "mkdir " + pcaPathB;
	system(command.c_str());
#endif
#ifdef LINUX
	rmDir(feaPathA);
	mkdir(feaPathA.data(), 0775);
	rmDir(pcaPathA);
	mkdir(pcaPathA.data(), 0775);
	rmDir(feaPathB);
	mkdir(feaPathB.data(), 0775);
	rmDir(pcaPathB);
	mkdir(pcaPathB.data(), 0775);
#endif

	vector<vector<string> > imageA;
	for(unsigned int i=0; i<detectThreadNum; i++){
		imageA.push_back(vector<string>());
		if(i == detectThreadNum-1){
			imageA[i].assign(imageAs.begin()+i*imgNumPerThreadA, imageAs.end());
		}
		else{
			imageA[i].assign(imageAs.begin()+i*imgNumPerThreadA, imageAs.begin()+(i+1)*imgNumPerThreadA);
		}
	}

	vector<vector<string> > imageB;
	for(unsigned int i=0; i<detectThreadNum; i++){
		imageB.push_back(vector<string>());
		if(i == detectThreadNum-1){
			imageB[i].assign(imageBs.begin()+i*imgNumPerThreadB, imageBs.end());
		}
		else{
			imageB[i].assign(imageBs.begin()+i*imgNumPerThreadB, imageBs.begin()+(i+1)*imgNumPerThreadB);
		}
	}

	vector<pthread_t> pThread(detectThreadNum);
	serial = upperDirectory(imgPathA) + "/" + "feaMA";
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceFeature, (void *)&imageA[i]));
	}

	void *retVal;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

	serial = upperDirectory(imgPathB) + "/" + "feaMB";
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceFeature, (void *)&imageB[i]));
	}

	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

	cout << "picture num of image directory A: " << imageAs.size() << endl;
	cout << "picture num of image directory B: " << imageBs.size() << endl;
	cout << "picture num got feature succ of image directory A: " << featureNumA << endl;
	cout << "picture num got feature succ of image directory B: " << featureNumB << endl;
	double percentA = double(featureNumA)/(imageAs.size() + 0.01)*100;
	cout << "success rate A: " << setiosflags(ios::fixed) << setprecision(2) << percentA << "%" << endl;
	double percentB = double(featureNumB)/(imageBs.size() + 0.01)*100;
	cout << "success rate B: " << setiosflags(ios::fixed) << setprecision(2) << percentB << "%" << endl;
	cout << "output feature of image directory to A: " << feaPathA << endl;
	cout << "output feature of image directory to B: " << feaPathB << endl;
	cout << "output pca of image directory to A: " << pcaPathA << endl;
	cout << "output pca of image directory to B: " << pcaPathB << endl;
	denominator = imageAs.size() + imageBs.size();
}

TEST_F(ftISFeature, ISGetFeaturePath_OutResultCheck){
	string imgPathA = GConfig::getInstance().getFeatureImgPathA();
	string imgPathB = GConfig::getInstance().getFeatureImgPathB();

	string feaSA = upperDirectory(imgPathA) + "/" + "feaSA";
	vector<string> recFeaSA;
	listOutDirectoryFiles(feaSA, recFeaSA);

	string feaMA = upperDirectory(imgPathA) + "/" + "feaMA";
	vector<string> recFeaMA;
	listOutDirectoryFiles(feaMA, recFeaMA);

	string pcaSA = upperDirectory(imgPathA) + "/" + "pcaSA";
	vector<string> recPcaSA;
	listOutDirectoryFiles(pcaSA, recPcaSA);

	string pcaMA = upperDirectory(imgPathA) + "/" + "pcaMA";
	vector<string> recPcaMA;
	listOutDirectoryFiles(pcaMA, recPcaMA);

	string feaSB = upperDirectory(imgPathB) + "/" + "feaSB";
	vector<string> recFeaSB;
	listOutDirectoryFiles(feaSB, recFeaSB);

	string feaMB = upperDirectory(imgPathB) + "/" + "feaMB";
	vector<string> recFeaMB;
	listOutDirectoryFiles(feaMB, recFeaMB);

	string pcaSB = upperDirectory(imgPathB) + "/" + "pcaSB";
	vector<string> recPcaSB;
	listOutDirectoryFiles(pcaSB, recPcaSB);

	string pcaMB = upperDirectory(imgPathB) + "/" + "pcaMB";
	vector<string> recPcaMB;
	listOutDirectoryFiles(pcaMB, recPcaMB);

	cout << ">>Inputs <<" << endl;
	cout << "single thread feature path A: " << feaSA << endl;
	cout << "single thread pca path A: " << pcaSA << endl;
	cout << "multi thread feature path A: " << feaMA << endl;
	cout << "multi thread pca path A: " << pcaMA << endl;
	cout << "single thread feature path B: " << feaSB << endl;
	cout << "single thread pca path B: " << pcaSB << endl;
	cout << "multi thread feature path B: " << feaMB << endl;
	cout << "multi thread pca path B: " << pcaMB << endl;
	cout << ">>Outputs<<" << endl;

	EXPECT_TRUE(recFeaSA.size()==recFeaMA.size());
	EXPECT_TRUE(recFeaSA.size()==recPcaSA.size());
	EXPECT_TRUE(recFeaMA.size()==recPcaMA.size());
	EXPECT_TRUE(recFeaSB.size()==recFeaMB.size());
	EXPECT_TRUE(recFeaSB.size()==recPcaSB.size());
	EXPECT_TRUE(recFeaMB.size()==recPcaMB.size());

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
	char pcaS[8192];
	char featureM[8192];
	char pcaM[8192];

	for(unsigned int i=0; i<recFeaSA.size(); i++){
#ifdef WIN32
		fFeaS.open(recFeaSA[i], ios::in | ios::binary);
		fFeaS.read(featureS, 8192);
		fFeaS.clear();
		fFeaS.close();

		fFeaM.open(recFeaMA[i], ios::in | ios::binary);
		fFeaM.read(featureM, 8192);
		fFeaM.clear();
		fFeaM.close();
#endif
#ifdef LINUX
		fFeaS = fopen(recFeaSA[i].data(), "rb");
		fread(featureS, 8192, 1, fFeaS);
		fclose(fFeaS);

		fFeaM = fopen(recFeaMA[i].data(), "rb");
		fread(featureM, 8192, 1, fFeaM);
		fclose(fFeaM);
#endif

		for(int j=0; j<8192; j++){
			EXPECT_TRUE(featureS[j]==featureM[j]);
		}

#ifdef WIN32
		fPcaS.open(recPcaSA[i], ios::in | ios::binary);
		fPcaS.read(pcaS, 2048);
		fPcaS.clear();
		fPcaS.close();

		fPcaM.open(recPcaMA[i], ios::in | ios::binary);
		fPcaM.read(pcaM, 2048);
		fPcaM.clear();
		fPcaM.close();
#endif
#ifdef LINUX
		fPcaS = fopen(recPcaSA[i].data(), "rb");
		fread(pcaS, 2048, 1, fPcaS);
		fclose(fPcaS);

		fPcaM = fopen(recPcaMA[i].data(), "rb");
		fread(pcaM, 2048, 1, fPcaM);
		fclose(fPcaM);
#endif

		for(int j=0; j<2048; j++){
			EXPECT_TRUE(pcaS[j]==pcaM[j]);
		}
	}

	cout << "imgPathA: " << "whether single thread or multi thread, the got result(pca/feature) by ISGetFeaturePath are the same" << endl;

	for(unsigned int i=0; i<recFeaSB.size(); i++){
#ifdef WIN32
		fFeaS.open(recFeaSB[i], ios::in | ios::binary);
		fFeaS.read(featureS, 8192);
		fFeaS.clear();
		fFeaS.close();

		fFeaM.open(recFeaMB[i], ios::in | ios::binary);
		fFeaM.read(featureM, 8192);
		fFeaM.clear();
		fFeaM.close();
#endif
#ifdef LINUX
		fFeaS = fopen(recFeaSB[i].data(), "rb");
		fread(featureS, 8192, 1, fFeaS);
		fclose(fFeaS);

		fFeaM = fopen(recFeaMB[i].data(), "rb");
		fread(featureM, 8192, 1, fFeaM);
		fclose(fFeaM);
#endif

		for(int j=0; j<8192; j++){
			EXPECT_TRUE(featureS[j]==featureM[j]);
		}

#ifdef WIN32
		fPcaS.open(recPcaSB[i], ios::in | ios::binary);
		fPcaS.read(pcaS, 2048);
		fPcaS.clear();
		fPcaS.close();

		fPcaM.open(recPcaMB[i], ios::in | ios::binary);
		fPcaM.read(pcaM, 2048);
		fPcaM.clear();
		fPcaM.close();
#endif
#ifdef LINUX
		fPcaS = fopen(recPcaSB[i].data(), "rb");
		fread(pcaS, 2048, 1, fPcaS);
		fclose(fPcaS);

		fPcaM = fopen(recPcaMB[i].data(), "rb");
		fread(pcaM, 2048, 1, fPcaM);
		fclose(fPcaM);
#endif

		for(int j=0; j<2048; j++){
			EXPECT_TRUE(pcaS[j]==pcaM[j]);
		}
	}

	cout << "imgPathB: " << "whether single thread or multi thread, the got result(pca/feature) by ISGetFeaturePath are the same" << endl;
	denominator = recFeaSA.size() + recPcaSA.size() + recFeaSB.size() + recPcaSB.size();
}

TEST_F(ftISFeature, ISGetFeatureWithFacePosPath_SingleThread){
	string imgPathA, imgPathB;
	if(isFlow){
		imgPathA = GConfig::getInstance().getAppliancePathA();
		imgPathB = GConfig::getInstance().getAppliancePathB();
	}else{
		imgPathA = GConfig::getInstance().getDetectImgPathA();
		imgPathB = GConfig::getInstance().getDetectImgPathB();
	}

	string facePosPathA = upperDirectory(imgPathA) + "/" + "recDetectSA";
	string facePosPathB = upperDirectory(imgPathB) + "/" + "recDetectSB";
	string saveFeaPathA = upperDirectory(imgPathA) + "/" + "feaSA";
	string saveFeaPathB = upperDirectory(imgPathB) + "/" + "feaSB";
	string savePcaPathA = upperDirectory(imgPathA) + "/" + "pcaSA";
	string savePcaPathB = upperDirectory(imgPathB) + "/" + "pcaSB";
	vector<string> facePosAs;
	listOutDirectoryFiles(facePosPathA, facePosAs);
	vector<string> facePosBs;
	listOutDirectoryFiles(facePosPathB, facePosBs);

	cout << ">>Inputs <<" << endl;
	cout << "facePos directory A: " << facePosPathA << endl;
	cout << "facePos directory B: " << facePosPathB << endl;
	cout << "threads num: " << "1" << endl;
	cout << ">>Outputs<<" << endl;

	char feature[5][8192];
	char pca[2048];
	int len = 0;
	int outRst[50][4];
#ifdef WIN32
	fstream f;
	string command;
	saveFeaPathA = slashConvert(saveFeaPathA, '/', '\\');
	saveFeaPathB = slashConvert(saveFeaPathB, '/', '\\');
	savePcaPathA = slashConvert(savePcaPathA, '/', '\\');
	savePcaPathB = slashConvert(savePcaPathB, '/', '\\');
	command = "rd /s /q " + saveFeaPathA;
	system(command.c_str());
	command = "rd /s /q " + saveFeaPathB;
	system(command.c_str());
	command = "rd /s /q " + savePcaPathA;
	system(command.c_str());
	command = "rd /s /q " + savePcaPathB;
	system(command.c_str());
	command = "mkdir " + saveFeaPathA;
	system(command.c_str());
	command = "mkdir " + saveFeaPathB;
	system(command.c_str());
	command = "mkdir " + savePcaPathA;
	system(command.c_str());
	command = "mkdir " + savePcaPathB;
	system(command.c_str());
#endif
#ifdef LINUX
	FILE *f;
	rmDir(saveFeaPathA);
	rmDir(saveFeaPathB);
	rmDir(savePcaPathA);
	rmDir(savePcaPathB);
	mkdir(saveFeaPathA.data(), 0775);
	mkdir(saveFeaPathB.data(), 0775);
	mkdir(savePcaPathA.data(), 0775);
	mkdir(savePcaPathB.data(), 0775);
#endif

	int defaultFeatureChannel = DEFAULT_FEATURE_CHANNEL();
	for(unsigned int i=0; i<facePosAs.size(); i++){
#ifdef WIN32
		f.open(facePosAs[i], ios::in | ios::binary);
		f.read((char *)&len, sizeof(len));
		f.read((char *)outRst[0], sizeof(outRst[0])*len);
		f.clear();
		f.close();
#endif
#ifdef LINUX
		f = fopen(facePosAs[i].data(), "rb");
		fseek(f, 0, SEEK_SET);
		fread(&len, sizeof(int), 1, f);
		fread(outRst, 4*sizeof(int)*len, 1, f);
		fclose(f);
#endif
		string imgPath = imgPathA + "/" + getFileHeader(facePosAs[i].data()) + ".jpg";
		if(SUCC == ISGetFeatureWithFacePosPath(defaultFeatureChannel, const_cast<char *>(imgPath.data()), outRst, len, feature[0])){
			ISGetPcaFea(defaultFeatureChannel, feature[0], pca);
			featureNumA++;
#ifdef WIN32
			string thisFeaPath = saveFeaPathA + "\\" + getFileHeader(facePosAs[i].data()) + ".fea";
			f.open(thisFeaPath, ios::out | ios::binary);
			f.write(feature[0], sizeof(feature[0]));
			f.close();
			f.clear();

			string thisPcaPath = savePcaPathA + "\\" + getFileHeader(facePosAs[i].data()) + ".pca";
			f.open(thisPcaPath, ios::out | ios::binary);
			f.write(pca, sizeof(pca));
			f.close();
			f.clear();
#endif
#ifdef LINUX
			string thisFeaPath = saveFeaPathA + "/" + getFileHeader(facePosAs[i].data()) + ".fea";
			f = fopen(thisFeaPath.data(), "wb");
			fwrite(feature, 8192, 1, f);
			fclose(f);

			string thisPcaPath = savePcaPathA + "/" + getFileHeader(facePosAs[i].data()) + ".pca";
			f = fopen(thisPcaPath.data(), "wb");
			fwrite(pca, 2048, 1, f);
			fclose(f);
#endif
		}
	}
	for(unsigned int i=0; i<facePosBs.size(); i++){
#ifdef WIN32
		f.open(facePosBs[i], ios::in | ios::binary);
		f.read((char *)&len, sizeof(len));
		f.read((char *)outRst[0], sizeof(outRst[0])*len);
		f.clear();
		f.close();
#endif
#ifdef LINUX
		f = fopen(facePosBs[i].data(), "rb");
		fseek(f, 0, SEEK_SET);
		fread(&len, sizeof(int), 1, f);
		fread(outRst, 4*sizeof(int)*len, 1, f);
		fclose(f);
#endif
		string imgPath = imgPathB + "/" + getFileHeader(facePosBs[i].data()) + ".jpg";
		if(SUCC == ISGetFeatureWithFacePosPath(defaultFeatureChannel, const_cast<char *>(imgPath.data()), outRst, len, feature[0])){
			ISGetPcaFea(defaultFeatureChannel, feature[0], pca);
			featureNumB++;
#ifdef WIN32
			string thisFeaPath = saveFeaPathB + "\\" + getFileHeader(facePosBs[i].data()) + ".fea";
			f.open(thisFeaPath, ios::out | ios::binary);
			f.write(feature[0], sizeof(feature[0]));
			f.close();
			f.clear();

			string thisPcaPath = savePcaPathB + "\\" + getFileHeader(facePosBs[i].data()) + ".pca";
			f.open(thisPcaPath, ios::out | ios::binary);
			f.write(pca, sizeof(pca));
			f.close();
			f.clear();
#endif
#ifdef LINUX
			string thisFeaPath = saveFeaPathB + "/" + getFileHeader(facePosBs[i].data()) + ".fea";
			f = fopen(thisFeaPath.data(), "wb");
			fwrite(feature, 8192, 1, f);
			fclose(f);

			string thisPcaPath = savePcaPathB + "/" + getFileHeader(facePosBs[i].data()) + ".pca";
			f = fopen(thisPcaPath.data(), "wb");
			fwrite(pca, 2048, 1, f);
			fclose(f);
#endif
		}
	}
	DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);

	cout << "picture num got feature succ of image directory A: " << featureNumA << endl;
	cout << "picture num got feature succ of image directory B: " << featureNumB << endl;
	double percentA = double(featureNumA)/(facePosAs.size() + 0.01)*100;
	cout << "success rate A: " << setiosflags(ios::fixed) << setprecision(2) << percentA << "%" << endl;
	double percentB = double(featureNumB)/(facePosBs.size() + 0.01)*100;
	cout << "success rate B: " << setiosflags(ios::fixed) << setprecision(2) << percentB << "%" << endl;
	cout << "output feature of image directory to A: " << saveFeaPathA << endl;
	cout << "output feature of image directory to B: " << saveFeaPathB << endl;
	cout << "output pca of image directory to A: " << savePcaPathA << endl;
	cout << "output pca of image directory to B: " << savePcaPathB << endl;
	denominator = facePosAs.size() + facePosBs.size();
}

TEST_F(ftISFeature, ISGetFeatureWithFacePosPath_MultiThread){
	string imgPathA, imgPathB;
	if(isFlow){
		imgPathA = GConfig::getInstance().getAppliancePathA();
		imgPathB = GConfig::getInstance().getAppliancePathB();
	}else{
		imgPathA = GConfig::getInstance().getDetectImgPathA();
		imgPathB = GConfig::getInstance().getDetectImgPathB();
	}

	string facePosPathA = upperDirectory(imgPathA) + "/" + "recDetectMA";
	string facePosPathB = upperDirectory(imgPathB) + "/" + "recDetectMB";
	vector<string> facePosAs;
	listOutDirectoryFiles(facePosPathA, facePosAs);
	vector<string> facePosBs;
	listOutDirectoryFiles(facePosPathB, facePosBs);

	featureNumA = 0;
	featureNumB = 0;

	unsigned int detectThreadNum = GConfig::getInstance().getGetFeaThreadNum();
	int facePosNumPerThreadA = int(facePosAs.size()/detectThreadNum);
	int facePosNumPerThreadB = int(facePosBs.size()/detectThreadNum);

	cout << ">>Inputs <<" << endl;
	cout << "facePos directory A: " << facePosPathA << endl;
	cout << "facePos directory B: " << facePosPathB << endl;
	cout << "threads num: " << detectThreadNum << endl;
	cout << ">>Outputs<<" << endl;

	string saveFeaPathA = upperDirectory(imgPathA) + "/" + "feaMA";
	string saveFeaPathB = upperDirectory(imgPathB) + "/" + "feaMB";
	string savePcaPathA = upperDirectory(imgPathA) + "/" + "pcaMA";
	string savePcaPathB = upperDirectory(imgPathB) + "/" + "pcaMB";

#ifdef WIN32
	saveFeaPathA = slashConvert(saveFeaPathA, '/', '\\');
	saveFeaPathB = slashConvert(saveFeaPathB, '/', '\\');
	savePcaPathA = slashConvert(savePcaPathA, '/', '\\');
	savePcaPathB = slashConvert(savePcaPathB, '/', '\\');
	string command = "rd /s /q " + saveFeaPathA;
	system(command.c_str());
	command = "mkdir " + saveFeaPathA;
	system(command.c_str());
	command = "rd /s /q " + saveFeaPathB;
	system(command.c_str());
	command = "mkdir " + saveFeaPathB;
	system(command.c_str());
	command = "rd /s /q " + savePcaPathA;
	system(command.c_str());
	command = "mkdir " + savePcaPathA;
	system(command.c_str());
	command = "rd /s /q " + savePcaPathB;
	system(command.c_str());
	command = "mkdir " + savePcaPathB;
	system(command.c_str());
#endif
#ifdef LINUX
	rmDir(saveFeaPathA);
	mkdir(saveFeaPathA.data(), 0775);
	rmDir(saveFeaPathB);
	mkdir(saveFeaPathB.data(), 0775);
	rmDir(savePcaPathA);
	mkdir(savePcaPathA.data(), 0775);
	rmDir(savePcaPathB);
	mkdir(savePcaPathB.data(), 0775);
#endif

	vector<vector<string> > facePosA;
	for(unsigned int i=0; i<detectThreadNum; i++){
		facePosA.push_back(vector<string>());
		if(i == detectThreadNum-1){
			facePosA[i].assign(facePosAs.begin()+i*facePosNumPerThreadA, facePosAs.end());
		}
		else{
			facePosA[i].assign(facePosAs.begin()+i*facePosNumPerThreadA, facePosAs.begin()+(i+1)*facePosNumPerThreadA);
		}
	}

	vector<vector<string> > facePosB;
	for(unsigned int i=0; i<detectThreadNum; i++){
		facePosB.push_back(vector<string>());
		if(i == detectThreadNum-1){
			facePosB[i].assign(facePosBs.begin()+i*facePosNumPerThreadB, facePosBs.end());
		}
		else{
			facePosB[i].assign(facePosBs.begin()+i*facePosNumPerThreadB, facePosBs.begin()+(i+1)*facePosNumPerThreadB);
		}
	}

	vector<pthread_t> pThread(detectThreadNum);
	serial = facePosPathA;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceFeatureWithPos, (void *)&facePosA[i]));
	}

	void *retVal;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

	serial = facePosPathB;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceFeatureWithPos, (void *)&facePosB[i]));
	}

	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

	cout << "picture num got feature succ of image directory A: " << featureNumA << endl;
	cout << "picture num got feature succ of image directory B: " << featureNumB << endl;
	double percentA = double(featureNumA)/(facePosAs.size() + 0.01)*100;
	cout << "success rate A: " << setiosflags(ios::fixed) << setprecision(2) << percentA << "%" << endl;
	double percentB = double(featureNumB)/(facePosBs.size() + 0.01)*100;
	cout << "success rate B: " << setiosflags(ios::fixed) << setprecision(2) << percentB << "%" << endl;
	cout << "output feature of image directory to A: " << saveFeaPathA << endl;
	cout << "output feature of image directory to B: " << saveFeaPathB << endl;
	cout << "output pca of image directory to A: " << savePcaPathA << endl;
	cout << "output pca of image directory to B: " << savePcaPathB << endl;
	denominator = facePosAs.size() + facePosBs.size();
}

TEST_F(ftISFeature, ISGetFeatureWithFacePosPath_OutResultCheck){
	string imgPathA, imgPathB;
	if(isFlow){
		imgPathA = GConfig::getInstance().getAppliancePathA();
		imgPathB = GConfig::getInstance().getAppliancePathB();
	}else{
		imgPathA = GConfig::getInstance().getDetectImgPathA();
		imgPathB = GConfig::getInstance().getDetectImgPathB();
	}

	string feaSA = upperDirectory(imgPathA) + "/" + "feaSA";
	vector<string> recFeaSA;
	listOutDirectoryFiles(feaSA, recFeaSA);

	string feaMA = upperDirectory(imgPathA) + "/" + "feaMA";
	vector<string> recFeaMA;
	listOutDirectoryFiles(feaMA, recFeaMA);

	string pcaSA = upperDirectory(imgPathA) + "/" + "pcaSA";
	vector<string> recPcaSA;
	listOutDirectoryFiles(pcaSA, recPcaSA);

	string pcaMA = upperDirectory(imgPathA) + "/" + "pcaMA";
	vector<string> recPcaMA;
	listOutDirectoryFiles(pcaMA, recPcaMA);

	string feaSB = upperDirectory(imgPathB) + "/" + "feaSB";
	vector<string> recFeaSB;
	listOutDirectoryFiles(feaSB, recFeaSB);

	string feaMB = upperDirectory(imgPathB) + "/" + "feaMB";
	vector<string> recFeaMB;
	listOutDirectoryFiles(feaMB, recFeaMB);

	string pcaSB = upperDirectory(imgPathB) + "/" + "pcaSB";
	vector<string> recPcaSB;
	listOutDirectoryFiles(pcaSB, recPcaSB);

	string pcaMB = upperDirectory(imgPathB) + "/" + "pcaMB";
	vector<string> recPcaMB;
	listOutDirectoryFiles(pcaMB, recPcaMB);

	cout << ">>Inputs <<" << endl;
	cout << "single thread feature path A: " << feaSA << endl;
	cout << "single thread pca path A: " << pcaSA << endl;
	cout << "multi thread feature path A: " << feaMA << endl;
	cout << "multi thread pca path A: " << pcaMA << endl;
	cout << "single thread feature path B: " << feaSB << endl;
	cout << "single thread pca path B: " << pcaSB << endl;
	cout << "multi thread feature path B: " << feaMB << endl;
	cout << "multi thread pca path B: " << pcaMB << endl;
	cout << ">>Outputs<<" << endl;

	EXPECT_TRUE(recFeaSA.size()==recFeaMA.size());
	EXPECT_TRUE(recFeaSA.size()==recPcaSA.size());
	EXPECT_TRUE(recFeaMA.size()==recPcaMA.size());
	EXPECT_TRUE(recFeaSB.size()==recFeaMB.size());
	EXPECT_TRUE(recFeaSB.size()==recPcaSB.size());
	EXPECT_TRUE(recFeaMB.size()==recPcaMB.size());

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
	char pcaS[2048];
	char featureM[8192];
	char pcaM[2048];

	for(unsigned int i=0; i<recFeaSA.size(); i++){
#ifdef WIN32
		fFeaS.open(recFeaSA[i], ios::in | ios::binary);
		fFeaS.read(featureS, 8192);
		fFeaS.clear();
		fFeaS.close();

		fFeaM.open(recFeaMA[i], ios::in | ios::binary);
		fFeaM.read(featureM, 8192);
		fFeaM.clear();
		fFeaM.close();
#endif
#ifdef LINUX
		fFeaS = fopen(recFeaSA[i].data(), "rb");
		fread(featureS, 8192, 1, fFeaS);
		fclose(fFeaS);

		fFeaM = fopen(recFeaMA[i].data(), "rb");
		fread(featureM, 8192, 1, fFeaM);
		fclose(fFeaM);
#endif

		for(int j=0; j<8192; j++){
			EXPECT_TRUE(featureS[j]==featureM[j]);
		}

#ifdef WIN32
		fPcaS.open(recPcaSA[i], ios::in | ios::binary);
		fPcaS.read(pcaS, 2048);
		fPcaS.clear();
		fPcaS.close();

		fPcaM.open(recPcaMA[i], ios::in | ios::binary);
		fPcaM.read(pcaM, 2048);
		fPcaM.clear();
		fPcaM.close();
#endif
#ifdef LINUX
		fPcaS = fopen(recPcaSA[i].data(), "rb");
		fread(pcaS, 2048, 1, fPcaS);
		fclose(fPcaS);

		fPcaM = fopen(recPcaMA[i].data(), "rb");
		fread(pcaM, 2048, 1, fPcaM);
		fclose(fPcaM);
#endif

		for(int j=0; j<2048; j++){
			EXPECT_TRUE(pcaS[j]==pcaM[j]);
		}
	}

	cout << "imgPathA: " << "whether single thread or multi thread, the got result(pca/feature) by ISGetFeatureWithFacePosPath are the same" << endl;

	for(unsigned int i=0; i<recFeaSB.size(); i++){
#ifdef WIN32
		fFeaS.open(recFeaSB[i], ios::in | ios::binary);
		fFeaS.read(featureS, 8192);
		fFeaS.clear();
		fFeaS.close();

		fFeaM.open(recFeaMB[i], ios::in | ios::binary);
		fFeaM.read(featureM, 8192);
		fFeaM.clear();
		fFeaM.close();
#endif
#ifdef LINUX
		fFeaS = fopen(recFeaSB[i].data(), "rb");
		fread(featureS, 8192, 1, fFeaS);
		fclose(fFeaS);

		fFeaM = fopen(recFeaMB[i].data(), "rb");
		fread(featureM, 8192, 1, fFeaM);
		fclose(fFeaM);
#endif

		for(int j=0; j<8192; j++){
			EXPECT_TRUE(featureS[j]==featureM[j]);
		}

#ifdef WIN32
		fPcaS.open(recPcaSB[i], ios::in | ios::binary);
		fPcaS.read(pcaS, 2048);
		fPcaS.clear();
		fPcaS.close();

		fPcaM.open(recPcaMB[i], ios::in | ios::binary);
		fPcaM.read(pcaM, 2048);
		fPcaM.clear();
		fPcaM.close();
#endif
#ifdef LINUX
		fPcaS = fopen(recPcaSB[i].data(), "rb");
		fread(pcaS, 2048, 1, fPcaS);
		fclose(fPcaS);

		fPcaM = fopen(recPcaMB[i].data(), "rb");
		fread(pcaM, 2048, 1, fPcaM);
		fclose(fPcaM);
#endif

		for(int j=0; j<2048; j++){
			EXPECT_TRUE(pcaS[j]==pcaM[j]);
		}
	}

	cout << "imgPathB: " << "whether single thread or multi thread, the got result(pca/feature) by ISGetFeatureWithFacePosPath are the same" << endl;
	denominator = recFeaSA.size() + recPcaSA.size() + recFeaSB.size() + recPcaSB.size();
}
