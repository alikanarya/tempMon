QT += core
QT -= gui
QT += network
QT += sql

CONFIG += c++11

TARGET = tempMon
target.files = tempMon
target.path=/root

INSTALLS += target
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    client.cpp \
    server.cpp \
    gpiothread.cpp \
    datathread.cpp \
    startthr.cpp \
    checkclient.cpp \
    gpiods18b20.cpp

HEADERS += \
    client.h \
    server.h \
    globals.h \
    gpiothread.h \
    datathread.h \
    startthr.h \
    checkclient.h \
    gpiods18b20.h

DISTFILES +=
