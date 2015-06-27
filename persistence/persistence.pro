#-------------------------------------------------
#
# Project created by QtCreator 2015-05-26T23:09:10
#
#-------------------------------------------------

QT       -= core gui

TARGET = persistence
TEMPLATE = lib
CONFIG += staticlib create_prl

SOURCES += \
    internal/linkserializer.cpp \
    internal/linktypeserializer.cpp \
    internal/trajectoryserializer.cpp \
    geometryreader.cpp \
    jsonxx.cc \
    robotpersistence.cpp \
    linktypepersistence.cpp

HEADERS += \
    internal/linkserializer.h \
    internal/linktypeserializer.h \
    internal/trajectoryserializer.h \
    geometryreader.h \
    jsonxx.h \
    robotpersistence.h \
    linktypepersistence.h

# Project dependencies
INCLUDEPATH += ../domain/ ../utils/
LIBS += $$OUT_PWD/../domain/libdomain.a $$OUT_PWD/../utils/libutils.a
