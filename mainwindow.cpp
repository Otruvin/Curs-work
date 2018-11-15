#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "citydata.h"
#include "networkhandler.h"
#include "weatherdata.h"
#include "searchhelper.h"
#include <iostream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    networkHandler = new NetworkHandler();
    forecastWindow = new ViewForecast();
    fileHandler = new FileHandler();
    completerForSearch = new QCompleter(SearchHelper::getListWithCities(), this);
    ui->search->setCompleter(this->completerForSearch);
    connect(this, SIGNAL(sendForecast(QMultiMap<int,WeatherData*>)), forecastWindow, SLOT(recieveForecast(QMultiMap<int,WeatherData*>)));
    ui->clearSearchField->hide();
}

MainWindow::~MainWindow()
{
    delete fileHandler;
    delete networkHandler;
    delete forecastWindow;
    delete completerForSearch;
    delete cityData;
    delete ui;
}

void MainWindow::on_okSearch_clicked()
{

        if(ui->search->text().isEmpty())
        {
            QMessageBox::information(this, "Ошибка введенных данных", "Поле для ввода поисковых данных пустое");
        }else if(!ui->search->text().contains(","))
        {
            QMessageBox::information(this, "Ошибка формата введенных данных", "Формат ввода: город,страна");
        }else{

            QStringList searchParam = ui->search->text().split(",");

            this->cityData = new CityData(searchParam.at(1), searchParam.at(0));

            if(this->cityData->getLatitude() == 0 && this->cityData->getLongitude() == 0)
            {
            QMessageBox::information(this, "Ошибка введенных данных", "Не найдено городов с таким названием, или страной");
            }else{

                this->networkHandler->makeCityQuery(*cityData);

                WeatherData *weatherData = networkHandler->getRealTimeWeatherData();
                this->weatherForecast = networkHandler->getWeatherForecast();

                ui->humidityL->setText(weatherData->getHumidity() + " %");
                ui->pressureL->setText(weatherData->getPressure() + " hPa");
                ui->temperatureL->setText(weatherData->getTemperature() + " °C");
                ui->weatherDescrL->setText(weatherData->getWeatherDescription());
                ui->maxTemperatureL->setText(weatherData->getTempMax() + " °C");
                ui->minTemperatureL->setText(weatherData->getTempMin() + " °C");

            }

        }

        if(!ui->search->text().isEmpty())
        {
            ui->clearSearchField->show();
        }
}

void MainWindow::on_viewForecast_clicked()
{

    emit sendForecast(this->weatherForecast);

    forecastWindow->show();
}

void MainWindow::on_clearSearchField_clicked()
{
    ui->search->clear();

}
