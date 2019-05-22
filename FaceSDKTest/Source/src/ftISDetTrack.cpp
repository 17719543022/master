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

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int detectedNum = 0;

namespace{
	void *faceDetect(void *ptr){
		vector<string> images = *(vector<string> *)ptr;
		int len = 0;
		int outRst[50][4] = {0};
		fstream f;
		string recDetectM = GConfig::getInstance().getRecDetectMPath();

		int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
		for(unsigned int i=0; i<images.size(); i++){
			char* image = const_cast<char*>(images[i].data());
			EXPECT_TRUE_EX(ISFaceDetectPath(defaultDetTrackChannel, image, outRst, &len));
			if(len >= 1){
				pthread_mutex_lock(&mutex);
				detectedNum += 1;
				string saveRecPath = recDetectM + "\\" + getFileHeader(images[i].data()) + ".rec";
				f.open(saveRecPath, ios::out | ios::binary);
				f.write(const_cast<char *>((char *)&len), sizeof(len));
				f.write(const_cast<char *>((char *)outRst[0]), sizeof(outRst[0])*len);
				f.close();
				f.clear();
				pthread_mutex_unlock(&mutex);
			}
		}
		DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);

		return NULL;
	}

	void *faceTrack(void *ptr){
		vector<string> images = *(vector<string> *)ptr;
		int len = 0;
		int outRst[50][4] = {0};
		fstream f;
		string recTrackM = GConfig::getInstance().getRecTrackMPath();

		int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
		Mat cache = imread(images[0]);
		EXPECT_TRUE_EX(ISFaceDetTrackRgb(defaultDetTrackChannel, (char *)cache.data, cache.rows*cache.cols*3, cache.cols, cache.rows, outRst, &len));
		for(unsigned int i=0; i<images.size(); i++){
			Mat image = imread(images[i]);
			EXPECT_TRUE_EX(ISFaceDetTrackRgb(defaultDetTrackChannel, (char *)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &len));
			if(len >= 1){
				pthread_mutex_lock(&mutex);
				detectedNum += 1;
				string saveRecPath = recTrackM + "\\" + getFileHeader(images[i].data()) + ".rec";
				f.open(saveRecPath, ios::out | ios::binary);
				f.write(const_cast<char *>((char *)&len), sizeof(len));
				f.write(const_cast<char *>((char *)outRst[0]), sizeof(outRst[0])*len);
				f.close();
				f.clear();
				pthread_mutex_unlock(&mutex);
			}
		}
		DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);

		return NULL;
	}
}

TEST_F(ftISDetTrack, ISFaceDetectPath_SingleThread)
{
	string imgPath = GConfig::getInstance().getDetectImgPath();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);
	int len = 0;
	int outRst[50][4] = {0};

	cout << ">>Inputs <<" << endl;
	cout << "待检测人脸目录：" << imgPath << endl;
	cout << "线程数：" << "单线程" << endl;
	cout << ">>Outputs<<" << endl;

	string recDetectS = GConfig::getInstance().getRecDetectSPath();
	string command = "rd /s /q " + recDetectS;
	system(command.c_str());
	command = "mkdir " + recDetectS;
	system(command.c_str());

	SYSTEMTIME tStart, tStop;
    GetSystemTime(&tStart);
	detectedNum = 0;
	fstream f;
	
	int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
	for(unsigned int i=0; i<images.size(); i++){
		char* image = const_cast<char*>(images[i].data());
		EXPECT_TRUE_EX(ISFaceDetectPath(defaultDetTrackChannel, image, outRst, &len));
		if(len >= 1){
			detectedNum += 1;
		}
		
		string saveRecPath = recDetectS + "\\" + getFileHeader(images[i].data()) + ".rec";
		f.open(saveRecPath, ios::out | ios::binary);
		f.write(const_cast<char *>((char *)&len), sizeof(len));
		f.write(const_cast<char *>((char *)outRst[0]), sizeof(outRst[0])*len);
		f.close();
		f.clear();
	}
	DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);

	GetSystemTime(&tStop);

	cout << "输入图片张数：" << images.size() << endl;
	cout << "检出到人脸张数：" << detectedNum << endl;
	float percent = float(detectedNum)/images.size()*100;
	cout << "检出成功率：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "检出结果存放路径：" << recDetectS << endl;
	cout << "总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
	float timePerPic = float(getGap(tStart, tStop))/images.size();
	cout << "单张图片耗时：" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "毫秒" << endl;
}

TEST_F(ftISDetTrack, ISFaceDetectPath_MultiThread)
{
	string imgPath = GConfig::getInstance().getDetectImgPath();
	unsigned int detectThreadNum = GConfig::getInstance().getDetectThreadNum();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);
	int imgNumPerThread = int(images.size()/detectThreadNum);

	cout << ">>Inputs <<" << endl;
	cout << "待检测人脸目录：" << imgPath << endl;
	cout << "线程数：" << detectThreadNum << endl;
	cout << ">>Outputs<<" << endl;

	string recDetectM = GConfig::getInstance().getRecDetectMPath();
	string command = "rd /s /q " + recDetectM;
	system(command.c_str());
	command = "mkdir " + recDetectM;
	system(command.c_str());

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
	detectedNum = 0;

	vector<pthread_t> pThread(detectThreadNum);
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceDetect, (void *)&image[i]));
	}

	void *retVal;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

    GetSystemTime(&tStop);

	cout << "输入图片张数：" << images.size() << endl;
	cout << "每个线程输入图片张数：" << imgNumPerThread << endl;
	cout << "检出到人脸张数：" << detectedNum << endl;
	float percent = float(detectedNum)/images.size()*100;
	cout << "检出成功率：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "检出结果存放路径：" << recDetectM << endl;
	cout << "总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
	float timePerPic = float(getGap(tStart, tStop))/images.size();
	cout << "单张图片耗时：" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "毫秒" << endl;
}

TEST_F(ftISDetTrack, ISFaceDetectPath_OutResultCheck)
{
	string recDetectS = GConfig::getInstance().getRecDetectSPath();
	vector<string> recS;
	listOutDirectoryFiles(recDetectS, recS);

	string recDetectM = GConfig::getInstance().getRecDetectMPath();
	vector<string> recM;
	listOutDirectoryFiles(recDetectM, recM);

	EXPECT_TRUE(recS.size()==recM.size());

	Mat imageS;
	Mat imageM;
	fstream fS;
	fstream fM;
	int lenS = 0;
	int lenM = 0;
	int outRstS[50][4];
	int outRstM[50][4];
	for(unsigned int i=0; i<recS.size(); i++){
		fS.open(recS[i], ios::in | ios::binary);
		fS.read(const_cast<char *>((char *)&lenS), sizeof(lenS));
		fS.read(const_cast<char *>((char *)outRstS[0]), sizeof(outRstS[0])*lenS);
		fS.clear();
		fS.close();

		fM.open(recM[i], ios::in | ios::binary);
		fM.read(const_cast<char *>((char *)&lenM), sizeof(lenM));
		fM.read(const_cast<char *>((char *)outRstM[0]), sizeof(outRstM[0])*lenM);
		fM.clear();
		fM.close();

		EXPECT_TRUE(lenS==lenM);
		for(int j=0; j<lenS; j++){
			for(int k=0; k<4; k++){
				EXPECT_TRUE(outRstS[j][k]==outRstM[j][k]);
			}
		}
	}

	cout << "单线程和多线程ISFaceDetectPath函数返回的outResult和len完全一致！" << endl;
}

TEST_F(ftISDetTrack, ISFaceDetTrackRgb_SingleThread)
{
	string imgPath = GConfig::getInstance().getTrackImgPath();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);
	int len = 0;
	int outRst[50][4] = {0};

	cout << ">>Inputs <<" << endl;
	cout << "待检测人脸目录：" << imgPath << endl;
	cout << "线程数：" << "单线程" << endl;
	cout << ">>Outputs<<" << endl;

	string recTrackS = GConfig::getInstance().getRecTrackSPath();
	string command = "rd /s /q " + recTrackS;
	system(command.c_str());
	command = "mkdir " + recTrackS;
	system(command.c_str());

	SYSTEMTIME tStart, tStop;
    GetSystemTime(&tStart);
	detectedNum = 0;
	fstream f;
	
	int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
	Mat cache = imread(images[0]);
	EXPECT_TRUE_EX(ISFaceDetTrackRgb(defaultDetTrackChannel, (char *)cache.data, cache.rows*cache.cols*3, cache.cols, cache.rows, outRst, &len));
	for(unsigned int i=0; i<images.size(); i++){
		Mat image = imread(images[i]);
		EXPECT_TRUE_EX(ISFaceDetTrackRgb(defaultDetTrackChannel, (char *)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &len));
		if(len >= 1){
			detectedNum += 1;
		}
		
		string saveRecPath = recTrackS + "\\" + getFileHeader(images[i].data()) + ".rec";
		f.open(saveRecPath, ios::out | ios::binary);
		f.write(const_cast<char *>((char *)&len), sizeof(len));
		f.write(const_cast<char *>((char *)outRst[0]), sizeof(outRst[0])*len);
		f.close();
		f.clear();
	}
	DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);

	GetSystemTime(&tStop);

	cout << "输入图片张数：" << images.size() << endl;
	cout << "检出到人脸张数：" << detectedNum << endl;
	float percent = float(detectedNum)/images.size()*100;
	cout << "检出成功率：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "检出结果存放路径：" << recTrackS << endl;
	cout << "总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
	float timePerPic = float(getGap(tStart, tStop))/images.size();
	cout << "单张图片耗时：" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "毫秒" << endl;
}

TEST_F(ftISDetTrack, ISFaceDetTrackRgb_MultiThread)
{
	string imgPath = GConfig::getInstance().getTrackImgPath();
	unsigned int detectThreadNum = GConfig::getInstance().getDetectThreadNum();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);
	int imgNumPerThread = int(images.size()/detectThreadNum);

	cout << ">>Inputs <<" << endl;
	cout << "待检测人脸目录：" << imgPath << endl;
	cout << "线程数：" << detectThreadNum << endl;
	cout << ">>Outputs<<" << endl;

	string recTrackM = GConfig::getInstance().getRecTrackMPath();
	string command = "rd /s /q " + recTrackM;
	system(command.c_str());
	command = "mkdir " + recTrackM;
	system(command.c_str());

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
	detectedNum = 0;

	vector<pthread_t> pThread(detectThreadNum);
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceTrack, (void *)&image[i]));
	}

	void *retVal;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

    GetSystemTime(&tStop);

	cout << "输入图片张数：" << images.size() << endl;
	cout << "每个线程输入图片张数：" << imgNumPerThread << endl;
	cout << "检出到人脸张数：" << detectedNum << endl;
	float percent = float(detectedNum)/images.size()*100;
	cout << "检出成功率：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "检出结果存放路径：" << recTrackM << endl;
	cout << "总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
	float timePerPic = float(getGap(tStart, tStop))/images.size();
	cout << "单张图片耗时：" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "毫秒" << endl;
}

TEST_F(ftISDetTrack, ISFaceDetTrackRgb_OutResultCheck)
{
	string recTrackS = GConfig::getInstance().getRecTrackSPath();
	vector<string> recS;
	listOutDirectoryFiles(recTrackS, recS);

	string recTrackM = GConfig::getInstance().getRecTrackMPath();
	vector<string> recM;
	listOutDirectoryFiles(recTrackM, recM);

	EXPECT_TRUE(recS.size()==recM.size());

	Mat imageS;
	Mat imageM;
	fstream fS;
	fstream fM;
	int lenS = 0;
	int lenM = 0;
	int outRstS[50][4];
	int outRstM[50][4];
	for(unsigned int i=0; i<recS.size(); i++){
		fS.open(recS[i], ios::in | ios::binary);
		fS.read(const_cast<char *>((char *)&lenS), sizeof(lenS));
		fS.read(const_cast<char *>((char *)outRstS[0]), sizeof(outRstS[0])*lenS);
		fS.clear();
		fS.close();

		fM.open(recM[i], ios::in | ios::binary);
		fM.read(const_cast<char *>((char *)&lenM), sizeof(lenM));
		fM.read(const_cast<char *>((char *)outRstM[0]), sizeof(outRstM[0])*lenM);
		fM.clear();
		fM.close();

		EXPECT_TRUE(lenS==lenM);
		for(int j=0; j<lenS; j++){
			for(int k=0; k<4; k++){
				EXPECT_TRUE(outRstS[j][k]==outRstM[j][k]);
			}
		}
	}

	cout << "单线程和多线程ISFaceDetTrackRgb函数返回的outResult和len完全一致！" << endl;
}
