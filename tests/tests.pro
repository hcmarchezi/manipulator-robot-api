TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += link_prl

# Test source files
HEADERS += \
    domain/concretelinktype.h

SOURCES += \
    domain/facetest.cpp \
    domain/linkpositiontest.cpp \
    domain/linktest.cpp \
    domain/linktrajectorytest.cpp \
    domain/linktypetest.cpp \
    domain/partialrobottrajectorytest.cpp \
    domain/posetest.cpp \
    domain/prismaticlinktypetest.cpp \
    domain/revolutelinktypetest.cpp \
    domain/robotpositiontest.cpp \
    domain/robottest.cpp \
    domain/trajectorytest.cpp \
    persistence/internal/linkserializertest.cpp \
    persistence/internal/linktypeserializertest.cpp \
    persistence/internal/trajectoryserializertest.cpp \
    persistence/geometryreadertest.cpp \
    persistence/linktypepersistencetest.cpp \
    persistence/robotpersistencetest.cpp

# GTEST dependency
INCLUDEPATH += /usr/src/gtest/
SOURCES += /usr/src/gtest/src/*
LIBS += -lpthread

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

include(deployment.pri)
qtcAddDeployment()

QMAKE_POST_LINK += cp $$_PRO_FILE_PWD_/persistence/robotarm.3ds $$OUT_PWD

DISTFILES += \
    persistence/robotarm.3ds


