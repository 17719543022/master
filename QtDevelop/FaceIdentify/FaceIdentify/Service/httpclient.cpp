#include "httpclient.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QBuffer>

HttpClient::HttpClient(QObject *parent) : QObject(parent)
{
    m_boundary= QString("------WebKitFormBoundaryOGkWPJsSaJCPWjZP");
}


void HttpClient::Post(const FIResult &fiResult)
{
    try {
        if(fiResult.matchResult==1 && fiResult.isExpire==false){

            QByteArray data;
            QString boundary = "--" + m_boundary;
            //组装数据
            QString param0 = boundary + "\r\nContent-Disposition: form-data; name=\"info\"\r\n\r\n";

            data=param0.toUtf8();

            QJsonObject json0;
            json0.insert("name",fiResult.name);
            json0.insert("gender",fiResult.gender);
            json0.insert("nation",fiResult.folk);
            json0.insert("birthday",fiResult.birthDay);
            json0.insert("number",fiResult.code);
            json0.insert("address",fiResult.address);
            json0.insert("department",fiResult.agency);
            json0.insert("date",fiResult.expireStart);
            json0.insert("date2",fiResult.expireEnd);

            data.append(QJsonDocument(json0).toJson());
            QString param1="\r\n";
            data.append(param1.toUtf8());

            QString dataFormat = boundary + "\r\n";//new line
            dataFormat += "Content-Disposition: form-data; name=\"photo\"; filename=\"%1\"\r\n";
            dataFormat += "Content-Type: image/jpeg\r\n\r\n";//new line and space line.
            QString bodyHeader = QString(dataFormat).arg("photo.jpg");
            data.append(bodyHeader.toUtf8());
            QByteArray imgData;
            if (!fiResult.liveImage.isNull()) {
              QBuffer buffer(&imgData);
              buffer.open(QIODevice::WriteOnly);
              fiResult.liveImage.save(&buffer, "JPG");
              buffer.close();
              data.append(imgData);
            }

            QString endparam="\r\n" + boundary + "--\r\n";
            data.append(endparam.toUtf8());

            QNetworkRequest request;
            QString url=QString("http://%1:%2/FaceIdentify/").arg(Constants::XmlSetting["ServerIp1N"]).arg(Constants::XmlSetting["ServerPort1N"]);
            request.setUrl(QUrl(url));

            request.setHeader(QNetworkRequest::ContentTypeHeader,QString("multipart/form-data;charset=utf-8;boundary=%1").arg(m_boundary));
            request.setHeader(QNetworkRequest::ContentLengthHeader,data.length());
            const auto &&reply = JQNet::HTTP::post(request, data,5000 );
            qInfo()<<QString("Http post ID:%1,result:%2").arg(fiResult.code).arg(reply.first);
        }
    }catch (std::exception &ex) {
        qCritical()<<ex.what();
    }
}
