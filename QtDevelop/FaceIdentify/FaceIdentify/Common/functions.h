#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QString>
#include <QMap>
#include <QImage>

class Functions
{
public:
    Functions();
    static QMap<QString,QString> GetSettingsFromXML(QString fileName);
    static void SaveQImageToFile(const QImage& image,QString filepath,bool encryption);
    static int FindFirstBytes(QByteArray qmain, QByteArray qsub);
    static int isDigitStr(QString src);
};

#endif // FUNCTIONS_H
