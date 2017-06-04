#include "broadcastthread.h"

BroadcastThread::BroadcastThread(QObject *parent) :
    QObject(parent),
    bStop(true)
{
    timeCount = 0;
    frameCount = 0;

    datagram.resize(STD_FRAME_SIZE);
    datagram.fill(0xAA);
    datagram[0] = 0x1A;
    datagram[1] = 0xCF;
    datagram[2] = 0xFC;
    datagram[3] = 0x1D;
    datagram[4] = 0x00;
    datagram[5] = 0xDC;
    ///
    sender = new QUdpSocket(this);
    logger = new Logger(this);
    connect(this, SIGNAL(ReadyWrite(QString)), logger, SLOT(writeLog(QString)));
}

void BroadcastThread::setBroadcastStatus(bool Stop)
{
    bStop = Stop;
}

/// 本方法只适用于所定义的广播帧
void BroadcastThread::calcCheckSum(QByteArray &data)
{
    if(data.size() != STD_FRAME_SIZE)
    {
        return;
    }
    quint16 nCheckSum = 0x0000;
    ///
    for(quint32 i = 4; i < STD_FRAME_SIZE-2; i++)
    {
        nCheckSum += data[i]; /// 从同步头后开始校验，溢出不处理，只要剩余部分
    }
    memcpy(data.data()+1022, (char*)&nCheckSum, sizeof(quint16));
}

quint64 BroadcastThread::getTimeCount() const
{
    return timeCount;
}

void BroadcastThread::onBroadcast()
{
    if (!bStop)
    {
        mutex.lock();
        timeCount++;
        frameCount++;
        memcpy(datagram.data() + 6, (char*)&frameCount, sizeof(frameCount));
        memcpy(datagram.data() + 10, (char*)&timeCount, sizeof(timeCount));
        mutex.unlock();
        ///
        calcCheckSum(datagram);
        ///
        qint64 nWrite = sender->writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast, 7007);
        if (nWrite != datagram.size())
        {
            emit ReadyWrite(tr("广播消息发送异常。"));
        }
        ///qDebug() << "QHostAddress::Broadcast, Port 7007 continue...";
    }

}
