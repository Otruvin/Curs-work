#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QUrlQuery>
#include <QUrl>
#include <QEventLoop>
#include <QJsonArray>
#include "citydata.h"
#include "weatherdata.h"

class NetworkHandler : public QObject
{
    Q_OBJECT
public:
    explicit NetworkHandler(QObject *parent = nullptr);
    WeatherData* getRealTimeWeatherData() const;
    QMultiMap<int, WeatherData*> getWeatherForecast() const;
    void makeCityQuery(const CityData &city);
    ~NetworkHandler();

signals:
    //void onReady();

public slots:
    void onResult(QNetworkReply *replyForRealTimeWeather, QNetworkReply *replyForForecast);

private:
    QNetworkAccessManager *accessManager;
    WeatherData *realTimeweatherData;
    QMultiMap<int, WeatherData*> weatherForecast;
};

#endif // NETWORKHANDLER_H
