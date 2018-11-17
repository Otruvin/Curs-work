#pragma once
#ifndef CITYDATA_H
#define CITYDATA_H
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QJsonObject>

class CityData
{
private:
    QString latitude;
    QString longitude;
    QString country;
    QString cityName;

public:

    CityData(const QString &latitude, const QString &longitude,
             const QString &country, const QString &cityName);
    CityData();
    ~CityData() = default;


    QString getLatitude() const;
    QString getLongitude() const;
    QString getCountry() const;
    QString getCityName() const;
    QJsonObject getJSONCityData() const;


    void setLatitude(const QString &latitude);
    void setLongitude(const QString &longitude);
    void setCountry(const QString &country);
    void setCityName(const QString &cityName);
};

#endif // CITYDATA_H
