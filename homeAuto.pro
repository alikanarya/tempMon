QT += core
QT -= gui
QT += network
QT += sql

CONFIG += c++11



TARGET = homeAuto
target.files = homeAuto
target.path=/root

INSTALLS += target
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    client.cpp \
    server.cpp \
    gpiothread.cpp \
    datathread.cpp

HEADERS += \
    client.h \
    server.h \
    globals.h \
    gpiothread.h \
    datathread.h

DISTFILES +=
