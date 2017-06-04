#ifndef BROADCASTTHREAD_H
#define BROADCASTTHREAD_H

#include <QtNetwork>
#include <QObject>
#include <QDebug>
#include <QMutex>
#include "logger.h"
/**
 * @brief The BroadcastThread class
 * 广播消息，也许采用定时器QTimer方式更为合适
 */

class BroadcastThread : public QObject
{
    Q_OBJECT
public:
    explicit BroadcastThread(QObject *parent = 0);

    void setBroadcastStatus(bool Stop);

    void calcCheckSum(QByteArray &data);

public:
    const quint32 STD_FRAME_SIZE = 1024;

    quint64 getTimeCount() const;

signals:
    void ReadyWrite(QString strContext);

public slots:
    void onBroadcast(); /// 定时广播

private:
    bool bStop;
    quint32 frameCount;
    quint64 timeCount;
    QMutex mutex;
    Logger *logger;
    QByteArray datagram;
    QUdpSocket *sender;
};

#endif // BROADCASTTHREAD_H
