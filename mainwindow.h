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
#include <QPixmap>
#include <QWidgetItem>
#include "itemforecastwidget.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void sendForecast(QMultiMap<int, WeatherData*> forecast);
    void sendRealTimeWeather(WeatherData *weatherData);

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

public slots:
    void catchRealTimeWeather(WeatherData *weatherData);
    void catchForecastToList(QMultiMap<int, WeatherData *> forecast);
    void searchChangeUserCity();
    void searchClearUserCity();

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
    WeatherData* currentForecastData;
    OptionsWindow *optionsWindow;
    QStringList lisWithUserCityCoords;
    QPixmap *pixmapForWeatherIcon;
    QWidgetItem *itemForecast;

};

#endif // MAINWINDOW_H
