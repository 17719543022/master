#ifndef HTTPSERVER_H
#define HTTPSERVER_H
#include "Common/constants.h"
#include "Common/functions.h"
#include "Common/paramdef.h"
#include "JQHttpServer.h"
#include "FaceIdentifySDK.h"
#include "ParamDefine.h"


#include <QObject>
#include <cstdint>
#include <QString>

class HttpServer : public QObject
{
    Q_OBJECT
public:
    explicit HttpServer();
    ~HttpServer();

signals:
    void IDCardResponse(IDInfos* pIdInfos, MatchResultInfo* pMatchNetResp);

private:

    JQHttpServer::TcpServerManage* m_server;
};
Q_DECLARE_METATYPE(QPointer<JQHttpServer::Session>)
Q_DECLARE_METATYPE(IDInfos)
Q_DECLARE_METATYPE(MatchResultInfo)
#endif // HTTPSERVER_H
