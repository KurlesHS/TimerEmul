#-------------------------------------------------
#
# Project created by QtCreator 2014-04-01T14:58:48
#
#-------------------------------------------------

QT       += core gui serialport
CONFIG   += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TimerEmulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    timeremulthreadworker.cpp

HEADERS  += mainwindow.h \
    timeremulthreadworker.h

FORMS    += mainwindow.ui
