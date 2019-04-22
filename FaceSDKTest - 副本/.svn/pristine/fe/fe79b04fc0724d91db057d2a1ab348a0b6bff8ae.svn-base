#ifndef ISCompare_H
#define ISCompare_H


#include "ISConfig.h"


#if defined (__cplusplus)
extern "C" {
#endif


	///@brief
	///创建相似度比较通道，以后相关操作作为参数传入
	///@return
	///-1 失败，0...N 成功
IS_API int ISCreateCompareChannel();

	///@brief
	///销毁
	///@param
	///channel-ISCreateCompareChannel返回值
IS_API int ISDestroyCompareChannel(int channel);

	///@brief
	///返回两个特征值的相似度
IS_API int ISCompare(int channel,char *feature1,char *feature2,float *outScore);

	///@brief
	///返回M和N个特征值的相似度矩阵
IS_API int ISCompareMN(int channel, char **featureM, int numM, char **featureN, int numN, float **outScore);

	///@brief
	///将N个特征值预先载入，可以节省比对时间
IS_API int ISCompareMNfasterprep(int channel, char **featureN, int numN);

	///@brief·
	///返回M和N个特征值的相似度矩阵，需要先使用ISCompareMNfasterprep载入N个特征值
IS_API int ISCompareMNfaster(int channel, char **featureM, int numM, float **outScore);

	///@brief
	///返回当前SDK  能够创建的特征提取器最大通道数
IS_API int ISGetMaxCompareChannel();

	///@brief
	///返回当前SDK  特征提取器信息
IS_API const char* ISGetCompareVersionInfo();
	

#if defined (__cplusplus)
}
#endif


#endif


