#include "itemforecastwidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>

ItemForecastWidget::ItemForecastWidget(QWidget *parent) : QWidget(parent)
{

}

ItemForecastWidget::ItemForecastWidget(QString weekDay, QString time, QString weatherDescription, QString temp, QString humidity, QString weatherIcon, QString date)
{

    this->layout = new QHBoxLayout();
    this->pixmapForHumidityLabel = new QPixmap();
    this->pixmapForTempLabel = new QPixmap();
    this->pixmapForWeatherIcon = new QPixmap();
    this->humidityLabel = new QLabel(this);
    this->humidityValue = new QLabel(this);
    this->tempLabel = new QLabel(this);
    this->tempValue = new QLabel(this);
    this->weatherIconImg = new QLabel(this);
    this->weatherIconLabel = new QLabel(this);
    this->weekDay = new QLabel(this);
    this->date = new QLabel(this);
    this->layout->setMargin(0);

    this->weekDay->setText("Время: " + time + "\nДата: " + weekDay + " " + date);
    this->weekDay->setStyleSheet("font-size: 10pt;");
    this->weatherIconLabel->setText("Погода: " + weatherDescription);
    this->weatherIconLabel->setStyleSheet("font-size: 10pt");
    this->weatherIconImg->setFixedSize(QSize(50, 50));
    this->pixmapForWeatherIcon->load("C:/Users/Admin/Desktop/Curs-work/Icons_weather/" + weatherIcon + ".png");
    this->weatherIconImg->setPixmap(pixmapForWeatherIcon->scaled(weatherIconImg->width(), weatherIconImg->height() , Qt::KeepAspectRatio));
    this->tempLabel->setFixedSize(QSize(50, 40));
    this->pixmapForTempLabel->load("C:/Users/Admin/Desktop/Curs-work/Icons_weather/temp.png");
    this->tempLabel->setPixmap(pixmapForTempLabel->scaled(tempLabel->width(), tempLabel->height(), Qt::KeepAspectRatio));
    this->tempLabel->setAlignment(Qt::AlignRight);
    //this->tempLabel->setMaximumWidth(20);
    this->tempValue->setText(temp + " °C");
    this->humidityLabel->setFixedSize(QSize(50, 50));
    this->pixmapForHumidityLabel->load("C:/Users/Admin/Desktop/Curs-work/Icons_weather/rainy.png");
    this->humidityLabel->setPixmap(pixmapForHumidityLabel->scaled(humidityLabel->width(), humidityLabel->height(), Qt::KeepAspectRatio));
    this->humidityLabel->setAlignment(Qt::AlignRight);
    this->humidityValue->setText(humidity + " %");

    this->layout->addWidget(this->weekDay, 0, Qt::AlignRight);

    this->layout->addWidget(this->tempLabel, 5, Qt::AlignRight);
    this->layout->addWidget(this->tempValue, 6, Qt::AlignLeft);
    this->layout->addWidget(this->humidityLabel, 7, Qt::AlignRight);
    this->layout->addWidget(this->humidityValue, 8, Qt::AlignLeft);

    this->layout->addWidget(this->weatherIconLabel, 3, Qt::AlignRight);
    this->layout->addWidget(this->weatherIconImg, 4, Qt::AlignLeft);

    this->setLayout(this->layout);

}

ItemForecastWidget::~ItemForecastWidget()
{
    delete this->humidityLabel;
    delete this->humidityValue;
    delete this->layout;
    delete this->pixmapForHumidityLabel;
    delete this->pixmapForTempLabel;
    delete this->pixmapForWeatherIcon;
    delete this->tempLabel;
    delete this->tempValue;
    delete this->weatherIconImg;
    delete this->weatherIconLabel;
    delete this->weekDay;
    delete this->date;

}

