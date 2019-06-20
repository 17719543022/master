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

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
extern int denominator;
int detectedNum = 0;

namespace{
	void *faceDetect(void *ptr){
		vector<string> images = *(vector<string> *)ptr;
		int len = 0;
		int outRst[50][4];
#ifdef WIN32
		fstream f;
#endif
#ifdef LINUX
		FILE *f;
#endif
		string recDetectM = GConfig::getInstance().getRecDetectMPath();

		int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
		for(unsigned int i=0; i<images.size(); i++){
			EXPECT_TRUE_EX(ISFaceDetectPath(defaultDetTrackChannel, const_cast<char*>(images[i].data()), outRst, &len));
			if(len >= 1){
				pthread_mutex_lock(&mutex);
				detectedNum += 1;
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
				pthread_mutex_unlock(&mutex);
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
#endif

	void *faceInfo(void *ptr){
		vector<string> images = *(vector<string> *)ptr;
		int len = 0;
		int outRst[50][4];
		int keyPoint[50][6];
		float angle[50][3];
		float kScore[50];
#ifdef WIN32
		fstream f;
#endif
#ifdef LINUX
		FILE *f;
#endif
		string faceInfoM = GConfig::getInstance().getFaceInfoMPath();

		int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
		for(unsigned int i=0; i<images.size(); i++){
			EXPECT_TRUE_EX(ISFaceDetectPath(defaultDetTrackChannel, const_cast<char *>(images[i].data()), outRst, &len));
			EXPECT_TRUE_EX(ISCalFaceInfoPath2(defaultDetTrackChannel, const_cast<char *>(images[i].data()), outRst, len, keyPoint, angle, kScore));
			if(len >= 1){
				pthread_mutex_lock(&mutex);
				detectedNum += 1;
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
	string imgPath = GConfig::getInstance().getDetectImgPath();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);
	int len = 0;
	int outRst[50][4];

	cout << ">>Inputs <<" << endl;
	cout << "image directory: " << imgPath << endl;
	cout << "Threads Num: " << "1" << endl;
	cout << ">>Outputs<<" << endl;

	string recDetectS = GConfig::getInstance().getRecDetectSPath();
#ifdef WIN32
	recDetectS = slashConvert(recDetectS, '/', '\\');
	string command = "rd /s /q " + recDetectS;
	system(command.c_str());
	command = "mkdir " + recDetectS;
	system(command.c_str());
#endif
#ifdef LINUX
	rmDir(recDetectS);
	mkdir(recDetectS.data(), 0775);
#endif

	detectedNum = 0;
#ifdef WIN32
	fstream f;
#endif
#ifdef LINUX
	FILE *f;
#endif

	int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
	for(unsigned int i=0; i<images.size(); i++){
		EXPECT_TRUE_EX(ISFaceDetectPath(defaultDetTrackChannel, const_cast<char*>(images[i].data()), outRst, &len));
		if(len >= 1){
			detectedNum += 1;
#ifdef WIN32
			string saveRecPath = recDetectS + "\\" + getFileHeader(images[i].data()) + ".rec";
			f.open(saveRecPath, ios::out | ios::binary);
			f.write((char *)&len, sizeof(len));
			f.write((char *)outRst[0], sizeof(outRst[0])*len);
			f.close();
			f.clear();
#endif
#ifdef LINUX
			string saveRecPath = recDetectS + "/" + getFileHeader(images[i].data()) + ".rec";
			f = fopen(saveRecPath.data(), "wb");
			fseek(f, 0, SEEK_SET);
			fwrite(&len, sizeof(int), 1, f);
			fwrite(outRst, 4*sizeof(int)*len, 1, f);
			fclose(f);
#endif
		}
	}
	DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);

	cout << "picture num of image directory: " << images.size() << endl;
	cout << "picture num detected face succ of image directory: " << detectedNum << endl;
	float percent = float(detectedNum)/images.size()*100;
	cout << "success rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "output detect result to: " << recDetectS << endl;
	denominator = images.size();
}

TEST_F(ftISDetTrack, ISFaceDetectPath_MultiThread){
	string imgPath = GConfig::getInstance().getDetectImgPath();
	unsigned int detectThreadNum = GConfig::getInstance().getDetectThreadNum();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);
	int imgNumPerThread = int(images.size()/detectThreadNum);

	cout << ">>Inputs <<" << endl;
	cout << "image directory: " << imgPath << endl;
	cout << "Threads Num: " << detectThreadNum << endl;
	cout << ">>Outputs<<" << endl;

	string recDetectM = GConfig::getInstance().getRecDetectMPath();
#ifdef WIN32
	recDetectM = slashConvert(recDetectM, '/', '\\');
	string command = "rd /s /q " + recDetectM;
	system(command.c_str());
	command = "mkdir " + recDetectM;
	system(command.c_str());
#endif
#ifdef LINUX
	rmDir(recDetectM);
	mkdir(recDetectM.data(), 0775);
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

	detectedNum = 0;

	vector<pthread_t> pThread(detectThreadNum);
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceDetect, (void *)&image[i]));
	}

	void *retVal;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

	cout << "picture num of image directory: " << images.size() << endl;
	cout << "picture num allocated to each thread: " << imgNumPerThread << endl;
	cout << "picture num detected face succ of image directory: " << detectedNum << endl;
	float percent = float(detectedNum)/images.size()*100;
	cout << "success rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "output detect result to: " << recDetectM << endl;
	denominator = images.size();
}

TEST_F(ftISDetTrack, ISFaceDetectPath_OutResultCheck){
	string recDetectS = GConfig::getInstance().getRecDetectSPath();
	vector<string> recS;
	listOutDirectoryFiles(recDetectS, recS);

	string recDetectM = GConfig::getInstance().getRecDetectMPath();
	vector<string> recM;
	listOutDirectoryFiles(recDetectM, recM);

	cout << ">>Inputs <<" << endl;
	cout << "single thread detect result path: " << recDetectS << endl;
	cout << "multi thread detect result path: " << recDetectM << endl;
	cout << ">>Outputs<<" << endl;

	EXPECT_TRUE(recS.size()==recM.size());

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
	for(unsigned int i=0; i<recS.size(); i++){
#ifdef WIN32
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
#endif
#ifdef LINUX
		fS = fopen(recS[i].data(), "rb");
		fseek(fS, 0, SEEK_SET);
		fread(&lenS, sizeof(int), 1, fS);
		fread(outRstS, 4*sizeof(int)*lenS, 1, fS);
		fclose(fS);

		fM = fopen(recM[i].data(), "rb");
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

	cout << "whether single thread or multi thread, the detect result(len/outResult) by ISFaceDetectPath are the same" << endl;
}

#ifdef WIN32
TEST_F(ftISDetTrack, ISFaceDetTrackRgb_SingleThread){
	string imgPath = GConfig::getInstance().getTrackImgPath();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);
	int len = 0;
	int outRst[50][5];

	cout << ">>Inputs <<" << endl;
	cout << "image directory: " << imgPath << endl;
	cout << "threads num: " << "1" << endl;
	cout << ">>Outputs<<" << endl;

	string recTrackS = GConfig::getInstance().getRecTrackSPath();
	recTrackS = slashConvert(recTrackS, '/', '\\');
	string command = "rd /s /q " + recTrackS;
	system(command.c_str());
	command = "mkdir " + recTrackS;
	system(command.c_str());

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
			string saveRecPath = recTrackS + "\\" + getFileHeader(images[i].data()) + ".rec";
			f.open(saveRecPath, ios::out | ios::binary);
			f.write((char *)&len, sizeof(len));
			f.write((char *)outRst[0], sizeof(outRst[0])*len);
			f.close();
			f.clear();
		}
	}
	DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);

	cout << "picture num of image directory: " << images.size() << endl;
	cout << "picture num detected face succ of image directory: " << detectedNum << endl;
	float percent = float(detectedNum)/images.size()*100;
	cout << "success rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "output detect result to: " << recTrackS << endl;
	denominator = images.size();
}

TEST_F(ftISDetTrack, ISFaceDetTrackRgb_MultiThread){
	string imgPath = GConfig::getInstance().getTrackImgPath();
	unsigned int detectThreadNum = GConfig::getInstance().getDetectThreadNum();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);
	int imgNumPerThread = int(images.size()/detectThreadNum);

	cout << ">>Inputs <<" << endl;
	cout << "image directory: " << imgPath << endl;
	cout << "threads num: " << detectThreadNum << endl;
	cout << ">>Outputs<<" << endl;

	string recTrackM = GConfig::getInstance().getRecTrackMPath();
	recTrackM = slashConvert(recTrackM, '/', '\\');
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

	detectedNum = 0;
	vector<pthread_t> pThread(detectThreadNum);
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceTrack, (void *)&image[i]));
	}

	void *retVal;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

	cout << "picture num of image directory: " << images.size() << endl;
	cout << "picture num allocated to each thread: " << imgNumPerThread << endl;
	cout << "picture num detected face succ of image directory: " << detectedNum << endl;
	float percent = float(detectedNum)/images.size()*100;
	cout << "success rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "output detect result to: " << recTrackM << endl;
	denominator = images.size();
}

TEST_F(ftISDetTrack, ISFaceDetTrackRgb_OutResultCheck){
	string recTrackS = GConfig::getInstance().getRecTrackSPath();
	vector<string> recS;
	listOutDirectoryFiles(recTrackS, recS);

	string recTrackM = GConfig::getInstance().getRecTrackMPath();
	vector<string> recM;
	listOutDirectoryFiles(recTrackM, recM);

	cout << ">>Inputs <<" << endl;
	cout << "single thread detect result path: " << recTrackS << endl;
	cout << "multi thread detect result path: " << recTrackM << endl;
	cout << ">>Outputs<<" << endl;

	EXPECT_TRUE(recS.size()==recM.size());

	fstream fS;
	fstream fM;
	int lenS = 0;
	int lenM = 0;
	int outRstS[50][5];
	int outRstM[50][5];
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
				if(outRstS[j][k]!=outRstM[j][k]){
					cout << recS[i].data() << endl;
				}
			}
		}
	}

	cout << "whether single thread or multi thread, the detect result(len/outResult) by ISFaceDetTrackRgb are the same" << endl;
}
#endif

TEST_F(ftISDetTrack, ISCalFaceInfoPath_SingleThread){
	string imgPath = GConfig::getInstance().getFaceInfoImgPath();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);
	int len = 0;
	int outRst[50][4];
	int keyPoint[50][6];
	float angle[50][3];
	float kScore[50];

	cout << ">>Inputs <<" << endl;
	cout << "image directory: " << imgPath << endl;
	cout << "threads num: " << "1" << endl;
	cout << ">>Outputs<<" << endl;

	string faceInfoS = GConfig::getInstance().getFaceInfoSPath();
#ifdef WIN32
	faceInfoS = slashConvert(faceInfoS, '/', '\\');
	string command = "rd /s /q " + faceInfoS;
	system(command.c_str());
	command = "mkdir " + faceInfoS;
	system(command.c_str());
#endif
#ifdef LINUX
	rmDir(faceInfoS);
	mkdir(faceInfoS.data(), 0775);
#endif

	detectedNum = 0;
#ifdef WIN32
	fstream f;
#endif
#ifdef LINUX
	FILE *f;
#endif

	int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
	for(unsigned int i=0; i<images.size(); i++){
		EXPECT_TRUE_EX(ISFaceDetectPath(defaultDetTrackChannel, const_cast<char *>(images[i].data()), outRst, &len));
		if(len >= 1){
			detectedNum += 1;
			EXPECT_TRUE_EX(ISCalFaceInfoPath2(defaultDetTrackChannel, const_cast<char *>(images[i].data()), outRst, len, keyPoint, angle, kScore));
#ifdef WIN32
			string saveFaceInfoPath = faceInfoS + "\\" + getFileHeader(images[i].data()) + ".rec";
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
			string saveFaceInfoPath = faceInfoS + "/" + getFileHeader(images[i].data()) + ".rec";
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

	cout << "picture num of image directory: " << images.size() << endl;
	cout << "picture num detected face succ of image directory: " << detectedNum << endl;
	float percent = float(detectedNum)/images.size()*100;
	cout << "success rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "output detect result to: " << faceInfoS << endl;
	denominator = images.size();
}

TEST_F(ftISDetTrack, ISCalFaceInfoPath_MultiThread){
	string imgPath = GConfig::getInstance().getFaceInfoImgPath();
	unsigned int detectThreadNum = GConfig::getInstance().getDetectThreadNum();
	vector<string> images;
	listOutDirectoryFiles(imgPath, images);
	int imgNumPerThread = int(images.size()/detectThreadNum);

	cout << ">>Inputs <<" << endl;
	cout << "image directory: " << imgPath << endl;
	cout << "thread num: " << detectThreadNum << endl;
	cout << ">>Outputs<<" << endl;

	string faceInfoM = GConfig::getInstance().getFaceInfoMPath();
#ifdef WIN32
	faceInfoM = slashConvert(faceInfoM, '/', '\\');
	string command = "rd /s /q " + faceInfoM;
	system(command.c_str());
	command = "mkdir " + faceInfoM;
	system(command.c_str());
#endif
#ifdef LINUX
	rmDir(faceInfoM);
	mkdir(faceInfoM.data(), 0775);
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

	detectedNum = 0;
	vector<pthread_t> pThread(detectThreadNum);
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_create(&pThread[i], NULL, faceInfo, (void *)&image[i]));
	}

	void *retVal;
	for(unsigned int i=0; i<detectThreadNum; i++){
		EXPECT_TRUE(SUCC == pthread_join(pThread[i], &retVal));
	}

	cout << "picture num of image directory: " << images.size() << endl;
	cout << "picture num allocated to each thread: " << imgNumPerThread << endl;
	cout << "picture num detected face succ of image directory: " << detectedNum << endl;
	float percent = float(detectedNum)/images.size()*100;
	cout << "success rate: " << setiosflags(ios::fixed) << setprecision(2) << percent << "%" << endl;
	cout << "output detect result to: " << faceInfoM << endl;
	denominator = images.size();
}

TEST_F(ftISDetTrack, ISCalFaceInfoPath_OutResultCheck){
	string faceInfoS = GConfig::getInstance().getFaceInfoSPath();
	vector<string> recS;
	listOutDirectoryFiles(faceInfoS, recS);

	string faceInfoM = GConfig::getInstance().getFaceInfoMPath();
	vector<string> recM;
	listOutDirectoryFiles(faceInfoM, recM);

	cout << ">>Inputs <<" << endl;
	cout << "single thread detect result path: " << faceInfoS << endl;
	cout << "multi thread detect result path: " << faceInfoM << endl;
	cout << ">>Outputs<<" << endl;

	EXPECT_TRUE(recS.size()==recM.size());

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
	for(unsigned int i=0; i<recS.size(); i++){
#ifdef WIN32
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
#endif
#ifdef LINUX
		fS = fopen(recS[i].data(), "rb");
		fseek(fS, 0, SEEK_SET);
		fread(&lenS, sizeof(lenS), 1, fS);
		fread(outRstS, 4*sizeof(int)*lenS, 1, fS);
		fread(keyPointS, 6*sizeof(int)*lenS, 1, fS);
		fread(angleS, 3*sizeof(float)*lenS, 1, fS);
		fread(kScoreS, sizeof(float)*lenS, 1, fS);
		fclose(fS);

		fM = fopen(recM[i].data(), "rb");
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
				EXPECT_TRUE(angleS[s][t]==angleM[s][t]);
			}
		}
		for(int x=0; x<lenS; x++){
			EXPECT_TRUE(kScoreS[x]==kScoreM[x]);
		}
	}

	cout << "whether single thread or multi thread, the detect result(len/outResult/keyPoint/angle/kScore) by ISCalFaceInfoPath are the same" << endl;
}
