#-------------------------------------------------
#
# Project created by QtCreator 2017-06-02T15:11:34
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = softproject
TEMPLATE = app


SOURCES += main.cpp\
        softroboticwidget.cpp

HEADERS  += softroboticwidget.h

FORMS    += softroboticwidget.ui

RESOURCES += \
    figure.qrc
