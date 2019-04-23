#include "stdafx.h"
#include <gtest/gtest.h>
#include "common.h"
#include "sdk_error_code.h"
#include "log_format.h"

using namespace std;

TEST(face,shouldIdCardAndLiveBatchCompareSuccess)
{
	const char dirRoot[200]="..\\..\\..\\Images\\人证1比1\\";
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
}
