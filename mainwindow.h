#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMultiMap>
#include "weatherdata.h"
#include "viewforecast.h"
#include "citydata.h"
#include "networkhandler.h"
#include <QCompleter>

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

private slots:
    void on_okSearch_clicked();

    void on_viewForecast_clicked();

    void on_clearSearchField_clicked();

private:
    Ui::MainWindow *ui;

    ViewForecast *forecastWindow;
    QMultiMap<int, WeatherData*> weatherForecast;
    CityData *cityData;
    NetworkHandler *networkHandler;
    QCompleter *completerForSearch;
};

#endif // MAINWINDOW_H
