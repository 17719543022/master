//#include <Windows.h>

#include <vector>
#include <time.h>
#include "opencv2/opencv.hpp"
#include "ISConfig.h"
#include "ISError.h"
#include "ISDetTrack.h"
#include "ISFeature.h"
#include "ISCompare.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/time.h>
using namespace std;
using namespace cv;
int main()
{
	cout<<"123"<<endl;
	//videoTest();
	//return 0;
	Mat image = imread("2.jpg",1);
	int detChannelId = ISCreateDetTrackChannel(48,1000,"./model");
	cout<<"detChannel"<<endl;
	int featureChannelId = ISCreateFeatureChannel("./model");
	cout<<"feature"<<endl;
	int similarityChannelId = ISCreateCompareChannel("./model");
	int feaLen = ISGetFeatureLength();
	int facenum = 0;
	////////////////////////////////////////////////////////////////////////////////////////
	Mat show = image.clone();
	int outRst[50][4];
	int outRst1[50][5];
	int outLength;
	int kpoint[50][6];
	float angle[50][3];
	float kscore[50];
	struct timeval temp_s,temp_e;
	gettimeofday(&temp_s,NULL);
	cout<<"detect begin"<<endl;
	int rtn = ISFaceDetectRgb(detChannelId,(char*)image.data,image.rows*image.cols*3,image.cols,image.rows,outRst,&facenum);
	ISCalFaceInfoRgb(detChannelId,(char*)image.data,image.rows*image.cols*3,image.cols,image.rows,outRst,facenum,kpoint,angle,kscore);
	for (int i =0;i<facenum;i++)
	{
		for(int jj=0;jj<3;jj++)
		{
			cv::circle(show,cv::Point(cvRound(kpoint[0][jj*2]),cvRound(kpoint[0][jj*2+1])),3,cv::Scalar(0,255,0),3);
		}
		
	}
	gettimeofday(&temp_e,NULL);
	double duration=((temp_e.tv_sec-temp_s.tv_sec)*1000000+(temp_e.tv_usec-temp_s.tv_usec))/1000;
	cout<<"detect big image duration: "<<duration<<endl;
	
	rtn = ISFaceDetTrackRgb(detChannelId,(char*)image.data,image.rows*image.cols*3,image.cols,image.rows,outRst1,&facenum);
	for (int i = 0; i< 20;i++)
	{
	rtn = ISFaceDetTrackRgb(detChannelId,(char*)image.data,image.rows*image.cols*3,image.cols,image.rows,outRst1,&facenum);
	if(rtn!=0)
	{
		cout<<rtn<<endl;
		//return rtn;
	}
	cout<<"facenum:"<<facenum<<endl;
	//if (facenum>50)
	//	facenum=50;
	char *imgData[100];
	int imgLen[100];
	int imgWidth[100];
	int imgHeight[100];
	float outScore[100];
	int *facePos[150];
	//int count = 0;
	
	//vector<string> facePosVec = split(string(outRst),"^");
	for(int i=0;i<facenum;i++)
	{
		facePos[i] = (int*)malloc(sizeof(int)*4);
		cout<<outRst1[i][0]<<" "<<outRst1[i][1]<<" "<<outRst1[i][2]<<" "<<outRst1[i][3]<<" "<<outRst1[i][4]<<endl;
			for(int n=0;n<4;n++)
			facePos[i][n] = outRst1[i][n];

		Rect rect = Rect(facePos[i][0],facePos[i][1],facePos[i][2]-facePos[i][0]+1,facePos[i][3]-facePos[i][1]+1);
		cv::rectangle(show,rect,Scalar(0,0,255));

		

	}
	imshow("show",show);
	waitKey(500);
	}
	

	////////////////////////////////////////////////////////////////////////////////////////

	time_t start = time(NULL);
	Mat image1 = imread("1.png",1);
	vector<unsigned char> buff; 
	vector<int> param = vector<int>(2); 
	param[0] = CV_IMWRITE_PNG_COMPRESSION; 
	param[1] = 60; //default(3) 0-9. 
	cv::imencode(".png",image1,buff,param); 
	char* img1 = (char*)malloc(sizeof(uchar)*buff.size());
	for(int i=0;i<buff.size();i++)
	{
		img1[i]=(char)buff[i];
	}
	int img1Len = buff.size();
	int outResult[50][4];
	int outLen;
	// ·µ»Ø¼ì²âÈËÁ³¶þÎ¬Êý×é(left,top,right,bottom)£¬
	//int rt = ISFaceDetect(detChannelId,img1,img1Len,outResult,&outLen);


        
	gettimeofday(&temp_s,NULL);
	int rt = ISFaceDetectRgb(detChannelId,(char*)image1.data,image1.rows*image1.cols*3,image1.cols,image1.rows,outResult,&outLen);
	gettimeofday(&temp_e,NULL);
	//rt = ISFaceDetTrackRgb(detChannelId,(char*)image1.data,image1.rows*image1.cols*3,image1.cols,image1.rows,outRst1,&outLen);
	duration=((temp_e.tv_sec-temp_s.tv_sec)*1000000+(temp_e.tv_usec-temp_s.tv_usec))/1000;
	cout<<"detection duration: "<<duration<<endl;

	//char* imgPath = "1.png";
	//int rt = ISFaceDetectPath(detChannelId,imgPath,outResult,100,&outLen);

	cout<<"Detection"<<endl;
		for(int i=0;i<outLen;i++)
	{
		int pos[4] = {0};
		for(int n=0;n<4;n++)
			pos[n] = outResult[i][n];

		cout<<pos[0]<<' '<<pos[1]<<' '<<pos[2]<<' '<<pos[3]<<endl;
		
	}
	

	Mat image2 = imread("2.png",1);
	cv::imencode(".png",image2,buff,param); 
	char* img2 = (char*)malloc(sizeof(uchar)*buff.size());
	for(int i=0;i<buff.size();i++)
	{
		img2[i]=(char)buff[i];
	}
	int img2Len = buff.size();

	
	char *outFeature1 = (char*)malloc(feaLen*outLen);
	ISGetFeatureWithFacePosRgb(featureChannelId,(char*)image1.data, image1.rows*image1.cols*3, image1.cols, image1.rows, outResult,outLen,outFeature1);
	char *outFeature11 = (char*)malloc(feaLen);
	char *outFeature12 = (char*)malloc(feaLen);
	memcpy(outFeature11,outFeature1,feaLen);
	memcpy(outFeature12,outFeature1+feaLen,feaLen);
	
	


	char *outFeature2 = (char*)malloc(feaLen);
	ISGetFeatureRgb(featureChannelId,(char*)image2.data, image2.rows*image2.cols*3, image2.cols,image2.rows,outFeature2);

	// 1:1
	float outScore1,outScore2;
	rtn = ISCompare(similarityChannelId,outFeature11,outFeature12,&outScore1); // Í¬Ò»ÈË
	cout<<"ISCompare:"<<rtn<<endl;
	rtn = ISCompare(similarityChannelId,outFeature11,outFeature2,&outScore2); // ²»Í¬ÈË
	cout<<"ISCompare:"<<rtn<<endl;
	cout<<"1:1"<<endl;
	cout<<outScore1<<' '<<outScore2<<endl;
	time_t end = time(NULL);
	// M:N
	int numM = 3;
	int numN = 2;
	char **featureM = new char*[numM];
	char **featureN = new char*[numN];
	float **outScoreMN = new float*[numM];
	for(int i=0;i<numM;i++)
	{
		outScoreMN[i] = new float[numN];
	}
	featureM[0] = outFeature11;
	featureM[1] = outFeature12;
	featureM[2] = outFeature2;
	featureN[0] = outFeature11;
	featureN[1] = outFeature2;
	ISGetPcaFea(featureChannelId,featureM[0],featureM[0]);
	ISGetPcaFea(featureChannelId,featureM[1],featureM[1]);
	ISGetPcaFea(featureChannelId,featureM[2],featureM[2]);
	ISGetPcaFea(featureChannelId,featureN[0],featureN[0]);
	ISGetPcaFea(featureChannelId,featureN[1],featureN[1]);
	ISCompareMN(similarityChannelId,featureM,numM,featureN,numN,outScoreMN);
	cout<<"M:N"<<endl;
	for(int i=0;i<numM;i++)
	{
		for(int j=0;j<numN;j++)
		{
			cout<<outScoreMN[i][j]<<" ";
		}
		cout<<endl;
	}
	ISCompareMNfasterprep(0,featureN,numN);
	ISCompareMNfaster(0,featureM,numM,outScoreMN);
	cout<<"M:N faster"<<endl;
		for(int i=0;i<numM;i++)
	{
		for(int j=0;j<numN;j++)
		{
			cout<<outScoreMN[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"1:1 cost:"<<end-start<<endl;
	//cout<<similarityChannelId<<" "<<featureChannelId<<" "<<detChannelId<<endl;
	while(1)
{
sleep(5000);
}

	return 1;
}


