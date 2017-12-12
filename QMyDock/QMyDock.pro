QT       += core gui
QT       += xml
QT       += sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET    = QMyDock
TEMPLATE  = lib
DESTDIR   = ../bin

DEFINES  += QMYDOCK_LIBRARY
DEFINES  += QT_DEPRECATED_WARNINGS

SOURCES  += \
            NXDockWidget.cpp \
            NXDockWidgetTabBar.cpp \
            NXDockWidgetTabButton.cpp \
            NXDockWidgetTitle.cpp \
            NXMainWindow.cpp

HEADERS += \
            NXDockWidget.h \
            NXDockWidgetTabBar.h \
            NXDockWidgetTabButton.h \
            NXDockWidgetTitle.h \
            NXMainWindow.h      \
            qmydock_global.h

RESOURCES += \
               nxmainwindow.qrc

unix {
    target.path = /usr/lib
    INSTALLS += target
}
