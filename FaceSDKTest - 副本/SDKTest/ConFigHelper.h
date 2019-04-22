#pragma once
#include <string>

class ConFigHelper
{
public:
	ConFigHelper(void);
	~ConFigHelper(void);

	int init();

private:
	void check();

public:
	std::string _strImgPath;	//图片位置
	std::string _strFeaPath;	//特征位置
	std::string _strPcaFeaPath;	//PCA特征位置
	int _nMaxImgNum;			//参与测试最大图片数量
	int _nDetectThreadNum;		//人脸检测并发线程（最大支持10）
	int _nGetFeaThreadNum;		//特征提取并发线程（最大支持10）
	//人脸对比
	int _nCompareThreadNum;		//并发线程（最大支持10）
	double _dCompareValue;		//对比阈值
	//识别
	int _nRecogniseThreadNum;	//并发线程（最大支持10）
	double _dRecogniseValue;	//识别阈值

	std::string _strTextReport;	//测试报告
	std::string _strErrLog;		//错误日志
};

extern ConFigHelper config;

