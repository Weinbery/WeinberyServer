#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QtSql>
#include <QDebug>

static bool createConnection()
{
    /// 创建DB文件，创建表格
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("WeinberyServer.db");
    ///
    if (!db.open())
    {
        qDebug() << "连接数据库失败!";
        return false;
    }
    QSqlQuery query;
    bool bOk = query.exec("CREATE TABLE IF NOT EXISTS tbl_logger("
                          "timestamp text, context text)");
    if (!bOk)
    {
        qDebug() << "创建运行日志表失败!";
        return false;
    }
    bOk = query.exec("CREATE TABLE IF NOT EXISTS City(ID INTEGER PRIMARY KEY NOT NULL,"
                                             "Name TEXT NOT NULL DEFAULT '',"
                                             "CountryCode TEXT NOT NULL DEFAULT '',"
                                             "District TEXT NOT NULL DEFAULT '',"
                                             "Population INTEGER NOT NULL DEFAULT 0)");
    if (!bOk)
    {
        qDebug() << "创建运行城市表失败!";
        return false;
    }

    bOk = query.exec("CREATE TABLE IF NOT EXISTS Country("
      "Code TEXT NOT NULL,"
      "Name TEXT NOT NULL,"
      "Continent TEXT NOT NULL,"
      "Region TEXT NOT NULL,"
      "SurfaceArea REAL NOT NULL,"
      "IndepYear INTEGER,"
      "Population INTEGER NOT NULL,"
      "LifeExpectancy REAL,"
      "GNP REAL,"
      "GNPOld REAL,"
      "LocalName TEXT NOT NULL,"
      "GovernmentForm TEXT NOT NULL,"
      "HeadOfState TEXT,"
      "Capital INTEGER,"
      "Code2 TEXT NOT NULL,"
      "PRIMARY KEY('Code'))");
    if (!bOk)
    {
        qDebug() << "创建国家表失败!";
        return false;
    }

    bOk = query.exec("CREATE TABLE IF NOT EXISTS CountryLanguage("
      "CountryCode TEXT NOT NULL,"
      "Language TEXT NOT NULL,"
      "IsOfficial INTEGER NOT NULL DEFAULT 0,"
      "Percentage REAL NOT NULL,"
      "PRIMARY KEY(CountryCode, Language))");
    if (!bOk)
    {
        qDebug() << "创建国家语言表失败!";
        return false;
    }
/*
    bOk = query.exec("CREATE TRIGGER IF NOT EXISTS Delete_Country DELETE ON Country"
      "BEGIN"
        "DELETE FROM City WHERE CountryCode = old.Code;"
        "DELETE FROM CountryLanguage WHERE CountryCode = old.Code;"
      "END");
    if (!bOk)
    {
        qDebug() << "创建国家表触发失败!";
        return false;
    }
*/
    return true;
}

#endif // SQLITEDATABASE_H
