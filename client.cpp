#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    logger = new Logger(this);
    connect(this, SIGNAL(ReadyWrite(QString)), logger, SLOT(writeLog(QString)));
}

void Client::setSocket(int Descriptor)
{
    nDescriptor = Descriptor;
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    socket->setSocketDescriptor(Descriptor);
}

void Client::connected()
{
    //qDebug() << "client connected event";
    emit ReadyWrite(tr("客户端：%1已经连接").arg(QString::number(nDescriptor)));
}

void Client::disconnected()
{
    //qDebug() << "client disconnected";
    emit ReadyWrite(tr("客户端：%1退出连接").arg(QString::number(nDescriptor)));
}

void Client::readyRead()
{
    QByteArray request = socket->readAll();

    //qDebug() << "Client request msg:" << request;

    quint8 OpCode = request[5];

    if (OpCode == 0xEF) ///查询日志请求
    {
        Task* task = new Task();
        task->setAutoDelete(true);
        connect(task, SIGNAL(Result(QString,QString)), this, SLOT(TaskResult(QString,QString)), Qt::QueuedConnection);
        QThreadPool::globalInstance()->start(task);
        emit ReadyWrite(tr("开始日志查询服务，请求客户端：%1。").arg(QString::number(nDescriptor)));
    }
}

void Client::TaskResult(QString strTime, QString strContext)
{
    strTime += strContext;
    QByteArray buffer = strTime.toUtf8();
    //buffer.append("\n");
    //qDebug() << "Client send:" << buffer;
    socket->write(buffer);
}
