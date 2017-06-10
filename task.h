#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QRunnable>
#include "logger.h"
#include "defination.h"

class Task : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = 0);

public:
    void setFunctionOption(FUNCTION_OPTION opt);

signals:
    void ReadyWrite(QString strContext);
    // 数据查询结果
    void LoggerQueryResult(QListLog loglist);
    void CityQueryResult(QListCity citylist);
    void CountryQueryResult(QListCountry countrylist);
    void CountryLanguageQueryResult(QListCountryLanguage countryLanguagelist);

protected:
    void run();

public slots:

private:
    Logger *logger;
    FUNCTION_OPTION funcOpt;

private:
    void QueryLogger();
    void QueryCity();
    void QueryCountry();
    void QueryCountryLanguage();
};

#endif // TASK_H
