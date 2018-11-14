#include "citydata.h"


CityData::CityData(const QString &latitude, const QString &longitude,
                   const QString &country, const QString &cityName)
{
    this->latitude = latitude;
    this->longitude = longitude;
    this->country = country;
    this->cityName = cityName;
}

CityData::CityData(const QString &country, const QString &cityName)
{
    QFile file("/home/otruvin/QtProject/CursWork/worldcities.csv");

        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            qDebug("File with cities not found!");
        }else
        {
            QTextStream in(&file);

            while (!file.atEnd())
            {
                QString line = in.readLine();

                QStringList tempList = line.split(",");

                if (tempList.at(1).contains(cityName) && tempList.at(4).contains(country))
                {

                    for (int i = 1; i < 5; ++i)
                    {
                        tempList[i].chop(1);
                        tempList[i].remove(0,1);
                    }

                    this->latitude = tempList.at(2);
                    this->longitude = tempList.at(3);
                    this->country = tempList.at(4);
                    this->cityName = tempList.at(1);

                    break;
                }

            }

            file.close();
        }
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

void CityData::setLatitude(const double &latitude)
{
    this->latitude = latitude;
}

void CityData::setLongitude(const double &longitude)
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
