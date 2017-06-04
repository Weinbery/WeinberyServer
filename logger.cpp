#include "logger.h"
#include <QDebug>

Logger::Logger(QObject *parent) : QObject(parent)
{

}

void Logger::writeLog(QString strContext)
{
    /// 时间戳
    QString strTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ///
    QSqlQuery query;
    query.prepare("insert into tbl_logger(timestamp, context) values(:timestamp, :context)");
    query.bindValue(":timestamp", strTime);
    query.bindValue(":context", strContext);
    bool bOk = query.exec();
    if (!bOk)
    {
        qDebug() << "插入日志失败";
    }
    strTime = "[" + strTime + "] " + strContext;
    qDebug() << strTime;
}
