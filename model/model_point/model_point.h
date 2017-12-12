#ifndef MODEL_POINT_H
#define MODEL_POINT_H

#include "../model/model_global.h"
#include "../date/date_point/date_point.h"

#include <QSqlTableModel>
#include <QSqlRelationalTableModel>

#include <QStringList>

#include <Windows.h>

class MODELSHARED_EXPORT model_point
{
public:
    model_point();

public:
    void init_all();

    void model_point_threeAxis_init();

    void model_point_workStation1_init();
    void model_point_workStation2_init();
    void model_point_workStation3_init();
    void model_point_workStation4_init();

public:
    QSqlTableModel *model_point_threeAxis;

    QSqlTableModel *model_point_workStation1;
    QSqlTableModel *model_point_workStation2;
    QSqlTableModel *model_point_workStation3;
    QSqlTableModel *model_point_workStation4;

public:
    date_point *c_date_point;
};

#endif // MODEL_POINT_H
