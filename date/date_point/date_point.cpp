#include "date_point.h"

date_point::date_point()
{

}


/** 创建数据库连接,创建表单
 * @brief
 *     1 创建数据库连接
 *     2 创建表单
 * @arguments   NULL
 * @return  QSqlError
 * @author  Didiwei
 * @date    2017/11/16
 */
QSqlError date_point::db_point_three_axis_creat()
{
    // 【1】 创建数据库连接
    db_point_three_axis = QSqlDatabase::addDatabase("QSQLITE");
    db_point_three_axis.setDatabaseName("db_point_three_axis.db");
    QSqlQuery query_point_three_axis(db_point_three_axis);

    if( !db_point_three_axis.open())
    {
        QSqlError lastError = query_point_three_axis.lastError();
        qDebug() << lastError.driverText() << "无法建立QSQLITE数据库";
    }

    // 【2】 创建数据库表单
    bool success = query_point_three_axis.exec(QLatin1String("create table point_three_axis("
                                                             "ID     integer primary key,"
                                                             "Point_name        varchar,"
                                                             "Point_description varchar,"
                                                             "X_axis double,"
                                                             "Y_axis double,"
                                                             "Z_axis double)"));

    // 【3】 异常处理
    if(!success)
    {
        QSqlError lastError = query_point_three_axis.lastError();
        qDebug() << lastError.driverText() << "无法创建数据库表单";
    }



    query_point_three_axis.exec(QLatin1String("create table point_workStation1("
                                                                 "ID     integer primary key,"
                                                                 "Point_name        varchar,"
                                                                 "Point_description varchar,"
                                                                 "X_axis double,"
                                                                 "Y_axis double,"
                                                                 "Z_axis double)"));
    query_point_three_axis.exec(QLatin1String("create table point_workStation2("
                                                                 "ID     integer primary key,"
                                                                 "Point_name        varchar,"
                                                                 "Point_description varchar,"
                                                                 "X_axis double,"
                                                                 "Y_axis double,"
                                                                 "Z_axis double)"));
    query_point_three_axis.exec(QLatin1String("create table point_workStation3("
                                                                 "ID     integer primary key,"
                                                                 "Point_name        varchar,"
                                                                 "Point_description varchar,"
                                                                 "X_axis double,"
                                                                 "Y_axis double,"
                                                                 "Z_axis double)"));
    query_point_three_axis.exec(QLatin1String("create table point_workStation4("
                                                                 "ID     integer primary key,"
                                                                 "Point_name        varchar,"
                                                                 "Point_description varchar,"
                                                                 "X_axis double,"
                                                                 "Y_axis double,"
                                                                 "Z_axis double)"));
    return QSqlError();
}

/** 添加数据到数据库
 * @brief   添加数据到数据库
 * @arguments
 *      1. QSqlQuery &query：
 *      2. const QString &Point     点位名
 *      3. const QString &Point_description    点位描述
 *      4. const double  &X_axis    X
 *      5. const double  &Y_axis    Y
 *      6. const double  &Z_axis    Z
 * @return  QSqlError
 * @author  Didiwei
 * @date    2017/11/16
 */
QSqlError date_point::db_point_three_axis_add(QSqlQuery &query,
                                              const QString &Point_name, const QString &Point_description,
                                              double &X_axis, double &Y_axis, double &Z_axis)
{
    // 【1】打开数据库,选择插入位置
    if (!query.prepare(QLatin1String("insert into "
                                 "point_three_axis(Point_name, Point_description, X_axis, Y_axis, Z_axis) "
                                 "values(?, ?, ?, ?, ?)")))
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << "数据插入位置错误";
    }

    // 【2】添加数据
    query.addBindValue(Point_name);
    query.addBindValue(Point_description);
    query.addBindValue(X_axis);
    query.addBindValue(Y_axis);
    query.addBindValue(Z_axis);

    // 【3】异常处理
    if(!query.exec())
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << "插入数据失败";
    }

    return QSqlError();
}

/** 连接数据库
 * @brief   连接数据库
 * @arguments   NULL
 * @return  QSqlError
 * @author  Didiwei
 * @date    2017/11/16
 */
QSqlError date_point::db_point_three_axis_connect()
{
    // 【1】 创建数据库连接
    db_point_three_axis = QSqlDatabase::addDatabase("QSQLITE");
    db_point_three_axis.setDatabaseName("db_point_three_axis.db");
    QSqlQuery query_point_three_axis(db_point_three_axis);

    if( !db_point_three_axis.open())
    {
        QSqlError lastError = query_point_three_axis.lastError();
        qDebug() << lastError.driverText() << "无法建立QSQLITE数据库";
    }

    return QSqlError();
}
