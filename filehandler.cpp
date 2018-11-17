#include "filehandler.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

FileHandler::FileHandler()
{
    this->file = new QFile("C:/Users/Admin/Desktop/Curs-work/favoraties.bin");
    this->fileWithCityUser = new QFile("C:/Users/Admin/Desktop/Curs-work/userCity.bin");
}

FileHandler::~FileHandler()
{
    delete fileWithCityUser;
    delete file;
}

void FileHandler::saveFavor(QSet<QString> set)
{

    if(!this->file->open(QIODevice::WriteOnly))
    {
        qDebug() << "Not open";
        return;
    }

    QDataStream out(this->file);
    out.setVersion(QDataStream::Qt_5_9);

    out << set;

    this->file->flush();
    this->file->close();
}

QSet<QString> FileHandler::loadFavor()
{
    QSet<QString> set;

    if(!this->file->open(QIODevice::ReadOnly))
    {
        qDebug() << "Not open";
        return set;
    }

    QDataStream in(this->file);
    in.setVersion(QDataStream::Qt_5_9);

    in >> set;

    this->file->close();

    return set;
}

void FileHandler::clear()
{
    this->file->resize(0);
}

void FileHandler::clearUserCity()
{
    this->fileWithCityUser->resize(0);
}

QString FileHandler::loadCityUser()
{
    QString userCity;

    if(!this->fileWithCityUser->open(QIODevice::ReadOnly))
    {
        qDebug() << "Not open";
        return userCity;
    }

    QDataStream in(this->fileWithCityUser);
    in.setVersion(QDataStream::Qt_5_9);

    in >> userCity;

    this->fileWithCityUser->close();

    return userCity;
}

void FileHandler::saveCityUser(QString userCity)
{
    if(!this->fileWithCityUser->open(QIODevice::WriteOnly))
    {
        qDebug() << "Not open";
        return;
    }

    QDataStream out(this->fileWithCityUser);
    out.setVersion(QDataStream::Qt_5_9);

    out << userCity;

    this->fileWithCityUser->flush();
    this->fileWithCityUser->close();
}
