#-------------------------------------------------
#
# Project created by QtCreator 2015-05-26T20:04:50
#
#-------------------------------------------------

QT       -= core gui

TARGET = domain
target.path =
TEMPLATE = lib
CONFIG += staticlib create_prl

SOURCES += domain.cpp \
    Face.cpp \
    geometry.cpp \
    geometrysource.cpp \
    Link.cpp \
    LinkPosition.cpp \
    LinkTrajectory.cpp \
    LinkType.cpp \
    linktypefactory.cpp \
    linktyperepository.cpp \
    PartialRobotTrajectory.cpp \
    Point.cpp \
    pose.cpp \
    PrismaticLinkType.cpp \
    RevoluteLinkType.cpp \
    Robot.cpp \
    RobotPosition.cpp \
    trajectory.cpp \
    matrix.cpp

HEADERS += domain.h \
    Face.h \
    geometry.h \
    geometrysource.h \
    Link.h \
    LinkPosition.h \
    LinkTrajectory.h \
    LinkType.h \
    linktypefactory.h \
    linktyperepository.h \
    PartialRobotTrajectory.h \
    Point.h \
    pose.h \
    PrismaticLinkType.h \
    RevoluteLinkType.h \
    Robot.h \
    RobotPosition.h \
    trajectory.h \
    graphicobject.h \
    matrix.h
