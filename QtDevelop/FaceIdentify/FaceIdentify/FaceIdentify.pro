#-------------------------------------------------
#
# Project created by QtCreator 2019-01-07T15:38:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FaceIdentify
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    Common/constants.cpp \
    Common/functions.cpp \
    Service/dataanalysis.cpp \
    secondwindow.cpp \
    Service/httpserver.cpp \
    Service/httpclient.cpp

HEADERS += \
        mainwindow.h \
    Common/constants.h \
    Common/functions.h \
    Service/dataanalysis.h \
    Common/paramdef.h \
    Service/sqlitedb.h \
    secondwindow.h \
    Service/httpserver.h \
    Service/httpclient.h

FORMS += \
        mainwindow.ui \
    secondwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT+=xml

QT+=sql

QT+= network concurrent

RC_ICONS = Application_64X64.ico

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../FaceIdentifySDK_win32/lib/ -lFaceIdentifySDK
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../FaceIdentifySDK_win32/lib/ -lFaceIdentifySDK

INCLUDEPATH += $$PWD/../FaceIdentifySDK_win32/include
DEPENDPATH += $$PWD/../FaceIdentifySDK_win32/include

RESOURCES += \
    images.qrc

unix|win32: LIBS += -L$$PWD/../Log4qtSDK/ -llog4qt


INCLUDEPATH += $$PWD/../Log4qtSDK/src
DEPENDPATH += $$PWD/../Log4qtSDK/src

include( $$PWD/../JQLibrary/JQLibrary.pri )

