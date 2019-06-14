#include "stdafx.h"
#include <gtest/gtest.h>
#include "testSuits.h"
#include "common.h"
#include "face_sdk.h"
#include "listOut.h"
#include "config.h"
#include <fstream>

TEST_F(ftError, inputImagesWithATooSmallSize){
	int outRst[50][4];
	int outLength;
	Mat image = imread("..\\..\\Data\\Error\\501.jpg");
	
	int detChannelId = DEFAULT_DET_TRACK_CHANNEL();
	EXPECT_TRUE(IMG_SIZE_TOO_SMALL == ISFaceDetectRgb(detChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength));
	DESTROY_DET_TRACK_CHANNEL(detChannelId);
}

TEST_F(ftError, inputImagesCanNotBeFound){
	int outRst[50][4];
	int outLength;
	Mat image = imread("..\\..\\Data\\Error\\50x.jpg");
	
	int detChannelId = DEFAULT_DET_TRACK_CHANNEL();
	EXPECT_TRUE(IMG_DATA_ERROR == ISFaceDetectRgb(detChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength));
	DESTROY_DET_TRACK_CHANNEL(detChannelId);
}

TEST_F(ftError, detectWithOutCreatingDectectChannel){
	int outRst[50][4];
	int outLength;
	Mat image = imread("..\\..\\Data\\Error\\50x.jpg");
	
	EXPECT_TRUE(UNKNOWN_ERROR == ISFaceDetectRgb(0, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength));
}

TEST_F(ftError, inputImagesDetectedNoFace){
	int outRst[50][4];
	int outLength;
	Mat image = imread("..\\..\\Data\\Error\\502.jpg");
	
	imCommonReadAndShow("..\\..\\Data\\Error\\502.jpg");

	int detChannelId = DEFAULT_DET_TRACK_CHANNEL();
	//ISFaceDetect return SUCC when the picture has no face, however, ISGetFeature returns DETECT_NO_FACE.
	EXPECT_TRUE(SUCC == ISFaceDetectRgb(detChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength));
	EXPECT_TRUE(0 == outLength);
	DESTROY_DET_TRACK_CHANNEL(detChannelId);
}

TEST_F(ftError, inputImagesGetNoFeature){
	Mat image = imread("..\\..\\Data\\Error\\502.jpg");

	vector<char> vec(8192);
	int defaultFeatureChannelId = PREDICT_FEATURE_CHANNEL();
	EXPECT_TRUE(DETECT_NO_FACE == ISGetFeatureRgb(defaultFeatureChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, vec.data()));
	DESTROY_FEATURE_CHANNEL(defaultFeatureChannelId);
}

TEST_F(ftError, whatImageLeadsToGetFeatureError){
	Mat img = imread("..\\..\\Data\\Error\\503.jpg");

	imCommonReadAndShow("..\\..\\Data\\Error\\503.jpg");

	vector<char> vec(8192);
	int defaultFeatureChannelId = PREDICT_FEATURE_CHANNEL();
	EXPECT_TRUE(GET_FEATURE_ERROR == ISGetFeatureRgb(defaultFeatureChannelId, (char *)img.data, img.rows*img.cols*3, img.cols, img.rows, vec.data()));
	DESTROY_FEATURE_CHANNEL(defaultFeatureChannelId);
}

//M*N overflows
TEST_F(ftError, whatIsCompareMNError){
	string pcaAPath = "..\\..\\Data\\Error\\pcaA";
	vector<string> pcaAs;
	listOutDirectoryFiles(pcaAPath, pcaAs);
	int pcaAs_size = pcaAs.size();
	string pcaBPath = "..\\..\\Data\\Error\\pcaB";
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

	int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
	EXPECT_TRUE(COMPARE_MN_ERROR == ISCompareMN(defaultCompareChannel, pcaA, pcaAs_size, pcaB, pcaBs_size, score));
	DESTROY_COMPARE_CHANNEL(defaultCompareChannel);
}