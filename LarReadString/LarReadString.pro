#-------------------------------------------------
#
# Project created by QtCreator 2015-01-08T22:17:45
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LarReadString
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    desenharcampo.cpp \
    customscene.cpp \
    robo1.cpp

HEADERS  += mainwindow.h \
    desenharcampo.h \
    customscene.h \
    robo1.h

FORMS    += mainwindow.ui

RESOURCES += \
    rs.qrc
