#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <QStringList>
#include <QFile>

class FileHandler
{
private:
    QFile *file;
    QFile *fileWithCityUser;

public:
    FileHandler();
    ~FileHandler();
    void saveFavor(QSet<QString> set);
    QSet<QString> loadFavor();
    void clear();
    void clearUserCity();
    QString loadCityUser();
    void saveCityUser(QString userCity);
};

#endif // FILEHANDLER_H
