#ifndef SQLITEDB_H
#define SQLITEDB_H

#include "Common/paramdef.h"

#include <QObject>
#include <QMap>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QVariant>
#include <QVector>
#include <QString>

template <class T>
class SqliteDB :public QObject
{
    Q_OBJECT
public:
    SqliteDB();
    ~SqliteDB();
    void createConnection();
    void releaseConnection();
    QSqlQuery query(QString sql);
    QVector<T> selectItems(QString sql,QString table);
    int insertItem(T obj,QString table);
    int deleteItem(QString sql);
    int updateItem(T obj,QString table);

private:
    void CheckConnection();
};

#endif // SQLITEDB_H
