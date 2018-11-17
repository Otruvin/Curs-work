#include "citydata.h"


CityData::CityData(const QString &latitude, const QString &longitude,
                   const QString &country, const QString &cityName)
{
    this->latitude = latitude;
    this->longitude = longitude;
    this->country = country;
    this->cityName = cityName;
}

CityData::CityData()
{

}

QString CityData::getLatitude() const
{
    return this->latitude;
}

QString CityData::getLongitude() const
{
    return this->longitude;
}

QString CityData::getCountry() const
{
    return this->country;
}

QString CityData::getCityName() const
{
    return this->cityName;
}

QJsonObject CityData::getJSONCityData() const
{
    QJsonObject jsonCity;

    jsonCity.insert("latitude", QJsonValue::fromVariant(this->latitude.toDouble()));
    jsonCity.insert("longitude", QJsonValue::fromVariant(this->longitude.toDouble()));
    jsonCity.insert("country", QJsonValue::fromVariant(this->country));
    jsonCity.insert("city_name", QJsonValue::fromVariant(this->cityName));

    return jsonCity;
}

void CityData::setLatitude(const QString &latitude)
{
    this->latitude = latitude;
}

void CityData::setLongitude(const QString &longitude)
{
    this->longitude = longitude;
}

void CityData::setCountry(const QString &country)
{
    this->country = country;
}

void CityData::setCityName(const QString &cityName)
{
    this->cityName = cityName;
}
