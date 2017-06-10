#include "task.h"

Task::Task(QObject *parent) : QObject(parent), funcOpt(OPT_NONE)
{
    logger = new Logger(this);
    connect(this, SIGNAL(ReadyWrite(QString)), logger, SLOT(writeLog(QString)));
}

void Task::setFunctionOption(FUNCTION_OPTION opt)
{
    funcOpt = opt;
}

void Task::run()
{
    switch (funcOpt)
    {
    case OPT_NONE:
        break;
    case OPT_LOGGER:
        QueryLogger();
        break;
    case OPT_CITY:
        QueryCity();
        break;
    case OPT_COUNTRY:
        QueryCountry();
        break;
    case OPT_COUNTRY_LANGUAGE:
        QueryCountryLanguage();
    default:
        break;
    }
}

void Task::QueryLogger()
{
    QListLog loglist;
    //
    QSqlQuery query;
    query.exec("SELECT * FROM tbl_logger");
    while(query.next())
    {
        Log log;
        log.strTime = query.value(0).toString();
        log.strContext = query.value(1).toString();
        loglist.append(log);
    }
    // 查询完毕
    emit LoggerQueryResult(loglist);
    //
    emit ReadyWrite(tr("日志查询服务结束。"));
}

void Task::QueryCity()
{
    QListCity citylist;
    //
    QSqlQuery query;
    query.exec("SELECT * FROM City");
    while(query.next())
    {
        City city;
        city.id = query.value(0).toInt();
        city.name = query.value(1).toString();
        city.countryCode = query.value(2).toString();
        city.district = query.value(3).toString();
        city.population = query.value(4).toInt();
        citylist.append(city);
    }
    // 查询完毕
    emit CityQueryResult(citylist);
    //
    emit ReadyWrite(tr("城市信息群查询服务结束。"));
}

void Task::QueryCountry()
{
    QListCountry countrylist;

    QSqlQuery query;
    query.exec("SELECT * FROM Country");
    while(query.next())
    {
        Country country;
        country.code = query.value(0).toString();
        country.name = query.value(1).toString();
        country.continent = query.value(2).toString();
        country.region = query.value(3).toString();
        country.surfaceArea = query.value(4).toFloat();
        country.indepYear = query.value(5).toInt();
        country.population = query.value(6).toInt();
        country.lifeExpectancy = query.value(7).toFloat();
        country.gnp = query.value(8).toFloat();
        country.oldgnp = query.value(9).toFloat();
        country.localName = query.value(10).toString();
        country.govermentFrom = query.value(11).toString();
        country.headOfState = query.value(12).toString();
        country.captial = query.value(13).toInt();
        country.code2 = query.value(14).toString();
        //
        countrylist.append(country);
    }
    // 查询完毕
    emit CountryQueryResult(countrylist);
    //
    emit ReadyWrite(tr("国家信息查询服务结束。"));
}

void Task::QueryCountryLanguage()
{
    QListCountryLanguage countrylanguagelist;

    QSqlQuery query;
    query.exec("SELECT * FROM Country");
    while(query.next())
    {
        CountryLanguage countryLanguage;
        countryLanguage.countryCode = query.value(0).toString();
        countryLanguage.language = query.value(1).toString();
        countryLanguage.isOfficial = query.value(2).toInt();
        countryLanguage.percentage = query.value(3).toFloat();
    }
}
