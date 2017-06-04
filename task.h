#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QRunnable>
#include "logger.h"

class Task : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = 0);

signals:
    void ReadyWrite(QString strContext);

    void Result(QString strTime, QString strContext);

protected:
    void run();

public slots:

private:
    Logger *logger;
};

#endif // TASK_H
