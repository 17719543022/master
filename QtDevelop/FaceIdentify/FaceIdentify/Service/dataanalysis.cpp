#include "dataanalysis.h"

#include <QDebug>
#include <algorithm>
#include <QString>
#include <QDateTime>
#include <QTextCodec>
#include <QByteArray>
#include <QDateTime>
#include <QPixmap>
#include <QBuffer>
#include <QPointer>
#include <QThread>

DataAnalysis::DataAnalysis():QObject (nullptr)
{
    QString videoStr;
    QString videoTypeStr;
    if("USB"==Constants::XmlSetting["VideoType"]){
        videoStr=QString("USB-Camera,%1,640,480,%2").arg(Constants::XmlSetting["VideoPort"]).arg(Constants::XmlSetting["VideoFrame"]);
        videoTypeStr=QString("usb");
    }
    qInfo()<<videoStr;

    QByteArray videobytes = videoStr.toLocal8Bit();
    strcpy(m_FISDKParam.sVideoParam, videobytes.constData());
    QByteArray videoTypebytes = videoTypeStr.toLocal8Bit();
    strcpy(m_FISDKParam.sourceType, videoTypebytes.constData());

    //是否是网络调用
    if("1"==Constants::XmlSetting["IdCardSrc"]){
        m_FISDKParam.nIsIdCardExit=0;
        m_httpServer=new HttpServer();
        connect(m_httpServer,&HttpServer::IDCardResponse,this,&DataAnalysis::OnIDCardResponse,Qt::DirectConnection);

    }
    else {
        m_FISDKParam.nIsIdCardExit=1;
    }

    m_OptimumParam.nMaxTrackFaceNum=1;
    m_OptimumParam.nOptTimeLength=Constants::XmlSetting["FaceOptTimeLength"].toInt();
    m_OptimumParam.nTrigTimeInterval=1000;
    m_OptimumParam.nDetFrmInterval=Constants::XmlSetting["DetFrmInterval"].toInt();
    m_OptimumParam.nMaxDetInterval=Constants::XmlSetting["MaxDetInterval"].toInt();
    m_OptimumParam.nEvalFrmFactor=Constants::XmlSetting["EvalFrmFactor"].toInt();
    m_OptimumParam.nPicType=PicRGB;
    m_OptimumParam.nTriggerType=TrigByEvent;
    m_OptimumParam.fDetRatio=Constants::XmlSetting["ImageSacle"].toFloat();
    m_OptimumParam.fQualityLimit=Constants::XmlSetting["FaceQualityLimit"].toFloat();
    m_OptimumParam.fKptCfdLimit=Constants::XmlSetting["FaceKptCfdLimit"].toFloat();
    m_OptimumParam.fAngleXLimit=Constants::XmlSetting["FaceAngleXLimit"].toFloat();
    m_OptimumParam.fAngleYLimit=Constants::XmlSetting["FaceAngleYLimit"].toFloat();
    m_OptimumParam.fAngleZLimit=Constants::XmlSetting["FaceAngleZLimit"].toFloat();


    int ret =CoreFIInit(&m_FISDKParam);
    if(ret!=0){
        throw std::runtime_error("CoreFIInit failed");
    }

    ret=CoreFISetOptParam(&m_OptimumParam);
    if(ret!=0){
        throw std::runtime_error("CoreFISetOptParam failed");
    }


}

DataAnalysis::~DataAnalysis()
{
    if(m_httpServer!=nullptr){
        //delete m_httpServer;
        m_httpServer=nullptr;
    }
    ReleaseDataAnalysis();
}

void DataAnalysis::RegistCallback()
{
    CoreFISetVideoDetectCB(VideoDetectCallback,this);
    CoreFISetIDCardResponseCB(IDCardResponseCallback,this,IDCardOnlineCallback,IDCardOfflineCallback);
}

void DataAnalysis::ReleaseDataAnalysis()
{
    CoreFIRelease();
}

void DataAnalysis::FacePhotographResult()
{
    FIResult fiResult;
    IDImageInfo idImageInfo;
    FaceIdentifyResult pFIResult;
    try {
        auto gbk =  QTextCodec::codecForName("gbk");

        idImageInfo.idImageType=2;
        QPixmap pixmap;
        pixmap.load(":/Images/photographIDtest.bmp");
        QByteArray bytearray;
        QBuffer buffer;
        buffer.open(QIODevice::ReadWrite);
        pixmap.save(&buffer,"BMP");
        bytearray.append(buffer.data());
        idImageInfo.idImageBMP=bytearray.data();
        idImageInfo.idImageBMPLen=bytearray.length();

        CoreFIIdentifyInputImg(&idImageInfo,&pFIResult);

        fiResult.idType=0;
        fiResult.name=tr("000000");
        fiResult.gender=tr("未知");
        fiResult.folk=tr("未知");
        fiResult.birthDay="";
        fiResult.code=QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz");
        fiResult.address="";
        fiResult.agency="";
        fiResult.expireStart=QDateTime::currentDateTime().toString("yyyyMMdd");
        fiResult.expireEnd=QDateTime::currentDateTime().toString("yyyyMMdd");;
        fiResult.isExpire=false;
        fiResult.prCode="";
        fiResult.nation="";
        fiResult.idVersion="";
        fiResult.agencyCode="";
        fiResult.idImageType=2;
        //fiResult.idImage
        fiResult.idImagePath="";

        if(pFIResult.liveImageLen!=0)
        {
            fiResult.liveImage=QImage(reinterpret_cast<uchar*>(pFIResult.liveImageRGB), pFIResult.liveImageWidth,pFIResult.liveImageHeight,3*pFIResult.liveImageWidth, QImage::Format_RGB888).rgbSwapped();
        }
        fiResult.liveImagePath="";
        if(pFIResult.liveFrameLen!=0)
        {
            fiResult.liveFrameImageJPG.loadFromData(reinterpret_cast<uchar*>(pFIResult.liveFrameImage),pFIResult.liveFrameLen);
        }
        fiResult.liveFrameImageJPGPath="";

        if(pFIResult.matchResult==2){
            fiResult.matchResult=2;
        }else {
            fiResult.matchResult=1;
        }

        fiResult.matchScore=0.0f;
        fiResult.liveImageAge=pFIResult.liveImageAge;
        fiResult.liveImageGender=gbk->toUnicode(pFIResult.liveImageGender);
        fiResult.matchTime=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        emit ResponseResult(fiResult);
        if("0"!=Constants::XmlSetting["Need1N"]){
            emit ResponseResultToClient(fiResult);
        }
        emit ResponseResultData(fiResult);

    } catch (std::exception &ex) {
        qCritical()<<ex.what();
    }
}

void DataAnalysis::IDCardResponseProcess(IDInfos *pIdInfos, FaceIdentifyResult *pFIResult, void *userData)
{
    try {
        auto dataAnalysis=static_cast<DataAnalysis*>(userData);
        auto gbk =  QTextCodec::codecForName("gbk");
        //如果身份证号不为空，且出生日期或性别为空，补全其信息
        QString code0=gbk->toUnicode(pIdInfos->code);
        QString birthDay0=gbk->toUnicode(pIdInfos->birthDay);
        QString gender0=gbk->toUnicode(pIdInfos->gender);
        if(!code0.isEmpty() && code0.length()==18){
            QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
            if(birthDay0.isEmpty()){
                QString str=code0.mid(6,8);
                if(Functions::isDigitStr(str)==0){
                    QByteArray ba=str.toLocal8Bit();
                    int len = qMin( int(ba.size()), int(sizeof(pIdInfos->birthDay))-1 );
                    memccpy(pIdInfos->birthDay,ba,0,size_t(len));
                    pIdInfos->birthDay[len]='\0';
                }
            }
            if(gender0.isEmpty()){ //性别通过身份证号码判断，第17位为奇数是男性，为偶数为女性
                QString str=code0.mid(16,1);
                if(Functions::isDigitStr(str)==0){
                    if(str.toInt()%2==1){
                        str="男";
                        QByteArray ba=str.toLocal8Bit();
                        int len = qMin( int(ba.size()), int(sizeof(pIdInfos->gender))-1 );
                        memccpy(pIdInfos->gender,ba,0,size_t(len));
                        pIdInfos->gender[len]='\0';
                    }else {
                        str="女";
                        QByteArray ba=str.toLocal8Bit();
                        int len = qMin( int(ba.size()), int(sizeof(pIdInfos->gender))-1 );
                        memccpy(pIdInfos->gender,ba,0,size_t(len));
                        pIdInfos->gender[len]='\0';
                    }
                }
            }
        }

        QString idgender=gbk->toUnicode(pIdInfos->gender);
        if(pFIResult->matchResult==0){
            if("女"==idgender)
            {
                float add=Constants::XmlSetting["FemaleScore"].toFloat();
                if(pFIResult->matchScore<Constants::XmlSetting["RecogThreshold"].toFloat() && pFIResult->matchScore>0.6f){
                    pFIResult->matchScore=pFIResult->matchScore+add;
                    if(pFIResult->matchScore>=0.85f)
                    {
                        pFIResult->matchScore=0.85f;
                    }
                }

            }
            if("1"==Constants::XmlSetting["AgeGenderFlag"]){
                if(!gbk->toUnicode(pIdInfos->gender).isEmpty() && !gbk->toUnicode(pIdInfos->birthDay).isEmpty()){
                    pFIResult->matchScore=FIResultWithAgeAndGender(pIdInfos,pFIResult);
                }
            }
        }
        FIResult fiResult;
        fiResult.idType=pIdInfos->idType;
        fiResult.name=gbk->toUnicode(pIdInfos->name);
        fiResult.gender=gbk->toUnicode(pIdInfos->gender);
        fiResult.folk=gbk->toUnicode(pIdInfos->folk);
        fiResult.birthDay=gbk->toUnicode(pIdInfos->birthDay);
        fiResult.code=gbk->toUnicode(pIdInfos->code);
        fiResult.address=gbk->toUnicode(pIdInfos->address);
        fiResult.agency=gbk->toUnicode(pIdInfos->agency);
        fiResult.expireStart=gbk->toUnicode(pIdInfos->expireStart);
        fiResult.expireEnd=gbk->toUnicode(pIdInfos->expireEnd);
        fiResult.prCode=gbk->toUnicode(pIdInfos->prCode);
        fiResult.nation=gbk->toUnicode(pIdInfos->nation);
        fiResult.idVersion=gbk->toUnicode(pIdInfos->idVersion);
        fiResult.agencyCode=gbk->toUnicode(pIdInfos->agencyCode);
        fiResult.idImageType=pIdInfos->imgInfo.idImageType;
        if(fiResult.idImageType==0){
            if(pIdInfos->imgInfo.idImageRGBLen!=0){
                fiResult.idImage=QImage(reinterpret_cast<uchar*>(pIdInfos->imgInfo.idImageRGB), pIdInfos->imgInfo.idImageWidth,pIdInfos->imgInfo.idImageHeight,3*pIdInfos->imgInfo.idImageWidth, QImage::Format_RGB888).rgbSwapped();
            }
        }else if (fiResult.idImageType==1) {
             if(pIdInfos->imgInfo.idImagePath!=nullptr && pIdInfos->imgInfo.idImagePath[0]!='\0'){
                fiResult.idImage=QImage(pIdInfos->imgInfo.idImagePath);
             }
        }
        else if (fiResult.idImageType==2) {
             if(pIdInfos->imgInfo.idImageBMPLen!=0){
                 fiResult.idImage.loadFromData(reinterpret_cast<uchar*>(pIdInfos->imgInfo.idImageBMP),pIdInfos->imgInfo.idImageBMPLen);
             }

        }

        fiResult.idImagePath="";


        if(pFIResult->liveImageLen!=0)
        {
            fiResult.liveImage=QImage(reinterpret_cast<uchar*>(pFIResult->liveImageRGB), pFIResult->liveImageWidth,pFIResult->liveImageHeight,3*pFIResult->liveImageWidth, QImage::Format_RGB888).rgbSwapped();
        }
        fiResult.liveImagePath="";
        if(pFIResult->liveFrameLen!=0)
        {
            fiResult.liveFrameImageJPG.loadFromData(reinterpret_cast<uchar*>(pFIResult->liveFrameImage),pFIResult->liveFrameLen);
        }
        fiResult.liveFrameImageJPGPath="";

        if(pFIResult->matchResult==1)
        {
            fiResult.matchResult=3;
            pFIResult->matchResult=3;
        }else if (pFIResult->matchResult==2) {
            fiResult.matchResult=2;
            pFIResult->matchResult=2;
        }else if (pFIResult->matchResult==0) {
            if(pFIResult->matchScore>=Constants::XmlSetting["RecogThreshold"].toFloat())
            {
                fiResult.matchResult=1;
                pFIResult->matchResult=1;
            }else {
                fiResult.matchResult=0;
                pFIResult->matchResult=0;
            }
        }else {
            fiResult.matchResult=-1;
            qCritical()<<QString("IDCardResponseCallback matchResult:其他错误情况");
        }

        if("长期"!=fiResult.expireEnd && fiResult.expireEnd!=nullptr && fiResult.expireEnd[0]!='\0'){
            QDate dt=QDate::fromString(fiResult.expireEnd,"yyyyMMdd");
            if(QDate::currentDate()>dt){
                fiResult.isExpire=true;
                pFIResult->matchResult=4;
            }
        }

        fiResult.matchScore=pFIResult->matchScore;
        fiResult.liveImageAge=pFIResult->liveImageAge;
        fiResult.liveImageGender=gbk->toUnicode(pFIResult->liveImageGender);
        fiResult.matchTime=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");


        emit dataAnalysis->ResponseResult(fiResult);
        if("0"!=Constants::XmlSetting["Need1N"]){
            emit dataAnalysis->ResponseResultToClient(fiResult);
        }
        emit dataAnalysis->ResponseResultData(fiResult);
    } catch (std::exception &ex) {
        qCritical()<<ex.what();
    }
}

DataAnalysis *DataAnalysis::instance()
{
    static DataAnalysis da;
    return &da;
}

void DataAnalysis::OnIDCardResponse(IDInfos *pIdInfos, MatchResultInfo *pMatchNetResp)
{
    IDImageInfo idImageInfo=pIdInfos->imgInfo;
    FaceIdentifyResult fiResult;
    CoreFIIdentifyInputImg(&idImageInfo,&fiResult);
    IDCardResponseProcess(pIdInfos,&fiResult,this);

    pMatchNetResp->status=0;

    pMatchNetResp->score=fiResult.matchScore;
    pMatchNetResp->matchResult=fiResult.matchResult;
    if(pMatchNetResp->matchResult!=2 && pMatchNetResp->matchResult!=3)
    {
        if(fiResult.liveImageLen!=0)
        {
            QImage livePhoto=QImage(reinterpret_cast<uchar*>(fiResult.liveImageRGB), fiResult.liveImageWidth,fiResult.liveImageHeight,3*fiResult.liveImageWidth, QImage::Format_RGB888).rgbSwapped();
            QByteArray imgData;
            if (!livePhoto.isNull()) {
              QBuffer buffer(&imgData);
              buffer.open(QIODevice::WriteOnly);
              livePhoto.save(&buffer, "JPG");
              buffer.close();
              pMatchNetResp->livePhotoStr=imgData.toBase64();
            }
        }
    }
}

void DataAnalysis::VideoDetectCallback(char *videoData,int dataLen, int videoWidth, int videoHeight, int faceNum, int facePos[][5], void *userData)
{
    Q_UNUSED(dataLen);
    try {
        auto dataAnalysis=static_cast<DataAnalysis*>(userData);
        if(videoWidth!=0 && videoHeight!=0){
            QImage image(reinterpret_cast<uchar*>(videoData), videoWidth,videoHeight,3*videoWidth, QImage::Format_RGB888);
            QVector<QRect> faceList;

            int fn=faceNum>Constants::MaxDetectFace?Constants::MaxDetectFace:faceNum;
            for(int i=0;i<fn;i++)
            {
                QRect rect(QPoint(facePos[i][0],facePos[i][1]),QPoint(facePos[i][2],facePos[i][3]));
                faceList<<rect;
            }
            emit dataAnalysis->VideoFrame(image,faceList);

        }else {
            qCritical()<<QString("VideoDetectCallback failed,videoWidth %1 videoHeight %2").arg(videoWidth).arg(videoHeight);
        }
    } catch (std::exception &ex) {
        qCritical()<<ex.what();
    }
}

void DataAnalysis::IDCardResponseCallback(IDInfos *pIdInfos, FaceIdentifyResult *pFIResult, void *userData)
{
    auto dataAnalysis=static_cast<DataAnalysis*>(userData);
    dataAnalysis->IDCardResponseProcess(pIdInfos,pFIResult,userData);
}

void DataAnalysis::IDCardOnlineCallback(void *userData)
{
    Q_UNUSED(userData);
}

void DataAnalysis::IDCardOfflineCallback(void *userData)
{
    Q_UNUSED(userData);
}

float DataAnalysis::FIResultWithAgeAndGender(IDInfos *pIdInfos, FaceIdentifyResult *pFIResult)
{
    float matchScore=pFIResult->matchScore;
    try {
        if(matchScore>=Constants::XmlSetting["RecogThreshold"].toFloat() && matchScore<=Constants::XmlSetting["AgeGenderThreshold"].toFloat()){
            auto gbk =  QTextCodec::codecForName("gbk");
            QString idgender=gbk->toUnicode(pIdInfos->gender);
            QString livegender=gbk->toUnicode(pFIResult->liveImageGender);
            float liveage=pFIResult->liveImageAge;
            float currentYear =QDateTime::currentDateTime().toString("yyyy").toFloat();
            char birthYearChr[5]={0};
            strncpy(birthYearChr,pIdInfos->birthDay,4);
            float birthYear=gbk->toUnicode(birthYearChr).toFloat();
            float idage=currentYear-birthYear;

            qInfo()<<QString("ID:%1 IDage:%2 IDgender:%3 Liveage:%4 Livegender:%5").arg(pIdInfos->code).arg(static_cast<double>(idage)).arg(idgender).arg(static_cast<double>(liveage)).arg(livegender);

            if("男"==idgender)
            {
                 if("Mal"==livegender)
                 {
                     if(liveage<idage-Constants::XmlSetting["AgeSpan"].toFloat() || liveage>idage+Constants::XmlSetting["AgeSpan"].toFloat()){
                         matchScore=Constants::XmlSetting["AgeScore"].toFloat();
                     }
                 }else {
                    matchScore=Constants::XmlSetting["GenderScore"].toFloat();
                }
            }else {
                if("Mal"!=livegender)
                {
                    if(liveage<idage-Constants::XmlSetting["AgeSpan"].toFloat() || liveage>idage+Constants::XmlSetting["AgeSpan"].toFloat()){
                        matchScore=Constants::XmlSetting["AgeScore"].toFloat();
                    }
                }else {
                   matchScore=Constants::XmlSetting["GenderScore"].toFloat();
               }
            }
        }
    }catch (std::exception &ex) {
        qCritical()<<ex.what();
        return matchScore;
    }
    qInfo()<<QString("ID:%1 beforeScore:%2 endScore:%3").arg(pIdInfos->code).arg(static_cast<double>(pFIResult->matchScore)).arg(static_cast<double>(matchScore));
    return matchScore;
}

