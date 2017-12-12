#ifndef QMYXML_H
#define QMYXML_H

#include "qmyxml_global.h"

#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include <QFile>
#include <QIODevice>

#include <QtWidgets>
#include <QMessageBox>


class QMYXMLSHARED_EXPORT QMyXml
{

public:
    QMyXml();

public:
    void MyXml_insert(QXmlStreamWriter &stream,
                      int row, const QString &point_name, const QString &point_doc,
                      double X, double Y, double Z);

    void MyXml_analysis(const QString &filepath);
};

#endif // QMYXML_H
