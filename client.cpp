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
    QByteArray requestMsg = socket->readAll();

    quint8 OpCode = requestMsg[5]; /// 获取请求指令码，加以判断，属于什么请求

    if (OpCode == 0xAA) /// 查询日志请求
    {
        Task* task = new Task();
        task->setAutoDelete(true);
        task->setFunctionOption(OPT_LOGGER);
        qRegisterMetaType<QListLog>("QListLog");
        connect(task, SIGNAL(LoggerQueryResult(QListLog)), this, SLOT(LoggerQueryTask(QListLog)), Qt::QueuedConnection);
        QThreadPool::globalInstance()->start(task);
        emit ReadyWrite(tr("开始日志查询服务，请求客户端：%1。").arg(QString::number(nDescriptor)));
    }
    else if (OpCode == 0xBB)
    {
        Task* task = new Task();
        task->setAutoDelete(true);
        task->setFunctionOption(OPT_CITY);
        qRegisterMetaType<QListCity>("QListCity");
        connect(task, SIGNAL(CityQueryResult(QListCity)), this, SLOT(CityQueryTask(QListCity)), Qt::QueuedConnection);
        QThreadPool::globalInstance()->start(task);
        emit ReadyWrite(tr("开始城市信息查询服务，请求客户端：%1。").arg(QString::number(nDescriptor)));
    }
    else if (OpCode == 0xCC)
    {
        Task* task = new Task();
        task->setAutoDelete(true);
        task->setFunctionOption(OPT_COUNTRY);
        qRegisterMetaType<QListCountry>("QListCountry");
        connect(task, SIGNAL(CountryQueryResult(QListCountry)), this, SLOT(CountryQueryTask(QListCountry)), Qt::QueuedConnection);
        QThreadPool::globalInstance()->start(task);
        emit ReadyWrite(tr("开始国家信息查询服务，请求客户端：%1。").arg(QString::number(nDescriptor)));
    }
    else if (OpCode == 0xDD)
    {
        Task* task = new Task();
        task->setAutoDelete(true);
        task->setFunctionOption(OPT_COUNTRY_LANGUAGE);
        qRegisterMetaType<QListCountryLanguage>("QListCountryLanguage");
        connect(task, SIGNAL(CountryLanguageQueryResult(QListCountryLanguage)), this, SLOT(CountryLanguageQueryTask(QListCountryLanguage)), Qt::QueuedConnection);
        QThreadPool::globalInstance()->start(task);
        emit ReadyWrite(tr("开始国家语言查询服务，请求客户端：%1。").arg(QString::number(nDescriptor)));
    }
}

void Client::LoggerQueryTask(QListLog loglist)
{
    if(loglist.empty())
    {
        return;
    }
    QString strSerial = "";
    for (int i = 0; i < loglist.size(); i++)
    {
        Log log = loglist.at(i);
        strSerial += log.strTime;
        strSerial += "\t";
        strSerial += log.strContext;
        strSerial += "\n";
    }
    QByteArray buffer = strSerial.toUtf8();
    socket->write(buffer);
    emit ReadyWrite(tr("日志查询服务结束。"));
}

void Client::CityQueryTask(QListCity citylist)
{
    if(citylist.empty())
    {
        return;
    }

    QByteArray buffer;
    QDataStream dsOut(&buffer, QIODevice::ReadWrite);
    dsOut.setVersion(QDataStream::Qt_5_8);
    //
    for (int i = 0; i < citylist.size(); i++)
    {
        City city = citylist.at(i);
        dsOut << city.id << city.name << city.countryCode << city.district << city.population;
        //QThread::sleep(1);
        //qDebug() << "[DEBUG INFO] Current times =" << i;
    }
    socket->write(buffer);
    //
    emit ReadyWrite(tr("城市信息查询服务结束。"));
}

void Client::CountryQueryTask(QListCountry listcountry)
{

}

void Client::CountryLanguageQueryTask(QListCountryLanguage listcountrylanguage)
{

}
