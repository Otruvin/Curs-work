#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMultiMap>
#include "weatherdata.h"
#include "citydata.h"
#include "networkhandler.h"
#include "filehandler.h"
#include <QCompleter>
#include "optionswindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_okSearch_clicked();

    void on_clearSearchField_clicked();


    void on_addFavorCity_clicked();

    void on_dropFavorCity_clicked();

    void on_clearFavoraties_clicked();

    void on_selectFavorCity_clicked();



    void on_choiseMetricTemperature_activated(int index);

    void on_viewForecast_clicked();

    void on_realTimeWeatherShow_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QMultiMap<int, WeatherData*> weatherForecast;
    CityData *cityData;
    NetworkHandler *networkHandler;
    QCompleter *completerForSearch;
    FileHandler *fileHandler;
    QSet<QString> favoraties;
    QString searchCity;
    QStringList searchParam;
    void refreshFavorList();
    void showWeather(WeatherData *weatherData);
    void setAllForecastToList();
    WeatherData* currentForecastData;
    OptionsWindow *optionsWindow;
};

#endif // MAINWINDOW_H
