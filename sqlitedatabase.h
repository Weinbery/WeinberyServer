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
    bool bOk = query.exec("create table if not exists tbl_logger(timestamp text, context text)");
    if (!bOk)
    {
        qDebug() << "创建运行日志表失败!";
        return false;
    }

    return true;
}

#endif // SQLITEDATABASE_H
