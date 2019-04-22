#pragma once
#include <vector>
class CompareImp
{
public:
	~CompareImp(void);

	static CompareImp* GetInstance();

	int CreateChannel();

	int DestoryChannel();

	int Compare(char* fea1,char* fea2, double& s);

	int Compare(int index1,int index2, double& s);

	int addFeature(char* fea, int feaLen);

	int releaseFeature();

	int importFeature();

	int Recognise(char **featureM, int numM, std::vector<int>& vecIndex, std::vector<float>& vecSource);

	int Recognise(int index, int& recogIndex, float& source);

protected:
	CompareImp(void);

private:
	int _nCompareChannel;
	std::vector<char*> _vecFeaN;
};

