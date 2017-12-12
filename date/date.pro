QT       += core gui widgets
QT       += sql
QT       += xml
QT       += network

TARGET    = date
TEMPLATE  = lib
DESTDIR   = ../bin      #定义项目编译之后生成的结果文件的存放路径

DEFINES  += DATE_LIBRARY
DEFINES  += QT_DEPRECATED_WARNINGS


SOURCES  += \
            date_point/date_point.cpp

HEADERS  += \
            date_global.h \
            date_point/date_point.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
