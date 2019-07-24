#include "httpserver.h"
#include "qglobal.h"
#include <QCoreApplication>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QBuffer>
#include <QPixmap>
#include <QImageReader>
#include <QTextCodec>


HttpServer::HttpServer() : QObject(nullptr)
{
    m_server=new JQHttpServer::TcpServerManage(1);// 设置最大处理线程数，默认2个
    //设置处理请求回调函数
    m_server->setHttpAcceptedCallback( [this]( const QPointer< JQHttpServer::Session > &session )
    {
        try {
            if(!session.isNull()){
                if ("/FaceIdentify/"==session->requestUrl()){

                    MatchResultInfo m_matchNetResp;
                    m_matchNetResp.status=3;


                    QMap<QString, QString> map=session->requestHeader();
                    QMap<QString, QString>::iterator it=map.find("Content-Type");
                    QString ct=it.value();
                    int binx=ct.indexOf("boundary=");
                    QString bound;
                    if(binx>0){
                        IDImageInfo idImageInfo;
                        IDInfos IdInfos;

                        QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));

                        bound="--"+ct.mid(binx+9);
                        QByteArray bodyByteArray=session->requestBody();

                        int binx1=Functions::FindFirstBytes(bodyByteArray,bound.toUtf8());
                        if(binx1>=0){
                            QByteArray bodyByteArray1=bodyByteArray.mid(binx1+bound.toUtf8().length());
                            int binx2=Functions::FindFirstBytes(bodyByteArray1,bound.toUtf8());
                            if(binx2>0){
                                bodyByteArray1=bodyByteArray1.left(binx2);
                                QString segstr1(bodyByteArray1);

                                segstr1=segstr1.replace(QString("\r\n"),QString("")).replace(QString(" "),QString(""));
                                int binx11=segstr1.indexOf("name=\"info\"");
                                if(binx11>0){
                                    QString str1=segstr1.mid(binx11+11);
                                    QJsonParseError jsonParseError;
                                    QJsonDocument document = QJsonDocument::fromJson(str1.toUtf8(), &jsonParseError);
                                    if(!document.isNull() && jsonParseError.error == QJsonParseError::NoError) {
                                        QJsonObject json = document.object();
                                        IdInfos.idType=0;
                                        if(json.contains("address")){
                                            QByteArray ba=json["address"].toString().toLocal8Bit();
                                            int len = qMin( int(ba.size()), int(sizeof(IdInfos.address))-1 );
                                            memccpy(IdInfos.address,ba,0,size_t(len));
                                            IdInfos.address[len]='\0';
                                        }
                                        if(json.contains("birthday")){
                                            QByteArray ba=json["birthday"].toString().toLocal8Bit();
                                            int len = qMin( int(ba.size()), int(sizeof(IdInfos.birthDay))-1 );
                                            memccpy(IdInfos.birthDay,ba,0,size_t(len));
                                            IdInfos.birthDay[len]='\0';
                                        }
                                        if(json.contains("date")){
                                            QByteArray ba=json["date"].toString().toLocal8Bit();
                                            int len = qMin( int(ba.size()), int(sizeof(IdInfos.expireStart))-1 );
                                            memccpy(IdInfos.expireStart,ba,0,size_t(len));
                                            IdInfos.expireStart[len]='\0';
                                        }
                                        if(json.contains("date2")){
                                            QByteArray ba=json["date2"].toString().toLocal8Bit();
                                            int len = qMin( int(ba.size()), int(sizeof(IdInfos.expireEnd))-1 );
                                            memccpy(IdInfos.expireEnd,ba,0,size_t(len));
                                            IdInfos.expireEnd[len]='\0';
                                        }
                                        if(json.contains("department")){
                                            QByteArray ba=json["department"].toString().toLocal8Bit();
                                            int len = qMin( int(ba.size()), int(sizeof(IdInfos.agency))-1 );
                                            memccpy(IdInfos.agency,ba,0,size_t(len));
                                            IdInfos.agency[len]='\0';
                                        }
                                        if(json.contains("gender")){
                                            QByteArray ba=json["gender"].toString().toLocal8Bit();
                                            int len = qMin( int(ba.size()), int(sizeof(IdInfos.gender))-1 );
                                            memccpy(IdInfos.gender,ba,0,size_t(len));
                                            IdInfos.gender[len]='\0';
                                        }
                                        if(json.contains("name")){
                                            QByteArray ba=json["name"].toString().toLocal8Bit();
                                            int len = qMin( int(ba.size()), int(sizeof(IdInfos.name))-1 );
                                            memccpy(IdInfos.name,ba,0,size_t(len));
                                            IdInfos.name[len]='\0';
                                        }
                                        if(json.contains("nation")){
                                            QByteArray ba=json["nation"].toString().toLocal8Bit();
                                            int len = qMin( int(ba.size()), int(sizeof(IdInfos.folk))-1 );
                                            memccpy(IdInfos.folk,ba,0,size_t(len));
                                            IdInfos.folk[len]='\0';
                                        }
                                        if(json.contains("number")){
                                            QByteArray ba=json["number"].toString().toLocal8Bit();
                                            int len = qMin( int(ba.size()), int(sizeof(IdInfos.code))-1 );
                                            memccpy(IdInfos.code,ba,0,size_t(len));
                                            IdInfos.code[len]='\0';
                                        }
                                    }
                                }
                                QByteArray bodyByteArray2=bodyByteArray.mid(binx1+bound.toUtf8().length()+binx2+bound.toUtf8().length());

                                QString end="\r\n" + bound + "--\r\n";
                                int binx3=Functions::FindFirstBytes(bodyByteArray2,end.toUtf8());
                                if(binx3>0){
                                    bodyByteArray2=bodyByteArray2.left(binx3);
                                    QByteArray bytes0("image/jpeg\r\n\r\n");
                                    int ind0=Functions::FindFirstBytes(bodyByteArray2,bytes0);
                                    bodyByteArray2=bodyByteArray2.mid(ind0+bytes0.length());    //图片byte[]

                                    idImageInfo.idImageType=2;
                                    QPixmap pixmap;
                                    pixmap.loadFromData(bodyByteArray2);
                                    QByteArray bytearray;
                                    QBuffer buffer;
                                    buffer.open(QIODevice::ReadWrite);
                                    pixmap.save(&buffer,"BMP");
                                    bytearray.append(buffer.data());
                                    idImageInfo.idImageBMP=bytearray.data();
                                    idImageInfo.idImageBMPLen=bytearray.length();

                                    IdInfos.imgInfo=idImageInfo;


                                    //抛出识别结果
                                    emit this->IDCardResponse(&IdInfos,&m_matchNetResp);
                                }
                            }
                        }
                    }
                    if(m_matchNetResp.status!=0)
                    {
                        m_matchNetResp.status = 3;
                        m_matchNetResp.score = 0;
                        m_matchNetResp.matchResult = 0;
                        m_matchNetResp.livePhotoStr="";
                    }

                    //响应http请求
                    QJsonObject json;
                    json.insert("status",m_matchNetResp.status);
                    json.insert("score",QString::number(double(m_matchNetResp.score), 10, 4));
                    json.insert("matchResult",m_matchNetResp.matchResult);
                    json.insert("livePhoto",m_matchNetResp.livePhotoStr);

                    session->replyJsonObject(json);
                }
            }
        } catch (std::exception &ex) {
            qCritical()<<ex.what();
        }
    } );

    //设置监听
    QHostAddress address=QHostAddress(Constants::XmlSetting["FaceServerIp"]);
    quint16 port=quint16(Constants::XmlSetting["FaceServerPort"].toUInt());
    m_server->listen(address,port);
}

HttpServer::~HttpServer()
{
    if(m_server!=nullptr){
        m_server->destroyed();
        delete m_server;
        m_server=nullptr;
    }
}



