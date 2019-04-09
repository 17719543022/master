#ifndef ISDetection_H
#define ISDetection_H


#include "ISConfig.h"
#include <vector>


#if defined (__cplusplus)
extern "C" {
#endif


	///@brief
	///�����������ټ��ͨ�����Ժ���ز�����Ϊ��������
	///@param
	///faceMinSize-��С��������ֵ
	///faceMaxSize-�����������ֵ
	///@return
	///-1 ʧ�ܣ�0...N �ɹ�
IS_API int ISCreateDetTrackChannel(int faceMinSize,int faceMaxSize,char *modelpath);

	///@brief
	///����
	///@param
	///channel-mmCreateDetectChannel����ֵ
IS_API int ISDestroyDetTrackChannel(int channel);

	///@brief
	///�������
	///�������������ά����(left,top,right,bottom),��outResult[0][0],outResult[0][1],outResult[0][2],outResult[0][3]
	 ///outLenΪ��⵽����������
IS_API int ISFaceDetect(int channel,char *img,int imgLen,int outResult[][4],int *outLen);

    ///@brief
	///�������
	///�������������ά����(left,top,right,bottom),��outResult[0][0],outResult[0][1],outResult[0][2],outResult[0][3]
	 ///outLenΪ��⵽����������
IS_API int ISFaceDetectPath(int channel,char *imgPath,int outResult[][4],int outResultLen,int *outLen);

	///@brief
	///�������
	///�������������ά����(left,top,right,bottom),��outResult[0][0],outResult[0][1],outResult[0][2],outResult[0][3]
    ///outLenΪ��⵽����������
IS_API int ISFaceDetectRgb(int channel, char *imgData, int imgLen, int imgWidth, int imgHeight, int outResult[][4],int *outLen);

	///@brief
	///��Ⲣ��������
	///�������������ά�����person���(left,top,right,bottom,id),��outResult[0][0],outResult[0][1],outResult[0][2],outResult[0][3],outResult[0][4]
    ///outLenΪ��⵽����������
IS_API int ISFaceDetTrackRgb(int channel, char *imgData, int imgLen, int imgWidth, int imgHeight, int outResult[][5],int *outLen);

	///@brief
	///��ȡ������Ϣ
	///@param
	///pos-ͼƬ�ж�Ӧ����λ��
	///faceNum-�������������
	///keypoint-���عؼ�������
	///angle-���������Ƕȣ�������ˮƽ��ƫת��
	///kscore-�ؼ������Ŷ�
IS_API int ISCalFaceInfo(int channel, char *img, int imgLen,int pos[][4],int faceNum,int keypoint[][6],float angle[][3], float kscore[]);

    ///@brief
	///��ȡ������Ϣ
	///@param
	///pos-ͼƬ�ж�Ӧ����λ��
	///faceNum-�������������
	///keypoint-���عؼ�������
	///angle-���������Ƕȣ�������ˮƽ��ƫת��
	///kscore-�ؼ������Ŷ�
IS_API int ISCalFaceInfoPath(int channel, char *imgPath, int pos[][4],int faceNum,int keypoint[][6],float angle[][3], float kscore[]);

	///@brief
	///��ȡ������Ϣ
	///@param
	///pos-ͼƬ�ж�Ӧ����λ��
	///faceNum-�������������
	///keypoint-���عؼ�������
	///angle-���������Ƕȣ�������ˮƽ��ƫת��
	///kscore-�ؼ������Ŷ�
IS_API int ISCalFaceInfoRgb(int channel, char *imgData, int imgLen, int imgWidth, int imgHeight, int pos[][4],int faceNum,int keypoint[][6],float angle[][3], float kscore[]);

    ///@brief
	///��ȡ����������������
	///@param
	///pos-ͼƬ�ж�Ӧ����λ��
	///outScore-������������
IS_API int ISCalFaceQualityRgb(int channel, char **imgData, int imgLen[100], int imgWidth[100], int imgHeight[100], int **pos, int count, float *outScore);

	///@brief
	///���ص�ǰSDK  �ܹ�������������������ͨ����
IS_API int ISGetMaxDetTrackChannel();

	///@brief
	///���ص�ǰSDK  �����������Ϣ
IS_API const char* ISGetDetTrackVersionInfo();


#if defined (__cplusplus)
}
#endif


#endif


