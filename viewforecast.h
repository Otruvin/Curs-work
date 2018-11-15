#ifndef VIEWFORECAST_H
#define VIEWFORECAST_H

#include <QWidget>
#include <QMultiMap>
#include "weatherdata.h"

namespace Ui {
class ViewForecast;
}

class ViewForecast : public QWidget
{
    Q_OBJECT

public:
    explicit ViewForecast(QWidget *parent = 0);
    ~ViewForecast();

public slots:
    void recieveForecast(QMultiMap<int, WeatherData*> forecast);

private slots:
    void on_backToMainMenu_clicked();

private:
    Ui::ViewForecast *ui;
};

#endif // VIEWFORECAST_H
