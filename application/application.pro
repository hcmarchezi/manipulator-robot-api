#-------------------------------------------------
#
# Project created by QtCreator 2016-02-08T16:15:18
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = application
TEMPLATE = app

SOURCES += main.cpp\
        wmain.cpp \
    applicationglwidget.cpp \
    appmain.cpp \
    robotcontrol.cpp \
    jointcontrol.cpp

HEADERS  += wmain.h \
    applicationglwidget.h \
    appmain.h \
    robotcontrol.h \
    jointcontrol.h

FORMS    += wmain.ui

# OpenGL glut configuration
LIBS += -lglut

# Domain project dependency
INCLUDEPATH += ../domain/
LIBS += $$OUT_PWD/../domain/libdomain.a

# Persistence project dependency
INCLUDEPATH += ../persistence/
LIBS += $$OUT_PWD/../persistence/libpersistence.a

# Utils project dependency
INCLUDEPATH += ../utils
LIBS += $$OUT_PWD/../utils/libutils.a

# lib3ds external dependency
LIBS += -l3ds



