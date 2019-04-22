#include "stdafx.h"
#include "FeatureImp.h"
#include "SDK\ISFeature.h"
#include "Helper.h"

FeatureImp::FeatureImp(void):
	_nFeatureChannel(-1),
	_sFeatureBuf(nullptr),
	_sPcaFeatureBuf(nullptr)
{
}


FeatureImp::~FeatureImp(void)
{
}

FeatureImp* FeatureImp::GetInstance()
{
	return new FeatureImp();
}

int FeatureImp::CreatureChannel()
{
	_nFeatureChannel = ISCreateFeatureChannel();
	if(_nFeatureChannel >= 0 )
	{
		_nFeatureLen = ISGetFeatureLength();
		_sFeatureBuf = new char[_nFeatureLen];
		_sPcaFeatureBuf = new char[_nFeatureLen / 4];
	}
	return _nFeatureChannel;
}

int FeatureImp::DestoryChannel()
{
	delete[] _sFeatureBuf;
	_sFeatureBuf = nullptr;
	int ret = ISDestroyFeatureChannel(_nFeatureChannel);
	return ret;
}

int FeatureImp::GetFeature(const char* imgData, int nLen)
{
	int ret = ISGetFeature(_nFeatureChannel, (char*)imgData, nLen, _sFeatureBuf);
	return ret;
}

int FeatureImp::GetPcaFeature()
{
	int ret = ISGetPcaFea(_nFeatureChannel, _sFeatureBuf, _sPcaFeatureBuf);
	return ret;
}

int FeatureImp::SaveFeature(const char* feaPath, const char* pcaFeaPath)
{
	int ret = help.writeFile(feaPath, _sFeatureBuf, _nFeatureLen);
	if(ret != 0)
	{
		return ret;
	}

	ret = help.writeFile(pcaFeaPath, _sPcaFeatureBuf, _nFeatureLen / 4);
	return ret;
}
