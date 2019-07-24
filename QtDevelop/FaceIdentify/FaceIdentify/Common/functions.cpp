#include "functions.h"

#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QXmlStreamReader>
#include <QString>
#include <QDomDocument>
#include <QMap>
#include <QByteArray>
#include <QBuffer>

Functions::Functions()
{

}

QMap<QString,QString> Functions::GetSettingsFromXML(QString fileName)
{
    QMap<QString,QString> XmlSetting;
    try {
        QString path=QCoreApplication::applicationDirPath();
        QDomDocument doc;
        QFile file(path+"/"+fileName);
        if(!file.open(QIODevice::ReadOnly)){ 
            qCritical()<<QString("%1 QFile open failure").arg(fileName);
            return XmlSetting;
        }
        if(!doc.setContent(&file))
        {
            qCritical()<<QString("%1 QDomDocument setContent failure").arg(fileName);
            file.close();
            return XmlSetting;
        }
        file.close();

        QDomElement docElem=doc.documentElement();
        if(docElem.toElement().tagName()=="Message"){
            QDomNode node=docElem.firstChild();
            while (!node.isNull()) {
                if(node.isElement()){
                    QDomElement elem=node.toElement();
                    QDomNodeList list=elem.childNodes();
                    for(int i=0;i<list.count();i++){
                        QDomNode node1=list.at(i);
                        if(node1.isElement()){
                            XmlSetting.insert(node1.toElement().tagName(),node1.toElement().text());
                        }
                    }
                }
                node=node.nextSibling();
            }
        }

    } catch (std::exception &ex) {
        qCritical()<<ex.what();
        return XmlSetting;
    }
    return XmlSetting;
}

void Functions::SaveQImageToFile(const QImage &image, QString filepath, bool encryption)
{
    try {
        QByteArray imgArray;
        QBuffer buffer(&imgArray);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer,"jpg");
        if(!imgArray.isEmpty() && !filepath.isEmpty()){
            QFile file(filepath);
            if(!file.exists() && file.open(QIODevice::WriteOnly)){
                if(encryption){
                    imgArray.prepend("cigitcigitcigit");
                    file.write(imgArray);
                }else {
                    file.write(imgArray);
                }
                file.close();
            }
        }

    } catch (std::exception &ex) {
        qCritical()<<ex.what();
    }
}

int Functions::FindFirstBytes(QByteArray qmain, QByteArray qsub)
{
    try {
        if(qmain.isNull() || qsub.isNull()){
            return -1;
        }
        if(qmain.length()==0 || qsub.length()==0){
            return -1;
        }
        int ind = 0;
        bool find = false;

        for (int i = 0; i < qmain.length(); i++)
        {
            if (qmain[i] == qsub[0] && qmain.length()-i>=qsub.length())
            {
                find = true;
                ind = i;
                for (int j = 1; j < qsub.length(); j++)
                {
                    if (qsub[j] != qmain[i + j])
                    {
                        find = false;
                        break;
                    }
                }

                if (find)
                {
                    return ind;
                }
            }
        }
        return -1;
} catch (std::exception &ex) {
        qCritical()<<ex.what();
        return -1;
    }

}

int Functions::isDigitStr(QString src)
{
    QByteArray ba = src.toLatin1();//QString 转换为 char*
    const char *s = ba.data();
    while(*s && *s>='0' && *s<='9') s++;
    if (*s){ //不是纯数字
        return -1;
    }else{ //纯数字
        return 0;
    }
}
