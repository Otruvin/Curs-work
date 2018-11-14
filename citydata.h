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
    CityData(const QString &country, const QString &cityName);
    ~CityData() = default;


    QString getLatitude() const;
    QString getLongitude() const;
    QString getCountry() const;
    QString getCityName() const;
    QJsonObject getJSONCityData() const;


    void setLatitude(const double &latitude);
    void setLongitude(const double &longitude);
    void setCountry(const QString &country);
    void setCityName(const QString &cityName);
};

#endif // CITYDATA_H
