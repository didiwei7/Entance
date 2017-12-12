QT       += core gui
QT       += sql
QT       += xml
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET    = QMySocket
TEMPLATE  = lib
DESTDIR   = ../bin

DEFINES  += QMYSOCKET_LIBRARY
DEFINES  += QT_DEPRECATED_WARNINGS

SOURCES  += \
            qmysocket.cpp

HEADERS  += \
            socket_global.h \
            qmysocket.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
