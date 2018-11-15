#include "weatherdata.h"

WeatherData::WeatherData(const QString &weatherDescription,
                         const QString &weatherIcon,
                         const QString &pressure,
                         const QString &humidity,
                         const QString &tempMin,
                         const QString &tempMax,
                         const QString &temperature,
                         const QString &time)
{
    this->weatherDescription = weatherDescription;
    this->weatherIcon = weatherIcon;
    this->pressure = pressure;
    this->humidity = humidity;
    this->tempMin = tempMin;
    this->tempMax = tempMax;
    this->temperature = temperature;
    this->time = time;
}

WeatherData::WeatherData()
{

}

void WeatherData::setWeatherDescription(const QString &weatherDescription)
{
    this->weatherDescription = weatherDescription;
}

void WeatherData::setWeatherIcon(const QString &weatherIcon)
{
    this->weatherIcon = weatherIcon;
}

void WeatherData::setPressure(const QString &pressure)
{
    this->pressure = pressure;
}

void WeatherData::setHumidity(const QString &humidity)
{
    this->humidity = humidity;
}

void WeatherData::setTempMin(const QString &tempMin)
{
    this->tempMin = tempMin;
}

void WeatherData::setTempMax(const QString &tempMax)
{
    this->tempMax = tempMax;
}

void WeatherData::setTemperature(const QString &temperature)
{
    this->temperature = temperature;
}

void WeatherData::setTime(const QString &time)
{
    this->time = time;
}

QString WeatherData::getWeatherDescription() const
{
    return this->weatherDescription;
}

QString WeatherData::getWeatherIcon() const
{
    return this->weatherIcon;
}

QString WeatherData::getPressure() const
{
    return this->pressure;
}

QString WeatherData::getHumidity() const
{
    return this->humidity;
}

QString WeatherData::getTempMin() const
{
    return this->tempMin;
}

QString WeatherData::getTempMax() const
{
    return this->tempMax;
}

QString WeatherData::getTemperature() const
{
    return this->temperature;
}

QString WeatherData::getTime() const
{
    return this->time;
}
