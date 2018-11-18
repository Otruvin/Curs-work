#ifndef ITEMFORECASTWIDGET_H
#define ITEMFORECASTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

class ItemForecastWidget : public QWidget
{
    Q_OBJECT

private:
    QLabel *weatherIconLabel;
    QLabel *time;
    QLabel *weekDay;
    QLabel *tempLabel;
    QLabel *tempValue;
    QLabel *humidityLabel;
    QLabel *humidityValue;
    QLabel *weatherIconImg;
    QPixmap *pixmapForTempLabel;
    QPixmap *pixmapForHumidityLabel;
    QPixmap *pixmapForWeatherIcon;
    QHBoxLayout *layout;

public:
    explicit ItemForecastWidget(QWidget *parent = nullptr);
    ItemForecastWidget(QString weekDay, QString time, QString weatherDescription, QString temp, QString humidity, QString weatherIcon);
    ~ItemForecastWidget();

signals:

public slots:
};

#endif // ITEMFORECASTWIDGET_H
