#include "task.h"

Task::Task(QObject *parent) : QObject(parent)
{
    logger = new Logger(this);
    connect(this, SIGNAL(ReadyWrite(QString)), logger, SLOT(writeLog(QString)));
}
void Task::run()
{
    QString strTime;
    QString strContext;
    //
    QSqlQuery query;
    query.exec("SELECT * FROM tbl_logger");
    while(query.next())
    {
        strTime = query.value(0).toString();
        strContext = query.value(1).toString();
        emit Result(strTime, strContext);
        QThread::sleep(1);
    }
    emit ReadyWrite(tr("日志查询服务结束。"));
}
