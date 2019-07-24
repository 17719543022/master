#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>
#include "Common/constants.h"
#include "Common/paramdef.h"
#include "JQNet.h"

class HttpClient : public QObject
{
    Q_OBJECT
public:
    explicit HttpClient(QObject *parent = nullptr);
    void Post(const FIResult &fiResult);

signals:

public slots:
private:
    QString m_boundary;
};

#endif // HTTPCLIENT_H
