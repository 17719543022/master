#ifndef PARAMDEF_H
#define PARAMDEF_H

#include <QString>
#include <QImage>
#include <QDateTime>

typedef struct FIResult_s
{
    int idType;///<breif 身份证类型 0-国人身份证 1-外国人身份证
    QString name;///< brief 姓名
    QString gender;///< brief 性别
    QString folk;///< brief 名族
    QString birthDay;///< brief 出生日期
    QString code;///< brief 身份证号
    QString address;///< brief 地址
    QString agency;///< brief 发证机关
    QString expireStart;///< brief 有效期起
    QString expireEnd;///< brief 有效期止
    bool isExpire;///< brief 证件是否失效
    QString eName;///<breif 英文姓名
    QString prCode;///<breif 永久居住代码
    QString nation;///<breif 国籍或所在地区代码
    QString idVersion;///<breif 证件版本号
    QString agencyCode;///<breif 受理机关代码

    int		idImageType;//证件照类型
    QImage	idImage;//证件照
    QString	idImagePath;//证件照路径

    QImage liveImage;///<breif 现场照
    QString	liveImagePath;//现场照照路径

    QImage liveFrameImageJPG;///<breif 现场照全图 JPG格式
    QString liveFrameImageJPGPath; //现场照全图路径

    int matchResult;///<breif 人证比对结果 表示人证比对的几种状态  //0 验证失败   1 验证成功  2 现场照未检测到人脸 3 证件照未检测到人脸 4 证件失效
    float matchScore;///<breif 人证比对得分
    float liveImageAge;///<breif 现场照年龄
    QString liveImageGender;///<breif 现场照性别

    QString matchTime; //比对时间

    FIResult_s()
    {
        idType = 0;
        name="";
        eName="";
        gender="";
        folk="";
        birthDay="";
        code="";
        address="";
        agency="";
        expireStart="";
        expireEnd="";
        isExpire=false;
        prCode="";
        nation="";
        idVersion="";
        agencyCode="";

        idImageType = 0;
        //idImage;
        idImagePath = "";

        //liveImage;
        liveImagePath="";

        //liveFrameImageJPG;
        liveFrameImageJPGPath="";

        matchResult = -1;
        matchScore = 0.0f;
        liveImageAge = 0;
        liveImageGender="";
        matchTime="";
    }
}FIResult;

class FIResultData{
public:
    QString id;
    int passagewayId;
    int idType;///<breif 身份证类型 0-国人身份证 1-外国人身份证
    QString name;///< brief 姓名
    QString eName;///<breif 英文姓名
    QString gender;///< brief 性别
    QString folk;///< brief 名族
    QString birthDay;///< brief 出生日期
    QString code;///< brief 身份证号
    QString address;///< brief 地址
    QString agency;///< brief 发证机关
    QString expireStart;///< brief 有效期起
    QString expireEnd;///< brief 有效期止

    QString prCode;///<breif 永久居住代码
    QString nation;///<breif 国籍或所在地区代码
    QString idVersion;///<breif 证件版本号
    QString agencyCode;///<breif 受理机关代码

    int		idImageType;//证件照类型
    QImage	idImage;//证件照
    QString	idImagePath;//证件照路径

    QImage liveImage;///<breif 现场照
    QString	liveImagePath;//现场照照路径

    QImage liveFrameImageJPG;///<breif 现场照全图 JPG格式
    QString liveFrameImageJPGPath; //现场照全图路径
    float liveImageAge;///<breif 现场照年龄
    QString liveImageGender;///<breif 现场照性别

    int matchResult;///<breif 人证比对结果 表示人证比对的几种状态  //0 验证失败   1 验证成功  2 现场照未检测到人脸 3 证件照未检测到人脸 4 证件失效
    float matchScore;///<breif 人证比对得分
    float matchScoreThreshold;///<breif 识别分数阈值
    QString matchTime; //比对时间
};

class MatchResultInfo{
public:
    int status;///<breif 请求的总体状态：0，成功；1，网络连接错误；2，网络响应异常；3、请求图片异常。
    int matchResult;///<breif 人证比对结果 表示人证比对的几种状态  //0 验证失败   1 验证成功  2 现场照未检测到人脸 3 证件照未检测到人脸 4 证件失效
    float score;///<breif 人证比对得分
    QString livePhotoStr;///<breif 现场照ba64格式
};

#endif // PARAMDEF_H
