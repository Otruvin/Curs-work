#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <QStringList>
#include <QFile>

class FileHandler
{
private:
    QFile *file;

public:
    FileHandler();
    ~FileHandler();
    void saveFavor(QSet<QString> set);
    QSet<QString> loadFavor();
    void clear();
};

#endif // FILEHANDLER_H
