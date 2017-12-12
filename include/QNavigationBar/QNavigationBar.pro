QT       += core gui widgets
QT       += sql
QT       += xml
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET    = QNavigationBar
TEMPLATE  = lib
DESTDIR   = ../     #定义项目编译之后生成的结果文件的存放路径

DEFINES  += QNAVIGATIONBAR_LIBRARY
DEFINES  += QT_DEPRECATED_WARNINGS

SOURCES  += \
            qnavigationbar.cpp

HEADERS += \
            qnavigationbar.h \
            qnavigationbar_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
