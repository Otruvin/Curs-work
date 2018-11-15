#pragma once
#ifndef WEATHERDATA_H
#define WEATHERDATA_H
#include <QString>

class WeatherData
{

private:
    QString weatherDescription;
    QString weatherIcon;
    QString pressure;
    QString humidity;
    QString tempMin;
    QString tempMax;
    QString temperature;
    QString time;
public:


    WeatherData(const QString &weatherDescription, const QString &weatherIcon,
                const QString &pressure, const QString &humidity,
                const QString &tempMin, const QString &tempMax,
                const QString &temperature, const QString &time);
    WeatherData();
    ~WeatherData() = default;


    void setWeatherDescription(const QString &weatherDescription);
    void setWeatherIcon(const QString &weatherIcon);
    void setPressure(const QString &pressure);
    void setHumidity(const QString &humidity);
    void setTempMin(const QString &tempMin);
    void setTempMax(const QString &tempMax);
    void setTemperature(const QString &temperature);
    void setTime(const QString &time);


    QString getWeatherDescription() const;
    QString getWeatherIcon() const;
    QString getPressure() const;
    QString getHumidity() const;
    QString getTempMin() const;
    QString getTempMax() const;
    QString getTemperature() const;
    QString getTime() const;
};

#endif // WEATHERDATA_H
