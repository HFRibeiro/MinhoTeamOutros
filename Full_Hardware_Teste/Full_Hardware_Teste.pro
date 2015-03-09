#-------------------------------------------------
#
# Project created by QtCreator 2014-11-10T22:25:38
#
#-------------------------------------------------

QT       += core gui opengl
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Full_Hardware_Teste
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    model.cpp \
    backbutton.cpp \
    hat.cpp \
    myitem.cpp \
    textitem.cpp \
    joypad.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    model.h \
    backbutton.h \
    hat.h \
    myitem.h \
    textitem.h \
    joypad.h

FORMS    += mainwindow.ui

#-------------------Windows------------------------------
#
#LIBS += -L"C:\Users\Helder\Documents\QtProjetcts\GLUT" \
#        -lglut32
#
#LIBS += -L"C:\Users\Helder\Documents\QtProjetcts\SDL\x86" \
#        -lSDL2
#-------------------------------------------------------

#-------------------Ubuntu-----------------------------
LIBS += -L"/home/code/Documents/LIBS/SDL" \
        -lSDL2

LIBS += -L"/home/code/Documents/LIBS/GLUT" \
        -lglut -lGLU -lGL

#-------------------------------------------------------
RESOURCES += \
    rs.qrc
