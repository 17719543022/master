#include "constants.h"

#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>
#include <QString>
#include <QDomDocument>
#include <QMap>

QMap<QString,QString> Constants::XmlSetting;
QString  Constants::SoftVersion="V1.0.0";
int Constants::MaxDetectFace=1;

Constants::Constants()
{

}

