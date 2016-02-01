#-------------------------------------------------
#
# Project created by QtCreator 2013-06-26T16:16:13
#
#-------------------------------------------------

QT       += core gui phonon
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = multimedia
TEMPLATE = lib

DEFINES += MULTIMEDIA_LIBRARY

SOURCES += *.cpp

HEADERS += *.h

#external libs
LIBS += -L../../basedef/basedef/ \
    -L../../lib/3rdpart/vlc/ \
    -lbasedef -lvlc

INCLUDEPATH += ../../ \
    ../../qt_glue_img/ \
    ../../include/3rdpart/

#c++ 11 standard support
QMAKE_CXXFLAGS += -std=c++11


