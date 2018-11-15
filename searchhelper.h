#ifndef SEARCHHELPER_H
#define SEARCHHELPER_H
#include <QStringList>

class SearchHelper
{

public:
    SearchHelper();
    ~SearchHelper() = default;
    static QStringList getListWithCities();
};

#endif // SEARCHHELPER_H
