QT       += core gui
QT       += sql
QT       += xml
QT       += network
QT       += multimedia

TARGET    = QMyXml
TEMPLATE  = lib
DESTDIR   = ../bin

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES  += QMYXML_LIBRARY
DEFINES  += QT_DEPRECATED_WARNINGS

SOURCES  += \
            qmyxml.cpp

HEADERS  += \
            qmyxml.h \
            qmyxml_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
