#ifndef ISFeature_H
#define ISFeature_H


#include "ISConfig.h"


#if defined (__cplusplus)
extern "C" {
#endif


	///@brief
	///创建特征提取通道，以后相关操作作为参数传入
	///@return
	///-1 失败，0...N 成功
IS_API int ISCreateFeatureChannel(bool AgeGender = true,bool Glasses = true,bool Smile = true,bool Expression = true,bool Beauty = true);

	///@brief
	///销毁
	///@param
	///channel-ISCreateFeatureChannel返回值
IS_API int ISDestroyFeatureChannel(int channel);

	///@brief
	///返回单个模板字节长度
IS_API int ISGetFeatureLength();

	///@brief
	///提取特征，返回传入图片最中间人脸的特征
	///@param
	///channel-会话句柄
	///imgData-图片数据
	///imgLen-图片长度
	///outFeature-用于保存返回的特征数据(ISGetFeatureLength函数返回长度的缓冲区)
IS_API int ISGetFeature(int channel,char *imgData,int imgLen,char *outFeature,float KPtScore=0.5);

    ///@brief
	///提取特征，返回传入图片最中间人脸的特征
	///@param
	///channel-会话句柄
	///imgPath-图片路径
	///outFeature-用于保存返回的特征数据(ISGetFeatureLength函数返回长度的缓冲区)
IS_API int ISGetFeaturePath(int channel,char *imgPath,char *outFeature,float KPtScore=0.5);

	///@brief
	///提取特征，返回传入图片最中间人脸的特征
	///@param
	///channel-会话句柄
	///imgData-图片数据
	///imgLen-图片长度
	///outFeature-用于保存返回的特征数据(swGetFeatureLength函数返回长度的缓冲区)
IS_API int ISGetFeatureRgb(int channel, char *imgData, int imgLen, int imgWidth, int imgHeight, char *outFeature,float KPtScore=0.5);

	///@brief
	///提取特征，应用将图片中对应人脸的位置作为参数传给系统提取每个
	///人脸特征并返回
	///@param
	///param-图片中所有人脸位置二维数组(left,top,right,bottom)
    ///facenum-图片中人脸个数
	///outFeature-人脸个数乘以  单个特征模板字节长度的缓冲区
IS_API int ISGetFeatureWithFacePos(int channel,char *imgData,int imgLen,int param[][4],int facenum,char *outFeature);

    ///@brief
	///提取特征，应用将图片中对应人脸的位置作为参数传给系统提取每个
	///人脸特征并返回
	///@param
	///param-图片中所有人脸位置二维数组(left,top,right,bottom)
    ///facenum-图片中人脸个数
	///outFeature-人脸个数乘以  单个特征模板字节长度的缓冲区
IS_API int ISGetFeatureWithFacePosPath(int channel,char *imgPath,int param[][4],int facenum,char *outFeature);

	///@brief
	///提取特征，应用将图片中对应人脸的位置作为参数传给系统提取每个
	///人脸特征并返回
	///@param
	///param-图片中所有人脸位置二维数组(left,top,right,bottom)
    ///facenum-图片中人脸个数
	///outFeature-人脸个数乘以  单个特征模板字节长度的缓冲区
IS_API int ISGetFeatureWithFacePosRgb(int channel, char *imgData, int imgLen, int imgWidth, int imgHeight, int param[][4], int facenum, char *outFeature);

	///@brief
	///特征融合，最多传入十个特征
	///@param
	///feature-需要融合的特征集
	///weight-特征集的权重
	///count-实际传入特征个数
	///outFeature-融合后的特征
IS_API int ISMergeFeature(char *feature[10], float weight[10], int count, char *outFeature);

    ///@brief
    ///返回对输入的2048维特征进行Pca
IS_API int ISGetPcaFea(int channel,char* fea_Org,char* fea_Pca);

	///@brief
	///预测年龄性别
	///@param
	///feature-传入提取到的人脸特征
	///age-返回的年龄
	///gender-返回的性别字符串(Female or Male)
IS_API int ISpredictAgeGender(int channel,char *feature,float* age,char *gender);

	///@brief
	///返回当前SDK  能够创建的特征提取器最大通道数
IS_API int ISGetMaxFeatureChannel();

	///@brief
	///返回当前SDK  特征提取器信息
IS_API const char* ISGetFeatureVersionInfo();
	

#if defined (__cplusplus)
}
#endif


#endif


