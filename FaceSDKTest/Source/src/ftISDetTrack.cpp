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
		int outRst[50][4];
		fstream f;
		string recDetectM = GConfig::getInstance().getRecDetectMPath();

		int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
		for(unsigned int i=0; i<images.size(); i++){
			EXPECT_TRUE_EX(ISFaceDetectPath(defaultDetTrackChannel, const_cast<char*>(images[i].data()), outRst, &len));
			if(len >= 1){
				pthread_mutex_lock(&mutex);
				detectedNum += 1;
				string saveRecPath = recDetectM + "\\" + getFileHeader(images[i].data()) + ".rec";
				f.open(saveRecPath, ios::out | ios::binary);
				f.write((char *)&len, sizeof(len));
				f.write((char *)outRst[0], sizeof(outRst[0])*len);
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
		int outRst[50][4];
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
				f.write((char *)&len, sizeof(len));
				f.write((char *)outRst[0], sizeof(outRst[0])*len);
				f.close();
				f.clear();
				pthread_mutex_unlock(&mutex);
			}
		}
		DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);

		return NULL;
	}

	void *faceInfo(void *ptr){
		vector<string> images = *(vector<string> *)ptr;
		int len = 0;
		int outRst[50][4];
		int keyPoint[50][6];
		float angle[50][3];
		float kScore[50];
		fstream f;
		string faceInfoM = GConfig::getInstance().getFaceInfoMPath();

		int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
		for(unsigned int i=0; i<images.size(); i++){
			EXPECT_TRUE_EX(ISFaceDetectPath(defaultDetTrackChannel, const_cast<char *>(images[i].data()), outRst, &len));
			EXPECT_TRUE_EX(ISCalFaceInfoPath(defaultDetTrackChannel, const_cast<char *>(images[i].data()), outRst, len, keyPoint, angle, kScore));
			if(len >= 1){
				pthread_mutex_lock(&mutex);
				detectedNum += 1;
				string saveRecPath = faceInfoM + "\\" + getFileHeader(images[i].data()) + ".rec";
				f.open(saveRecPath, ios::out | ios::binary);
				f.write((char *)&len, sizeof(len));
				f.write((char *)outRst[0], sizeof(outRst[0])*len);
				f.write((char *)keyPoint[0], sizeof(keyPoint[0])*len);
				f.write((char *)angle[0], sizeof(angle[0])*len);
				f.write((char *)kScore, sizeof(float)*len);
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
	int outRst[50][4];

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
		EXPECT_TRUE_EX(ISFaceDetectPath(defaultDetTrackChannel, const_cast<char*>(images[i].data()), outRst, &len));
		if(len >= 1){
			detectedNum += 1;
		}
		
		string saveRecPath = recDetectS + "\\" + getFileHeader(images[i].data()) + ".rec";
		f.open(saveRecPath, ios::out | ios::binary);
		f.write((char *)&len, sizeof(len));
		f.write((char *)outRst[0], sizeof(outRst[0])*len);
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

	fstream fS;
	fstream fM;
	int lenS = 0;
	int lenM = 0;
	int outRstS[50][4];
	int outRstM[50][4];
	for(unsigned int i=0; i<recS.size(); i++){
		fS.open(recS[i], ios::in | ios::binary);
		fS.read((char *)&lenS, sizeof(lenS));
		fS.read((char *)outRstS[0], sizeof(outRstS[0])*lenS);
		fS.clear();
		fS.close();

		fM.open(recM[i], ios::in | ios::binary);
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

	cout << "单线程和多线程ISFaceDetectPath函数返回的outResult和len完全一致！" << endl;
}

TEST_F(ftISDetTrack, ISFaceDetTrackRgb_SingleThread)
{
	string imgPath = GConfig::getInstance().getTrackImgPath();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);
	int len = 0;
	int outRst[50][4];

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
		f.write((char *)&len, sizeof(len));
		f.write((char *)outRst[0], sizeof(outRst[0])*len);
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

	fstream fS;
	fstream fM;
	int lenS = 0;
	int lenM = 0;
	int outRstS[50][4];
	int outRstM[50][4];
	for(unsigned int i=0; i<recS.size(); i++){
		fS.open(recS[i], ios::in | ios::binary);
		fS.read((char *)&lenS, sizeof(lenS));
		fS.read((char *)outRstS[0], sizeof(outRstS[0])*lenS);
		fS.clear();
		fS.close();

		fM.open(recM[i], ios::in | ios::binary);
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

	cout << "单线程和多线程ISFaceDetTrackRgb函数返回的outResult和len完全一致！" << endl;
}

TEST_F(ftISDetTrack, ISCalFaceInfoPath_SingleThread)
{
	string imgPath = GConfig::getInstance().getFaceInfoImgPath();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);
	int len = 0;
	int outRst[50][4];
	int keyPoint[50][6];
	float angle[50][3];
	float kScore[50];

	cout << ">>Inputs <<" << endl;
	cout << "待检测人脸目录：" << imgPath << endl;
	cout << "线程数：" << "单线程" << endl;
	cout << ">>Outputs<<" << endl;

	string faceInfoS = GConfig::getInstance().getFaceInfoSPath();
	string command = "rd /s /q " + faceInfoS;
	system(command.c_str());
	command = "mkdir " + faceInfoS;
	system(command.c_str());

	SYSTEMTIME tStart, tStop;
    GetSystemTime(&tStart);
	detectedNum = 0;
	fstream f;
	
	int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
	for(unsigned int i=0; i<images.size(); i++){
		EXPECT_TRUE_EX(ISFaceDetectPath(defaultDetTrackChannel, const_cast<char *>(images[i].data()), outRst, &len));
		if(len >= 1){
			detectedNum += 1;
		}
		EXPECT_TRUE_EX(ISCalFaceInfoPath(defaultDetTrackChannel, const_cast<char *>(images[i].data()), outRst, len, keyPoint, angle, kScore));
		
		string saveFaceInfoPath = faceInfoS + "\\" + getFileHeader(images[i].data()) + ".rec";
		f.open(saveFaceInfoPath, ios::out | ios::binary);
		f.write((char *)&len, sizeof(len));
		f.write((char *)outRst[0], sizeof(outRst[0])*len);
		f.write((char *)keyPoint[0], sizeof(keyPoint[0])*len);
		f.write((char *)angle[0], sizeof(angle[0])*len);
		f.write((char *)kScore, sizeof(float)*len);
		f.close();
		f.clear();
	}
	DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);

	GetSystemTime(&tStop);

	cout << "输入图片张数：" << images.size() << endl;
	cout << "检出到人脸张数：" << detectedNum << endl;
	float percent = float(detectedNum)/images.size()*100;
	cout << "检出成功率：" << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "检出结果存放路径：" << faceInfoS << endl;
	cout << "总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
	float timePerPic = float(getGap(tStart, tStop))/images.size();
	cout << "单张图片耗时：" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "毫秒" << endl;
}

TEST_F(ftISDetTrack, ISCalFaceInfoPath_MultiThread)
{
	string imgPath = GConfig::getInstance().getFaceInfoImgPath();
	unsigned int detectThreadNum = GConfig::getInstance().getDetectThreadNum();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);
	int imgNumPerThread = int(images.size()/detectThreadNum);

	cout << ">>Inputs <<" << endl;
	cout << "待检测人脸目录：" << imgPath << endl;
	cout << "线程数：" << detectThreadNum << endl;
	cout << ">>Outputs<<" << endl;

	string faceInfoM = GConfig::getInstance().getFaceInfoMPath();
	string command = "rd /s /q " + faceInfoM;
	system(command.c_str());
	command = "mkdir " + faceInfoM;
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
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceInfo, (void *)&image[i]));
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
	cout << "检出结果存放路径：" << faceInfoM << endl;
	cout << "总共耗时：" << getGap(tStart, tStop) << "毫秒" << endl;
	float timePerPic = float(getGap(tStart, tStop))/images.size();
	cout << "单张图片耗时：" << setiosflags(ios::fixed) << setprecision(2) << timePerPic << "毫秒" << endl;
}

TEST_F(ftISDetTrack, ISCalFaceInfoPath_OutResultCheck)
{
	string faceInfoS = GConfig::getInstance().getFaceInfoSPath();
	vector<string> recS;
	listOutDirectoryFiles(faceInfoS, recS);

	string faceInfoM = GConfig::getInstance().getFaceInfoMPath();
	vector<string> recM;
	listOutDirectoryFiles(faceInfoM, recM);

	EXPECT_TRUE(recS.size()==recM.size());

	fstream fS;
	fstream fM;
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
	for(unsigned int i=0; i<recS.size(); i++){
		fS.open(recS[i], ios::in | ios::binary);
		fS.read((char *)&lenS, sizeof(lenS));
		fS.read((char *)outRstS[0], sizeof(outRstS[0])*lenS);
		fS.read((char *)keyPointS[0], sizeof(keyPointS[0])*lenS);
		fS.read((char *)angleS[0], sizeof(angleS[0])*lenS);
		fS.read((char *)kScoreS, sizeof(float)*lenS);
		fS.clear();
		fS.close();

		fM.open(recM[i], ios::in | ios::binary);
		fM.read((char *)&lenM, sizeof(lenM));
		fM.read((char *)outRstM[0], sizeof(outRstM[0])*lenM);
		fM.read((char *)keyPointM[0], sizeof(keyPointM[0])*lenM);
		fM.read((char *)angleM[0], sizeof(angleM[0])*lenM);
		fM.read((char *)kScoreM, sizeof(float)*lenM);
		fM.clear();
		fM.close();

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
				EXPECT_TRUE(angleS[s][t]==angleM[s][t]);
			}
		}
		for(int x=0; x<lenS; x++){
			EXPECT_TRUE(kScoreS[x]==kScoreM[x]);
		}
	}

	cout << "单线程和多线程ISFaceDetTrackRgb函数返回的len、outResult、keyPoint、angle、kScore完全一致！" << endl;
}
