#include "ui_point_workstation2.h"

ui_point_workStation2::ui_point_workStation2(QWidget *parent) : QWidget(parent)
{
    this->point_init_action();
    this->point_tableView_init();

    c_NavigationBar_point = new QVNavigationBar();
    c_NavigationBar_point->setSelectColor("#FFC0CB");
    c_NavigationBar_point->setRowHeight(30);
    c_NavigationBar_point->setWidth(80);
    c_NavigationBar_point->addItem(QStringLiteral("刷新"));
    c_NavigationBar_point->addItem(QStringLiteral("撤销"));
    c_NavigationBar_point->addItem(QStringLiteral("保存"));

    QHBoxLayout *layout_1   = new QHBoxLayout();
    layout_1->setContentsMargins(0, 0, 0, 0);
    layout_1->setSpacing(0);

    layout_1->addWidget(point_tableView_workStation2);
    layout_1->addWidget(c_NavigationBar_point);

    this->setLayout(layout_1);

    this->connect_signals_slots();

}


void ui_point_workStation2::connect_signals_slots()
{
    connect(point_action_table_add,    &QAction::triggered, this, &ui_point_workStation2::point_add);
    connect(point_action_table_insert, &QAction::triggered, this, &ui_point_workStation2::point_insert);
    connect(point_action_table_del,    &QAction::triggered, this, &ui_point_workStation2::point_del);
    connect(point_action_table_revert, &QAction::triggered, c_model_point->model_point_workStation2, &QSqlTableModel::revertAll);
    connect(point_action_table_save,   &QAction::triggered, this, &ui_point_workStation2::point_save);

    connect(point_tableView_workStation2, &QTableView::customContextMenuRequested,
            this, &ui_point_workStation2::point_tableView_rightClicked);

    connect(c_NavigationBar_point, &QVNavigationBar::currentItemChanged,
            this, &ui_point_workStation2::slot_NavigationBar_point);
}


void ui_point_workStation2::point_init_action()
{
    point_action_table_add    = new QAction(QStringLiteral("&添加"), this);
    point_action_table_insert = new QAction(QStringLiteral("&插入"), this);
    point_action_table_del    = new QAction(QStringLiteral("&删除"), this);

    point_action_table_revert = new QAction(QStringLiteral("&撤销"), this);
    point_action_table_save   = new QAction(QStringLiteral("&保存"), this);

    point_action_table_select = new QAction(QStringLiteral("&查找"), this);

    list_action_table << point_action_table_add << point_action_table_insert << point_action_table_del
                      << point_action_table_revert  << point_action_table_save << point_action_table_select;

}


void ui_point_workStation2::point_tableView_init()
{
    point_tableView_workStation2 = new QTableView();

    // 【1】 载入模型
    c_model_point = new model_point();

    // 【2】 绑定模型
    point_tableView_workStation2->setModel(c_model_point->model_point_workStation2);

    // 【3】 数据处理
    // point_tableView_workStation2->setColumnHidden(c_model_point->model_point_threeAxis->fieldIndex("ID"), true);

    // 【4】 添加 QAction
    point_tableView_workStation2->setContextMenuPolicy(Qt::CustomContextMenu);
    // point_tableView_workStation2->addActions(list_action_table);

    // 【5】 表格专属
    // 设置背景网格虚线
    point_tableView_workStation2->setShowGrid (true);
    point_tableView_workStation2->setGridStyle(Qt::DotLine);

    // 排序功能开启
    point_tableView_workStation2->setSortingEnabled(false);

    // 设置整行选中
    point_tableView_workStation2->setSelectionBehavior(QAbstractItemView::SelectRows);
}


void ui_point_workStation2::point_tableView_rightClicked(const QPoint &)
{
    QItemSelectionModel *select_current = point_tableView_workStation2->selectionModel();
    if (!select_current->hasSelection())
    {
        QMenu *point_menu_tableView = new QMenu();
        point_menu_tableView->addActions(list_action_table);

        point_action_table_del   ->setEnabled(false);
        point_action_table_insert->setEnabled(false);

        point_menu_tableView->exec(QCursor::pos());
    }
    else
    {
        QMenu *point_menu_tableView = new QMenu();
        point_menu_tableView->addActions(list_action_table);

        point_action_table_del   ->setEnabled(true);
        point_action_table_insert->setEnabled(true);

        point_menu_tableView->exec(QCursor::pos());
    }
}


bool ui_point_workStation2::point_add()
{
    int row_count = c_model_point->model_point_workStation2->rowCount();

    QSqlRecord record_point = c_model_point->model_point_workStation2->record();
    record_point.setValue("ID", row_count);
    record_point.setValue("Point_name",        QStringLiteral("Point"));
    record_point.setValue("Point_description", QStringLiteral("..."));
    record_point.setValue("X_axis", 0.00);
    record_point.setValue("Y_axis", 0.00);
    record_point.setValue("Z_axis", 0.00);

    if (c_model_point->model_point_workStation2->insertRecord(row_count, record_point))
    {
        c_model_point->model_point_workStation2->submitAll();
        return true;
    }
    else
    {
        QMessageBox::information(NULL, "Waring", "Add Faild", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return false;
    }
}

bool ui_point_workStation2::point_del()
{
    int ret = QMessageBox::warning(NULL, QStringLiteral("Waring"),
                                   QStringLiteral("你确定删除当前行吗?"),
                                   QMessageBox::Yes,QMessageBox::No);
    if(ret == QMessageBox::No)
    {
        c_model_point->model_point_workStation2->revertAll(); //如果不删除，则撤销
        return false;
    }
    else
    {
        // 【1】 获取当前行, 总行数
        int row       = point_tableView_workStation2->currentIndex().row();
        int row_count = c_model_point->model_point_workStation2->rowCount();

        // 【2】 差错处理
        if (!c_model_point->model_point_workStation2->removeRow(row))
        {
            QMessageBox::information(NULL, "Waring", "Delete Faild", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            return false;
        }
        else
        {
            c_model_point->model_point_workStation2->submitAll();

            // 【3】 将下面的行 ID -1, 节约空间
            for (int i = row; i < row_count - 1; ++i)
            {
                c_model_point->model_point_workStation2->setData(c_model_point->model_point_workStation2->index(i, 0), i);
                c_model_point->model_point_workStation2->submitAll();
            }

            return true;
        }
    }
}

bool ui_point_workStation2::point_insert()
{
    // 【1】 获取当前行, 总行数
    int row       = point_tableView_workStation2->currentIndex().row();
    int row_count = c_model_point->model_point_workStation2->rowCount();

    // 【2】 对当前行,下面的行ID加1, 腾出空间
    for (int i = row_count - 1; i >= row; --i)
    {
        c_model_point->model_point_workStation2->setData(c_model_point->model_point_workStation2->index(i, 0), i + 1);
        c_model_point->model_point_workStation2->submitAll();
    }

    // 【3】 插入一行数据
    QSqlRecord record_point = c_model_point->model_point_workStation2->record();
    record_point.setValue("ID", row);
    record_point.setValue("Point_name",        QStringLiteral("Point"));
    record_point.setValue("Point_description", QStringLiteral("..."));
    record_point.setValue("X_axis", 0.00);
    record_point.setValue("Y_axis", 0.00);
    record_point.setValue("Z_axis", 0.00);

    // 【3】 差错处理
    if (!c_model_point->model_point_workStation2->insertRecord(row, record_point))
    {
        QMessageBox::information(NULL, "Waring", "Insert Faild", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return false;
    }
    else
    {
        c_model_point->model_point_workStation2->submitAll();
        return true;
    }
}

bool ui_point_workStation2::point_save()
{
    // 【1】 用MyJson保存数据
    QMyJson  *my = new QMyJson();
    QJsonObject   json;

    // 【2】 遍历模型
    for ( int i = 0; i < c_model_point->model_point_workStation2->rowCount(); ++i)
    {
        int point_ID       = c_model_point->model_point_workStation2->record(i).value("ID").toInt();
        QString point_name = c_model_point->model_point_workStation2->record(i).value("Point_name").toString();
        QString point_disc = c_model_point->model_point_workStation2->record(i).value("Point_description").toString();
        double point_X     = c_model_point->model_point_workStation2->record(i).value("X_axis").toDouble();
        double point_Y     = c_model_point->model_point_workStation2->record(i).value("Y_axis").toDouble();
        double point_Z     = c_model_point->model_point_workStation2->record(i).value("Z_axis").toDouble();

        my->MyJson_insert(json, point_ID, point_name, point_disc, point_X, point_Y, point_Z);
    }

    // 【3】 保存数据到Json文件
    my->MyJson_save("../bin/point_workStation2.json", json);




    // 【1】 用 XML流保存数据
    QMyXml *myXml = new QMyXml ;
    QFile xmlFile("../bin/point_workStation2.xml");

    if(!xmlFile.open((QIODevice::WriteOnly)))
    {
        QMessageBox::warning(NULL, "Warning", QStringLiteral("保存文件失败"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return false;
    }

    QXmlStreamWriter stream(&xmlFile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("point_workStation2");

    for ( int i = 0; i < c_model_point->model_point_workStation2->rowCount(); ++i)
    {
        int point_ID       = c_model_point->model_point_workStation2->record(i).value("ID").toInt();
        QString point_name = c_model_point->model_point_workStation2->record(i).value("Point_name").toString();
        QString point_disc = c_model_point->model_point_workStation2->record(i).value("Point_description").toString();
        double point_X     = c_model_point->model_point_workStation2->record(i).value("X_axis").toDouble();
        double point_Y     = c_model_point->model_point_workStation2->record(i).value("Y_axis").toDouble();
        double point_Z     = c_model_point->model_point_workStation2->record(i).value("Z_axis").toDouble();

        myXml->MyXml_insert(stream, point_ID, point_name, point_disc, point_X, point_Y, point_Z);
    }

    stream.writeEndElement();
    stream.writeEndDocument();

    xmlFile.close();



    // 【2】 解析 XML数据流
    QMyXml  *myXml2 = new QMyXml();
    myXml2->MyXml_analysis("../bin/point_workStation2.xml");



    // 【4】 提交表单
    if(c_model_point->model_point_workStation2->submitAll())
    {
        return true;
    }
    else
    {
        QMessageBox::information(NULL, "Waring", "Submit Faild", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return false;
    }
}


void ui_point_workStation2::slot_NavigationBar_point(const int &currentIndex)
{
//    switch (currentIndex) {
//    case 0:
//        c_model_point->model_point_workStation2->revertAll();
//        break;
//    case 1:
//        c_model_point->model_point_workStation2->submitAll();
//        break;
//    case 2:
//        c_model_point->model_point_workStation2->select();
//        break;
//    default:
//        break;
//    }
    if (0 == currentIndex) // 刷新
    {
        c_model_point->model_point_workStation2->select();
    }
    else if (1 == currentIndex) // 撤销
    {
        c_model_point->model_point_workStation2->revertAll();
    }
    else if (2 == currentIndex) // 保存
    {
        c_model_point->model_point_workStation2->submitAll();
    }
    else
    {
        return;
    }
}
