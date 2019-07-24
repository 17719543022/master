#include "secondwindow.h"
#include "ui_secondwindow.h"

#include <QString>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QPen>
#include <QDir>

SecondWindow::SecondWindow(DataAnalysis *dataAnalysis, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);

    try {
        qInfo()<<"Show SecondWindow!";
        m_frameConnection=connect(dataAnalysis,&DataAnalysis::VideoFrame,this,&SecondWindow::OnVideoFrame,Qt::QueuedConnection);

        QString rollImgFolderPath=QCoreApplication::applicationDirPath()+"\\rollImages\\";
        QDir dir(rollImgFolderPath);
        if(dir.exists()){
            QStringList filters;
            filters<<QString("*.jpeg")<<QString("*.jpg")<<QString("*.png");
            dir.setFilter(QDir::Files | QDir::NoSymLinks);
            dir.setNameFilters(filters);  //设置文件名称过滤器，只为filters格式（后缀为.jpeg等图片格式）
            QFileInfoList fileInfoList = dir.entryInfoList();
            if(fileInfoList.count()>0){
                for(int i=0;i<fileInfoList.count();i++){
                    m_imgPathList<<fileInfoList.at(i).absoluteFilePath();
                }
            }

            //初始化轮播图片
            QImage img1;
            img1.load(":/Images/rollImg.png");
            img1=img1.scaled(ui->RollImg->width(),ui->RollImg->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
            ui->RollImg->setPixmap(QPixmap::fromImage(img1));

            m_curIndex=0;
            m_imgTimer=new QTimer(this);
            m_imgTimer->setInterval(6000);
            m_timerConnection=connect(m_imgTimer, &QTimer::timeout, this, &SecondWindow::onImageShowTimeOut);
            m_imgTimer->start();

        }else {
            QImage img2;
            img2.load(":/Images/rollImg.png");
            img2=img2.scaled(ui->RollImg->width(),ui->RollImg->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
            ui->RollImg->setPixmap(QPixmap::fromImage(img2));
        }
    } catch (std::exception &ex) {
        qCritical()<<ex.what();
    }
}

SecondWindow::~SecondWindow()
{
    qInfo()<<"End SecondWindow!";
    if(m_frameConnection!=nullptr){
        disconnect(m_frameConnection);
    }
    if(m_timerConnection!=nullptr){
        disconnect(m_timerConnection);
    }
    if(m_imgTimer!=nullptr){
        m_imgTimer->stop();
        delete m_imgTimer;
    }
    delete ui;
}


void SecondWindow::OnVideoFrame(const QImage &image, const QVector<QRect> &sFacePst)
{
    try {
        QPixmap pixmap=QPixmap::fromImage(image.rgbSwapped());
        for(int i=0;i<sFacePst.size();i++){
            QPainter painter(&pixmap);
            painter.setRenderHint(QPainter::Antialiasing);
            QPen pen(Qt::green);
            pen.setWidth(3);
            painter.setPen(pen);
            painter.drawRect(sFacePst[i]);
        }
        QImage img=pixmap.toImage().scaled(ui->VideoFrame->width(),ui->VideoFrame->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        ui->VideoFrame->setPixmap(QPixmap::fromImage(img));
    } catch (std::exception &ex) {
        qCritical()<<ex.what();
    }
}

void SecondWindow::onImageShowTimeOut()
{
    try {
        m_curIndex++;
        if(m_curIndex>=m_imgPathList.count()){
            m_curIndex=0;
        }
        ui->RollImg->clear();
        QImage img;
        img.load(m_imgPathList.at(m_curIndex));
        img=img.scaled(ui->RollImg->width(),ui->RollImg->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        ui->RollImg->setPixmap(QPixmap::fromImage(img));
    } catch (std::exception &ex) {
        qCritical()<<ex.what();
    }
}
