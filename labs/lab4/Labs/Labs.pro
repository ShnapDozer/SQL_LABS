QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 debug

SOURCES += \
    src/MainWindow.cpp \
    src/main.cpp

HEADERS += \
    include/MainWindow.h

FORMS += \
    forms/MainWindow.ui

configPath.path = $$OUT_PWD/cfg
configPath.files = ./cfg/*

INSTALLS += \
    configPath


