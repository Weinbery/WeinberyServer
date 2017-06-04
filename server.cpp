#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    logger = new Logger(this);
    connect(this, SIGNAL(ReadyWrite(QString)), logger, SLOT(writeLog(QString)));
    ///
    broadcastThread = new BroadcastThread();
    ///
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), broadcastThread, SLOT(onBroadcast()));
}

void Server::startServer()
{
    if (this->listen(QHostAddress::Any, 7070))
    {
        /// 只有服务器启动成功，才能进行后续的服务
        emit ReadyWrite(tr("服务器启动成功，监听端口：7070。"));
        broadcastThread->setBroadcastStatus(false);
        timer->start(1000);
        emit ReadyWrite(tr("服务器开始广播，广播端口：7007。"));
    }
    else
    {
        emit ReadyWrite(tr("服务器启动失败。"));
    }
}

void Server::incomingConnection(int handle)
{
    Client* client = new Client(this);
    client->setSocket(handle);
    ///
    emit ReadyWrite(tr("客户端：%1已经连接。").arg(QString::number(handle)));
}
