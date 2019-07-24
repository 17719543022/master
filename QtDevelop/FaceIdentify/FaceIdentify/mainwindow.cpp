#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QPen>
#include <QMessageBox>
#include <QDir>
#include <QUuid>
#include <QDesktopWidget>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::FramelessWindowHint);
    ui->setupUi(this);
    window()->showFullScreen();

    qInfo()<<"System Version:"+Constants::SoftVersion+"_"+QDateTime::currentDateTime().toString("yyyyMMdd");

    ui->settingBtn->hide();

    try {
        m_imgFolderPath=QCoreApplication::applicationDirPath()+"\\images\\";
        //初始化tableWidget
        ui->RecordTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->RecordTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->RecordTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->RecordTableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
        ui->RecordTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->RecordTableWidget->verticalHeader()->setVisible(false);
        m_itemClickedConnection=connect(ui->RecordTableWidget,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(slotItemClicked(QTableWidgetItem*)));

        //m_dataAnalysis=DataAnalysis::instance();
        m_dataAnalysis=new DataAnalysis();

        m_dataAnalysis->RegistCallback();

        m_frameConnection=connect(m_dataAnalysis,&DataAnalysis::VideoFrame,this,&MainWindow::OnVideoFrame,Qt::QueuedConnection);
        m_resultConnection=connect(m_dataAnalysis,&DataAnalysis::ResponseResult,this,&MainWindow::OnResponseResult,Qt::QueuedConnection);
        m_resultDataConnection=connect(m_dataAnalysis,&DataAnalysis::ResponseResultData,this,&MainWindow::OnResponseResultData,Qt::QueuedConnection);

        //是否启动第二屏
        QDesktopWidget *desktop = QApplication::desktop();
        int screen_count = desktop->screenCount();
        if(screen_count>1){
            m_bIsTwoScreen=true;
            m_secondWindow=new SecondWindow(m_dataAnalysis,nullptr);
            m_secondWindow->setGeometry(desktop->screenGeometry(1));
            m_secondWindow->showFullScreen();
        }else {
            m_bIsTwoScreen=false;
        }

        //是否启用网络请求
        if("0"!=Constants::XmlSetting["Need1N"]){
            m_httpClient=new HttpClient();
            m_resultToClientConnection=connect(m_dataAnalysis,&DataAnalysis::ResponseResultToClient,this,&MainWindow::OnResponseResultToClient,Qt::QueuedConnection);
        }

    } catch (std::runtime_error &ex) {
        QMessageBox::warning(this,tr("警告"),ex.what());
        qCritical()<<ex.what();
        qApp->exit();
    }
}

MainWindow::~MainWindow()
{
    if(m_dataAnalysis!=nullptr){
        //delete m_dataAnalysis;
        m_dataAnalysis=nullptr;
    }

    if(m_frameConnection!=nullptr){
        disconnect(m_frameConnection);
    }
    if(m_resultConnection!=nullptr){
        disconnect(m_resultConnection);
    }
    if(m_resultToClientConnection!=nullptr){
        disconnect(m_resultToClientConnection);
    }
    if(m_resultDataConnection!=nullptr){
        disconnect(m_resultDataConnection);
    }
    if(m_itemClickedConnection!=nullptr){
        disconnect(m_itemClickedConnection);
    }

    if(m_httpClient!=nullptr){
        delete m_httpClient;
        m_httpClient=nullptr;
    }
    if(m_secondWindow!=nullptr){
        delete m_secondWindow;
        m_secondWindow=nullptr;
    }
    qInfo()<<"End soft!";
    delete ui;
}

void MainWindow::slotItemClicked(QTableWidgetItem* item)
{
    try {
        int row=item->row();
        if(row<m_fIResultVector.count()){
            ui->idNameLab->setText(tr("姓      名: ")+m_fIResultVector.at(row).name);
            ui->idNationLab->setText(tr("民      族: ")+m_fIResultVector.at(row).folk);
            ui->idNumberLab->setText(tr("身份证号: ")+m_fIResultVector.at(row).code);
            ui->idExpireEndLab->setText(tr("有效期限: ")+m_fIResultVector.at(row).expireStart+tr("-")+ m_fIResultVector.at(row).expireEnd);
            ui->matchScoreLab->setText(tr("比对分值: ")+QString::number(double(m_fIResultVector.at(row).matchScore), 10, 4));
            if(m_fIResultVector.at(row).matchResult==1)
            {
                QPalette pa;
                pa.setColor(QPalette::WindowText,Qt::green);
                ui->matchScoreLab->setPalette(pa);
            }else {
                QPalette pa;
                pa.setColor(QPalette::WindowText,Qt::red);
                ui->matchScoreLab->setPalette(pa);
            }

            if(m_fIResultVector.at(row).matchResult==0)
            {
                if(!m_fIResultVector.at(row).idImage.isNull()){
                    QImage img0=m_fIResultVector.at(row).idImage.scaled(ui->IDImageLab->width(),ui->IDImageLab->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                    ui->IDImageLab->setPixmap(QPixmap::fromImage(img0));
                }

                if(!m_fIResultVector.at(row).liveImage.isNull()){
                    QPixmap pixmap1=QPixmap::fromImage(m_fIResultVector.at(row).liveImage);
                    ui->LiveImageBtn->setIcon(QIcon(pixmap1.scaled(pixmap1.width(),pixmap1.height()).scaled(183,227,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
                    ui->LiveImageBtn->setIconSize(QSize(183,227));
                    ui->LiveImageBtn->setFlat(true);
                }

                QImage img2;
                img2.load(":/Images/failed.png");
                img2=img2.scaled(ui->resultImgLab->width(),ui->resultImgLab->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                ui->resultImgLab->setPixmap(QPixmap::fromImage(img2));

            }else if (m_fIResultVector.at(row).matchResult==1) {
                if(!m_fIResultVector.at(row).idImage.isNull()){
                    QImage img0=m_fIResultVector.at(row).idImage.scaled(ui->IDImageLab->width(),ui->IDImageLab->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                    ui->IDImageLab->setPixmap(QPixmap::fromImage(img0));
                }

                if(!m_fIResultVector.at(row).liveImage.isNull()){
                    QPixmap pixmap1=QPixmap::fromImage(m_fIResultVector.at(row).liveImage);
                    ui->LiveImageBtn->setIcon(QIcon(pixmap1.scaled(pixmap1.width(),pixmap1.height()).scaled(183,227,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
                    ui->LiveImageBtn->setIconSize(QSize(183,227));
                    ui->LiveImageBtn->setFlat(true);
                }

                QImage img2;
                img2.load(":/Images/success.png");
                img2=img2.scaled(ui->resultImgLab->width(),ui->resultImgLab->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                ui->resultImgLab->setPixmap(QPixmap::fromImage(img2));

            }else if (m_fIResultVector.at(row).matchResult==2) {
                if(!m_fIResultVector.at(row).idImage.isNull()){
                    QImage img0=m_fIResultVector.at(row).idImage.scaled(ui->IDImageLab->width(),ui->IDImageLab->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                    ui->IDImageLab->setPixmap(QPixmap::fromImage(img0));
                }

                QPixmap pixmap1;
                pixmap1.load(":/Images/noface.png");
                ui->LiveImageBtn->setIcon(QIcon(pixmap1.scaled(pixmap1.width(),pixmap1.height()).scaled(183,227,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
                ui->LiveImageBtn->setIconSize(QSize(183,227));
                ui->LiveImageBtn->setFlat(true);

                QImage img2;
                img2.load(":/Images/failed.png");
                img2=img2.scaled(ui->resultImgLab->width(),ui->resultImgLab->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                ui->resultImgLab->setPixmap(QPixmap::fromImage(img2));

            }else if (m_fIResultVector.at(row).matchResult==3) {

                QImage img0;
                img0.load(":/Images/noface.png");
                img0=img0.scaled(ui->IDImageLab->width(),ui->IDImageLab->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                ui->IDImageLab->setPixmap(QPixmap::fromImage(img0));

                if(!m_fIResultVector.at(row).liveImage.isNull()){
                    QPixmap pixmap1=QPixmap::fromImage(m_fIResultVector.at(row).liveImage);
                    ui->LiveImageBtn->setIcon(QIcon(pixmap1.scaled(pixmap1.width(),pixmap1.height()).scaled(183,227,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
                    ui->LiveImageBtn->setIconSize(QSize(183,227));
                    ui->LiveImageBtn->setFlat(true);
                }

                QImage img2;
                img2.load(":/Images/failed.png");
                img2=img2.scaled(ui->resultImgLab->width(),ui->resultImgLab->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                ui->resultImgLab->setPixmap(QPixmap::fromImage(img2));
            }else{
                //其他错误暂不处理
            }

            if(m_fIResultVector.at(row).isExpire)
            {
                QImage img2;
                img2.load(":/Images/invalid.png");
                img2=img2.scaled(ui->resultImgLab->width(),ui->resultImgLab->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                ui->resultImgLab->setPixmap(QPixmap::fromImage(img2));
            }
        }
    } catch (std::exception &ex) {
        qCritical()<<ex.what();
    }
}

void MainWindow::OnVideoFrame(const QImage &image, const QVector<QRect> &sFacePst)
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

void MainWindow::OnResponseResult(const FIResult &fiResult)
{
    try {
        ControlInit();

        if(m_fIResultVector.count()>10)
        {
            m_fIResultVector.remove(9);
        }


        m_fIResultVector.insert(m_fIResultVector.begin(),fiResult);

        ui->RecordTableWidget->clearContents();
        QVector<FIResult>::iterator iter;
        int index=0;
        for (iter=m_fIResultVector.begin();iter!=m_fIResultVector.end();iter++)
        {
            if("000000"==iter->name)
            {
                iter->name="拍照人脸";
            }

            QTableWidgetItem *item0=new QTableWidgetItem(iter->name);
            item0->setTextAlignment(Qt::AlignCenter);
            ui->RecordTableWidget->setItem(index, 0, item0);
            QTableWidgetItem *item1=new QTableWidgetItem(iter->matchTime);
            item1->setTextAlignment(Qt::AlignCenter);
            ui->RecordTableWidget->setItem(index, 1, item1);
            QTableWidgetItem *item2=new QTableWidgetItem(QString("%1").arg(double(iter->matchScore)));
            item2->setTextAlignment(Qt::AlignCenter);
            ui->RecordTableWidget->setItem(index, 2, item2);
            if(iter->matchResult==0){
                QTableWidgetItem *item3=new QTableWidgetItem(tr("比对不通过"));
                item3->setForeground(QBrush(Qt::red));
                item3->setTextAlignment(Qt::AlignCenter);
                ui->RecordTableWidget->setItem(index, 3,item3);
            }else if(iter->matchResult==1){
                QTableWidgetItem *item3=new QTableWidgetItem(tr("比对通过"));
                item3->setForeground(QBrush(Qt::green));
                item3->setTextAlignment(Qt::AlignCenter);
                ui->RecordTableWidget->setItem(index, 3,item3);
            }else if(iter->matchResult==2 || iter->matchResult==3){
                QTableWidgetItem *item3=new QTableWidgetItem(tr("无人脸信息"));
                item3->setForeground(QBrush(Qt::red));
                item3->setTextAlignment(Qt::AlignCenter);
                ui->RecordTableWidget->setItem(index, 3,item3);
            }else{
                QTableWidgetItem *item3=new QTableWidgetItem(tr("其他错误"));
                item3->setForeground(QBrush(Qt::red));
                item3->setTextAlignment(Qt::AlignCenter);
                ui->RecordTableWidget->setItem(index, 3,item3);
            }

            if(iter->isExpire)
            {
                QTableWidgetItem *item4=new QTableWidgetItem(tr("无效"));
                item4->setForeground(QBrush(Qt::red));
                item4->setTextAlignment(Qt::AlignCenter);
                ui->RecordTableWidget->setItem(index, 4, item4);
            }else{
                QTableWidgetItem *item4=new QTableWidgetItem(tr("有效"));
                item4->setForeground(QBrush(Qt::green));
                item4->setTextAlignment(Qt::AlignCenter);
                ui->RecordTableWidget->setItem(index, 4, item4);
            }
            index++;
        }

        emit ui->RecordTableWidget->itemClicked(ui->RecordTableWidget->item(0,0));
    } catch (std::exception &ex) {
        qCritical()<<ex.what();
    }
}

void MainWindow::OnResponseResultToClient(const FIResult &fiResult)
{
    if("0"!=Constants::XmlSetting["Need1N"] &&m_httpClient!=nullptr && fiResult.matchResult==1 && fiResult.isExpire==false){
        m_httpClient->Post(fiResult);
    }
}

void MainWindow::OnResponseResultData(const FIResult &fiResult)
{
    try {
        qInfo()<<QString("save data-ID:%1").arg(fiResult.code);

        FIResultData frd;
        QUuid id = QUuid::createUuid();
        QString strId = id.toString();
        strId.remove("{").remove("}").remove("-"); // 一般习惯去掉左右花括号和连字符
        frd.id=strId;
        frd.passagewayId=Constants::XmlSetting["RecogLocationID"].toInt();
        frd.idType=fiResult.idType;
        frd.name=fiResult.name;
        frd.eName=fiResult.eName;
        frd.gender=fiResult.gender;
        frd.folk=fiResult.folk;
        frd.birthDay=fiResult.birthDay;
        frd.code=fiResult.code;
        frd.address=fiResult.address;
        frd.agency=fiResult.agency;
        frd.expireStart=fiResult.expireStart;
        frd.expireEnd=fiResult.expireEnd;
        frd.prCode=fiResult.prCode;
        frd.nation=fiResult.nation;
        frd.idVersion=fiResult.idVersion;
        frd.agencyCode=fiResult.agencyCode;
        frd.liveImageAge=fiResult.liveImageAge;
        frd.liveImageGender=fiResult.liveImageGender;
        frd.idImageType=fiResult.idImageType;

        frd.matchResult=fiResult.matchResult;
        frd.matchScore=fiResult.matchScore;
        frd.matchScoreThreshold=Constants::XmlSetting["RecogThreshold"].toFloat();
        frd.matchTime=fiResult.matchTime;


        if(fiResult.isExpire) //证件失效换算为识别结果中的证件失效
        {
            frd.matchResult=4;
        }

        QDateTime dateTime=QDateTime::currentDateTime();
        QString datePath = dateTime.toString("yyyyMMdd");
        QString timePath = dateTime.toString("HHmmss");
        QString folderPath=m_imgFolderPath+datePath+"\\";
        QDir dir(folderPath);
        if(!dir.exists())
        {
            dir.mkpath(folderPath);
        }

        QString IDFileName=QString("%1-%2-%3-%4-0").arg(fiResult.code).arg(double(fiResult.matchScore)).arg(fiResult.matchResult).arg(timePath);
        QString liveFileName=QString("%1-%2-%3-%4-1").arg(fiResult.code).arg(double(fiResult.matchScore)).arg(fiResult.matchResult).arg(timePath);
        QString liveBigFileName=QString("%1-%2-%3-%4-1_W").arg(fiResult.code).arg(double(fiResult.matchScore)).arg(fiResult.matchResult).arg(timePath);
        QString IDFilePath = folderPath  + IDFileName;
        QString liveFilePath = folderPath  + liveFileName;
        QString liveBigFilePath = folderPath  + liveBigFileName;
        if(!fiResult.idImage.isNull()){
            Functions::SaveQImageToFile(fiResult.idImage,IDFilePath,true);
            frd.idImage=fiResult.idImage;
            frd.idImagePath=IDFilePath;
        }
        if(!fiResult.liveImage.isNull()){
            Functions::SaveQImageToFile(fiResult.liveImage,liveFilePath,true);
            frd.liveImage=fiResult.liveImage;
            frd.liveImagePath=liveFilePath;
        }
        if(!fiResult.liveFrameImageJPG.isNull()){
            Functions::SaveQImageToFile(fiResult.liveFrameImageJPG,liveBigFilePath,true);
            frd.liveFrameImageJPG=fiResult.liveFrameImageJPG;
            frd.liveFrameImageJPGPath=liveBigFilePath;
        }

        //插入数据库
        SqliteDB<FIResultData> db;
        db.insertItem(frd,"identifyrecord_tb");
    } catch (std::exception &ex) {
        qCritical()<<ex.what();
    }

}


void MainWindow::ControlInit()
{
    QImage img;
    img.load(":/Images/default.png");
    ui->IDImageLab->setPixmap(QPixmap::fromImage(img));

    QIcon liveImageBtn_ico(":/Images/default.png");
    ui->LiveImageBtn->setIcon(liveImageBtn_ico);

    ui->idNameLab->setText(tr("姓      名："));
    ui->idNationLab->setText(tr("民      族:"));
    ui->idNumberLab->setText(tr("身份证号："));
    ui->idExpireEndLab->setText(tr("有效期限："));
    ui->matchScoreLab->setText(tr("比对分值："));
    ui->resultImgLab->clear();
}


void MainWindow::on_shutdownBtn_clicked()
{
    QMessageBox message(QMessageBox::NoIcon, tr("关机"), tr("是否关闭计算机?"), QMessageBox::Yes | QMessageBox::No, nullptr);
   if(message.exec() == QMessageBox::Yes)
   {
        QString cmd="shutdown -s -t 5";
        qInfo()<<cmd;
        system(cmd.toLatin1());
   }
}


void MainWindow::on_LiveImageBtn_clicked()
{
    m_dataAnalysis->FacePhotographResult();
}

void MainWindow::on_livePushBtn_clicked()
{
    m_dataAnalysis->FacePhotographResult();
}
