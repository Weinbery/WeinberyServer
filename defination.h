#ifndef DEFINATION_H
#define DEFINATION_H

#include <QObject>
#include <QtCore>
#include <QList>
#include <QMetaType>

typedef enum _FUNCTION_OPTION {
    OPT_NONE = 0,
    OPT_LOGGER,
    OPT_CITY,
    OPT_COUNTRY,
    OPT_COUNTRY_LANGUAGE,
}FUNCTION_OPTION;

typedef struct _Log
{
    QString strTime;
    QString strContext;
    _Log() {
        strTime = "";
        strContext = "";
    }
}Log;

typedef QList<Log> QListLog;

typedef struct _City
{
    quint32     id;
    QString     name;
    QString     countryCode;
    QString     district;
    quint32     population;
    _City() {
        id = 0;
        name = "";
        countryCode = "";
        district = "";
        population = 0;
    }
}City;

typedef QList<City> QListCity;

typedef struct _Country
{
    QString code;
    QString name;
    QString continent;
    QString region;
    float surfaceArea;
    quint32 indepYear;
    quint32 population;
    float lifeExpectancy;
    float gnp;
    float oldgnp;
    QString localName;
    QString govermentFrom;
    QString headOfState;
    quint32 captial;
    QString code2;

    _Country() {
        code = "";
        name = "";
        continent = "";
        region = "";
        surfaceArea = 0.0;
        indepYear = 0;
        population = 0;
        lifeExpectancy = 0.0;
        gnp = 0.0;
        oldgnp = 0.0;
        localName = "";
        govermentFrom = "";
        headOfState = "";
        captial = 0;
        code2 = "";
    }
}Country;

typedef QList<Country> QListCountry;

typedef struct _CountryLanguage
{
    QString countryCode;
    QString language;
    quint32 isOfficial;
    float percentage;
    _CountryLanguage() {
        countryCode = "";
        language = "";
        isOfficial = 0;
        percentage = 0.0;
    }
}CountryLanguage;

typedef QList<CountryLanguage> QListCountryLanguage;

#endif // DEFINATION_H
