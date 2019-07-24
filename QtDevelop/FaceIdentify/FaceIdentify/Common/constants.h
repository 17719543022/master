#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QMap>
#include <QString>

class Constants
{
public:
    Constants();
    static QMap<QString,QString> XmlSetting;
    static QString SoftVersion;
    static int MaxDetectFace;
};

#endif // CONSTANTS_H
