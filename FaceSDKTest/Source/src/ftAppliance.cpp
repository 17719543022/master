#include "stdafx.h"
#include <gtest/gtest.h>
#include "common.h"
#include "sdk_error_code.h"
#include "log_format.h"
#include "timer.h"

using namespace std;

TEST(ftAppliance, personAndIdCardCompareOfOneDirectory)
{
	//需要进行人证对比的整个文件夹的路径
	string dirInput = "..\\..\\Images\\人证1比1";

	_finddata_t tFolder;
	intptr_t hFolder = _findfirst((dirInput + "\\*.*").data(), &tFolder);
	EXPECT_TRUE(hFolder != -1);

	do{
		if (strcmp(tFolder.name, ".") == 0 || strcmp(tFolder.name, "..") == 0)
		{
			continue;
		}

		//身份证照片只可能有一张人脸
		char feature1[8192];
		//实景照片检测到的人脸可能不止一张
		char feature2[5][8192];

		if(DETECT_NO_FACE == getFeatureWithFacePosRgb((dirInput + "\\" + tFolder.name + "\\idcard.jpg").data(), feature1))
		{
			cout<<(dirInput + "\\" + tFolder.name + "\\idcard.jpg").data()<<"No Face"<<endl;
			continue;
		}
		if(DETECT_NO_FACE == getFeatureWithFacePosRgb((dirInput + "\\" + tFolder.name + "\\live.jpg").data(), feature2[0]))
		{
			cout<<(dirInput + "\\" + tFolder.name + "\\live.jpg").data()<<"No Face"<<endl;
			continue;
		}

		float score = 0;
		compare(feature1, feature2[0], &score);

		//打印测试结果
		cout << (dirInput + "\\" + tFolder.name + "\\").data() << endl;
		cout << "\tidcard.jpg + " << "live.jpg" << " = Compare Score: " << score << endl;
	}
	while (_findnext(hFolder, &tFolder) == 0);

	_findclose(hFolder);
}

TEST(ftAppliance, reviewOfTwoSeparateDirectories)
{
	string dirA = "..\\..\\Images\\复核\\A";
	string dirB = "..\\..\\Images\\复核\\B";

	//实景照片检测到的人脸可能不止一张
	char feature1[5][8192];
	char feature2[5][8192];

	//遍历A目录下的所有图片
	_finddata_t tA;
	intptr_t hA = _findfirst((dirA + "\\*.*").data(), &tA);
	EXPECT_TRUE(hA != -1);

	do{
		if (strcmp(tA.name, ".") == 0 || strcmp(tA.name, "..") == 0)
		{
			continue;
		}
		else
		{
			{
				//对A目录的每张图片同B目录的每张图片做compare运算
				cout<<(dirA + "\\" + tA.name).data()<<endl;
				if(DETECT_NO_FACE == getFeatureWithFacePosRgb((dirA + "\\" + tA.name).data(), feature1[0]))
				{
					continue;
				}

				_finddata_t tB;
				intptr_t hB = _findfirst((dirB + "\\*.*").data(), &tB);
				EXPECT_TRUE(hB != -1);

				do{
					if(strcmp(tB.name, ".") == 0 || strcmp(tB.name, "..") == 0)
					{
						continue;
					}
					else
					{
						if(DETECT_NO_FACE == getFeatureWithFacePosRgb((dirB + "\\" + tB.name).data(), feature2[0]))
						{
							cout<<setw(10) << setiosflags(ios::left) << "No Face";
							continue;
						}

						float score = 0;
						compare(feature1[0], feature2[0], &score);
						cout << setw(10) << setiosflags(ios::left) << score;
					}
				}while(_findnext(hB, &tB)==0);

				_findclose(hB);
				cout << endl;
			}
		}
	} while (_findnext(hA, &tA) == 0);

	_findclose(hA);
}

TEST(ftAppliance, whatFaceReturnsEarlierInOutResultAndWhatLater)
{
	char *imgPath = "..\\..\\Images\\beauty.jpg";
	int len = 0;
	int outRst[50][4] = {0};
	Mat image = imread(imgPath);

	char outFeature1[50][8192];
	getFeatureWithFacePosRgb(imgPath, outFeature1[0], outRst, &len);

	imCommonShow("beauty.jpg", image, outRst, len);
	waitKey(3000);
	destroyAllWindows();
}

TEST(ftAppliance, convolutionOfAllFacesInOnePicture)
{
	char *imgPath = "..\\..\\Images\\beauty.jpg";
	int len = 0;
	int outRst[50][4] = {0};
	Mat image = imread(imgPath);

	char outFeature[50][8192];
	getFeatureWithFacePosRgb(imgPath, outFeature[0], outRst, &len);

	char **featureM;
	ALLOC_DOUBLE_STAR(len, 8192, char, featureM, M)
	for(int i=0; i<len; i++)
	{
		featureM[i] = outFeature[i];
		getPcaFea(featureM[0], featureM[0]);
	}

	char **featureN;
	ALLOC_DOUBLE_STAR(len, 8192, char, featureN, N)
	for(int i=0; i<len; i++)
	{
		featureN[i] = outFeature[i];
		getPcaFea(featureN[i], featureN[i]);
	}

	float **outScoreMN;
	ALLOC_DOUBLE_STAR(len, len, float, outScoreMN, S)
	compareMN(featureM, len, featureN, len, outScoreMN);

	for(int i=0; i<len; i++)
	{
		for(int j=0;j<len;j++)
		{
			cout << setw(10) << setiosflags(ios::left) << outScoreMN[i][j];
		}
		cout<<endl;
	}
}

TEST(ftAppliance, compareMNfasterWay)
{
	char *imgPath = "..\\..\\Images\\beauty.jpg";
	int len = 0;
	int outRst[50][4] = {0};
	Mat image = imread(imgPath);

	char outFeature[50][8192];
	getFeatureWithFacePosRgb(imgPath, outFeature[0], outRst, &len);

	char **featureM;
	ALLOC_DOUBLE_STAR(len, 8192, char, featureM, M)
	for(int i=0; i<len; i++)
	{
		featureM[i] = outFeature[i];
		getPcaFea(featureM[0],featureM[0]);
	}

	char **featureN;
	ALLOC_DOUBLE_STAR(len, 8192, char, featureN, N)
	for(int i=0; i<len; i++)
	{
		featureN[i] = outFeature[i];
		getPcaFea(featureN[i], featureN[i]);
	}

	float **outScoreMN;
	ALLOC_DOUBLE_STAR(len, len, float, outScoreMN, S)
	compareMNfaster(featureM, len, featureN, len, outScoreMN);

	for(int i=0; i<len; i++)
	{
		for(int j=0;j<len;j++)
		{
			cout << setw(10) << setiosflags(ios::left) << outScoreMN[i][j];
		}
		cout<<endl;
	}
}

TEST(ftAppliance, camera)
{
	VideoCapture cap = VideoCapture(0);
	Mat img;
	char tempStr[64];

	while(!isTimeOut(300))
	{
		cout << "enter while loop." << endl;
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
		calFaceInfoRgb((char *)img.data
						, img.rows*img.cols*3
						, img.cols
						, img.rows
						, outRst
						, &outLen
						, keyPoint
						, angle
						, kScore);

		float beauty;
		char glasses[20];
		char smile[20];
		char expression[20];
		float age;
		char gender[10];

		getFeatureAndPredict((char *)img.data
							, img.rows*img.cols*3
							, img.cols
							, img.rows
							, expression
							, glasses
							, smile
							, &age
							, gender
							, &beauty);
		cout << "getFeatureAndPredict invoke succ." << endl;

		/*
		 * 注意把这些putText放在最后执行，
		 * 否则，可能image被污染了之后还在进行提取特征等操作。
		 */
		sprintf_s(tempStr, "Angle: %.3f %.3f %.3f", angle[0][0], angle[0][1], angle[0][2]);
		putText(img, tempStr, cvPoint(10, 160), CV_FONT_HERSHEY_COMPLEX, 1.0, cvScalar(0, 0, 255));
		sprintf_s(tempStr, "kScore: %.3f", kScore[0]);
		putText(img, tempStr, cvPoint(10, 200), CV_FONT_HERSHEY_COMPLEX, 1.0, cvScalar(0, 0, 255));

		for (int i = 0; i < 3; i++)
		{
			circle(img, Point(cvRound(keyPoint[0][2*i]), cvRound(keyPoint[0][2*i+1])), 35, Scalar(0, 0, 255));
		}

		sprintf_s(tempStr,"%d %s %.3f", (int)age, gender, beauty);
		putText(img, tempStr, cvPoint(outRst[0][0], outRst[0][1]), CV_FONT_HERSHEY_COMPLEX, 1.0, cvScalar(0, 0, 255));
		putText(img, glasses, cvPoint(10, 40), CV_FONT_HERSHEY_COMPLEX, 1.0, cvScalar(0, 0, 255));
		putText(img, smile, cvPoint(10, 80), CV_FONT_HERSHEY_COMPLEX, 1.0, cvScalar(0, 0, 255));
		putText(img, expression, cvPoint(10, 120), CV_FONT_HERSHEY_COMPLEX, 1.0, cvScalar(0, 0, 255));

		imCommonShow("Tracking", img, outRst, outLen, 1, 500);
	}
}
#if 0
TEST(ftAppliance, record)
{
	//int dettrackChannelId = ISCreateDetTrackChannelEx(48,1000);
	int dettrackChannelId = ISCreateDetTrackChannel(48,1000, 0);
	//int featureChannelId = ISCreateFeatureChannelEx(1,1,1,1,1);
	int featureChannelId = ISCreateFeatureChannel(1,1,1,0,0);
	int compareChannelId = ISCreateCompareChannel();
	int cur_id=0;
	char label_str[256];
	int outlen;
	char *feature1;
	vector<string> KPscore;
	vector<string> KPoint;
	feature1 = (char*)malloc(2048*sizeof(float));
	float age;
	char gender[10];
	int count = 0;
	namedWindow("Tracking");
	VideoCapture capture;
	ifstream filestr;
	ofstream filelist;
	int frame_idx=0;
	filestr.open("test_video_list.txt");	//读取视频list
	filelist.open("viewed_video_list.txt"); //保存已经跑过的视频路径，用于崩溃后检查断在哪个视频
	char picpath1[1024]={0};
	while(!filestr.eof())
	{
		filestr.getline (picpath1,sizeof(picpath1));  
		if(picpath1[0]==0||picpath1[0]=='\n')
		{			
			continue;
		}
		if (!capture.open(picpath1))  {
			cout<<"failed to open the video"<<picpath1<<endl;
			continue;
		}
		count++;
		cout<<picpath1<<" "<<count<<endl;
		filelist<<picpath1<<endl;
		Size size;
		size.width  = (int)capture.get(CV_CAP_PROP_FRAME_WIDTH);
		size.height = (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT);
		Mat frame;
		Mat cur_image;
		int skipped_frames=0;
		capture.set(CV_CAP_PROP_POS_FRAMES, skipped_frames);	

		bool btracked=false;
		while(capture.grab()){
			capture.retrieve(frame);

			frame.copyTo(cur_image);

			// int nRet = ISFaceDetTrackRgb(dettrackChannelId,(char *)cur_image.data,cur_image.rows*cur_image.cols*3,cur_image.cols,cur_image.rows,outRST,&outlen);
			int outRST4[50][4];
			int KeyPoint[50][6];
			float angle[50][3];
			float kptscore[50];
			clock_t tdt1 = clock();
			int nRet = ISFaceDetectRgb(dettrackChannelId,(char *)cur_image.data,cur_image.rows*cur_image.cols*3,cur_image.cols,cur_image.rows,outRST4,&outlen);
			clock_t tdt2 = clock();
			cout<<"detect cost:"<<tdt2-tdt1<<endl;
			if(outlen==0)
			{
				cout<<"detect no face"<<endl;
			}
			else
			{
				//ISBlurQuaEvalRgb(dettrackChannelId, (char*)cur_image.data, cur_image.rows*cur_image.cols*3, cur_image.cols,cur_image.rows,outRST4,outlen,ClarityScore);

				clock_t td1 = clock();
				//int ret = ISCalFaceInfoRgb2(dettrackChannelId, (char*)cur_image.data, cur_image.rows*cur_image.cols*3, cur_image.cols,cur_image.rows, outRST4, outlen, KeyPoint, angle,kptscore);
				int ret = ISCalFaceInfoRgb(dettrackChannelId, (char*)cur_image.data, cur_image.rows*cur_image.cols*3, cur_image.cols,cur_image.rows, outRST4, outlen, KeyPoint, angle,kptscore);
				clock_t td2 = clock();
				for (int jj = 0; jj < 3; jj++)
				{
					circle(cur_image,Point(cvRound(KeyPoint[0][2*jj]),cvRound(KeyPoint[0][2*jj+1])),20,Scalar(255, 255, 0),3);
					//imwrite("save1.jpg",cur_image);
				}

				ISGetFeatureRgb(featureChannelId,(char *)cur_image.data,cur_image.cols*cur_image.rows*3,cur_image.cols,cur_image.rows,feature1);
				//imshow("Tracking",cur_image);
				if(cur_image.data!=NULL){
					namedWindow("My Image");
					imshow("My Image",cur_image);
					waitKey(0);
				}

				float beauty;
				char glasses[20];
				char smile[20];
				char expression[20];
				ISpredictExpression(featureChannelId,feature1,expression);
				ISpredictGlasses(featureChannelId,feature1,glasses);
				ISpredictSmile(featureChannelId,feature1,smile);
				ISpredictAgeGender(featureChannelId,feature1,&age,gender);
				ISpredictBeauty(featureChannelId,feature1,&beauty);
				// ISGetPcaFea(featureChannelId,feature1,feature1);
				// ISCompare(0,feature1,feature1,&beauty);
				if(strcmp(gender,"Male")==0)
				{
					sprintf_s(label_str,"%d M %.3f",(int)age,beauty);
				}
				else
				{
					sprintf_s(label_str,"%d W %.3f",(int)age,beauty);
				}
				//}
				putText(cur_image,label_str,cvPoint(outRST4[0][0],outRST4[0][1]),CV_FONT_HERSHEY_COMPLEX,1.0,cvScalar(0,0,255),2);
				putText(cur_image,glasses,cvPoint(10,40),CV_FONT_HERSHEY_COMPLEX,1.0,cvScalar(0,0,255));
				putText(cur_image,smile,cvPoint(10,70),CV_FONT_HERSHEY_COMPLEX,1.0,cvScalar(0,0,255));
				putText(cur_image,expression,cvPoint(10,110),CV_FONT_HERSHEY_COMPLEX,1.0,cvScalar(0,0,255));
				for(int i=0;i<outlen;i++)
				{
					Rect rect = Rect(outRST4[i][0],outRST4[i][1],outRST4[i][2]-outRST4[i][0]+1,outRST4[i][3]-outRST4[i][1]+1);
					rectangle(cur_image,rect,Scalar(0,0,255));
					// sprintf_s(label_str,"%.3f",ClarityScore[i]);
					// putText(cur_image,label_str,cvPoint(outRST[i][0],outRST[i][3]),CV_FONT_HERSHEY_COMPLEX,1.0,cvScalar(0,0,255),2);
				}
			}

			imshow("Tracking",cur_image);	
			waitKey(1);
		}
	}
}
#endif