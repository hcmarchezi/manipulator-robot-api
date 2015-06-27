#-------------------------------------------------
#
# Project created by QtCreator 2015-06-06T11:38:44
#
#-------------------------------------------------

QT       -= core gui

TARGET = utils
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    filehelper.cpp

HEADERS += \
    filehelper.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
