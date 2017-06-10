#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>
#include "task.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

    void setSocket(int Descriptor);

signals:
    void ReadyWrite(QString strContext);

public slots:
    void connected();
    void disconnected();
    void readyRead();
    ///
    void LoggerQueryTask(QListLog loglist);
    void CityQueryTask(QListCity citylist);
    void CountryQueryTask(QListCountry listcountry);
    void CountryLanguageQueryTask(QListCountryLanguage listcountrylanguage);

private:
    int nDescriptor;
    Logger *logger;
    QTcpSocket *socket;
};

#endif // CLIENT_H
