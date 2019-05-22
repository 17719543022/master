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

TEST_F(ftISFeature, whatFaceReturnsEarlierInOutResultAndWhatLater)
{
	char *imgPath = "beauty.jpg";
	int len = 0;
	int outRst[50][4] = {0};
	Mat image = imread(imgPath);

	char outFeature1[50][8192];
	getFeatureWithFacePosRgb(imgPath, outFeature1[0], outRst, &len);
	cout << "len = " << len << endl;

	fstream f;
	string saveRecPath = "beauty.rec";
	f.open(saveRecPath, ios::out | ios::binary);
	f.write(const_cast<char *>((char *)&len), sizeof(len));
	f.write(const_cast<char *>((char *)outRst[0]), sizeof(outRst[0])*len);
	f.close();
	f.clear();
}

TEST_F(ftISFeature, readAndShow)
{
	int len = 0;
	int outRst[50][4] = {0};

	Mat image = imread("beauty.jpg");
	fstream f;
	f.open("beauty.rec", ios::in | ios::binary);
	f.read(const_cast<char *>((char *)&len), sizeof(len));
	f.read(const_cast<char *>((char *)outRst[0]), sizeof(outRst[0])*len);
	f.clear();
	f.close();

	imCommonShow("beauty.jpg", image, outRst, len);
	waitKey(3000);
}