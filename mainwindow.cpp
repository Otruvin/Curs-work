#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "citydata.h"
#include "networkhandler.h"
#include "weatherdata.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    networkHandler = new NetworkHandler();
    forecastWindow = new ViewForecast();
    connect(this, SIGNAL(sendForecast(QMultiMap<int,WeatherData*>)), forecastWindow, SLOT(recieveForecast(QMultiMap<int,WeatherData*>)));
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete networkHandler;
    delete forecastWindow;
    delete cityData;
    delete ui;
}

void MainWindow::on_okSearch_clicked()
{

    QStringList searchParam = ui->search->text().split(",");

    this->cityData = new CityData(searchParam.at(0), searchParam.at(1));

    QJsonObject jsonObject = cityData->getJSONCityData();
    QJsonDocument document(jsonObject);
    QString stringJson(document.toJson(QJsonDocument::Compact));

    std::cout << stringJson.toStdString() << std::endl;

    this->networkHandler->makeCityQuery(*cityData);

    WeatherData *weatherData = networkHandler->getRealTimeWeatherData();
    this->weatherForecast = networkHandler->getWeatherForecast();

    ui->humidityL->setText(weatherData->getHumidity() + " %");
    ui->pressureL->setText(weatherData->getPressure() + " hPa");
    ui->temperatureL->setText(weatherData->getTemperature() + " °C");
    ui->weatherDescrL->setText(weatherData->getWeatherDescription());
    ui->maxTemperatureL->setText(weatherData->getTempMax() + " °C");
    ui->minTemperatureL->setText(weatherData->getTempMin() + " °C");

    ui->search->clear();
}

void MainWindow::on_viewForecast_clicked()
{

    emit sendForecast(this->weatherForecast);

    forecastWindow->show();
}
