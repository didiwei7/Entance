#ifndef QMYJSON_H
#define QMYJSON_H

#include "qmyjson_global.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>

#include <QFile>
#include <QIODevice>

#include <QtWidgets>
#include <QMessageBox>

class QMYJSONSHARED_EXPORT QMyJson
{

public:
    QMyJson();

public:
    bool MyJson_save(const QString &filePath, QJsonObject &jsonObject);
    bool MyJson_load(const QString &filePath, QJsonObject &jsonObject);

    void MyJson_analysis(QJsonObject &jsonObject, int row);

    void MyJson_insert(QJsonObject &jsonObject,
                       int row, const QString &point_name, const QString &point_doc,
                       double X, double Y, double Z);
};

#endif // QMYJSON_H
