#include "mainwindow.h"
#include "Common/constants.h"
#include "Common/functions.h"
#include "log4qt/propertyconfigurator.h"
#include "log4qt/logmanager.h"
#include "Service/httpserver.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try {
        Log4Qt::PropertyConfigurator::configure(QCoreApplication::applicationDirPath()+"/log4j.conf");
        Log4Qt::LogManager::setHandleQtMessages(true);

        Constants::XmlSetting=Functions::GetSettingsFromXML("SystemParam.xml");
    } catch (std::exception &ex) {
        qCritical()<<ex.what();
        qApp->exit();
    }
    MainWindow w;
    w.show();

    int ret=a.exec();
    return ret;
}
