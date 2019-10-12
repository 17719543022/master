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
#include "timer.h"

using namespace std;
using namespace cv;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
extern string serial;
extern bool isFlow;
extern double cost;
int detectedNumA = 0;
int detectedNumB = 0;

namespace{
	void *faceDetect(void *ptr){
		string recDetectM = serial;
		vector<string> images = *(vector<string> *)ptr;
		int len = 0;
		int outRst[50][4];
		Timer timer;
#ifdef WIN32
		fstream f;
#endif
#ifdef LINUX
		FILE *f;
#endif

		int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
		for(unsigned int i=0; i<images.size(); i++){
			timer.start();
			EXPECT_TRUE_EX(ISFaceDetectPath(defaultDetTrackChannel, const_cast<char*>(images[i].data()), outRst, &len));
			pthread_mutex_lock(&mutex);
			cost += timer.stop();
			pthread_mutex_unlock(&mutex);
			if(len >= 1){
				pthread_mutex_lock(&mutex);
				if(recDetectM[recDetectM.size() - 1] == 'A')
				{
					detectedNumA += 1;
				}
				if(recDetectM[recDetectM.size() - 1] == 'B')
				{
					detectedNumB += 1;
				}
				pthread_mutex_unlock(&mutex);
#ifdef WIN32
				string saveRecPath = recDetectM + "\\" + getFileHeader(images[i].data()) + ".rec";
				f.open(saveRecPath, ios::out | ios::binary);
				f.write((char *)&len, sizeof(len));
				f.write((char *)outRst[0], sizeof(outRst[0])*len);
				f.close();
				f.clear();
#endif
#ifdef LINUX
				string saveRecPath = recDetectM + "/" + getFileHeader(images[i].data()) + ".rec";
				f = fopen(saveRecPath.data(), "wb");
				fseek(f, 0, SEEK_SET);
				fwrite(&len, sizeof(int), 1, f);
				fwrite(outRst, 4*sizeof(int)*len, 1, f);
				fclose(f);
#endif
			}
		}
		DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);

		return NULL;
	}

	void *faceDetectRgb(void *ptr){
		string recDetectM = serial;
		vector<string> images = *(vector<string> *)ptr;
		int len = 0;
		int outRst[50][4];
		Timer timer;
#ifdef WIN32
		fstream f;
#endif
#ifdef LINUX
		FILE *f;
#endif

		int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
		for(unsigned int i=0; i<images.size(); i++){
			Mat image = imread(images[i]);
			timer.start();
			EXPECT_TRUE_EX(ISFaceDetectRgb(defaultDetTrackChannel, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &len));
			pthread_mutex_lock(&mutex);
			cost += timer.stop();
			pthread_mutex_unlock(&mutex);
			if(len >= 1){
				pthread_mutex_lock(&mutex);
				if(recDetectM[recDetectM.size() - 1] == 'A')
				{
					detectedNumA += 1;
				}
				if(recDetectM[recDetectM.size() - 1] == 'B')
				{
					detectedNumB += 1;
				}
				pthread_mutex_unlock(&mutex);
#ifdef WIN32
				string saveRecPath = recDetectM + "\\" + getFileHeader(images[i].data()) + ".rec";
				f.open(saveRecPath, ios::out | ios::binary);
				f.write((char *)&len, sizeof(len));
				f.write((char *)outRst[0], sizeof(outRst[0])*len);
				f.close();
				f.clear();
#endif
#ifdef LINUX
				string saveRecPath = recDetectM + "/" + getFileHeader(images[i].data()) + ".rec";
				f = fopen(saveRecPath.data(), "wb");
				fseek(f, 0, SEEK_SET);
				fwrite(&len, sizeof(int), 1, f);
				fwrite(outRst, 4*sizeof(int)*len, 1, f);
				fclose(f);
#endif
			}
		}
		DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);

		return NULL;
	}

#ifdef WIN32
	void *faceTrack(void *ptr){
		vector<string> images = *(vector<string> *)ptr;
		int len = 0;
		int outRst[50][5];
		fstream f;
		string recTrackM = serial;
		Timer timer;

		int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
		Mat cache = imread(images[0]);
		EXPECT_TRUE_EX(ISFaceDetTrackRgb(defaultDetTrackChannel, (char *)cache.data, cache.rows*cache.cols*3, cache.cols, cache.rows, outRst, &len));
		for(unsigned int i=0; i<images.size(); i++){
			Mat image = imread(images[i]);
			timer.start();
			EXPECT_TRUE_EX(ISFaceDetTrackRgb(defaultDetTrackChannel, (char *)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &len));
			pthread_mutex_lock(&mutex);
			cost += timer.stop();
			pthread_mutex_unlock(&mutex);
			if(len >= 1){
				pthread_mutex_lock(&mutex);
				if(recTrackM[recTrackM.size() - 1] == 'A')
				{
					detectedNumA += 1;
				}
				if(recTrackM[recTrackM.size() - 1] == 'B')
				{
					detectedNumB += 1;
				}
				pthread_mutex_unlock(&mutex);
				string saveRecPath = recTrackM + "\\" + getFileHeader(images[i].data()) + ".rec";
				f.open(saveRecPath, ios::out | ios::binary);
				f.write((char *)&len, sizeof(len));
				f.write((char *)outRst[0], sizeof(outRst[0])*len);
				f.close();
				f.clear();
			}
		}
		DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);

		return NULL;
	}
#endif

	void *faceInfo(void *ptr){
		vector<string> images = *(vector<string> *)ptr;
		int len = 0;
		int outRst[50][4];
		int keyPoint[50][6];
		float angle[50][3];
		float kScore[50];
		Timer timer;
#ifdef WIN32
		fstream f;
#endif
#ifdef LINUX
		FILE *f;
#endif
		string faceInfoM = serial;

		int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
		for(unsigned int i=0; i<images.size(); i++){
			EXPECT_TRUE_EX(ISFaceDetectPath(defaultDetTrackChannel, const_cast<char *>(images[i].data()), outRst, &len));
			timer.start();
			EXPECT_TRUE_EX(ISCalFaceInfoPath2(defaultDetTrackChannel, const_cast<char *>(images[i].data()), outRst, len, keyPoint, angle, kScore));
			pthread_mutex_lock(&mutex);
			cost += timer.stop();
			pthread_mutex_unlock(&mutex);
			if(len >= 1){
				pthread_mutex_lock(&mutex);
				if(faceInfoM[faceInfoM.size() - 1] == 'A')
				{
					detectedNumA += 1;
				}
				if(faceInfoM[faceInfoM.size() - 1] == 'B')
				{
					detectedNumB += 1;
				}
#ifdef WIN32
				string saveRecPath = faceInfoM + "\\" + getFileHeader(images[i].data()) + ".rec";
				f.open(saveRecPath, ios::out | ios::binary);
				f.write((char *)&len, sizeof(len));
				f.write((char *)outRst[0], sizeof(outRst[0])*len);
				f.write((char *)keyPoint[0], sizeof(keyPoint[0])*len);
				f.write((char *)angle[0], sizeof(angle[0])*len);
				f.write((char *)kScore, sizeof(float)*len);
				f.close();
				f.clear();
#endif
#ifdef LINUX
				string saveRecPath = faceInfoM + "/" + getFileHeader(images[i].data()) + ".rec";
				f = fopen(saveRecPath.data(), "wb");
				fseek(f, 0, SEEK_SET);
				fwrite(&len, sizeof(int), 1, f);
				fwrite(outRst, 4*sizeof(int)*len, 1, f);
				fwrite(keyPoint, 6*sizeof(int)*len, 1, f);
				fwrite(angle, 3*sizeof(float)*len, 1, f);
				fwrite(kScore, sizeof(float)*len, 1, f);
				fclose(f);
#endif
				pthread_mutex_unlock(&mutex);
			}
		}
		DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);

		return NULL;
	}
}

TEST_F(ftISDetTrack, ISFaceDetectPath_SingleThread){
	string imgPathA = GConfig::getInstance().getDetectImgPathA();
	string imgPathB = GConfig::getInstance().getDetectImgPathB();

	vector<string> imageAs;
	vector<string> imageBs;
	listOutDirectoryFiles(imgPathA, imageAs);
	listOutDirectoryFiles(imgPathB, imageBs);
	int lenA = 0;
	int lenB = 0;
	int outRstA[50][4];
	int outRstB[50][4];
	Timer timer;
	cost = 0;

	cout << ">>Inputs <<" << endl;
	cout << "image directory A: " << imgPathA << endl;
	cout << "image directory B: " << imgPathB << endl;
	cout << "Threads Num: " << "1" << endl;
	cout << ">>Outputs<<" << endl;

	string recDetectSA = upperDirectory(imgPathA) + "/" + "recDetectSA";
	string recDetectSB = upperDirectory(imgPathB) + "/" + "recDetectSB";
#ifdef WIN32
	string command;
	recDetectSA = slashConvert(recDetectSA, '/', '\\');
	recDetectSB = slashConvert(recDetectSB, '/', '\\');
	command = "rd /s /q " + recDetectSA;
	system(command.c_str());
	command = "rd /s /q " + recDetectSB;
	system(command.c_str());
	command = "mkdir " + recDetectSA;
	system(command.c_str());
	command = "mkdir " + recDetectSB;
	system(command.c_str());
#endif
#ifdef LINUX
	rmDir(recDetectSA);
	rmDir(recDetectSB);
	mkdir(recDetectSA.data(), 0775);
	mkdir(recDetectSB.data(), 0775);
#endif

	detectedNumA = 0;
	detectedNumB = 0;
#ifdef WIN32
	fstream fA;
	fstream fB;
#endif
#ifdef LINUX
	FILE *fA;
	FILE *fB;
#endif

	int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
	for(unsigned int i=0; i<imageAs.size(); i++){
		timer.start();
		EXPECT_TRUE_EX(ISFaceDetectPath(defaultDetTrackChannel, const_cast<char*>(imageAs[i].data()), outRstA, &lenA));
		cost += timer.stop();
		if(lenA >= 1){
			detectedNumA += 1;
#ifdef WIN32
			string saveRecPath = recDetectSA + "\\" + getFileHeader(imageAs[i].data()) + ".rec";
			fA.open(saveRecPath, ios::out | ios::binary);
			fA.write((char *)&lenA, sizeof(lenA));
			fA.write((char *)outRstA[0], sizeof(outRstA[0])*lenA);
			fA.close();
			fA.clear();
#endif
#ifdef LINUX
			string saveRecPath = recDetectSA + "/" + getFileHeader(imageAs[i].data()) + ".rec";
			fA = fopen(saveRecPath.data(), "wb");
			fseek(fA, 0, SEEK_SET);
			fwrite(&lenA, sizeof(int), 1, fA);
			fwrite(outRstA, 4*sizeof(int)*lenA, 1, fA);
			fclose(fA);
#endif
		}
	}
	for(unsigned int i=0; i<imageBs.size(); i++){
		timer.start();
		EXPECT_TRUE_EX(ISFaceDetectPath(defaultDetTrackChannel, const_cast<char*>(imageBs[i].data()), outRstB, &lenB));
		cost += timer.stop();
		if(lenB >= 1){
			detectedNumB += 1;
#ifdef WIN32
			string saveRecPath = recDetectSB + "\\" + getFileHeader(imageBs[i].data()) + ".rec";
			fB.open(saveRecPath, ios::out | ios::binary);
			fB.write((char *)&lenB, sizeof(lenB));
			fB.write((char *)outRstB[0], sizeof(outRstB[0])*lenB);
			fB.close();
			fB.clear();
#endif
#ifdef LINUX
			string saveRecPath = recDetectSB + "/" + getFileHeader(imageBs[i].data()) + ".rec";
			fB = fopen(saveRecPath.data(), "wb");
			fseek(fB, 0, SEEK_SET);
			fwrite(&lenB, sizeof(int), 1, fB);
			fwrite(outRstB, 4*sizeof(int)*lenB, 1, fB);
			fclose(fB);
#endif
		}
	}
	DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);

	cout << "picture num of image directory A: " << imageAs.size() << endl;
	cout << "picture num of image directory B: " << imageBs.size() << endl;
	cout << "picture num detected face succ of image directory A: " << detectedNumA << endl;
	cout << "picture num detected face succ of image directory B: " << detectedNumB << endl;
	double percentA = double(detectedNumA)/imageAs.size()*100;
	double percentB = double(detectedNumB)/imageBs.size()*100;
	cout << "success rate A: " << setiosflags(ios::fixed) << setprecision(2) << percentA << "%" << endl;
	cout << "success rate B: " << setiosflags(ios::fixed) << setprecision(2) << percentB << "%" << endl;
	cout << "output detect result to A: " << recDetectSA << endl;
	cout << "output detect result to B: " << recDetectSB << endl;
	float timePerPic = float(cost)/(imageAs.size() + imageBs.size());
	cout << "whole cost: " << cost << "ms" << endl;
	cout << "average time cost: " << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "ms" << endl;
}

TEST_F(ftISDetTrack, ISFaceDetectPath_MultiThread){
	string imgPathA = GConfig::getInstance().getDetectImgPathA();
	string imgPathB = GConfig::getInstance().getDetectImgPathB();

	unsigned int detectThreadNum = GConfig::getInstance().getDetectThreadNum();
	vector<string> imageAs;
	vector<string> imageBs;
	listOutDirectoryFiles(imgPathA, imageAs);
	listOutDirectoryFiles(imgPathB, imageBs);
	int imgNumPerThreadA = int(imageAs.size()/detectThreadNum);
	int imgNumPerThreadB = int(imageBs.size()/detectThreadNum);
	cost = 0;

	cout << ">>Inputs <<" << endl;
	cout << "image directory A: " << imgPathA << endl;
	cout << "image directory B: " << imgPathB << endl;
	cout << "Threads Num: " << detectThreadNum << endl;
	cout << ">>Outputs<<" << endl;

	string recDetectMA = upperDirectory(imgPathA) + "/" + "recDetectMA";
	string recDetectMB = upperDirectory(imgPathB) + "/" + "recDetectMB";
#ifdef WIN32
	string command;
	recDetectMA = slashConvert(recDetectMA, '/', '\\');
	recDetectMB = slashConvert(recDetectMB, '/', '\\');
	command = "rd /s /q " + recDetectMA;
	system(command.c_str());
	command = "rd /s /q " + recDetectMB;
	system(command.c_str());
	command = "mkdir " + recDetectMA;
	system(command.c_str());
	command = "mkdir " + recDetectMB;
	system(command.c_str());
#endif
#ifdef LINUX
	rmDir(recDetectMA);
	mkdir(recDetectMA.data(), 0775);
	rmDir(recDetectMB);
	mkdir(recDetectMB.data(), 0775);
#endif

	vector<vector<string> > imageA;
	vector<vector<string> > imageB;
	for(unsigned int i=0; i<detectThreadNum; i++){
		imageA.push_back(vector<string>());
		if(i == detectThreadNum-1){
			imageA[i].assign(imageAs.begin()+i*imgNumPerThreadA, imageAs.end());
		}
		else{
			imageA[i].assign(imageAs.begin()+i*imgNumPerThreadA, imageAs.begin()+(i+1)*imgNumPerThreadA);
		}
	}
	for(unsigned int i=0; i<detectThreadNum; i++){
		imageB.push_back(vector<string>());
		if(i == detectThreadNum-1){
			imageB[i].assign(imageBs.begin()+i*imgNumPerThreadB, imageBs.end());
		}
		else{
			imageB[i].assign(imageBs.begin()+i*imgNumPerThreadB, imageBs.begin()+(i+1)*imgNumPerThreadB);
		}
	}

	detectedNumA = 0;
	detectedNumB = 0;

	serial = recDetectMA;
	vector<pthread_t> pThread(detectThreadNum);
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceDetect, (void *)&imageA[i]));
	}

	void *retVal;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

	serial = recDetectMB;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceDetect, (void *)&imageB[i]));
	}

	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

	cout << "picture num of image directory A: " << imageAs.size() << endl;
	cout << "picture num of image directory B: " << imageBs.size() << endl;
	cout << "picture num allocated to each thread A: " << imgNumPerThreadA << endl;
	cout << "picture num allocated to each thread B: " << imgNumPerThreadB << endl;
	cout << "picture num detected face succ of image directory A: " << detectedNumA << endl;
	cout << "picture num detected face succ of image directory B: " << detectedNumB << endl;
	double percentA = double(detectedNumA)/imageAs.size()*100;
	double percentB = double(detectedNumB)/imageBs.size()*100;
	cout << "success rate A: " << setiosflags(ios::fixed) << setprecision(2) << percentA << "%" << endl;
	cout << "success rate B: " << setiosflags(ios::fixed) << setprecision(2) << percentB << "%" << endl;
	cout << "output detect result to A: " << recDetectMA << endl;
	cout << "output detect result to B: " << recDetectMB << endl;
	cost = cost/detectThreadNum;
	float timePerPic = float(cost)/(imageAs.size() + imageBs.size());
	cout << "whole cost: " << cost << "ms" << endl;
	cout << "average time cost: " << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "ms" << endl;
}

TEST_F(ftISDetTrack, ISFaceDetectPath_OutResultCheck){
	string imgPathA = GConfig::getInstance().getDetectImgPathA();
	string imgPathB = GConfig::getInstance().getDetectImgPathB();

	string recDetectSA = upperDirectory(imgPathA) + "/" + "recDetectSA";
	vector<string> recSA;
	listOutDirectoryFiles(recDetectSA, recSA);

	string recDetectMA = upperDirectory(imgPathA) + "/" + "recDetectMA";
	vector<string> recMA;
	listOutDirectoryFiles(recDetectMA, recMA);

	string recDetectSB = upperDirectory(imgPathB) + "/" + "recDetectSB";
	vector<string> recSB;
	listOutDirectoryFiles(recDetectSB, recSB);

	string recDetectMB = upperDirectory(imgPathB) + "/" + "recDetectMB";
	vector<string> recMB;
	listOutDirectoryFiles(recDetectMB, recMB);

	cout << ">>Inputs <<" << endl;
	cout << "single thread detect result path A: " << recDetectSA << endl;
	cout << "multi thread detect result path A: " << recDetectMA << endl;
	cout << "single thread detect result path B: " << recDetectSB << endl;
	cout << "multi thread detect result path B: " << recDetectMB << endl;
	cout << ">>Outputs<<" << endl;

	EXPECT_TRUE(recSA.size()==recMA.size());
	EXPECT_TRUE(recSB.size()==recMB.size());

#ifdef WIN32
	fstream fS;
	fstream fM;
#endif
#ifdef LINUX
	FILE *fS;
	FILE *fM;
#endif
	int lenS = 0;
	int lenM = 0;
	int outRstS[50][4];
	int outRstM[50][4];
	for(unsigned int i=0; i<recSA.size(); i++){
#ifdef WIN32
		fS.open(recSA[i], ios::in | ios::binary);
		fS.read((char *)&lenS, sizeof(lenS));
		fS.read((char *)outRstS[0], sizeof(outRstS[0])*lenS);
		fS.clear();
		fS.close();

		fM.open(recMA[i], ios::in | ios::binary);
		fM.read((char *)&lenM, sizeof(lenM));
		fM.read((char *)outRstM[0], sizeof(outRstM[0])*lenM);
		fM.clear();
		fM.close();
#endif
#ifdef LINUX
		fS = fopen(recSA[i].data(), "rb");
		fseek(fS, 0, SEEK_SET);
		fread(&lenS, sizeof(int), 1, fS);
		fread(outRstS, 4*sizeof(int)*lenS, 1, fS);
		fclose(fS);

		fM = fopen(recMA[i].data(), "rb");
		fseek(fM, 0, SEEK_SET);
		fread(&lenM, sizeof(int), 1, fM);
		fread(outRstM, 4*sizeof(int)*lenM, 1, fM);
		fclose(fM);
#endif

		EXPECT_TRUE(lenS==lenM);
		for(int j=0; j<lenS; j++){
			for(int k=0; k<4; k++){
				EXPECT_TRUE(outRstS[j][k]==outRstM[j][k]);
			}
		}
	}

	cout << "imgPathA: " << "whether single thread or multi thread, the detect result(len/outResult) by ISFaceDetectPath are the same" << endl;

	for(unsigned int i=0; i<recSB.size(); i++){
#ifdef WIN32
		fS.open(recSB[i], ios::in | ios::binary);
		fS.read((char *)&lenS, sizeof(lenS));
		fS.read((char *)outRstS[0], sizeof(outRstS[0])*lenS);
		fS.clear();
		fS.close();

		fM.open(recMB[i], ios::in | ios::binary);
		fM.read((char *)&lenM, sizeof(lenM));
		fM.read((char *)outRstM[0], sizeof(outRstM[0])*lenM);
		fM.clear();
		fM.close();
#endif
#ifdef LINUX
		fS = fopen(recSB[i].data(), "rb");
		fseek(fS, 0, SEEK_SET);
		fread(&lenS, sizeof(int), 1, fS);
		fread(outRstS, 4*sizeof(int)*lenS, 1, fS);
		fclose(fS);

		fM = fopen(recMB[i].data(), "rb");
		fseek(fM, 0, SEEK_SET);
		fread(&lenM, sizeof(int), 1, fM);
		fread(outRstM, 4*sizeof(int)*lenM, 1, fM);
		fclose(fM);
#endif

		EXPECT_TRUE(lenS==lenM);
		for(int j=0; j<lenS; j++){
			for(int k=0; k<4; k++){
				EXPECT_TRUE(outRstS[j][k]==outRstM[j][k]);
			}
		}
	}

	cout << "imgPathB: " << "whether single thread or multi thread, the detect result(len/outResult) by ISFaceDetectPath are the same" << endl;
}

TEST_F(ftISDetTrack, ISFaceDetectRgb_SingleThread){
	string imgPathA, imgPathB;
	if(isFlow){
		imgPathA = GConfig::getInstance().getAppliancePathA();
		imgPathB = GConfig::getInstance().getAppliancePathB();
	}else{
		imgPathA = GConfig::getInstance().getDetectRgbImgPathA();
		imgPathB = GConfig::getInstance().getDetectRgbImgPathB();
	}

	vector<string> imageAs;
	vector<string> imageBs;
	listOutDirectoryFiles(imgPathA, imageAs);
	listOutDirectoryFiles(imgPathB, imageBs);
	int lenA = 0;
	int lenB = 0;
	int outRstA[50][4];
	int outRstB[50][4];
	Timer timer;
	cost = 0;

	cout << ">>Inputs <<" << endl;
	cout << "image directory A: " << imgPathA << endl;
	cout << "image directory B: " << imgPathB << endl;
	cout << "Threads Num: " << "1" << endl;
	cout << ">>Outputs<<" << endl;

	string recDetectSA = upperDirectory(imgPathA) + "/" + "recDetectSA";
	string recDetectSB = upperDirectory(imgPathB) + "/" + "recDetectSB";
#ifdef WIN32
	string command;
	recDetectSA = slashConvert(recDetectSA, '/', '\\');
	recDetectSB = slashConvert(recDetectSB, '/', '\\');
	command = "rd /s /q " + recDetectSA;
	system(command.c_str());
	command = "rd /s /q " + recDetectSB;
	system(command.c_str());
	command = "mkdir " + recDetectSA;
	system(command.c_str());
	command = "mkdir " + recDetectSB;
	system(command.c_str());
#endif
#ifdef LINUX
	rmDir(recDetectSA);
	rmDir(recDetectSB);
	mkdir(recDetectSA.data(), 0775);
	mkdir(recDetectSB.data(), 0775);
#endif

	detectedNumA = 0;
	detectedNumB = 0;
#ifdef WIN32
	fstream fA;
	fstream fB;
#endif
#ifdef LINUX
	FILE *fA;
	FILE *fB;
#endif

	int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
	for(unsigned int i=0; i<imageAs.size(); i++){
		Mat image = imread(imageAs[i]);
		timer.start();
		EXPECT_TRUE_EX(ISFaceDetectRgb(defaultDetTrackChannel, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRstA, &lenA));
		cost += timer.stop();
		if(lenA >= 1){
			detectedNumA += 1;
#ifdef WIN32
			string saveRecPath = recDetectSA + "\\" + getFileHeader(imageAs[i].data()) + ".rec";
			fA.open(saveRecPath, ios::out | ios::binary);
			fA.write((char *)&lenA, sizeof(lenA));
			fA.write((char *)outRstA[0], sizeof(outRstA[0])*lenA);
			fA.close();
			fA.clear();
#endif
#ifdef LINUX
			string saveRecPath = recDetectSA + "/" + getFileHeader(imageAs[i].data()) + ".rec";
			fA = fopen(saveRecPath.data(), "wb");
			fseek(fA, 0, SEEK_SET);
			fwrite(&lenA, sizeof(int), 1, fA);
			fwrite(outRstA, 4*sizeof(int)*lenA, 1, fA);
			fclose(fA);
#endif
		}
	}
	for(unsigned int i=0; i<imageBs.size(); i++){
		Mat image = imread(imageBs[i]);
		timer.start();
		EXPECT_TRUE_EX(ISFaceDetectRgb(defaultDetTrackChannel, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRstB, &lenB));
		cost += timer.stop();
		if(lenB >= 1){
			detectedNumB += 1;
#ifdef WIN32
			string saveRecPath = recDetectSB + "\\" + getFileHeader(imageBs[i].data()) + ".rec";
			fB.open(saveRecPath, ios::out | ios::binary);
			fB.write((char *)&lenB, sizeof(lenB));
			fB.write((char *)outRstB[0], sizeof(outRstB[0])*lenB);
			fB.close();
			fB.clear();
#endif
#ifdef LINUX
			string saveRecPath = recDetectSB + "/" + getFileHeader(imageBs[i].data()) + ".rec";
			fB = fopen(saveRecPath.data(), "wb");
			fseek(fB, 0, SEEK_SET);
			fwrite(&lenB, sizeof(int), 1, fB);
			fwrite(outRstB, 4*sizeof(int)*lenB, 1, fB);
			fclose(fB);
#endif
		}
	}
	DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);

	cout << "picture num of image directory A: " << imageAs.size() << endl;
	cout << "picture num of image directory B: " << imageBs.size() << endl;
	cout << "picture num detected face succ of image directory A: " << detectedNumA << endl;
	cout << "picture num detected face succ of image directory B: " << detectedNumB << endl;
	double percentA = double(detectedNumA)/imageAs.size()*100;
	double percentB = double(detectedNumB)/imageBs.size()*100;
	cout << "success rate A: " << setiosflags(ios::fixed) << setprecision(2) << percentA << "%" << endl;
	cout << "success rate B: " << setiosflags(ios::fixed) << setprecision(2) << percentB << "%" << endl;
	cout << "output detect result to A: " << recDetectSA << endl;
	cout << "output detect result to B: " << recDetectSB << endl;
	float timePerPic = float(cost)/(imageAs.size() + imageBs.size());
	cout << "whole cost: " << cost << "ms" << endl;
	cout << "average time cost: " << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "ms" << endl;
}

TEST_F(ftISDetTrack, ISFaceDetectRgb_MultiThread){
	string imgPathA, imgPathB;
	if(isFlow){
		imgPathA = GConfig::getInstance().getAppliancePathA();
		imgPathB = GConfig::getInstance().getAppliancePathB();
	}else{
		imgPathA = GConfig::getInstance().getDetectRgbImgPathA();
		imgPathB = GConfig::getInstance().getDetectRgbImgPathB();
	}

	unsigned int detectThreadNum = GConfig::getInstance().getDetectThreadNum();
	vector<string> imageAs;
	vector<string> imageBs;
	listOutDirectoryFiles(imgPathA, imageAs);
	listOutDirectoryFiles(imgPathB, imageBs);
	int imgNumPerThreadA = int(imageAs.size()/detectThreadNum);
	int imgNumPerThreadB = int(imageBs.size()/detectThreadNum);
	cost = 0;

	cout << ">>Inputs <<" << endl;
	cout << "image directory A: " << imgPathA << endl;
	cout << "image directory B: " << imgPathB << endl;
	cout << "Threads Num: " << detectThreadNum << endl;
	cout << ">>Outputs<<" << endl;

	string recDetectMA = upperDirectory(imgPathA) + "/" + "recDetectMA";
	string recDetectMB = upperDirectory(imgPathB) + "/" + "recDetectMB";
#ifdef WIN32
	string command;
	recDetectMA = slashConvert(recDetectMA, '/', '\\');
	recDetectMB = slashConvert(recDetectMB, '/', '\\');
	command = "rd /s /q " + recDetectMA;
	system(command.c_str());
	command = "rd /s /q " + recDetectMB;
	system(command.c_str());
	command = "mkdir " + recDetectMA;
	system(command.c_str());
	command = "mkdir " + recDetectMB;
	system(command.c_str());
#endif
#ifdef LINUX
	rmDir(recDetectMA);
	mkdir(recDetectMA.data(), 0775);
	rmDir(recDetectMB);
	mkdir(recDetectMB.data(), 0775);
#endif

	vector<vector<string> > imageA;
	vector<vector<string> > imageB;
	for(unsigned int i=0; i<detectThreadNum; i++){
		imageA.push_back(vector<string>());
		if(i == detectThreadNum-1){
			imageA[i].assign(imageAs.begin()+i*imgNumPerThreadA, imageAs.end());
		}
		else{
			imageA[i].assign(imageAs.begin()+i*imgNumPerThreadA, imageAs.begin()+(i+1)*imgNumPerThreadA);
		}
	}
	for(unsigned int i=0; i<detectThreadNum; i++){
		imageB.push_back(vector<string>());
		if(i == detectThreadNum-1){
			imageB[i].assign(imageBs.begin()+i*imgNumPerThreadB, imageBs.end());
		}
		else{
			imageB[i].assign(imageBs.begin()+i*imgNumPerThreadB, imageBs.begin()+(i+1)*imgNumPerThreadB);
		}
	}

	detectedNumA = 0;
	detectedNumB = 0;

	serial = recDetectMA;
	vector<pthread_t> pThread(detectThreadNum);
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceDetectRgb, (void *)&imageA[i]));
	}

	void *retVal;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

	serial = recDetectMB;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceDetectRgb, (void *)&imageB[i]));
	}

	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

	cout << "picture num of image directory A: " << imageAs.size() << endl;
	cout << "picture num of image directory B: " << imageBs.size() << endl;
	cout << "picture num allocated to each thread A: " << imgNumPerThreadA << endl;
	cout << "picture num allocated to each thread B: " << imgNumPerThreadB << endl;
	cout << "picture num detected face succ of image directory A: " << detectedNumA << endl;
	cout << "picture num detected face succ of image directory B: " << detectedNumB << endl;
	double percentA = double(detectedNumA)/imageAs.size()*100;
	double percentB = double(detectedNumB)/imageBs.size()*100;
	cout << "success rate A: " << setiosflags(ios::fixed) << setprecision(2) << percentA << "%" << endl;
	cout << "success rate B: " << setiosflags(ios::fixed) << setprecision(2) << percentB << "%" << endl;
	cout << "output detect result to A: " << recDetectMA << endl;
	cout << "output detect result to B: " << recDetectMB << endl;
	cost = cost/detectThreadNum;
	float timePerPic = float(cost)/(imageAs.size() + imageBs.size());
	cout << "whole cost: " << cost << "ms" << endl;
	cout << "average time cost: " << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "ms" << endl;
}

TEST_F(ftISDetTrack, ISFaceDetectRgb_OutResultCheck){
	string imgPathA, imgPathB;
	if(isFlow){
		imgPathA = GConfig::getInstance().getAppliancePathA();
		imgPathB = GConfig::getInstance().getAppliancePathB();
	}else{
		imgPathA = GConfig::getInstance().getDetectRgbImgPathA();
		imgPathB = GConfig::getInstance().getDetectRgbImgPathB();
	}

	string recDetectSA = upperDirectory(imgPathA) + "/" + "recDetectSA";
	vector<string> recSA;
	listOutDirectoryFiles(recDetectSA, recSA);

	string recDetectMA = upperDirectory(imgPathA) + "/" + "recDetectMA";
	vector<string> recMA;
	listOutDirectoryFiles(recDetectMA, recMA);

	string recDetectSB = upperDirectory(imgPathB) + "/" + "recDetectSB";
	vector<string> recSB;
	listOutDirectoryFiles(recDetectSB, recSB);

	string recDetectMB = upperDirectory(imgPathB) + "/" + "recDetectMB";
	vector<string> recMB;
	listOutDirectoryFiles(recDetectMB, recMB);

	cout << ">>Inputs <<" << endl;
	cout << "single thread detect result path A: " << recDetectSA << endl;
	cout << "multi thread detect result path A: " << recDetectMA << endl;
	cout << "single thread detect result path B: " << recDetectSB << endl;
	cout << "multi thread detect result path B: " << recDetectMB << endl;
	cout << ">>Outputs<<" << endl;

	EXPECT_TRUE(recSA.size()==recMA.size());
	EXPECT_TRUE(recSB.size()==recMB.size());

#ifdef WIN32
	fstream fS;
	fstream fM;
#endif
#ifdef LINUX
	FILE *fS;
	FILE *fM;
#endif
	int lenS = 0;
	int lenM = 0;
	int outRstS[50][4];
	int outRstM[50][4];
	for(unsigned int i=0; i<recSA.size(); i++){
#ifdef WIN32
		fS.open(recSA[i], ios::in | ios::binary);
		fS.read((char *)&lenS, sizeof(lenS));
		fS.read((char *)outRstS[0], sizeof(outRstS[0])*lenS);
		fS.clear();
		fS.close();

		fM.open(recMA[i], ios::in | ios::binary);
		fM.read((char *)&lenM, sizeof(lenM));
		fM.read((char *)outRstM[0], sizeof(outRstM[0])*lenM);
		fM.clear();
		fM.close();
#endif
#ifdef LINUX
		fS = fopen(recSA[i].data(), "rb");
		fseek(fS, 0, SEEK_SET);
		fread(&lenS, sizeof(int), 1, fS);
		fread(outRstS, 4*sizeof(int)*lenS, 1, fS);
		fclose(fS);

		fM = fopen(recMA[i].data(), "rb");
		fseek(fM, 0, SEEK_SET);
		fread(&lenM, sizeof(int), 1, fM);
		fread(outRstM, 4*sizeof(int)*lenM, 1, fM);
		fclose(fM);
#endif

		EXPECT_TRUE(lenS==lenM);
		for(int j=0; j<lenS; j++){
			for(int k=0; k<4; k++){
				EXPECT_TRUE(outRstS[j][k]==outRstM[j][k]);
			}
		}
	}

	cout << "imgPathA: " << "whether single thread or multi thread, the detect result(len/outResult) by ISFaceDetectRgb are the same" << endl;

	for(unsigned int i=0; i<recSB.size(); i++){
#ifdef WIN32
		fS.open(recSB[i], ios::in | ios::binary);
		fS.read((char *)&lenS, sizeof(lenS));
		fS.read((char *)outRstS[0], sizeof(outRstS[0])*lenS);
		fS.clear();
		fS.close();

		fM.open(recMB[i], ios::in | ios::binary);
		fM.read((char *)&lenM, sizeof(lenM));
		fM.read((char *)outRstM[0], sizeof(outRstM[0])*lenM);
		fM.clear();
		fM.close();
#endif
#ifdef LINUX
		fS = fopen(recSB[i].data(), "rb");
		fseek(fS, 0, SEEK_SET);
		fread(&lenS, sizeof(int), 1, fS);
		fread(outRstS, 4*sizeof(int)*lenS, 1, fS);
		fclose(fS);

		fM = fopen(recMB[i].data(), "rb");
		fseek(fM, 0, SEEK_SET);
		fread(&lenM, sizeof(int), 1, fM);
		fread(outRstM, 4*sizeof(int)*lenM, 1, fM);
		fclose(fM);
#endif

		EXPECT_TRUE(lenS==lenM);
		for(int j=0; j<lenS; j++){
			for(int k=0; k<4; k++){
				EXPECT_TRUE(outRstS[j][k]==outRstM[j][k]);
			}
		}
	}

	cout << "imgPathB: " << "whether single thread or multi thread, the detect result(len/outResult) by ISFaceDetectRgb are the same" << endl;
}

#ifdef WIN32
TEST_F(ftISDetTrack, ISFaceDetTrackRgb_SingleThread){
	string imgPathA = GConfig::getInstance().getTrackImgPathA();
	string imgPathB = GConfig::getInstance().getTrackImgPathB();
	vector<string> imageAs;
	vector<string> imageBs;
	listOutDirectoryFiles(imgPathA, imageAs);
	listOutDirectoryFiles(imgPathB, imageBs);
	int len = 0;
	int outRst[50][5];
	Timer timer;
	cost = 0;

	cout << ">>Inputs <<" << endl;
	cout << "image directory A: " << imgPathA << endl;
	cout << "image directory B: " << imgPathB << endl;
	cout << "threads num: " << "1" << endl;
	cout << ">>Outputs<<" << endl;

	string recTrackSA = upperDirectory(imgPathA) + "/" + "recTrackSA";
	recTrackSA = slashConvert(recTrackSA, '/', '\\');
	string command = "rd /s /q " + recTrackSA;
	system(command.c_str());
	command = "mkdir " + recTrackSA;
	system(command.c_str());
	string recTrackSB = upperDirectory(imgPathB) + "/" + "recTrackSB";
	recTrackSB = slashConvert(recTrackSB, '/', '\\');
	command = "rd /s /q " + recTrackSB;
	system(command.c_str());
	command = "mkdir " + recTrackSB;
	system(command.c_str());

	detectedNumA = 0;
	detectedNumB = 0;
	fstream f;

	int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
	Mat cache = imread(imageAs[0]);
	EXPECT_TRUE_EX(ISFaceDetTrackRgb(defaultDetTrackChannel, (char *)cache.data, cache.rows*cache.cols*3, cache.cols, cache.rows, outRst, &len));
	for(unsigned int i=0; i<imageAs.size(); i++){
		Mat image = imread(imageAs[i]);
		timer.start();
		EXPECT_TRUE_EX(ISFaceDetTrackRgb(defaultDetTrackChannel, (char *)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &len));
		cost += timer.stop();
		if(len >= 1){
			detectedNumA += 1;
			string saveRecPath = recTrackSA + "\\" + getFileHeader(imageAs[i].data()) + ".rec";
			f.open(saveRecPath, ios::out | ios::binary);
			f.write((char *)&len, sizeof(len));
			f.write((char *)outRst[0], sizeof(outRst[0])*len);
			f.close();
			f.clear();
		}
	}
	for(unsigned int i=0; i<imageBs.size(); i++){
		Mat image = imread(imageBs[i]);
		timer.start();
		EXPECT_TRUE_EX(ISFaceDetTrackRgb(defaultDetTrackChannel, (char *)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &len));
		cost += timer.stop();
		if(len >= 1){
			detectedNumB += 1;
			string saveRecPath = recTrackSB + "\\" + getFileHeader(imageBs[i].data()) + ".rec";
			f.open(saveRecPath, ios::out | ios::binary);
			f.write((char *)&len, sizeof(len));
			f.write((char *)outRst[0], sizeof(outRst[0])*len);
			f.close();
			f.clear();
		}
	}
	DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);

	cout << "picture num of image directory A: " << imageAs.size() << endl;
	cout << "picture num of image directory B: " << imageBs.size() << endl;
	cout << "picture num detected face succ of image directory A: " << detectedNumA << endl;
	cout << "picture num detected face succ of image directory B: " << detectedNumB << endl;
	double percentA = double(detectedNumA)/imageAs.size()*100;
	cout << "success rate A: " << setiosflags(ios::fixed) << setprecision(2) << percentA << "%" << endl;
	double percentB = double(detectedNumB)/imageBs.size()*100;
	cout << "success rate B: " << setiosflags(ios::fixed) << setprecision(2) << percentB << "%" << endl;
	cout << "output detect result to A: " << recTrackSA << endl;
	cout << "output detect result to B: " << recTrackSB << endl;
	float timePerPic = float(cost)/(imageAs.size() + imageBs.size());
	cout << "whole cost: " << cost << "ms" << endl;
	cout << "average time cost: " << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "ms" << endl;
}

TEST_F(ftISDetTrack, ISFaceDetTrackRgb_MultiThread){
	string imgPathA = GConfig::getInstance().getTrackImgPathA();
	string imgPathB = GConfig::getInstance().getTrackImgPathB();
	unsigned int detectThreadNum = GConfig::getInstance().getDetectThreadNum();
	vector<string> imageAs;
	vector<string> imageBs;
	listOutDirectoryFiles(imgPathA, imageAs);
	listOutDirectoryFiles(imgPathB, imageBs);
	int imgNumPerThreadA = int(imageAs.size()/detectThreadNum);
	int imgNumPerThreadB = int(imageBs.size()/detectThreadNum);
	cost = 0;

	cout << ">>Inputs <<" << endl;
	cout << "image directory A: " << imgPathA << endl;
	cout << "image directory B: " << imgPathB << endl;
	cout << "threads num: " << detectThreadNum << endl;
	cout << ">>Outputs<<" << endl;

	string recTrackMA = upperDirectory(imgPathA) + "/" + "recTrackMA";
	recTrackMA = slashConvert(recTrackMA, '/', '\\');
	string command = "rd /s /q " + recTrackMA;
	system(command.c_str());
	command = "mkdir " + recTrackMA;
	system(command.c_str());
	string recTrackMB = upperDirectory(imgPathB) + "/" + "recTrackMB";
	recTrackMB = slashConvert(recTrackMB, '/', '\\');
	command = "rd /s /q " + recTrackMB;
	system(command.c_str());
	command = "mkdir " + recTrackMB;
	system(command.c_str());

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

	detectedNumA = 0;
	detectedNumB = 0;

	serial = recTrackMA;
	vector<pthread_t> pThread(detectThreadNum);
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceTrack, (void *)&imageA[i]));
	}

	void *retVal;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

	serial = recTrackMB;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceTrack, (void *)&imageB[i]));
	}

	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

	cout << "picture num of image directory A: " << imageAs.size() << endl;
	cout << "picture num of image directory B: " << imageBs.size() << endl;
	cout << "picture num allocated to each thread A: " << imgNumPerThreadA << endl;
	cout << "picture num allocated to each thread B: " << imgNumPerThreadB << endl;
	cout << "picture num detected face succ of image directory A: " << detectedNumA << endl;
	cout << "picture num detected face succ of image directory B: " << detectedNumB << endl;
	double percentA = double(detectedNumA)/imageAs.size()*100;
	cout << "success rate A: " << setiosflags(ios::fixed) << setprecision(2) << percentA << "%" << endl;
	double percentB = double(detectedNumB)/imageBs.size()*100;
	cout << "success rate B: " << setiosflags(ios::fixed) << setprecision(2) << percentB << "%" << endl;
	cout << "output detect result to A: " << recTrackMA << endl;
	cout << "output detect result to B: " << recTrackMB << endl;
	cost = cost/detectThreadNum;
	float timePerPic = float(cost)/(imageAs.size() + imageBs.size());
	cout << "whole cost: " << cost << "ms" << endl;
	cout << "average time cost: " << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "ms" << endl;
}

TEST_F(ftISDetTrack, ISFaceDetTrackRgb_OutResultCheck){
	string imgPathA = GConfig::getInstance().getTrackImgPathA();
	string imgPathB = GConfig::getInstance().getTrackImgPathB();

	string recTrackSA = upperDirectory(imgPathA) + "/" + "recTrackSA";
	vector<string> recSA;
	listOutDirectoryFiles(recTrackSA, recSA);

	string recTrackMA = upperDirectory(imgPathA) + "/" + "recTrackMA";
	vector<string> recMA;
	listOutDirectoryFiles(recTrackMA, recMA);

	string recTrackSB = upperDirectory(imgPathB) + "/" + "recTrackSB";
	vector<string> recSB;
	listOutDirectoryFiles(recTrackSB, recSB);

	string recTrackMB = upperDirectory(imgPathB) + "/" + "recTrackMB";
	vector<string> recMB;
	listOutDirectoryFiles(recTrackMB, recMB);

	cout << ">>Inputs <<" << endl;
	cout << "single thread detect result path A: " << recTrackSA << endl;
	cout << "multi thread detect result path A: " << recTrackMA << endl;
	cout << "single thread detect result path B: " << recTrackSB << endl;
	cout << "multi thread detect result path B: " << recTrackMB << endl;
	cout << ">>Outputs<<" << endl;

	EXPECT_TRUE(recSA.size()==recMA.size());
	EXPECT_TRUE(recSB.size()==recMB.size());

	fstream fS;
	fstream fM;
	int lenS = 0;
	int lenM = 0;
	int outRstS[50][5];
	int outRstM[50][5];
	for(unsigned int i=0; i<recSA.size(); i++){
		fS.open(recSA[i], ios::in | ios::binary);
		fS.read((char *)&lenS, sizeof(lenS));
		fS.read((char *)outRstS[0], sizeof(outRstS[0])*lenS);
		fS.clear();
		fS.close();

		fM.open(recMA[i], ios::in | ios::binary);
		fM.read((char *)&lenM, sizeof(lenM));
		fM.read((char *)outRstM[0], sizeof(outRstM[0])*lenM);
		fM.clear();
		fM.close();

		EXPECT_TRUE(lenS==lenM);
		for(int j=0; j<lenS; j++){
			for(int k=0; k<4; k++){
				EXPECT_TRUE(outRstS[j][k]==outRstM[j][k]);
			}
		}
	}

	cout << "imgPathA: " << "whether single thread or multi thread, the detect result(len/outResult) by ISFaceDetTrackRgb are the same" << endl;

	for(unsigned int i=0; i<recSB.size(); i++){
		fS.open(recSB[i], ios::in | ios::binary);
		fS.read((char *)&lenS, sizeof(lenS));
		fS.read((char *)outRstS[0], sizeof(outRstS[0])*lenS);
		fS.clear();
		fS.close();

		fM.open(recMB[i], ios::in | ios::binary);
		fM.read((char *)&lenM, sizeof(lenM));
		fM.read((char *)outRstM[0], sizeof(outRstM[0])*lenM);
		fM.clear();
		fM.close();

		EXPECT_TRUE(lenS==lenM);
		for(int j=0; j<lenS; j++){
			for(int k=0; k<4; k++){
				EXPECT_TRUE(outRstS[j][k]==outRstM[j][k]);
			}
		}
	}

	cout << "imgPathB: " << "whether single thread or multi thread, the detect result(len/outResult) by ISFaceDetTrackRgb are the same" << endl;
}
#endif

TEST_F(ftISDetTrack, ISCalFaceInfoPath_SingleThread){
	string imgPathA = GConfig::getInstance().getFaceInfoImgPathA();
	string imgPathB = GConfig::getInstance().getFaceInfoImgPathB();
	vector<string> imageAs;
	vector<string> imageBs;
	listOutDirectoryFiles(imgPathA, imageAs);
	listOutDirectoryFiles(imgPathB, imageBs);
	int len = 0;
	int outRst[50][4];
	int keyPoint[50][6];
	float angle[50][3];
	float kScore[50];
	Timer timer;
	cost = 0;

	cout << ">>Inputs <<" << endl;
	cout << "image directory A: " << imgPathA << endl;
	cout << "image directory B: " << imgPathB << endl;
	cout << "threads num: " << "1" << endl;
	cout << ">>Outputs<<" << endl;

	string faceInfoSA = upperDirectory(imgPathA) + "/" + "faceInfoSA";
	string faceInfoSB = upperDirectory(imgPathB) + "/" + "faceInfoSB";
#ifdef WIN32
	faceInfoSA = slashConvert(faceInfoSA, '/', '\\');
	string command = "rd /s /q " + faceInfoSA;
	system(command.c_str());
	command = "mkdir " + faceInfoSA;
	system(command.c_str());
	faceInfoSB = slashConvert(faceInfoSB, '/', '\\');
	command = "rd /s /q " + faceInfoSB;
	system(command.c_str());
	command = "mkdir " + faceInfoSB;
	system(command.c_str());
#endif
#ifdef LINUX
	rmDir(faceInfoSA);
	mkdir(faceInfoSA.data(), 0775);
	rmDir(faceInfoSB);
	mkdir(faceInfoSB.data(), 0775);
#endif

	detectedNumA = 0;
	detectedNumB = 0;
#ifdef WIN32
	fstream f;
#endif
#ifdef LINUX
	FILE *f;
#endif

	int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
	for(unsigned int i=0; i<imageAs.size(); i++){
		EXPECT_TRUE_EX(ISFaceDetectPath(defaultDetTrackChannel, const_cast<char *>(imageAs[i].data()), outRst, &len));
		if(len >= 1){
			detectedNumA += 1;
			timer.start();
			EXPECT_TRUE_EX(ISCalFaceInfoPath2(defaultDetTrackChannel, const_cast<char *>(imageAs[i].data()), outRst, len, keyPoint, angle, kScore));
			cost += timer.stop();
#ifdef WIN32
			string saveFaceInfoPath = faceInfoSA + "\\" + getFileHeader(imageAs[i].data()) + ".rec";
			f.open(saveFaceInfoPath, ios::out | ios::binary);
			f.write((char *)&len, sizeof(len));
			f.write((char *)outRst[0], sizeof(outRst[0])*len);
			f.write((char *)keyPoint[0], sizeof(keyPoint[0])*len);
			f.write((char *)angle[0], sizeof(angle[0])*len);
			f.write((char *)kScore, sizeof(float)*len);
			f.close();
			f.clear();
#endif
#ifdef LINUX
			string saveFaceInfoPath = faceInfoSA + "/" + getFileHeader(imageAs[i].data()) + ".rec";
			f = fopen(saveFaceInfoPath.data(), "wb");
			fseek(f, 0, SEEK_SET);
			fwrite(&len, sizeof(int), 1, f);
			fwrite(outRst, 4*sizeof(int)*len, 1, f);
			fwrite(keyPoint, 6*sizeof(int)*len, 1, f);
			fwrite(angle, 3*sizeof(float)*len, 1, f);
			fwrite(kScore, sizeof(float)*len, 1, f);
			fclose(f);
#endif
		}
	}
	for(unsigned int i=0; i<imageBs.size(); i++){
		EXPECT_TRUE_EX(ISFaceDetectPath(defaultDetTrackChannel, const_cast<char *>(imageBs[i].data()), outRst, &len));
		if(len >= 1){
			detectedNumB += 1;
			timer.start();
			EXPECT_TRUE_EX(ISCalFaceInfoPath2(defaultDetTrackChannel, const_cast<char *>(imageBs[i].data()), outRst, len, keyPoint, angle, kScore));
			cost += timer.stop();
#ifdef WIN32
			string saveFaceInfoPath = faceInfoSB + "\\" + getFileHeader(imageBs[i].data()) + ".rec";
			f.open(saveFaceInfoPath, ios::out | ios::binary);
			f.write((char *)&len, sizeof(len));
			f.write((char *)outRst[0], sizeof(outRst[0])*len);
			f.write((char *)keyPoint[0], sizeof(keyPoint[0])*len);
			f.write((char *)angle[0], sizeof(angle[0])*len);
			f.write((char *)kScore, sizeof(float)*len);
			f.close();
			f.clear();
#endif
#ifdef LINUX
			string saveFaceInfoPath = faceInfoSB + "/" + getFileHeader(imageBs[i].data()) + ".rec";
			f = fopen(saveFaceInfoPath.data(), "wb");
			fseek(f, 0, SEEK_SET);
			fwrite(&len, sizeof(int), 1, f);
			fwrite(outRst, 4*sizeof(int)*len, 1, f);
			fwrite(keyPoint, 6*sizeof(int)*len, 1, f);
			fwrite(angle, 3*sizeof(float)*len, 1, f);
			fwrite(kScore, sizeof(float)*len, 1, f);
			fclose(f);
#endif
		}
	}
	DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);

	cout << "picture num of image directory A: " << imageAs.size() << endl;
	cout << "picture num of image directory B: " << imageBs.size() << endl;
	cout << "picture num detected face succ of image directory A: " << detectedNumA << endl;
	cout << "picture num detected face succ of image directory B: " << detectedNumB << endl;
	double percentA = double(detectedNumA)/imageAs.size()*100;
	cout << "success rate A: " << setiosflags(ios::fixed) << setprecision(2) << percentA << "%" << endl;
	double percentB = double(detectedNumB)/imageBs.size()*100;
	cout << "success rate B: " << setiosflags(ios::fixed) << setprecision(2) << percentB << "%" << endl;
	cout << "output detect result to A: " << faceInfoSA << endl;
	cout << "output detect result to B: " << faceInfoSB << endl;
	float timePerPic = float(cost)/(imageAs.size() + imageBs.size());
	cout << "whole cost: " << cost << "ms" << endl;
	cout << "average time cost: " << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "ms" << endl;
}

TEST_F(ftISDetTrack, ISCalFaceInfoPath_MultiThread){
	string imgPathA = GConfig::getInstance().getFaceInfoImgPathA();
	string imgPathB = GConfig::getInstance().getFaceInfoImgPathB();
	unsigned int detectThreadNum = GConfig::getInstance().getDetectThreadNum();
	vector<string> imageAs;
	vector<string> imageBs;
	listOutDirectoryFiles(imgPathA, imageAs);
	listOutDirectoryFiles(imgPathB, imageBs);
	int imgNumPerThreadA = int(imageAs.size()/detectThreadNum);
	int imgNumPerThreadB = int(imageBs.size()/detectThreadNum);
	cost = 0;

	cout << ">>Inputs <<" << endl;
	cout << "image directory A: " << imgPathA << endl;
	cout << "image directory B: " << imgPathB << endl;
	cout << "thread num: " << detectThreadNum << endl;
	cout << ">>Outputs<<" << endl;

	string faceInfoMA = upperDirectory(imgPathA) + "/" + "faceInfoMA";
	string faceInfoMB = upperDirectory(imgPathB) + "/" + "faceInfoMB";
#ifdef WIN32
	faceInfoMA = slashConvert(faceInfoMA, '/', '\\');
	string command = "rd /s /q " + faceInfoMA;
	system(command.c_str());
	command = "mkdir " + faceInfoMA;
	system(command.c_str());
	faceInfoMB = slashConvert(faceInfoMB, '/', '\\');
	command = "rd /s /q " + faceInfoMB;
	system(command.c_str());
	command = "mkdir " + faceInfoMB;
	system(command.c_str());
#endif
#ifdef LINUX
	rmDir(faceInfoMA);
	mkdir(faceInfoMA.data(), 0775);
	rmDir(faceInfoMB);
	mkdir(faceInfoMB.data(), 0775);
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

	detectedNumA = 0;
	detectedNumB = 0;
	serial = faceInfoMA;
	vector<pthread_t> pThread(detectThreadNum);
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceInfo, (void *)&imageA[i]));
	}

	void *retVal;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

	serial = faceInfoMB;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceInfo, (void *)&imageB[i]));
	}

	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

	cout << "picture num of image directory A: " << imageAs.size() << endl;
	cout << "picture num of image directory B: " << imageBs.size() << endl;
	cout << "picture num allocated to each thread A: " << imgNumPerThreadA << endl;
	cout << "picture num allocated to each thread B: " << imgNumPerThreadB << endl;
	cout << "picture num detected face succ of image directory A: " << detectedNumA << endl;
	cout << "picture num detected face succ of image directory B: " << detectedNumB << endl;
	double percentA = double(detectedNumA)/imageAs.size()*100;
	cout << "success rate A: " << setiosflags(ios::fixed) << setprecision(2) << percentA << "%" << endl;
	double percentB = double(detectedNumB)/imageBs.size()*100;
	cout << "success rate B: " << setiosflags(ios::fixed) << setprecision(2) << percentB << "%" << endl;
	cout << "output detect result to A: " << faceInfoMA << endl;
	cout << "output detect result to B: " << faceInfoMB << endl;
	cost = cost/detectThreadNum;
	float timePerPic = float(cost)/(imageAs.size() + imageBs.size());
	cout << "whole cost: " << cost << "ms" << endl;
	cout << "average time cost: " << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "ms" << endl;
}

TEST_F(ftISDetTrack, ISCalFaceInfoPath_OutResultCheck){
	string imgPathA = GConfig::getInstance().getFaceInfoImgPathA();
	string imgPathB = GConfig::getInstance().getFaceInfoImgPathB();

	string faceInfoSA = upperDirectory(imgPathA) + "/" + "faceInfoSA";
	vector<string> recSA;
	listOutDirectoryFiles(faceInfoSA, recSA);

	string faceInfoMA = upperDirectory(imgPathA) + "/" + "faceInfoMA";
	vector<string> recMA;
	listOutDirectoryFiles(faceInfoMA, recMA);

	string faceInfoSB = upperDirectory(imgPathB) + "/" + "faceInfoSB";
	vector<string> recSB;
	listOutDirectoryFiles(faceInfoSB, recSB);

	string faceInfoMB = upperDirectory(imgPathB) + "/" + "faceInfoMB";
	vector<string> recMB;
	listOutDirectoryFiles(faceInfoMB, recMB);

	cout << ">>Inputs <<" << endl;
	cout << "single thread detect result path A: " << faceInfoSA << endl;
	cout << "multi thread detect result path A: " << faceInfoMA << endl;
	cout << "single thread detect result path B: " << faceInfoSB << endl;
	cout << "multi thread detect result path B: " << faceInfoMB << endl;
	cout << ">>Outputs<<" << endl;

	EXPECT_TRUE(recSA.size()==recMA.size());
	EXPECT_TRUE(recSB.size()==recMB.size());

#ifdef WIN32
	fstream fS;
	fstream fM;
#endif
#ifdef LINUX
	FILE *fS;
	FILE *fM;
#endif
	int lenS = 0;
	int lenM = 0;
	int outRstS[50][4];
	int outRstM[50][4];
	int keyPointS[50][6];
	int keyPointM[50][6];
	float angleS[50][3];
	float angleM[50][3];
	float kScoreS[50];
	float kScoreM[50];
	for(unsigned int i=0; i<recSA.size(); i++){
#ifdef WIN32
		fS.open(recSA[i], ios::in | ios::binary);
		fS.read((char *)&lenS, sizeof(lenS));
		fS.read((char *)outRstS[0], sizeof(outRstS[0])*lenS);
		fS.read((char *)keyPointS[0], sizeof(keyPointS[0])*lenS);
		fS.read((char *)angleS[0], sizeof(angleS[0])*lenS);
		fS.read((char *)kScoreS, sizeof(float)*lenS);
		fS.clear();
		fS.close();

		fM.open(recMA[i], ios::in | ios::binary);
		fM.read((char *)&lenM, sizeof(lenM));
		fM.read((char *)outRstM[0], sizeof(outRstM[0])*lenM);
		fM.read((char *)keyPointM[0], sizeof(keyPointM[0])*lenM);
		fM.read((char *)angleM[0], sizeof(angleM[0])*lenM);
		fM.read((char *)kScoreM, sizeof(float)*lenM);
		fM.clear();
		fM.close();
#endif
#ifdef LINUX
		fS = fopen(recSA[i].data(), "rb");
		fseek(fS, 0, SEEK_SET);
		fread(&lenS, sizeof(lenS), 1, fS);
		fread(outRstS, 4*sizeof(int)*lenS, 1, fS);
		fread(keyPointS, 6*sizeof(int)*lenS, 1, fS);
		fread(angleS, 3*sizeof(float)*lenS, 1, fS);
		fread(kScoreS, sizeof(float)*lenS, 1, fS);
		fclose(fS);

		fM = fopen(recMA[i].data(), "rb");
		fseek(fM, 0, SEEK_SET);
		fread(&lenM, sizeof(lenM), 1, fM);
		fread(outRstM, 4*sizeof(int)*lenM, 1, fM);
		fread(keyPointM, 6*sizeof(int)*lenM, 1, fM);
		fread(angleM, 3*sizeof(float)*lenM, 1, fM);
		fread(kScoreM, sizeof(float)*lenM, 1, fM);
		fclose(fM);
#endif

		EXPECT_TRUE(lenS==lenM);
		for(int j=0; j<lenS; j++){
			for(int k=0; k<4; k++){
				EXPECT_TRUE(outRstS[j][k]==outRstM[j][k]);
			}
		}
		for(int m=0; m<lenS; m++){
			for(int n=0; n<6; n++){
				EXPECT_TRUE(keyPointS[m][n]==keyPointM[m][n]);
			}
		}
		for(int s=0; s<lenS; s++){
			for(int t=0; t<3; t++){
				EXPECT_TRUE(abs(angleS[s][t]-angleM[s][t])<0.0001);
			}
		}
		for(int x=0; x<lenS; x++){
			EXPECT_TRUE(abs(kScoreS[x]-kScoreM[x])<0.0001);
		}
	}

	cout << "imgPathA: " << "whether single thread or multi thread, the detect result(len/outResult/keyPoint/angle/kScore) by ISCalFaceInfoPath are the same" << endl;

	for(unsigned int i=0; i<recSB.size(); i++){
#ifdef WIN32
		fS.open(recSB[i], ios::in | ios::binary);
		fS.read((char *)&lenS, sizeof(lenS));
		fS.read((char *)outRstS[0], sizeof(outRstS[0])*lenS);
		fS.read((char *)keyPointS[0], sizeof(keyPointS[0])*lenS);
		fS.read((char *)angleS[0], sizeof(angleS[0])*lenS);
		fS.read((char *)kScoreS, sizeof(float)*lenS);
		fS.clear();
		fS.close();

		fM.open(recMB[i], ios::in | ios::binary);
		fM.read((char *)&lenM, sizeof(lenM));
		fM.read((char *)outRstM[0], sizeof(outRstM[0])*lenM);
		fM.read((char *)keyPointM[0], sizeof(keyPointM[0])*lenM);
		fM.read((char *)angleM[0], sizeof(angleM[0])*lenM);
		fM.read((char *)kScoreM, sizeof(float)*lenM);
		fM.clear();
		fM.close();
#endif
#ifdef LINUX
		fS = fopen(recSB[i].data(), "rb");
		fseek(fS, 0, SEEK_SET);
		fread(&lenS, sizeof(lenS), 1, fS);
		fread(outRstS, 4*sizeof(int)*lenS, 1, fS);
		fread(keyPointS, 6*sizeof(int)*lenS, 1, fS);
		fread(angleS, 3*sizeof(float)*lenS, 1, fS);
		fread(kScoreS, sizeof(float)*lenS, 1, fS);
		fclose(fS);

		fM = fopen(recMB[i].data(), "rb");
		fseek(fM, 0, SEEK_SET);
		fread(&lenM, sizeof(lenM), 1, fM);
		fread(outRstM, 4*sizeof(int)*lenM, 1, fM);
		fread(keyPointM, 6*sizeof(int)*lenM, 1, fM);
		fread(angleM, 3*sizeof(float)*lenM, 1, fM);
		fread(kScoreM, sizeof(float)*lenM, 1, fM);
		fclose(fM);
#endif

		EXPECT_TRUE(lenS==lenM);
		for(int j=0; j<lenS; j++){
			for(int k=0; k<4; k++){
				EXPECT_TRUE(outRstS[j][k]==outRstM[j][k]);
			}
		}
		for(int m=0; m<lenS; m++){
			for(int n=0; n<6; n++){
				EXPECT_TRUE(keyPointS[m][n]==keyPointM[m][n]);
			}
		}
		for(int s=0; s<lenS; s++){
			for(int t=0; t<3; t++){
				EXPECT_TRUE(abs(angleS[s][t]-angleM[s][t])<0.0001);
			}
		}
		for(int x=0; x<lenS; x++){
			EXPECT_TRUE(abs(kScoreS[x]-kScoreM[x])<0.0001);
		}
	}

	cout << "imgPathB: " << "whether single thread or multi thread, the detect result(len/outResult/keyPoint/angle/kScore) by ISCalFaceInfoPath are the same" << endl;
}
