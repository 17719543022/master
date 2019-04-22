#pragma once
class FeatureImp
{
public:
	FeatureImp(void);
	~FeatureImp(void);

	static FeatureImp* GetInstance();

	int CreatureChannel();

	int DestoryChannel();

	int GetFeature(const char* imgData, int nLen);

	int GetPcaFeature();

	int SaveFeature(const char* feaPath, const char* pcaFeaPath);

private:
	int  _nFeatureChannel;
	int  _nFeatureLen;
	char* _sFeatureBuf;
	char* _sPcaFeatureBuf;
};

