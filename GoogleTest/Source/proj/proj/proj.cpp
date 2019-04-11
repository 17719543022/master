// proj.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <gtest/gtest.h>
#include <iostream>
#include "common.h"
#include "sdk_error_code.h"
#include "log_format.h"
#include "opencv.hpp"
#include "io.h"
#include <cstring>
using namespace std;
using namespace cv;

TEST(face,shouldGivenPictureHasMoreThan15FacesBeDetected)
{
	char *imgPath = "beauty.jpg";
	int len = 0;
	int outResult[50][4] = {0};

	int channel = ISCreateDetTrackChannel(20, 5000, 0);
	int det = ISFaceDetectPath(channel,imgPath,outResult,&len);

	ISDestroyDetTrackChannel(channel);
	EXPECT_TRUE(len >= 15);
}

TEST(face,shouldSelfieAndIdCardBeComparedWithMustSimilarity)
{
	char feature1[8196],feature2[8196];
	getFeature("idCard.jpg",feature1);
	getFeature("selfie.jpg",feature2);

	float score = 0;
	int similarityChannelId = ISCreateCompareChannel();
	ISCompare(similarityChannelId,feature1,feature2,&score);

	ISDestroyCompareChannel(similarityChannelId);
	cout<<"ISCompare Score:"<<score<<endl;
	EXPECT_TRUE(score >= 0.9);
}

TEST(face,shouldIdCardAndLiveBatchCompareSuccess)
{
	const char dirRoot[200]="E:\\liuyong\\人证1比1\\人证1比1\\";
	char dirToUse[200]="\0";

	//遍历dir目录变量下的所有目录
	_finddata_t dataDir;
	strcpy(dirToUse,dirRoot);
	intptr_t hDir = _findfirst(strcat(dirToUse,"*.*"), &dataDir);
	EXPECT_TRUE(hDir != -1);

	do{
		if (strcmp(dataDir.name, ".") == 0 || strcmp(dataDir.name, "..") == 0)
		{
			continue;
		}
		else
		{
			{
				//遍历dir目录下每个子目录下的所有文件
				_finddata_t dataFile;
				cout<<dirRoot;
				strcpy(dirToUse,dirRoot);
				intptr_t hFile = _findfirst(strcat(strcat(dirToUse,dataDir.name),"\\*.*"),&dataFile);
				EXPECT_TRUE(hFile != -1);
				cout<<dataDir.name<<"\\"<<endl;

				char feature1[8196],feature2[8196];
				strcpy(dirToUse,dirRoot);
				strcat(strcat(dirToUse,dataDir.name),"\\idcard.jpg");
				getFeature(dirToUse,feature1);

				do{
					if(strcmp(dataFile.name, ".") == 0 || strcmp(dataFile.name, "..") == 0 || strcmp(dataFile.name,"idcard.jpg")==0)
					{
						continue;
					}
					else
					{
						strcpy(dirToUse,dirRoot);
						strcat(strcat(strcat(dirToUse,dataDir.name),"\\"),dataFile.name);
						getFeature(dirToUse,feature2);

						float score = 0;
						int similarityChannelId = ISCreateCompareChannel();
						ISCompare(similarityChannelId,feature1,feature2,&score);
						ISDestroyCompareChannel(similarityChannelId);

						cout<<"\tidcard.jpg + "<<dataFile.name<<" = Compare Score: "<<score<<endl;
					}
				}while(_findnext(hFile,&dataFile)==0);

				_findclose(hFile);
			}
		}
	} while (_findnext(hDir, &dataDir) == 0);

	_findclose(hDir);

	cout<<"ISGetDetTrackVersionInfo(): "<<ISGetDetTrackVersionInfo()<<endl;
	cout<<"ISGetFeatureVersionInfo(): "<<ISGetFeatureVersionInfo()<<endl;
	cout<<"ISGetCompareVersionInfo(): "<<ISGetCompareVersionInfo()<<endl;
}

TEST(face,shouldMatrixBeCaculatedSuccessWhenReview)
{
	const char dirA[200]="E:\\liuyong\\复核\\复核\\A";
	const char dirB[200]="E:\\liuyong\\复核\\复核\\B";
	char dirAUse[200];
	char dirBUse[200];
	char feature1[8196];
	char feature2[8196];

	//遍历A目录下的所有图片
	_finddata_t dataA;
	strcpy(dirAUse,dirA);
	intptr_t hA = _findfirst(strcat(dirAUse,"\\*.*"), &dataA);
	EXPECT_TRUE(hA != -1);

	do{
		if (strcmp(dataA.name, ".") == 0 || strcmp(dataA.name, "..") == 0)
		{
			continue;
		}
		else
		{
			{
				//对A目录的每张图片同B目录的所有图片做compare运算
				strcpy(dirAUse,dirA);
				strcat(strcat(dirAUse,"\\"),dataA.name);
				memset(feature1,0,8192);
				getFeature(dirAUse,feature1);
				cout<<dirAUse<<"\t";

				_finddata_t dataB;
				strcpy(dirBUse,dirB);
				intptr_t hB = _findfirst(strcat(dirBUse,"\\*.*"),&dataB);
				EXPECT_TRUE(hB != -1);

				do{
					if(strcmp(dataB.name, ".") == 0 || strcmp(dataB.name, "..") == 0)
					{
						continue;
					}
					else
					{
						strcpy(dirBUse,dirB);
						strcat(strcat(dirBUse,"\\"),dataB.name);
						memset(feature2,0,8192);
						getFeature(dirBUse,feature2);

						float score = 0;
						int similarityChannelId = ISCreateCompareChannel();
						ISCompare(similarityChannelId,feature1,feature2,&score);
						ISDestroyCompareChannel(similarityChannelId);

						if(feature2[0]==0&&feature2[100]==0&&feature2[1000]==0)
						{
							cout<<"NoFace"<<"\t";
						}
						else
						{
							cout<<score<<"\t";
						}
					}
				}while(_findnext(hB,&dataB)==0);

				_findclose(hB);
				cout<<endl;
			}
		}
	} while (_findnext(hA, &dataA) == 0);

	_findclose(hA);
}

/*
TEST(face,shouldTwoPicturesOfASamePersonBeDetectedWithMustSimilarity)
{
	int detChannelId = ISCreateDetTrackChannel(30,1000,2);
	int featureChannelId = ISCreateFeatureChannel(0,0,0,0,0);
	int similarityChannelId = ISCreateCompareChannel();
	int feaLen = ISGetFeatureLength();
	printf("获取当前特征格式的长度：%d\n",feaLen);
	int facenum = 0;
	////////////////////////////////////////////////////////////////////////////////////////
	Mat image = imread("1.jpg",1);
	int outRst[50][4];
	int outLength;
	const char *version;
	version = ISGetDetTrackVersionInfo();
	cout<<"version: "<<version<<endl;

	int rtn = ISFaceDetectRgb(detChannelId,(char*)image.data,image.rows*image.cols*3,image.cols,image.rows,outRst,&outLength);

	char *imgData[100];
	int imgLen[100];
	int imgWidth[100];
	int imgHeight[100];
	int facePos[400][4];
	int count = 0;
	Mat show = image.clone();
	for(int i=0;i<outLength;i++)
	{
		cout<<"outRst: "<<outRst[i][0]<<" "<<outRst[i][1]<<" "<<outRst[i][2]<<" "<<outRst[i][3]<<endl;
		cout<<"area: "<<(outRst[i][2]-outRst[i][0])*(outRst[i][3]-outRst[i][1])<<endl;
		for(int n=0;n<4;n++)
			facePos[i][n] = outRst[i][n];

		Rect rect = Rect(facePos[i][0],facePos[i][1],facePos[i][2]-facePos[i][0]+1,facePos[i][3]-facePos[i][1]+1);
		//图形先没有绘制出来，等到imshow的时候呈现出来。
		cv::rectangle(show,rect,Scalar(0,0,255));

		imgData[i] = (char*)malloc(image.rows*image.cols*3);
		memcpy(imgData[i],image.data,image.rows*image.cols*3);

		imgLen[i] = image.rows*image.cols*3;
		imgWidth[i] = image.cols;
		imgHeight[i] = image.rows;		
		count++;
	}
	imshow("show",show);
	waitKey(500);
	///////////////////////////////////////////////////////////////////////////////////////
	//测试两种提取特征的方式
	Mat image1 = imread("liuyifei.png",1);
	vector<unsigned char> buff; 
	vector<int> param = vector<int>(2); 
	param[0] = CV_IMWRITE_PNG_COMPRESSION; 
	param[1] = 60; //default(3) 0-9. 
	cv::imencode(".png",image1,buff,param); 
	char* img1 = (char*)malloc(sizeof(uchar)*buff.size());
	for(unsigned int i=0;i<buff.size();i++)
	{
		img1[i]=(char)buff[i];
	}
	int img1Len = buff.size();
	int outResult[50][4];
	int outLen;
	Mat show1 = image1.clone();

	int rt = ISFaceDetectRgb(detChannelId,(char*)image1.data,image1.rows*image1.cols*3,image1.cols,image1.rows,outResult,&outLen);
	for(int i=0;i<outLen;i++)
	{
		cout<<"outResult: "<<outResult[i][0]<<" "<<outResult[i][1]<<" "<<outResult[i][2]<<" "<<outResult[i][3]<<endl;
		for(int n=0;n<4;n++)
		{
			facePos[i][n] = outResult[i][n];
		}

		Rect rect1 = Rect(facePos[i][0],facePos[i][1],facePos[i][2]-facePos[i][0]+1,facePos[i][3]-facePos[i][1]+1);
		cv::rectangle(show1,rect1,Scalar(0,0,255));

	}
	imshow("show",show1);
	waitKey(300);

	cout<<"Detection: "<<endl;
	for(int i=0;i<outLen;i++)
	{
		int pos[4] = {0};
		for(int n=0;n<4;n++)
		{
			pos[n] = outResult[i][n];
		}

		cout<<"pos: "<<pos[0]<<' '<<pos[1]<<' '<<pos[2]<<' '<<pos[3]<<endl;
	}
	
	Mat image2 = imread("2.png",1);
	cv::imencode(".png",image2,buff,param); 
	char* img2 = (char*)malloc(sizeof(uchar)*buff.size());
	for(unsigned int i=0;i<buff.size();i++)
	{
		img2[i]=(char)buff[i];
	}
	int img2Len = buff.size();
	char *outFeature1 = (char*)malloc(feaLen*outLen);
	//传入人脸坐标提取特征
	ISGetFeatureWithFacePosRgb(featureChannelId,(char*)image1.data, image1.rows*image1.cols*3, image1.cols, image1.rows, outResult,outLen,outFeature1);

	char *outFeature11 = (char*)malloc(feaLen);
	char *outFeature12 = (char*)malloc(feaLen);
	memcpy(outFeature11,outFeature1,feaLen);
	memcpy(outFeature12,outFeature1+feaLen,feaLen);

	//提取特征，返回传入图片最大且满足关键点置信度（默认0.5，使用ISGetFeatureRgbEx可以自行设置）人脸的特征
	char *outFeature2 = (char*)malloc(feaLen);
	rtn = ISGetFeatureRgb(featureChannelId,(char*)image2.data, image2.rows*image2.cols*3, image2.cols,image2.rows,outFeature2);

	////////////////////////////////////////////////
	ISFaceDetectRgb(detChannelId,(char*)image2.data,image2.rows*image2.cols*3,image2.cols,image2.rows,outResult,&outLen);
	Rect rect2 = Rect(outResult[0][0],outResult[0][1],outResult[0][2]-outResult[0][0]+1,outResult[0][3]-outResult[0][1]+1);
	cv::rectangle(image2,rect2,Scalar(0,0,255));
	cv::imshow("2.png", image2);
	waitKey(10);
	////////////////////////////////////////////////

	// 1:1
	float outScore1,outScore2;
	ISCompare(similarityChannelId,outFeature11,outFeature12,&outScore1); // 同一人
	ISCompare(similarityChannelId,outFeature11,outFeature2,&outScore2); // 不同人
	cout<<"1:1"<<endl;
	printf("同一人outScore: %3f\n",outScore1);
	printf("不同人outScore: %3f\n",outScore2);

	EXPECT_TRUE(outScore1>0.9);
	EXPECT_TRUE(outScore2<0.6);
}
*/
int main(int argc,char **argv){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
