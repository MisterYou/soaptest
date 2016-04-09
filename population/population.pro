TEMPLATE = app
INCLUDEPATH += .
CONFIG += console

include(qtsoap.pri)

HEADERS += population.h
SOURCES += main.cpp population.cpp
