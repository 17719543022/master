#include "stdafx.h"
#include "ConFigHelper.h"
#include "ParamDef.h"
#include "Poco\Util\IniFileConfiguration.h"

ConFigHelper config;

ConFigHelper::ConFigHelper(void):
	_strImgPath(""),
	_strFeaPath(""),
	_strPcaFeaPath(""),
	_nMaxImgNum(10000)
{
}


ConFigHelper::~ConFigHelper(void)
{
}

int ConFigHelper::init()
{
	Poco::AutoPtr<Poco::Util::IniFileConfiguration> config = new Poco::Util::IniFileConfiguration("config.ini");
	_strImgPath = config->getString("imgPath");
	_strFeaPath = config->getString("feaPath");
	_strPcaFeaPath = config->getString("pcaFeaPath");

	_nMaxImgNum = config->getInt("maxImgNum");
	_nDetectThreadNum = config->getInt("detectThreadNum");
	_nGetFeaThreadNum = config->getInt("getFeaThreadNum");

	_nCompareThreadNum = config->getInt("compareThreadNum");
	_dCompareValue = config->getDouble("compareFaceValue");

	_nRecogniseThreadNum = config->getInt("recogniseThreadNum");
	_dRecogniseValue = config->getDouble("recogniseFaceValue");

	_strTextReport = config->getString("testReport");
	_strErrLog = config->getString("errLog");

	check();
	return 0;
}

void ConFigHelper::check()
{
	if(_nDetectThreadNum > MAXTHREADNUM)
	{
		_nDetectThreadNum = MAXTHREADNUM;
	}
	if(_nGetFeaThreadNum > MAXTHREADNUM)
	{
		_nGetFeaThreadNum = MAXTHREADNUM;
	}
	if(_nCompareThreadNum > MAXTHREADNUM)
	{
		_nCompareThreadNum = MAXTHREADNUM;
	}
	if(_nRecogniseThreadNum > MAXTHREADNUM)
	{
		_nRecogniseThreadNum = MAXTHREADNUM;
	}
}