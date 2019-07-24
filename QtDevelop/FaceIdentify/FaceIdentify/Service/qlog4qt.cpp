#include "qlog4qt.h"

#include<QCoreApplication>

QLog4Qt::QLog4Qt(QObject *parent) :QObject (parent)
{
}

QLog4Qt::~QLog4Qt()
{

}

QLog4Qt *QLog4Qt::instance()
{
    static QLog4Qt obj;
    return &obj;
}
