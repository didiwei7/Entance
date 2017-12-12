QT       += core gui
QT       += sql
QT       += xml
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET    = QMyCV
TEMPLATE  = lib
DESTDIR   = ../bin


DEFINES  += QMYCV_LIBRARY
DEFINES  += QT_DEPRECATED_WARNINGS

SOURCES  += \
            qmycv.cpp

HEADERS  += \
            qmycv.h \
            qmycv_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += C:/opencv331/opencv/build/include
INCLUDEPATH += C:/opencv331/opencv/build/include/opencv/
INCLUDEPATH += C:/opencv331/opencv/build/include/opencv2/

win32:CONFIG(debug, debug|release):{
    LIBS += C:/opencv331/opencv/build/x64/vc14/lib/opencv_world331d.lib
}else:win32:CONFIG(release, debug|release):{
    LIBS += C:/opencv331/opencv/build/x64/vc14/lib/opencv_world331.lib
}

win32{
    LIBS += ../bin/QMySlider.lib
    LIBS += ../bin/QNavigationBar.lib
}
