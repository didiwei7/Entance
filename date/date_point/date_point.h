#ifndef DATE_POINT_H
#define DATE_POINT_H

#include "../date/date_global.h"

#include <QtSql>


class DATESHARED_EXPORT date_point
{
public:
    date_point();

public:
    QSqlError db_point_three_axis_creat();
    QSqlError db_point_three_axis_add(QSqlQuery &query,
                                      const QString &Point_name, const QString &Point_description,
                                      double &X_axis, double &Y_axis, double &Z_axis);

    QSqlError db_point_three_axis_connect();

public:
    QSqlDatabase  db_point_three_axis;

};

#endif // DATE_POINT_H
