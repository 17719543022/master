#include "common.h"
#include "testSuits.h"
#include <iostream>
#include "config.h"
#include "listOut.h"
#include "timer.h"
#include "log_format.h"
#include <fstream>
#include "stdio.h"

using namespace std;

TEST_F(ftAppliance, dumpVersionNo){
	cout<<"ISGetDetTrackVersionInfo(): "<<ISGetDetTrackVersionInfo()<<endl;
	cout<<"ISGetFeatureVersionInfo(): "<<ISGetFeatureVersionInfo()<<endl;
	cout<<"ISGetCompareVersionInfo(): "<<ISGetCompareVersionInfo()<<endl;
}

TEST_F(ftAppliance, ISGetFeatureLengthCheck){
	EXPECT_TRUE(8192 == ISGetFeatureLength());
}

TEST_F(ftAppliance, dumpConfigIni){
	GConfig::getInstance().dump();
}

TEST_F(ftAppliance, theGivenPictureHasMoreThan15FacesBeDetected){
	char *imgPath = "../../Data/Appliance/beauty.jpg";
	int len = 0;
	int outRst[50][4] = {0};

	int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
	EXPECT_TRUE(SUCC == ISFaceDetectPath(defaultDetTrackChannel, imgPath, outRst, &len));
	DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);

#ifdef WIN32
	EXPECT_TRUE(len == 16);
#endif
#ifdef LINUX
	// ISFaceDetectPath detects 16 faces in windows, but 18 faces in linux.
	EXPECT_TRUE(len == 18);
#endif
}

TEST_F(ftAppliance, whatFaceReturnsEarlierInOutResultAndWhatLater){
	char *imgPath = "../../Data/Appliance/beauty.jpg";

	imCommonReadAndShow(imgPath);
}

TEST_F(ftAppliance, personAndIdCardCompareOfOneDirectory){
	string dir = "../../Data/Appliance/one_to_one";
	string idcard = "idcard.jpg";
	string live = "live.jpg";
	vector<string> listCard;
	vector<string> listLive;

	listOutSubdirectoryFiles(dir, idcard, listCard);
	listOutSubdirectoryFiles(dir, live, listLive);

	//the idcard has one face at most
	char featureCard[8192];
	//the live can has more than one face
	char featureLive[5][8192];
	float score = 0;

	int defaultFeatureChannel = DEFAULT_FEATURE_CHANNEL();
	int defaultCompareChannel = DEFAULT_COMPARE_CHANNEL();
	for(unsigned int i=0; i<listCard.size(); i++){
		if(SUCC != ISGetFeaturePath(defaultFeatureChannel, const_cast<char *>(listCard[i].data()), featureCard))
		{
			cout << setw(52) << setiosflags(ios::right) << listCard[i].data() << " Has No Face" << endl;
			continue;
		}
		if(SUCC != ISGetFeaturePath(defaultFeatureChannel, const_cast<char *>(listLive[i].data()), featureLive[0]))
		{
			cout << setw(52) << setiosflags(ios::right) << listLive[i].data() << " Has No Face" << endl;
			continue;
		}

		ISCompare(defaultCompareChannel, featureCard, featureLive[0], &score);

		cout << setw(52) << setiosflags(ios::right) << listCard[i].data() << " + " << "live.jpg" << " = Compare Score: " << score << endl;
	}
	DESTROY_COMPARE_CHANNEL(defaultCompareChannel);
	DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);
}

TEST_F(ftAppliance, camera){
	VideoCapture cap = VideoCapture(0);
	Mat img;
	char tempStr[64];

	int defaultDetTrackChannel = DEFAULT_DET_TRACK_CHANNEL();
	int defaultFeatureChannel = DEFAULT_FEATURE_CHANNEL();
	while(!isTimeOut(300))
	{
		cap >> img;
		if(!img.data)
		{
			DBG_LOG("camera is disconnect!");
			continue;
		}

		int outRst[50][4];
		int outLen;
		int keyPoint[50][6];
		float angle[50][3];
		float kScore[50];
		int nRet = ISFaceDetectRgb(defaultDetTrackChannel, (char *)img.data, img.rows*img.cols*3, img.cols, img.rows, outRst, &outLen);
		int ret = ISCalFaceInfoRgb2(defaultDetTrackChannel, (char *)img.data, img.rows*img.cols*3, img.cols, img.rows, outRst, outLen, keyPoint, angle, kScore);

		float beauty;
		char glasses[20];
		char smile[20];
		char expression[100];
		float age;
		char gender[10];

		getFeatureAndPredict(defaultFeatureChannel
							, (char *)img.data
							, img.rows*img.cols*3
							, img.cols
							, img.rows
							, expression
							, glasses
							, smile
							, &age
							, gender
							, &beauty);

		/*
		 * putText is placed at end, to make sure that image is not changed.
		 */
#ifdef WIN32
		sprintf_s(tempStr, "Angle: %.3f %.3f %.3f", angle[0][0], angle[0][1], angle[0][2]);
		putText(img, tempStr, cvPoint(10, 160), CV_FONT_HERSHEY_COMPLEX, 1.0, cvScalar(0, 0, 255));
		sprintf_s(tempStr, "kScore: %.3f", kScore[0]);
		putText(img, tempStr, cvPoint(10, 200), CV_FONT_HERSHEY_COMPLEX, 1.0, cvScalar(0, 0, 255));
#endif

		for (int i = 0; i < 3; i++)
		{
			circle(img, Point(cvRound(keyPoint[0][2*i]), cvRound(keyPoint[0][2*i+1])), 35, Scalar(0, 0, 255));
		}

#ifdef WIN32
		sprintf_s(tempStr,"%d %s %.3f", (int)age, gender, beauty);
		putText(img, tempStr, cvPoint(outRst[0][0], outRst[0][1]), CV_FONT_HERSHEY_COMPLEX, 1.0, cvScalar(0, 0, 255));
		putText(img, glasses, cvPoint(10, 40), CV_FONT_HERSHEY_COMPLEX, 1.0, cvScalar(0, 0, 255));
		putText(img, smile, cvPoint(10, 80), CV_FONT_HERSHEY_COMPLEX, 1.0, cvScalar(0, 0, 255));
		putText(img, expression, cvPoint(10, 120), CV_FONT_HERSHEY_COMPLEX, 1.0, cvScalar(0, 0, 255));
#endif

		imCommonShow("Tracking", img, outRst, outLen, 1, 500);
	}
	DESTROY_FEATURE_CHANNEL(defaultFeatureChannel);
	DESTROY_DET_TRACK_CHANNEL(defaultDetTrackChannel);
}
