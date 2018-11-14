#include "viewforecast.h"
#include "ui_viewforecast.h"
#include <QDebug>
#include <iostream>

ViewForecast::ViewForecast(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewForecast)
{
    ui->setupUi(this);
}

ViewForecast::~ViewForecast()
{
    delete ui;
}

void ViewForecast::recieveForecast(QMultiMap<int, WeatherData *> forecast)
{
    ui->listWidget->clear();
    qDebug() << forecast << endl;
    //QMultiMap<int, WeatherData*>::iterator i = forecast.constBegin();

    QList<WeatherData*> weather = forecast.values();
    QList<int> days = forecast.keys();

    qDebug() << days << endl;

    QString day;

    for(int i = 0; i < weather.size(); ++i)
    {
        if(days[i] == 1)
        {
            day = QStringLiteral("Понедельник");
        }else if(days[i] == 2)
        {
            day = QStringLiteral("Вторник");
        }else if(days[i] == 3)
        {
            day = QStringLiteral("Среда");
        }else if(days[i] == 4)
        {
            day = QStringLiteral("Четверг");
        }else if(days[i] == 5)
        {
            day = QStringLiteral("Пятница");
        }else if(days[i] == 6)
        {
            day = QStringLiteral("Суббота");
        }else if(days[i] == 7)
        {
            day = QStringLiteral("Воскресенье");
        }

        ui->listWidget->addItem(day + " "
                                + weather[i]->getTime() + " Температура: "
                                + weather[i]->getTemperature() + " °C   Погода: "
                                + weather[i]->getWeatherDescription());
    }


}

void ViewForecast::on_backToMainMenu_clicked()
{
    hide();
}
