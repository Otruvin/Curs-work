#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "citydata.h"
#include "networkhandler.h"
#include "weatherdata.h"
#include "searchhelper.h"
#include <iostream>
#include <QMessageBox>
#include <QIcon>
#include <QtGui>
#include <QListWidgetItem>
#include "itemforecastwidget.h"
//#define DEBUG = 1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cityData = new CityData();
    networkHandler = new NetworkHandler();
    fileHandler = new FileHandler();
    pixmapForWeatherIcon = new QPixmap();
    itemForecast = new QWidgetItem(this);
    favoraties = fileHandler->loadFavor();
    completerForSearch = new QCompleter(SearchHelper::getListWithCities(), this);
    this->optionsWindow = new OptionsWindow();


    connect(this, SIGNAL(sendForecast(QMultiMap<int, WeatherData*>)), this, SLOT(catchForecastToList(QMultiMap<int, WeatherData *>)));
    connect(this, SIGNAL(sendRealTimeWeather(WeatherData*)), this, SLOT(catchRealTimeWeather(WeatherData*)));
    connect(this->optionsWindow, SIGNAL(userCityAdded()), this, SLOT(searchChangeUserCity()));
    connect(this->optionsWindow, SIGNAL(userCityCleared()), this, SLOT(searchClearUserCity()));

    if(!fileHandler->loadCityUser().isEmpty())
    {

        lisWithUserCityCoords = this->fileHandler->loadCityUser().split(",");
        this->cityData->setCityName(lisWithUserCityCoords.at(0));
        this->cityData->setCountry(lisWithUserCityCoords.at(1));
        this->fileHandler->inserCoordCity(*cityData);
        this->networkHandler->makeCityQuery(*cityData);

        ui->selectedCountryAndCity->setText(this->cityData->getCityName() + ", " + this->cityData->getCountry());
        emit sendForecast(this->networkHandler->getWeatherForecast());
        emit sendRealTimeWeather(this->networkHandler->getRealTimeWeatherData());
    }else
    {
        ui->UserCityException->setText("Внимание! город пользователя не задан");
    }

    ui->search->setCompleter(this->completerForSearch);
    ui->clearSearchField->hide();

    refreshFavorList();
}

MainWindow::~MainWindow()
{
    fileHandler->saveFavor(this->favoraties);
    delete itemForecast;
    delete pixmapForWeatherIcon;
    delete cityData;
    delete optionsWindow;
    delete fileHandler;
    delete networkHandler;
    delete completerForSearch;
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

            this->searchCity = ui->search->text();
            searchParam = this->searchCity.split(",");

            this->cityData->setCountry(searchParam.at(1));
            this->cityData->setCityName(searchParam.at(0));

            this->fileHandler->inserCoordCity(*cityData);

            if(this->cityData->getLatitude() == 0 && this->cityData->getLongitude() == 0)
            {
            QMessageBox::information(this, "Ошибка введенных данных", "Не найдено городов с таким названием, или страной");
            }else{

                this->networkHandler->makeCityQuery(*cityData);

                ui->selectedCountryAndCity->setText(this->cityData->getCityName() + ", " + this->cityData->getCountry());

                emit sendForecast(this->networkHandler->getWeatherForecast());
                emit sendRealTimeWeather(this->networkHandler->getRealTimeWeatherData());

            }

        }

            ui->clearSearchField->show();

}

void MainWindow::on_clearSearchField_clicked()
{
    ui->search->clear();
    ui->clearSearchField->hide();
}

void MainWindow::on_addFavorCity_clicked()
{
    if(!this->searchCity.isEmpty())
    {
        this->favoraties.insert(this->searchCity);
        refreshFavorList();
    }else
    {
        QMessageBox::information(this, "Ошибка введенных данных", "Вы пытаетесь добавить город без заданных данных");
    }

}

void MainWindow::on_dropFavorCity_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Подтверждение удаления города из избранного",
                                                              "Вы действительно хотите удалить из избранного выбранный город?",
                                                              QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes)
    {
        this->favoraties.remove(ui->listWidget->selectedItems().at(0)->text());
        refreshFavorList();
    }
}

void MainWindow::on_clearFavoraties_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Подтверждение очистки списка избранного",
                                                              "Вы действительно хотите очистить список избранного?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        this->favoraties.clear();
        refreshFavorList();
    }

}

void MainWindow::refreshFavorList()
{
    ui->listWidget->clear();

    for(QString city: this->favoraties)
    {
        ui->listWidget->addItem(city);
    }
}

void MainWindow::on_viewForecast_clicked()
{
    if(ui->allForecastList->currentIndex().isValid())
    {
        emit sendRealTimeWeather(this->networkHandler->getWeatherForecast().values().at(ui->allForecastList->currentIndex().row()));
    }else
    {
        QMessageBox::information(this, "Ошибка выбора погоды из прогноза", "Вы не выбрали временной промежуток из прогноза");
    }

}

void MainWindow::on_selectFavorCity_clicked()
{
    if(ui->listWidget->currentIndex().isValid())
    {
        searchParam = ui->listWidget->currentItem()->text().split(",");
        this->cityData->setCountry(searchParam.at(1));
        this->cityData->setCityName(searchParam.at(0));
        this->fileHandler->inserCoordCity(*cityData);
        this->networkHandler->makeCityQuery(*cityData);

        ui->selectedCountryAndCity->setText(this->cityData->getCityName() + ", " + this->cityData->getCountry());

        emit sendForecast(this->networkHandler->getWeatherForecast());
        emit sendRealTimeWeather(this->networkHandler->getRealTimeWeatherData());

    }else
    {
        QMessageBox::information(this, "Ошибка выбора", "Вы не выбрали город");
    }

}

void MainWindow::on_choiseMetricTemperature_activated(int index)
{
    if(index == 1 && !ui->temperatureL->text().isEmpty() && ui->temperatureL->text().contains("°C"))
    {
        temperaturePars = ui->temperatureL->text().split(" ");
        ui->temperatureL->setText(QString::number(temperaturePars.at(0).toDouble() + 273.15) + " °F");
        temperaturePars = ui->maxTemperatureL->text().split(" ");
        ui->maxTemperatureL->setText(QString::number(temperaturePars.at(0).toDouble() + 273.15) + " °F");
        temperaturePars = ui->minTemperatureL->text().split(" ");
        ui->minTemperatureL->setText(QString::number(temperaturePars.at(0).toDouble() + 273.15) + " °F");


    }else if(!ui->temperatureL->text().isEmpty() && ui->temperatureL->text().contains("°F"))
    {
        temperaturePars = ui->temperatureL->text().split(" ");
        ui->temperatureL->setText(QString::number(temperaturePars.at(0).toDouble() - 273.15) + " °C");
        temperaturePars = ui->maxTemperatureL->text().split(" ");
        ui->maxTemperatureL->setText(QString::number(temperaturePars.at(0).toDouble() - 273.15) + " °C");
        temperaturePars = ui->minTemperatureL->text().split(" ");
        ui->minTemperatureL->setText(QString::number(temperaturePars.at(0).toDouble() - 273.15) + " °C");

    }
}

void MainWindow::on_realTimeWeatherShow_clicked()
{
    if(networkHandler->getRealTimeWeatherData()->getTemperature() != NULL)
    {
        emit catchRealTimeWeather(this->networkHandler->getRealTimeWeatherData());
    }else
    {
        QMessageBox::information(this, "Ошибка введения данных", "Данные о городе не заданы");
    }

}

void MainWindow::on_pushButton_clicked()
{
    this->optionsWindow->show();
}

void MainWindow::catchRealTimeWeather(WeatherData *weatherData)
{
    ui->humidityL->setText(weatherData->getHumidity() + " %");
    ui->pressureL->setText(weatherData->getPressure() + " hPa");
    ui->temperatureL->setText(weatherData->getTemperature() + " °C");
    ui->weatherDescrL->setText(weatherData->getWeatherDescription());
    ui->maxTemperatureL->setText(weatherData->getTempMax() + " °C");
    ui->minTemperatureL->setText(weatherData->getTempMin() + " °C");
    ui->choiseMetricTemperature->setCurrentIndex(0);
    this->pixmapForWeatherIcon->load("C:/Users/Admin/Desktop/Curs-work/Icons_weather/" + weatherData->getWeatherIcon() + ".png");
    ui->weatherIcon->setPixmap(pixmapForWeatherIcon->scaled(ui->weatherIcon->width(), ui->weatherIcon->height(), Qt::KeepAspectRatio));
}

void MainWindow::catchForecastToList(QMultiMap<int, WeatherData *> forecast)
{
    ui->allForecastList->clear();

    #ifdef DEBUG
    qDebug() << forecast << endl;
    #endif

    QList<WeatherData*> weather = forecast.values();
    QList<int> days = forecast.keys();

    #ifdef DEBUG
    qDebug() << days << endl;
    #endif

    QString day;

    for(int i = 0; i < weather.size(); ++i)
    {
        if(days[i] == 1)
        {
            day = "Понедельник";
        }else if(days[i] == 2)
        {
            day = "Вторник";
        }else if(days[i] == 3)
        {
            day = "Среда";
        }else if(days[i] == 4)
        {
            day = "Четверг";
        }else if(days[i] == 5)
        {
            day = "Пятница";
        }else if(days[i] == 6)
        {
            day = "Суббота";
        }else if(days[i] == 7)
        {
            day = "Воскресенье";
        }

        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(90, 50));
        ui->allForecastList->addItem(item);
        ui->allForecastList->setItemWidget(item, new ItemForecastWidget(day, weather[i]->getTime(), weather[i]->getWeatherDescription(),
                                                                        weather[i]->getTemperature(), weather[i]->getHumidity(), weather[i]->getWeatherIcon()));
    }

}

void MainWindow::searchChangeUserCity()
{
    ui->UserCityException->clear();
}

void MainWindow::searchClearUserCity()
{
    ui->UserCityException->setText("Внимание! город пользователя не задан");
}
