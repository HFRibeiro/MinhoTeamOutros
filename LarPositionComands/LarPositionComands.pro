#-------------------------------------------------
#
# Project created by QtCreator 2015-02-02T16:45:28
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LarPositionComands
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customscene.cpp \
    desenharcampo.cpp \
    robo1.cpp

HEADERS  += mainwindow.h \
    customscene.h \
    desenharcampo.h \
    robo1.h

FORMS    += mainwindow.ui

RESOURCES += \
    ra.qrc
