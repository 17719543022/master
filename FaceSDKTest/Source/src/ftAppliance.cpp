#include "stdafx.h"
#include <gtest/gtest.h>
#include "common.h"
#include "sdk_error_code.h"
#include "log_format.h"

using namespace std;

TEST(ftAppliance,personAndIdCardCompareOfOneDirectory)
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

TEST(ftAppliance,reviewOfTwoSeparateDirectories)
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
				if(DETECT_NO_FACE == getFeatureWithFacePosRgb((dirA + "\\" + tA.name).data(),feature1[0]))
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
						if(DETECT_NO_FACE == getFeatureWithFacePosRgb((dirB + "\\" + tB.name).data(),feature2[0]))
						{
							cout<<setw(10)<<setiosflags(ios::left)<<"No Face";
							continue;
						}

						float score = 0;
						compare(feature1[0], feature2[0], &score);
						cout<<setw(10)<<setiosflags(ios::left)<<score;
					}
				}while(_findnext(hB, &tB)==0);

				_findclose(hB);
				cout<<endl;
			}
		}
	} while (_findnext(hA, &tA) == 0);

	_findclose(hA);
}
