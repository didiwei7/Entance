QT       += core gui
QT       += sql
QT       += xml
QT       += network
QT       += multimedia

TARGET    = model
TEMPLATE  = lib
DESTDIR   = ../bin      #定义项目编译之后生成的结果文件的存放路径

DEFINES  += MODEL_LIBRARY
DEFINES  += QT_DEPRECATED_WARNINGS

SOURCES  += \
            model_point/model_point.cpp

HEADERS  += \
            model_global.h \
            model_point/model_point.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

#表示Windows环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报错
win32{
    LIBS += ../bin/date.lib  #包含项目需要用到的共享库
}

