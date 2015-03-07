#-------------------------------------------------
#
# Project created by QtCreator 2014-12-29T21:35:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AjusteLUT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    rs.qrc

INCLUDEPATH += C://opencv//release//install//include
LIBS += C://opencv//release//bin//*.dll
