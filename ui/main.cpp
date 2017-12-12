#include "ui_mainwindow/ui_mainwindow.h"
#include "../date/date_point/date_point.h"
#include <time.h>
#include "../QFlex/QtFlexStyle.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QFile file("C:/Users/MSI/Desktop/myDarkStyle.qss");
//    file.open(QFile::ReadOnly);
//    QString style = file.readAll();
//    qApp->setStyleSheet(style);

    qsrand(clock());
    QApplication::setStyle(new FlexStyle());

    ui_mainwindow w;
    w.show();

    return a.exec();
}
