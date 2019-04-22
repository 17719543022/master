#include "stdafx.h"
#include "CompareImp.h"
#include "SDK\ISCompare.h"


CompareImp::CompareImp(void):
	_nCompareChannel(-1)
{
}


CompareImp::~CompareImp(void)
{
	releaseFeature();
}

CompareImp* CompareImp::GetInstance()
{
	return new CompareImp();
}

int CompareImp::CreateChannel()
{
	_nCompareChannel = ISCreateCompareChannel();
	return _nCompareChannel;
}

int CompareImp::DestoryChannel()
{
	int ret = ISDestroyCompareChannel(_nCompareChannel);
	return ret;
}

int CompareImp::Compare(char* fea1, char* fea2, double& s)
{
	float source;
	int ret = ISCompare(_nCompareChannel, fea1, fea2, &source);
	s = source;
	return ret;
}

int CompareImp::Compare(int index1,int index2, double& s)
{
	if(index1 < _vecFeaN.size() && index2 < _vecFeaN.size())
	{
		float source;
		int ret = ISCompare(_nCompareChannel, _vecFeaN[index1], _vecFeaN[index2], &source);
		s = source;
		return ret;
	}
	
	return -1;
}

int CompareImp::addFeature(char* fea, int feaLen)
{
	char* ptr = new char[feaLen];
	memset(ptr, 0, feaLen);
	memcpy(ptr, fea, feaLen);
	_vecFeaN.push_back(ptr);
	return _vecFeaN.size();
}

int CompareImp::releaseFeature()
{
	for(int i = 0; i < _vecFeaN.size(); i++)
	{
		delete[] _vecFeaN[i];
	}

	_vecFeaN.clear();
	return 0;
}

int CompareImp::importFeature()
{
	int ret = ISCompareMNfasterprep(_nCompareChannel, _vecFeaN.data(), _vecFeaN.size());
	return ret;
}

int CompareImp::Recognise(char **featureM, int numM, std::vector<int>& vecIndex, std::vector<float>& vecSource)
{
	int N = _vecFeaN.size();
	std::vector<float*> _source;
	for(int i = 0; i < numM; i++)
	{
		float* ptr = new float[N];
		_source.push_back(ptr);
	}

	int ret = ISCompareMNfaster(_nCompareChannel, featureM, numM, _source.data());

	if(ret == 0)
	{
		for(int i = 0; i < numM; i++)
		{
			float v = 0.0;
			int index = -1;
			for(int j = 0; j < N; j++)
			{
				if(_source[i][j] - v > 0.0001)
				{
					v = _source[i][j];
					index = j;
				}
			}

			vecIndex.push_back(index);
			vecSource.push_back(v);
		}
	}

	for(int i = 0; i < _source.size(); i++)
	{
		delete[] _source[i];
	}

	return ret;
}

int CompareImp::Recognise(int index, int& recogIndex, float& source)
{
	int nFeaNSize = _vecFeaN.size();
	std::vector<float*> _source;
	float* ptr = new float[nFeaNSize];
	_source.push_back(ptr);
	

	int ret = ISCompareMNfaster(_nCompareChannel, &_vecFeaN[index], 1, _source.data());

	if(ret == 0)
	{
		source = 0.0;
		recogIndex = -1;
		for(int j = 0; j < nFeaNSize; j++)
		{
			if(_source[0][j] - source > 0.0001)
			{
				source = _source[0][j];
				recogIndex = j;
			}
		}
	}

	for(int i = 0; i < _source.size(); i++)
	{
		delete[] _source[i];
	}

	return ret;
}