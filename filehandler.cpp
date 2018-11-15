#include "filehandler.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

FileHandler::FileHandler()
{
    this->file = new QFile("/home/otruvin/QtProject/Curs-work/favoraties.bin");
}

FileHandler::~FileHandler()
{
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
