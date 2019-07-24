#ifndef QLOG4QT_H
#define QLOG4QT_H

#include <log4qt/log4qt.h>
#include "log4qt/propertyconfigurator.h"
#include "log4qt/logmanager.h"
#include "log4qt/logger.h"

#include <QObject>
#include <QString>

#define Qlogger QLog4Qt::instance()

class QLog4Qt : public QObject
{
    Q_OBJECT
    LOG4QT_DECLARE_QCLASS_LOGGER
public:
    explicit QLog4Qt(QObject *parent=0);
    ~QLog4Qt();

    static QLog4Qt *instance();
    virtual void debug(const QString logstr){logger()->debug(logstr);}
    virtual void info(const QString logstr){logger()->info(logstr);}
    virtual void warn(const QString logstr){logger()->warn(logstr);}
    virtual void error(const QString logstr){logger()->error(logstr);}
    virtual void fatal(const QString logstr){logger()->fatal(logstr);}
};

#endif // QLOG4QT_H
