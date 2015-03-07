#-------------------------------------------------
#
# Project created by QtCreator 2015-01-23T18:08:43
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LarPlayerBall
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    customscene.cpp \
    desenharcampo.cpp \
    robo1.cpp \
    ball.cpp \
    obstaculo.cpp

HEADERS  += mainwindow.h \
    customscene.h \
    desenharcampo.h \
    robo1.h \
    ball.h \
    obstaculo.h

FORMS    += mainwindow.ui
