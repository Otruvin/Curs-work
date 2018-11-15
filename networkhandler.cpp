#include "networkhandler.h"

NetworkHandler::NetworkHandler(QObject *parent) : QObject(parent)
{
    accessManager = new QNetworkAccessManager();
    realTimeweatherData = new WeatherData();
    //connect(accessManager, &QNetworkAccessManager::finished, this, &NetworkHandler::onResult);
}

WeatherData* NetworkHandler::getRealTimeWeatherData() const
{
    return this->realTimeweatherData;
}

QMultiMap<int, WeatherData *> NetworkHandler::getWeatherForecast() const
{
    return this->weatherForecast;
}

void NetworkHandler::makeCityQuery(const CityData &city)
{
    QString ppid = QStringLiteral("cee8f380d51692f89832bb6160c7c4a9");
    QEventLoop eventLoop;
    QUrl urlForRealTimeWeather("http://api.openweathermap.org/data/2.5/weather");
    QUrlQuery queryForRealTimeWeather;

    queryForRealTimeWeather.addQueryItem("lat", city.getLatitude());
    queryForRealTimeWeather.addQueryItem("lon", city.getLongitude());
    queryForRealTimeWeather.addQueryItem("lang", "ru");
    queryForRealTimeWeather.addQueryItem("units", "metric");
    queryForRealTimeWeather.addQueryItem("mode", "json");
    queryForRealTimeWeather.addQueryItem("APPID", ppid);
    urlForRealTimeWeather.setQuery(queryForRealTimeWeather);


    QNetworkReply *replyForRealTimeWeather = accessManager->get(QNetworkRequest(urlForRealTimeWeather));
    connect(replyForRealTimeWeather, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    QUrl urlForForecast("http://api.openweathermap.org/data/2.5/forecast");
    QUrlQuery queryForForecast;

    queryForForecast.addQueryItem("lat", city.getLatitude());
    queryForForecast.addQueryItem("lon", city.getLongitude());
    queryForForecast.addQueryItem("lang", "ru");
    queryForForecast.addQueryItem("units", "metric");
    queryForForecast.addQueryItem("mode", "json");
    queryForForecast.addQueryItem("cnt", "40");
    queryForForecast.addQueryItem("APPID", ppid);
    urlForForecast.setQuery(queryForForecast);

    QNetworkReply *replyForForecast = accessManager->get(QNetworkRequest(urlForForecast));
    connect(replyForForecast, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    onResult(replyForRealTimeWeather, replyForForecast);
}

NetworkHandler::~NetworkHandler()
{
    delete accessManager;
    delete realTimeweatherData;

}

void NetworkHandler::onResult(QNetworkReply *replyForRealTimeWeather, QNetworkReply *replyForForecast)
{
    if(replyForRealTimeWeather->error())
    {
        qDebug() << "Error with reply for realtime weather";
        qDebug() << replyForRealTimeWeather->errorString();

    }else
    {
        QJsonDocument documentWithRealtimeWeather = QJsonDocument::fromJson(replyForRealTimeWeather->readAll());

        if(documentWithRealtimeWeather.isObject())
        {
            QJsonObject object = documentWithRealtimeWeather.object();
            QJsonObject tempObject;
            QJsonValue value;

            if(object.contains("weather"))
            {
                value = object.value("weather");
                QJsonArray weatherArray = value.toArray();
                value = weatherArray.at(0);
                tempObject = value.toObject();
                this->realTimeweatherData->setWeatherDescription(tempObject.value("description").toString());
                this->realTimeweatherData->setWeatherIcon(tempObject.value("icon").toString());
            }
            if(object.contains("main"))
            {
                value = object.value("main");
                tempObject = value.toObject();
                this->realTimeweatherData->setTemperature(QString::number(tempObject.value("temp").toDouble()));
                this->realTimeweatherData->setPressure(QString::number(tempObject.value("pressure").toDouble()));
                this->realTimeweatherData->setHumidity(QString::number(tempObject.value("humidity").toDouble()));
                this->realTimeweatherData->setTempMin(QString::number(tempObject.value("temp_min").toDouble()));
                this->realTimeweatherData->setTempMax(QString::number(tempObject.value("temp_max").toDouble()));
                this->realTimeweatherData->setTime(NULL);

            }

        }
    }

    replyForRealTimeWeather->deleteLater();

    if(replyForForecast->error())
    {
        qDebug() << "Error with reply for forecast" << endl;
        qDebug() << replyForForecast->errorString();
    }else
    {
        if(!this->weatherForecast.isEmpty())
        {
            this->weatherForecast.clear();
        }

        QJsonDocument documentWithForecast = QJsonDocument::fromJson(replyForForecast->readAll());

        if(documentWithForecast.isObject())
        {
            QJsonObject object = documentWithForecast.object();
            QJsonObject tempObject;
            QJsonObject tempMain;
            QJsonArray forecastList = object.value("list").toArray();
            QJsonObject tempWeatherObject;
            QString tempData;
            QStringList dateAndTime;

            for(QJsonValue tempValue: forecastList)
            {
                tempObject = tempValue.toObject();
                tempWeatherObject = tempObject.value("weather").toArray().at(0).toObject();
                tempData = tempObject.value("dt_txt").toString();

                if(tempObject.contains("main"))
                {
                    tempMain = tempObject.value("main").toObject();
                    dateAndTime = tempData.split(" ");
                    this->weatherForecast.insert(QDate::fromString(tempData.split(" ").at(0), "yyyy-MM-dd").dayOfWeek(), new WeatherData(tempWeatherObject.value("description").toString(),
                                                                           tempWeatherObject.value("icon").toString(),
                                                                           QString::number(tempMain.value("pressure").toDouble()),
                                                                           QString::number(tempMain.value("humidity").toDouble()),
                                                                           QString::number(tempMain.value("temp_min").toDouble()),
                                                                           QString::number(tempMain.value("temp_max").toDouble()),
                                                                           QString::number(tempMain.value("temp").toDouble()),
                                                                           dateAndTime.at(1)));
                }
            }
        }

    }

    replyForForecast->deleteLater();
}



