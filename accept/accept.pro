#-------------------------------------------------
#
# Project created by QtCreator 2016-03-12T17:12:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = accept
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qextserialbase.cpp \
    posix_qextserialport.cpp

HEADERS  += mainwindow.h \
    qextserialbase.h \
    posix_qextserialport.h

FORMS    += mainwindow.ui
