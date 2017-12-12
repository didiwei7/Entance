#include "model_point.h"

model_point::model_point()
{
    this->init_all();
}


/** 初始化全部
 * @brief   初始化全部
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-11-17
 */
void model_point::init_all()
{
    this->model_point_threeAxis_init();

    this->model_point_workStation1_init();
    this->model_point_workStation2_init();
    this->model_point_workStation3_init();
    this->model_point_workStation4_init();
}

/** Model Point threeAxis 初始化表单
 * @brief   初始化表单
 *      1. 创建一个数据库对象,连接数据库
 *      2. 创建一个 SqlTableModel, 连接数据库中的某些 "表单对象"
 *      3. 更改Model对象的 头信息
 *      4. 设置选中,Model中的内容,就和数据库表单中的内容绑定了
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-11-17
 */
void model_point::model_point_threeAxis_init()
{
    // 【1】 创建一个数据库对象,连接数据库.
    c_date_point = new date_point();
    // c_date_point->db_point_three_axis_creat();
    c_date_point->db_point_three_axis_connect();

    // 【2】 创建一个 SqlTableModel, 连接数据库中的某些 "表单对象"
    model_point_threeAxis = new QSqlTableModel();
    // 设置为当 model_music 使用 submit 时,数据库才会更改,否则做出的更改存储在缓存中
    model_point_threeAxis->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_point_threeAxis->setTable("point_three_axis");

    // 【3】 更改Model对象的 头信息
    model_point_threeAxis->setHeaderData(model_point_threeAxis->fieldIndex("Point_name"), Qt::Horizontal, QStringLiteral("点位名称"));
    model_point_threeAxis->setHeaderData(model_point_threeAxis->fieldIndex("Point_description"),  Qt::Horizontal, QStringLiteral("点位描述"));

    // 【4】 设置选中,Model中的内容,就和数据库表单中的内容绑定了
    model_point_threeAxis->select();
}

/** Model Point workStation 初始化表单
 * @brief   初始化表单
 *      2. 创建一个 SqlTableModel, 连接数据库中的某些 "表单对象"
 *      3. 更改Model对象的 头信息
 *      4. 设置选中,Model中的内容,就和数据库表单中的内容绑定了
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-12-01
 */
void model_point::model_point_workStation1_init()
{
    // 【2】 创建一个 SqlTableModel, 连接数据库中的某些 "表单对象"
    model_point_workStation1 = new QSqlTableModel();

    // 设置为当 model_music 使用 submit 时,数据库才会更改,否则做出的更改存储在缓存中
    model_point_workStation1->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_point_workStation1->setTable("point_workStation1");

    // 设置按第0列升序排列
    model_point_workStation1->setSort(0, Qt::AscendingOrder);

    // 【3】 更改Model对象的 头信息
    model_point_workStation1->setHeaderData(model_point_threeAxis->fieldIndex("Point_name"), Qt::Horizontal, QStringLiteral("点位名称"));
    model_point_workStation1->setHeaderData(model_point_threeAxis->fieldIndex("Point_description"),  Qt::Horizontal, QStringLiteral("点位描述"));

    // 【4】 设置选中,Model中的内容,就和数据库表单中的内容绑定了
    model_point_workStation1->select();
}

/** Model Point workStation 初始化表单
 * @brief   初始化表单
 *      2. 创建一个 SqlTableModel, 连接数据库中的某些 "表单对象"
 *      3. 更改Model对象的 头信息
 *      4. 设置选中,Model中的内容,就和数据库表单中的内容绑定了
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-12-01
 */
void model_point::model_point_workStation2_init()
{
    // 【2】 创建一个 SqlTableModel, 连接数据库中的某些 "表单对象"
    model_point_workStation2 = new QSqlTableModel();
    // 设置为当 model_music 使用 submit 时,数据库才会更改,否则做出的更改存储在缓存中
    model_point_workStation2->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_point_workStation2->setTable("point_workStation2");

    // 设置按第0列升序排列
    model_point_workStation2->setSort(0, Qt::AscendingOrder);

    // 【3】 更改Model对象的 头信息
    model_point_workStation2->setHeaderData(model_point_threeAxis->fieldIndex("Point_name"), Qt::Horizontal, QStringLiteral("点位名称"));
    model_point_workStation2->setHeaderData(model_point_threeAxis->fieldIndex("Point_description"),  Qt::Horizontal, QStringLiteral("点位描述"));

    // 【4】 设置选中,Model中的内容,就和数据库表单中的内容绑定了
    model_point_workStation2->select();
}

/** Model Point workStation 初始化表单
 * @brief   初始化表单
 *      2. 创建一个 SqlTableModel, 连接数据库中的某些 "表单对象"
 *      3. 更改Model对象的 头信息
 *      4. 设置选中,Model中的内容,就和数据库表单中的内容绑定了
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-12-01
 */
void model_point::model_point_workStation3_init()
{
    // 【2】 创建一个 SqlTableModel, 连接数据库中的某些 "表单对象"
    model_point_workStation3 = new QSqlTableModel();
    // 设置为当 model_music 使用 submit 时,数据库才会更改,否则做出的更改存储在缓存中
    model_point_workStation3->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_point_workStation3->setTable("point_workStation3");

    // 设置按第0列升序排列
    model_point_workStation3->setSort(0, Qt::AscendingOrder);

    // 【3】 更改Model对象的 头信息
    model_point_workStation3->setHeaderData(model_point_threeAxis->fieldIndex("Point_name"), Qt::Horizontal, QStringLiteral("点位名称"));
    model_point_workStation3->setHeaderData(model_point_threeAxis->fieldIndex("Point_description"),  Qt::Horizontal, QStringLiteral("点位描述"));

    // 【4】 设置选中,Model中的内容,就和数据库表单中的内容绑定了
    model_point_workStation3->select();
}

/** Model Point workStation 初始化表单
 * @brief   初始化表单
 *      2. 创建一个 SqlTableModel, 连接数据库中的某些 "表单对象"
 *      3. 更改Model对象的 头信息
 *      4. 设置选中,Model中的内容,就和数据库表单中的内容绑定了
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-12-01
 */
void model_point::model_point_workStation4_init()
{
    // 【2】 创建一个 SqlTableModel, 连接数据库中的某些 "表单对象"
    model_point_workStation4 = new QSqlTableModel();
    // 设置为当 model_music 使用 submit 时,数据库才会更改,否则做出的更改存储在缓存中
    model_point_workStation4->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_point_workStation4->setTable("point_workStation4");

    // 设置按第0列升序排列
    model_point_workStation4->setSort(0, Qt::AscendingOrder);

    // 【3】 更改Model对象的 头信息
    model_point_workStation4->setHeaderData(model_point_threeAxis->fieldIndex("Point_name"), Qt::Horizontal, QStringLiteral("点位名称"));
    model_point_workStation4->setHeaderData(model_point_threeAxis->fieldIndex("Point_description"),  Qt::Horizontal, QStringLiteral("点位描述"));

    // 【4】 设置选中,Model中的内容,就和数据库表单中的内容绑定了
    model_point_workStation4->select();
}
