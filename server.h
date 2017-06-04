#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "client.h"
#include "logger.h"
#include "broadcastthread.h"

/**
 * @brief The Server class
 * 目前服务器仅提供以下两个功能：
 * 1，提供时间广播功能
 * 2，提供日志查询功能
 */

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

    void startServer();

protected:
    void incomingConnection(int handle);

signals:
    void ReadyWrite(QString strContext);

private:
    Logger *logger;
    QTimer *timer;
    BroadcastThread *broadcastThread;
};

#endif // SERVER_H
