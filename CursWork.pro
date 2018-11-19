#-------------------------------------------------
#
# Project created by QtCreator 2018-11-04T21:23:44
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CursWork
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    citydata.cpp \
    networkhandler.cpp \
    weatherdata.cpp \
    searchhelper.cpp \
    filehandler.cpp \
    optionswindow.cpp \
    itemforecastwidget.cpp

HEADERS += \
        mainwindow.h \
    citydata.h \
    networkhandler.h \
    weatherdata.h \
    searchhelper.h \
    filehandler.h \
    optionswindow.h \
    itemforecastwidget.h

FORMS += \
        mainwindow.ui \
    optionswindow.ui
