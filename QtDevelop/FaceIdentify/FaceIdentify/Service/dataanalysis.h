#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include "Common/constants.h"
#include "FaceIdentifySDK.h"
#include "ParamDefine.h"
#include "Common/paramdef.h"
#include "Service/httpserver.h"
#include "Service/httpclient.h"

#include <QDebug>
#include <QString>
#include <QByteArray>
#include <cstdint>
#include <QImage>

class DataAnalysis: public QObject
{
    Q_OBJECT
public:
     explicit DataAnalysis();
    ~DataAnalysis();
    void RegistCallback();
    void ReleaseDataAnalysis();
    void FacePhotographResult();
    static DataAnalysis* instance();

signals:
    void VideoFrame(const QImage& image,const QVector<QRect>& faceList);
    void ResponseResult(const FIResult& fiResult);
    void ResponseResultToClient(const FIResult& fiResult);
    void ResponseResultData(const FIResult& fiResult);

private:
    void OnIDCardResponse(IDInfos* pIdInfos, MatchResultInfo* pMatchNetResp);
    void IDCardResponseProcess(IDInfos* pIdInfos, FaceIdentifyResult* pFIResult,void *userData);
    float FIResultWithAgeAndGender(IDInfos* pIdInfos,FaceIdentifyResult* pFIResult);

    /// \breif 视频检测回调函数
    ///
    /// 返回视频检测相关值
    ///
    /// \param videoData[out]-图像数据rgb格式 videoLen[out]-图像字节长度 videoHeight[out]-图像高度
    /// \param videoWidth[out]-图像宽度 faceNum[out]-检测到的人脸个数 outResult[out]-人脸对应的位置
    /// \param userData[out]-用户信息
    static void STDCALL VideoDetectCallback(char *videoData, int dataLen,int videoWidth,int videoHeight,int faceNum,int facePos[][5],void *userData);

    /// \breif 读卡器响应后人证比对结果回调函数
    ///
    /// 读卡器响应回调，设置该回调函数后身份证读卡器读取数据后自动响应，返回人证比对结果,证件信息，现场照信息
    /// \param pIdInfos,[OUT],证件信息
    /// \param faceIdentifyResult[out]-人证比对结果返回
    /// \param userData[out]-用户信息
    static void STDCALL IDCardResponseCallback(IDInfos* pIdInfos, FaceIdentifyResult* pFIResult,void *userData);

    /// \brief 读卡器上线事件
    /// \param userData[out]-用户信息
    static void STDCALL  IDCardOnlineCallback(void *userData);
    /// \brief 读卡器下线事件
    /// \param userData[out]-用户信息
   static void STDCALL  IDCardOfflineCallback(void *userData);



   FISDKParam  m_FISDKParam;
   OptimumParam m_OptimumParam;
   HttpServer* m_httpServer;
};
Q_DECLARE_METATYPE(QVector<QRect>)
Q_DECLARE_METATYPE(FIResult)
#endif // DATAANALYSIS_H
