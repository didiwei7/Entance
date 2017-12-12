QT       += core gui
QT       += sql
QT       += xml
QT       += network
QT       += multimedia

TARGET    = QMyJson
TEMPLATE  = lib
DESTDIR   = ../bin

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES  += QMYJSON_LIBRARY
DEFINES  += QT_DEPRECATED_WARNINGS

SOURCES  += \
            qmyjson.cpp

HEADERS  += \
            qmyjson.h \
            qmyjson_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
