#-------------------------------------------------
#
# Project created by QtCreator 2014-12-23T01:38:49
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UDPRoboControl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    joypad.cpp

HEADERS  += mainwindow.h \
    joypad.h

FORMS    += mainwindow.ui

RESOURCES += \
    rs.qrc
