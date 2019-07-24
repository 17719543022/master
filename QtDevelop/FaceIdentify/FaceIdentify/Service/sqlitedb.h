#ifndef SQLITEDB_H
#define SQLITEDB_H

#include "Common/paramdef.h"

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QVector>
#include <QDebug>
#include <QPointer>
#include <QSqlError>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QFile>

template<class T>
class SqliteDB
{
public:
    explicit SqliteDB();
    ~SqliteDB();
    int query(QString sql);
    QVector<T> selectItems(QString sql,QString table);
    int deleteItem(QString sql);
    int insertItem(T obj,QString table);
    int updateItem(T obj,QString table);
private:
    QString m_dbFilePath;
    QSqlDatabase m_db;
};


template <class T>
SqliteDB<T>::SqliteDB()
{
    m_dbFilePath=QCoreApplication::applicationDirPath()+"/facerecognition_db.db";
}

template <class T>
SqliteDB<T>::~SqliteDB()
{
    if(m_db.isOpen())
    {
        m_db.close();
    }
}


template<class T>
int SqliteDB<T>::query(QString sql)
{
    try {

        if(QSqlDatabase::contains("facerecognition_db")){
            m_db =QSqlDatabase::database("facerecognition_db");
        }
        else{
            m_db =QSqlDatabase::addDatabase("QSQLITE","facerecognition_db");
        }

        if(m_dbFilePath.isEmpty())
        {
            qCritical()<<"sqlite db not exist";
            throw std::runtime_error("sqlite db not exist");
        }
        QFile file(m_dbFilePath);
        if(!file.exists())
        {
            qCritical()<<"sqlite db not exist";
            throw std::runtime_error("sqlite db not exist");
        }
        m_db.setDatabaseName(m_dbFilePath);
        if(!m_db.open())
        {
            qCritical()<<"sqlite db not open"<<m_db.lastError();
            throw std::runtime_error("sqlite db not open");
        }

        m_db.transaction();
        QSqlQuery m_qurey=QSqlQuery(m_db);

        bool ret= m_qurey.exec(sql);
        if(!ret)
        {
            qCritical()<<m_qurey.lastError();
            m_db.close();
            return 0;
        }

        if(ret)
        {
            ret=m_db.commit();
        }
        if(!ret)
        {
            ret=m_db.rollback();
            m_db.close();
            return 0;
        }
        m_qurey.clear();
        m_db.close();
        return 1;
    } catch (std::exception &ex) {
        qCritical()<<ex.what();
        return 0;
    }
}

template<class T>
QVector<T> SqliteDB<T>::selectItems(QString sql, QString table)
{
    QVector<T> TVector;
    try {
        if(QSqlDatabase::contains("facerecognition_db")){
            m_db =QSqlDatabase::database("facerecognition_db");
        }
        else{
            m_db =QSqlDatabase::addDatabase("QSQLITE","facerecognition_db");
        }

        if(m_dbFilePath.isEmpty())
        {
            qCritical()<<"sqlite db not exist";
            throw std::runtime_error("sqlite db not exist");
        }
        QFile file(m_dbFilePath);
        if(!file.exists())
        {
            qCritical()<<"sqlite db not exist";
            throw std::runtime_error("sqlite db not exist");
        }
        m_db.setDatabaseName(m_dbFilePath);
        if(!m_db.open())
        {
            qCritical()<<"sqlite db not open"<<m_db.lastError();
            throw std::runtime_error("sqlite db not open");
        }

        m_db.transaction();
        QSqlQuery m_qurey=QSqlQuery(m_db);

        bool ret= m_qurey.exec(sql);
        if(!ret)
        {
            qCritical()<<m_qurey.lastError();
            m_db.close();
            return TVector;
        }

        if(ret)
        {
            ret=m_db.commit();
        }
        if(!ret)
        {
            ret=m_db.rollback();
            m_db.close();
            return TVector;
        }

        if(table=="identifyrecord_tb"){
            while (m_qurey.next()) {
                FIResultData frd;
                frd.id=m_qurey.value(0).toString();
                frd.passagewayId=m_qurey.value(1).toInt();
                frd.idType=m_qurey.value(2).toInt();
                frd.name=m_qurey.value(3).toString();
                frd.eName=m_qurey.value(4).toString();
                frd.gender=m_qurey.value(5).toString();
                frd.folk=m_qurey.value(6).toString();
                frd.birthDay=m_qurey.value(7).toString();
                frd.code=m_qurey.value(8).toString();
                frd.address=m_qurey.value(9).toString();
                frd.agency=m_qurey.value(10).toString();
                frd.expireStart=m_qurey.value(11).toString();
                frd.expireEnd=m_qurey.value(12).toString();
                frd.prCode=m_qurey.value(13).toString();
                frd.nation=m_qurey.value(14).toString();
                frd.idVersion=m_qurey.value(15).toString();
                frd.agencyCode=m_qurey.value(16).toString();
                frd.liveImageAge=m_qurey.value(17).toFloat();
                frd.liveImageGender=m_qurey.value(18).toString();
                frd.idImageType=m_qurey.value(19).toInt();
                frd.idImagePath=m_qurey.value(20).toString();
                frd.liveImagePath=m_qurey.value(21).toString();
                frd.liveFrameImageJPGPath=m_qurey.value(22).toString();
                frd.matchResult=m_qurey.value(23).toInt();
                frd.matchScore=m_qurey.value(24).toFloat();
                frd.matchScoreThreshold=m_qurey.value(25).toFloat();
                frd.matchTime=m_qurey.value(26).toString();

                TVector.append(frd);
            }
        }
        m_qurey.clear();
        m_db.close();
        return TVector;
    } catch (std::exception &ex) {
        qCritical()<<ex.what();
        return TVector;
    }

}

template<class T>
int SqliteDB<T>::deleteItem(QString sql)
{
    try {

        if(QSqlDatabase::contains("facerecognition_db")){
            m_db =QSqlDatabase::database("facerecognition_db");
        }
        else{
            m_db =QSqlDatabase::addDatabase("QSQLITE","facerecognition_db");
        }

        if(m_dbFilePath.isEmpty())
        {
            qCritical()<<"sqlite db not exist";
            throw std::runtime_error("sqlite db not exist");
        }
        QFile file(m_dbFilePath);
        if(!file.exists())
        {
            qCritical()<<"sqlite db not exist";
            throw std::runtime_error("sqlite db not exist");
        }
        m_db.setDatabaseName(m_dbFilePath);
        if(!m_db.open())
        {
            qCritical()<<"sqlite db not open"<<m_db.lastError();
            throw std::runtime_error("sqlite db not open");
        }

        m_db.transaction();
        QSqlQuery m_qurey=QSqlQuery(m_db);

        bool ret= m_qurey.exec(sql);
        if(!ret)
        {
            qCritical()<<m_qurey.lastError();
            m_db.close();
            return 0;
        }

        if(ret)
        {
            ret=m_db.commit();
        }
        if(!ret)
        {
            ret=m_db.rollback();
            m_db.close();
            return 0;
        }
        m_qurey.clear();
        m_db.close();
        return 1;
    } catch (std::exception &ex) {
        qCritical()<<ex.what();
        return 0;
    }
}

template<class T>
int SqliteDB<T>::insertItem(T obj, QString table)
{
    try{
        if(QSqlDatabase::contains("facerecognition_db")){
            m_db =QSqlDatabase::database("facerecognition_db");
        }
        else{
            m_db =QSqlDatabase::addDatabase("QSQLITE","facerecognition_db");
        }

        if(m_dbFilePath.isEmpty())
        {
            qCritical()<<"sqlite db not exist";
            throw std::runtime_error("sqlite db not exist");
        }
        QFile file(m_dbFilePath);
        if(!file.exists())
        {
            qCritical()<<"sqlite db not exist";
            throw std::runtime_error("sqlite db not exist");
        }
        m_db.setDatabaseName(m_dbFilePath);
        if(!m_db.open())
        {
            qCritical()<<"sqlite db not open"<<m_db.lastError();
            throw std::runtime_error("sqlite db not open");
        }

        m_db.transaction();
        QSqlQuery m_qurey=QSqlQuery(m_db);

        QString sql;
        if(table=="identifyrecord_tb"){
            FIResultData frd=obj;
            sql=QString("INSERT INTO identifyrecord_tb (id,passagewayId,idType,idName,idEName,idGender,idFolk,idBirthDay,idCode,idAddress,idAgency,idExpireStart,idExpireEnd,idPrCode,idNation,idVersion,idAgencyCode,liveImageAge,liveImageGender,idImageType,idImagePath,liveImagePath,liveFrameImageJPGPath,matchResult,matchScore,matchScoreThreshold,matchTime)"
                        " VALUES (:id,:passagewayId,:idType,:idName,:idEName,:idGender,:idFolk,:idBirthDay,:idCode,:idAddress,:idAgency,:idExpireStart,:idExpireEnd,:idPrCode,:idNation,:idVersion,:idAgencyCode,:liveImageAge,:liveImageGender,:idImageType,:idImagePath,:liveImagePath,:liveFrameImageJPGPath,:matchResult,:matchScore,:matchScoreThreshold,:matchTime)");

            m_qurey.prepare(sql);

            m_qurey.bindValue(":id",frd.id);
            m_qurey.bindValue(":passagewayId",frd.passagewayId);
            m_qurey.bindValue(":idType",frd.idType);
            m_qurey.bindValue(":idName",frd.name);
            m_qurey.bindValue(":idEName",frd.eName);
            m_qurey.bindValue(":idGender",frd.gender);
            m_qurey.bindValue(":idFolk",frd.folk);
            m_qurey.bindValue(":idBirthDay",frd.birthDay);
            m_qurey.bindValue(":idCode",frd.code);
            m_qurey.bindValue(":idAddress",frd.address);
            m_qurey.bindValue(":idAgency",frd.agency);
            m_qurey.bindValue(":idExpireStart",frd.expireStart);
            m_qurey.bindValue(":idExpireEnd",frd.expireEnd);
            m_qurey.bindValue(":idPrCode",frd.prCode);
            m_qurey.bindValue(":idNation",frd.nation);
            m_qurey.bindValue(":idVersion",frd.idVersion);
            m_qurey.bindValue(":idAgencyCode",frd.agencyCode);
            m_qurey.bindValue(":liveImageAge", QString::number(double(frd.liveImageAge), 10, 4));
            m_qurey.bindValue(":liveImageGender",frd.liveImageGender);
            m_qurey.bindValue(":idImageType",frd.idImageType);
            m_qurey.bindValue(":idImagePath",frd.idImagePath);
            m_qurey.bindValue(":liveImagePath",frd.liveImagePath);
            m_qurey.bindValue(":liveFrameImageJPGPath",frd.liveFrameImageJPGPath);
            m_qurey.bindValue(":matchResult",frd.matchResult);
            m_qurey.bindValue(":matchScore",QString::number(double(frd.matchScore), 10, 4));
            m_qurey.bindValue(":matchScoreThreshold",QString::number(double(frd.matchScoreThreshold), 10, 4));
            m_qurey.bindValue(":matchTime",frd.matchTime);
        }

        if(sql.isEmpty())
        {
            m_db.close();
            return 0;
        }

        bool ret= m_qurey.exec();
        if(!ret)
        {
            qCritical()<<m_qurey.lastError();
            m_db.close();
            return 0;
        }

        if(ret)
        {
            ret=m_db.commit();
        }
        if(!ret)
        {
            ret=m_db.rollback();
            m_db.close();
            return 0;
        }
        m_qurey.clear();
        m_db.close();
        return 1;
    } catch (std::exception &ex) {
        qCritical()<<ex.what();
        return 0;
    }
}

template<class T>
int SqliteDB<T>::updateItem(T obj, QString table)
{
    try{
        if(QSqlDatabase::contains("facerecognition_db")){
            m_db =QSqlDatabase::database("facerecognition_db");
        }
        else{
            m_db =QSqlDatabase::addDatabase("QSQLITE","facerecognition_db");
        }
        if(m_dbFilePath.isEmpty())
        {
            qCritical()<<"sqlite db not exist";
            throw std::runtime_error("sqlite db not exist");
        }
        QFile file(m_dbFilePath);
        if(!file.exists())
        {
            qCritical()<<"sqlite db not exist";
            throw std::runtime_error("sqlite db not exist");
        }
        m_db.setDatabaseName(m_dbFilePath);
        if(!m_db.open())
        {
            qCritical()<<"sqlite db not open"<<m_db.lastError();
            throw std::runtime_error("sqlite db not open");
        }

        m_db.transaction();
        QSqlQuery m_qurey=QSqlQuery(m_db);

        QString sql;
        if(table=="identifyrecord_tb"){
            FIResultData frd=obj;
            sql=QString("update identifyrecord_tb set "
                        "passagewayId=:passagewayId,"
                        "idType=:idType,"
                        "idName=:idName,"
                        "idEName=:idEName,"
                        "idGender=:idGender,"
                        "idFolk=:idFolk,"
                        "idBirthDay=:idBirthDay,"
                        "idCode=:idCode,"
                        "idAddress=:idAddress,"
                        "idAgency=:idAgency,"
                        "idExpireStart=:idExpireStart,"
                        "idExpireEnd=:idExpireEnd,"
                        "idPrCode=:idPrCode,"
                        "idNation=:idNation,"
                        "idVersion=:idVersion,"
                        "idAgencyCode=:idAgencyCode,"
                        "liveImageAge=:liveImageAge,"
                        "liveImageGender=:liveImageGender,"
                        "idImageType=:idImageType,"
                        "idImagePath=:idImagePath,"
                        "liveImagePath=:liveImagePath,"
                        "liveFrameImageJPGPath=:liveFrameImageJPGPath,"
                        "matchResult=:matchResult,"
                        "matchScore=:matchScore,"
                        "matchScoreThreshold=:matchScoreThreshold,"
                        "matchTime=:matchTime "
                        "where id=:id");
            m_qurey.prepare(sql);

            m_qurey.bindValue(":passagewayId",frd.passagewayId);
            m_qurey.bindValue(":idType",frd.idType);
            m_qurey.bindValue(":idName",frd.name);
            m_qurey.bindValue(":idEName",frd.eName);
            m_qurey.bindValue(":idGender",frd.gender);
            m_qurey.bindValue(":idFolk",frd.folk);
            m_qurey.bindValue(":idBirthDay",frd.birthDay);
            m_qurey.bindValue(":idCode",frd.code);
            m_qurey.bindValue(":idAddress",frd.address);
            m_qurey.bindValue(":idAgency",frd.agency);
            m_qurey.bindValue(":idExpireStart",frd.expireStart);
            m_qurey.bindValue(":idExpireEnd",frd.expireEnd);
            m_qurey.bindValue(":idPrCode",frd.prCode);
            m_qurey.bindValue(":idNation",frd.nation);
            m_qurey.bindValue(":idVersion",frd.idVersion);
            m_qurey.bindValue(":idAgencyCode",frd.agencyCode);
            m_qurey.bindValue(":liveImageAge",frd.liveImageAge);
            m_qurey.bindValue(":liveImageGender",frd.liveImageGender);
            m_qurey.bindValue(":idImageType",frd.idImageType);
            m_qurey.bindValue(":idImagePath",frd.idImagePath);
            m_qurey.bindValue(":liveImagePath",frd.liveImagePath);
            m_qurey.bindValue(":liveFrameImageJPGPath",frd.liveFrameImageJPGPath);
            m_qurey.bindValue(":matchResult",frd.matchResult);
            m_qurey.bindValue(":matchScore",frd.matchScore);
            m_qurey.bindValue(":matchScoreThreshold",frd.matchScoreThreshold);
            m_qurey.bindValue(":matchTime",frd.matchTime);
            m_qurey.bindValue(":id",frd.id);

        }

        if(sql.isEmpty())
        {
            m_db.close();
            return 0;
        }

        bool ret= m_qurey.exec();
        if(!ret)
        {
            qCritical()<<m_qurey.lastError();
            m_db.close();
            return 0;
        }

        if(ret)
        {
            ret=m_db.commit();
        }
        if(!ret)
        {
            ret=m_db.rollback();
            m_db.close();
            return 0;
        }
        m_db.close();
        return 1;
    } catch (std::exception &ex) {
        qCritical()<<ex.what();
        return 0;
    }
}

#endif // SQLITEDB_H

