QT       += core gui
QT       += xml
QT       += sql
QT       += network
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET    = ui
TEMPLATE  = app
DESTDIR   = ../bin

DEFINES  += QT_DEPRECATED_WARNINGS

SOURCES  += \
            main.cpp \
            ui_mainwindow/ui_mainwindow.cpp \
            ui_main/ui_main.cpp \
            ui_motor/ui_motor.cpp \
            ui_motor_set/ui_motor_set.cpp \
            ui_motor_point/ui_motor_point.cpp \
            ui_point/ui_point_workstation1.cpp \
            ui_point/ui_point_workstation2.cpp \
            ui_point/ui_point_workstation3.cpp \
            ui_point/ui_point_workstation4.cpp \
            ui_communication/ui_communication.cpp

HEADERS  += \
            ui_mainwindow/ui_mainwindow.h \
            ui_main/ui_main.h \
            ui_motor/ui_motor.h \
            ui_motor_set/ui_motor_set.h \
            ui_motor_point/ui_motor_point.h \
            ui_point/ui_point_workstation1.h \
            ui_point/ui_point_workstation2.h \
            ui_point/ui_point_workstation3.h \
            ui_point/ui_point_workstation4.h \
            ui_communication/ui_communication.h

#表示Windows环境的特殊设置，这个大括号不能单独放在下一行，否则编译会报错
win32{
    LIBS  += ../bin/QFlex.lib  #包含项目需要用到的共享库
    LIBS  += ../bin/QNavigationBar.lib
    LIBS  += ../bin/QMyDock.lib
    LIBS  += ../bin/QMySocket.lib
    LIBS  += ../bin/model.lib
    LIBS  += ../bin/QMyJson.lib
    LIBS  += ../bin/QMyXml.lib
    LIBS  += ../bin/QMyMusic.lib
    LIBS  += ../bin/QMyCV.lib
}

INCLUDEPATH += C:/opencv331/opencv/build/include
INCLUDEPATH += C:/opencv331/opencv/build/include/opencv/
INCLUDEPATH += C:/opencv331/opencv/build/include/opencv2/

win32:CONFIG(debug, debug|release):{
    LIBS += C:/opencv331/opencv/build/x64/vc14/lib/opencv_world331d.lib
}else:win32:CONFIG(release, debug|release):{
    LIBS += C:/opencv331/opencv/build/x64/vc14/lib/opencv_world331.lib
}
