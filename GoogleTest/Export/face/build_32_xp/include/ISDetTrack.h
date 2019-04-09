#ifndef ISDetection_H
#define ISDetection_H


#include "ISConfig.h"
#include <vector>


#if defined (__cplusplus)
extern "C" {
#endif


	///@brief
	///创建人脸跟踪检测通道，以后相关操作作为参数传入
	///@param
	///faceMinSize-最小人脸像素值
	///faceMaxSize-最大人脸像素值
	///@return
	///-1 失败，0...N 成功
IS_API int ISCreateDetTrackChannel(int faceMinSize,int faceMaxSize);

	///@brief
	///销毁
	///@param
	///channel-mmCreateDetectChannel返回值
IS_API int ISDestroyDetTrackChannel(int channel);

	///@brief
	///检测人脸
	///返回人脸坐标二维数组(left,top,right,bottom),如outResult[0][0],outResult[0][1],outResult[0][2],outResult[0][3]
	 ///outLen为检测到的人脸数量
IS_API int ISFaceDetect(int channel,char *img,int imgLen,int outResult[][4],int *outLen);

    ///@brief
	///检测人脸
	///返回人脸坐标二维数组(left,top,right,bottom),如outResult[0][0],outResult[0][1],outResult[0][2],outResult[0][3]
	 ///outLen为检测到的人脸数量
IS_API int ISFaceDetectPath(int channel,char *imgPath,int outResult[][4],int *outLen);

	///@brief
	///检测人脸
	///返回人脸坐标二维数组(left,top,right,bottom),如outResult[0][0],outResult[0][1],outResult[0][2],outResult[0][3]
    ///outLen为检测到的人脸数量
IS_API int ISFaceDetectRgb(int channel, char *imgData, int imgLen, int imgWidth, int imgHeight, int outResult[][4],int *outLen);

	///@brief
	///检测并跟踪人脸
	///返回人脸坐标二维数组和person编号(left,top,right,bottom,id),如outResult[0][0],outResult[0][1],outResult[0][2],outResult[0][3],outResult[0][4]
    ///outLen为检测到的人脸数量
IS_API int ISFaceDetTrackRgb(int channel, char *imgData, int imgLen, int imgWidth, int imgHeight, int outResult[][4],int *outLen);

	///@brief
	///获取人脸信息
	///@param
	///pos-图片中对应人脸位置
	///faceNum-传入的人脸数量
	///keypoint-返回关键点坐标
	///angle-返回人脸角度（俯仰、水平、偏转）
	///kscore-关键点置信度
IS_API int ISCalFaceInfo(int channel, char *img, int imgLen,int pos[][4],int faceNum,int keypoint[][6],float angle[][3], float kscore[]);

    ///@brief
	///获取人脸信息
	///@param
	///pos-图片中对应人脸位置
	///faceNum-传入的人脸数量
	///keypoint-返回关键点坐标
	///angle-返回人脸角度（俯仰、水平、偏转）
	///kscore-关键点置信度
IS_API int ISCalFaceInfoPath(int channel, char *imgPath, int pos[][4],int faceNum,int keypoint[][6],float angle[][3], float kscore[]);

	///@brief
	///获取人脸信息
	///@param
	///pos-图片中对应人脸位置
	///faceNum-传入的人脸数量
	///keypoint-返回关键点坐标
	///angle-返回人脸角度（俯仰、水平、偏转）
	///kscore-关键点置信度
IS_API int ISCalFaceInfoRgb(int channel, char *imgData, int imgLen, int imgWidth, int imgHeight, int pos[][4],int faceNum,int keypoint[][6],float angle[][3], float kscore[]);

    ///@brief
	///获取人脸质量评估分数
	///@param
	///pos-图片中对应人脸位置
	///outScore-质量评估分数
IS_API int ISCalFaceQualityRgb(int channel, char **imgData, int imgLen[100], int imgWidth[100], int imgHeight[100], int pos[][4], int count, float *outScore);

	///@brief
	///返回当前SDK  能够创建的人脸检测器最大通道数
IS_API int ISGetMaxDetTrackChannel();

	///@brief
	///返回当前SDK  人脸检测器信息
IS_API const char* ISGetDetTrackVersionInfo();


#if defined (__cplusplus)
}
#endif


#endif


