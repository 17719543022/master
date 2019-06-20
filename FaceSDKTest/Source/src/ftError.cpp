#include <gtest/gtest.h>
#include "testSuits.h"
#include "common.h"
#include "face_sdk.h"
#include "listOut.h"
#include "config.h"
#include <fstream>
#include "log_format.h"

TEST_F(ftError, inputImagesWithATooSmallSize){
	int outRst[50][4];
	int outLength;
	Mat image = imread("../../Data/Error/501.jpg");

	int detChannelId = DEFAULT_DET_TRACK_CHANNEL();
	EXPECT_TRUE(IMG_SIZE_TOO_SMALL == ISFaceDetectRgb(detChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength));
	DESTROY_DET_TRACK_CHANNEL(detChannelId);
}

TEST_F(ftError, inputImagesCanNotBeFound){
	int outRst[50][4];
	int outLength;
	Mat image = imread("../../Data/Error/50x.jpg");

	int detChannelId = DEFAULT_DET_TRACK_CHANNEL();
	EXPECT_TRUE(IMG_DATA_ERROR == ISFaceDetectRgb(detChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength));
	DESTROY_DET_TRACK_CHANNEL(detChannelId);
}

TEST_F(ftError, detectWithOutCreatingDectectChannel){
	int outRst[50][4];
	int outLength;
	Mat image = imread("../../Data/Error/50x.jpg");

	EXPECT_TRUE(UNKNOWN_ERROR == ISFaceDetectRgb(0, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength));
}

TEST_F(ftError, inputImagesDetectedNoFace){
	int outRst[50][4];
	int outLength;

	Mat image = imread("../../Data/Error/502.jpg");
	imCommonReadAndShow("../../Data/Error/502.jpg");

	int detChannelId = DEFAULT_DET_TRACK_CHANNEL();
	//ISFaceDetect return SUCC when the picture has no face, however, ISGetFeature returns DETECT_NO_FACE.
	EXPECT_TRUE(SUCC == ISFaceDetectRgb(detChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, outRst, &outLength));
#ifdef WIN32
	EXPECT_TRUE(0 == outLength);
#endif
#ifdef LINUX
	// "0 == outLength" in windows, but "1 == outLength" in linux.
	EXPECT_TRUE(1 == outLength);
#endif
	DESTROY_DET_TRACK_CHANNEL(detChannelId);
}

TEST_F(ftError, inputImagesGetNoFeature){
	Mat image = imread("../../Data/Error/502.jpg");

	vector<char> vec(8192);
	int defaultFeatureChannelId = PREDICT_FEATURE_CHANNEL();
#ifdef WIN32
	EXPECT_TRUE(DETECT_NO_FACE == ISGetFeatureRgb(defaultFeatureChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, vec.data()));
#endif
#ifdef LINUX
	// ISGetFeatureRgb returns DETECT_NO_FACE in windows, but SUCC in linux.
	EXPECT_TRUE(SUCC == ISGetFeatureRgb(defaultFeatureChannelId, (char*)image.data, image.rows*image.cols*3, image.cols, image.rows, vec.data()));
#endif
	DESTROY_FEATURE_CHANNEL(defaultFeatureChannelId);
}

TEST_F(ftError, whatImageLeadsToGetFeatureError){
	Mat img = imread("../../Data/Error/503.jpg");
	imCommonReadAndShow("../../Data/Error/503.jpg");

	vector<char> vec(8192);
	int defaultFeatureChannelId = PREDICT_FEATURE_CHANNEL();
	EXPECT_TRUE(GET_FEATURE_ERROR == ISGetFeatureRgb(defaultFeatureChannelId, (char *)img.data, img.rows*img.cols*3, img.cols, img.rows, vec.data()));
	DESTROY_FEATURE_CHANNEL(defaultFeatureChannelId);
}

//M*N overflows
TEST_F(ftError, whatIsCompareMNError){
	string pcaAPath = "../../Data/Error/pcaA";
	vector<string> pcaAs;
	listOutDirectoryFiles(pcaAPath, pcaAs);
	int pcaAs_size = pcaAs.size();
	string pcaBPath = "../../Data/Error/pcaB";
	vector<string> pcaBs;
	listOutDirectoryFiles(pcaBPath, pcaBs);
	int pcaBs_size = pcaBs.size();

#ifdef WIN32
	fstream fileA, fileB;
#endif
#ifdef LINUX
	FILE *fileA, *fileB;
#endif
	char pcaTemp[2048];
	char **pcaA;
	ALLOC_DOUBLE_STAR(pcaAs_size, 2048, char, pcaA, M)
	for(int j=0; j<pcaAs_size; j++){
#ifdef WIN32
		fileA.open(pcaAs[j], ios::in | ios::binary);
		fileA.seekg(0, ios::beg);
		fileA.read(pcaTemp, 2048);
		fileA.clear();
		fileA.close();
#endif
#ifdef LINUX
		fileA = fopen(pcaAs[j].data(), "rb");
		fseek(fileA, 0, SEEK_SET);
		fread(pcaTemp, 2048, 1, fileA);
		fclose(fileA);
#endif

		memcpy(pcaA[j], pcaTemp, 2048);
	}

	char **pcaB;
	ALLOC_DOUBLE_STAR(pcaBs_size, 2048, char, pcaB, N)
	for(int i=0; i<pcaBs_size; i++)
	{
#ifdef WIN32
		fileB.open(pcaBs[i], ios::in | ios::binary);
		fileB.seekg(0, ios::beg);
		fileB.read(pcaTemp, 2048);
		fileB.clear();
		fileB.close();
#endif
#ifdef LINUX
		fileB = fopen(pcaBs[i].data(), "rb");
		fseek(fileB, 0, SEEK_SET);
		fread(pcaTemp, 2048, 1, fileB);
		fclose(fileB);
#endif

		memcpy(pcaB[i], pcaTemp, 2048);
	}

	float **score;
	ALLOC_DOUBLE_STAR(pcaAs_size, pcaBs_size, float, score, S)

	int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
#ifdef WIN32
	EXPECT_TRUE(COMPARE_MN_ERROR == ISCompareMN(defaultCompareChannel, pcaA, pcaAs_size, pcaB, pcaBs_size, score));
#endif
#ifdef LINUX
	// ISCompareMN returns COMPARE_MN_ERROR in windows, but SUCC in linux.
	EXPECT_TRUE(SUCC == ISCompareMN(defaultCompareChannel, pcaA, pcaAs_size, pcaB, pcaBs_size, score));
#endif
	DESTROY_COMPARE_CHANNEL(defaultCompareChannel);
}
