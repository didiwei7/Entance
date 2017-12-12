QT       += core gui
QT       += xml
QT       += sql
QT       += network
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET    = QMyMusic
TEMPLATE  = lib
DESTDIR   = ../bin

DEFINES  += QMYMUSIC_LIBRARY
DEFINES  += QT_DEPRECATED_WARNINGS

SOURCES  += \
            qmymusic.cpp

HEADERS  += \
            qmymusic.h \
            qmymusic_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    music.qrc
