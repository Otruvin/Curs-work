#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <QStringList>
#include <QFile>
#include "citydata.h"

class FileHandler
{
private:
    QFile *file;
    QFile *fileWithCityUser;
    QFile *fileWithCities;

public:
    FileHandler();
    ~FileHandler();
    void saveFavor(QSet<QString> set);
    QSet<QString> loadFavor();
    void clear();
    void clearUserCity();
    QString loadCityUser();
    void saveCityUser(QString userCity);
    void inserCoordCity(CityData &city);
};

#endif // FILEHANDLER_H
