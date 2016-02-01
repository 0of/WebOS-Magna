#-------------------------------------------------
#
# Project created by QtCreator 2013-06-27T17:34:03
#
#-------------------------------------------------

QT       += network webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += webkitwidgets

TARGET = mruntime
TEMPLATE = lib

DEFINES += MRUNTIME_LIBRARY

SOURCES += *.cpp

HEADERS += *.h

INCLUDEPATH += ../../ \
    ../../qt_glue_img/ \
    ../../qt_glue/  \
    ../../multimedia/

#c++ 11 standard support
QMAKE_CXXFLAGS += -std=c++11


