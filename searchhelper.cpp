#include "searchhelper.h"
#include <QFile>
#include <QTextStream>

SearchHelper::SearchHelper()
{

}


QStringList SearchHelper::getListWithCities()
{
    QStringList listWithCities;

    QFile file("C:/Users/Admin/Desktop/Curs-work/worldcities.csv");

        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            qDebug("File with cities not found!");
        }else
        {
            QTextStream in(&file);

            while (!file.atEnd())
            {
                QString line = in.readLine();

                QStringList tempList = line.split(",");

                tempList[1].chop(1);
                tempList[1].remove(0,1);
                tempList[4].chop(1);
                tempList[4].remove(0,1);

                listWithCities.append(tempList[1] + "," + tempList[4]);
            }

        }

            file.close();

    return listWithCities;
}
