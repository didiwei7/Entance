//#include "ui_point.h"

//ui_point::ui_point()
//{
//    this->init_all();
//}

//void ui_point::init_all()
//{
//    this->point_widget_threeAxis_init();
//    this->connect_signals_slots();
//}

//void ui_point::connect_signals_slots()
//{
//    connect(point_action_table_add,    &QAction::triggered, this, &ui_point::point_add);
//    connect(point_action_table_insert, &QAction::triggered, this, &ui_point::point_insert);
//    connect(point_action_table_del,    &QAction::triggered, this, &ui_point::point_del);
//    connect(point_action_table_revert, &QAction::triggered, c_model_point->model_point_threeAxis, &QSqlTableModel::revertAll);
//    connect(point_action_table_save,   &QAction::triggered, this, &ui_point::point_save);

//    connect(point_tableView_threeAxis, &QTableView::customContextMenuRequested, this, &ui_point::point_tableView_rightClicked);
//    // SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(popMenu(const QPoint&))
//}

//void ui_point::point_widget_threeAxis_init()
//{
//    // 【0】
//    this->point_init_action();
//    QSpacerItem *V_spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
//    // QSpacerItem *H_spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

//    // 【1】 初始化控件
//    point_widget_threeAxis    = new QWidget();
//    point_tableView_threeAxis = new QTableView();

//    point_btn_table_add    = new QToolButton();
//    point_btn_table_insert = new QToolButton();
//    point_btn_table_del    = new QToolButton();
//    point_btn_table_save   = new QToolButton();

//    point_btn_table_add   ->setText(QStringLiteral("添加"));
//    point_btn_table_insert->setText(QStringLiteral("插入"));
//    point_btn_table_del   ->setText(QStringLiteral("删除"));
//    point_btn_table_save  ->setText(QStringLiteral("保存"));

//    // 【2】 布局
//    QHBoxLayout *layout_1   = new QHBoxLayout();
//    QVBoxLayout *layout_2_1 = new QVBoxLayout();

//    point_widget_threeAxis->setLayout(layout_1);

//    layout_1->addWidget(point_tableView_threeAxis);
//    layout_1->addLayout(layout_2_1);

//    layout_2_1->addWidget(point_btn_table_add);
//    layout_2_1->addWidget(point_btn_table_insert);
//    layout_2_1->addWidget(point_btn_table_del);
//    layout_2_1->addWidget(point_btn_table_save);
//    layout_2_1->addSpacerItem(V_spacer);

//    // 【3】 初始化 QTableView
//    this->point_tableView_threeAxis_init();
//}

//void ui_point::point_tableView_threeAxis_init()
//{
//    // 【1】 载入模型
//    c_model_point = new model_point();

//    // 【2】 绑定模型
//    point_tableView_threeAxis->setModel(c_model_point->model_point_threeAxis);

//    // 【3】 数据处理
//    // point_tableView_threeAxis->setColumnHidden(c_model_point->model_point_threeAxis->fieldIndex("ID"), true);

//    // 【4】 添加 QAction
//    point_tableView_threeAxis->setContextMenuPolicy(Qt::CustomContextMenu);
//    // point_tableView_threeAxis->addActions(list_action_table);

//    // 【5】 表格专属
//    // 设置背景网格虚线
//    point_tableView_threeAxis->setShowGrid (true);
//    point_tableView_threeAxis->setGridStyle(Qt::DotLine);

//    // 排序功能开启
//    point_tableView_threeAxis->setSortingEnabled(false);

//    // 设置整行选中
//    point_tableView_threeAxis->setSelectionBehavior(QAbstractItemView::SelectRows);
//}

//void ui_point::point_tableView_rightClicked(const QPoint &)
//{
//    // QTableWidgetItem *curItem = ui->m_table_point->itemAt(pos);
//     QItemSelectionModel *select_current = point_tableView_threeAxis->selectionModel();
//     if (!select_current->hasSelection())
//     {
//         qDebug() << "false";
//         QMenu *point_menu_tableView = new QMenu();
//         point_menu_tableView->addActions(list_action_table);

//         point_action_table_del   ->setEnabled(false);
//         point_action_table_insert->setEnabled(false);

//         point_menu_tableView->exec(QCursor::pos());
//     }
//     else
//     {
//         qDebug() << "true";
//         QMenu *point_menu_tableView = new QMenu();
//         point_menu_tableView->addActions(list_action_table);

//         point_action_table_del   ->setEnabled(true);
//         point_action_table_insert->setEnabled(true);

//         point_menu_tableView->exec(QCursor::pos());
//     }

////    QModelIndex select_current = point_tableView_threeAxis->indexAt(pos);
////    if(!select_current.isValid())
////    {
////        qDebug() << "false";
////        QMenu *point_menu_tableView = new QMenu();
////        point_menu_tableView->addActions(list_action_table);

////        point_action_table_del   ->setEnabled(false);
////        point_action_table_insert->setEnabled(false);

////        point_menu_tableView->exec(QCursor::pos());
////    }
////    else
////    {
////        qDebug() << "true";
////        QMenu *point_menu_tableView = new QMenu();
////        point_menu_tableView->addActions(list_action_table);

////        point_action_table_del   ->setEnabled(true);
////        point_action_table_insert->setEnabled(true);

////        point_menu_tableView->exec(QCursor::pos());
////    }
//}

//void ui_point::point_init_action()
//{
//    point_action_table_add    = new QAction(QStringLiteral("&添加"), this);
//    point_action_table_insert = new QAction(QStringLiteral("&插入"), this);
//    point_action_table_del    = new QAction(QStringLiteral("&删除"), this);

//    point_action_table_revert = new QAction(QStringLiteral("&撤销"), this);
//    point_action_table_save   = new QAction(QStringLiteral("&保存"), this);

//    point_action_table_select = new QAction(QStringLiteral("&查找"), this);

//    list_action_table << point_action_table_add << point_action_table_insert << point_action_table_del
//                      << point_action_table_revert  << point_action_table_save << point_action_table_select;
//}

//bool ui_point::point_add()
//{
//    int row_count = c_model_point->model_point_threeAxis->rowCount();

//    QSqlRecord record_point = c_model_point->model_point_threeAxis->record();
//    record_point.setValue("ID", row_count);
//    record_point.setValue("Point_name",        QStringLiteral("Point"));
//    record_point.setValue("Point_description", QStringLiteral("..."));
//    record_point.setValue("X_axis", 0.00);
//    record_point.setValue("Y_axis", 0.00);
//    record_point.setValue("Z_axis", 0.00);

//    if (c_model_point->model_point_threeAxis->insertRecord(row_count, record_point))
//    {
//        c_model_point->model_point_threeAxis->submitAll();
//        return true;
//    }
//    else
//    {
//        QMessageBox::information(NULL, "Waring", "Add Faild", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//        return false;
//    }
//}

//bool ui_point::point_del()
//{
//    int ret = QMessageBox::warning(NULL, QStringLiteral("Waring"),
//                                   QStringLiteral("你确定删除当前行吗?"),
//                                   QMessageBox::Yes,QMessageBox::No);
//    if(ret == QMessageBox::No)
//    {
//        c_model_point->model_point_threeAxis->revertAll(); //如果不删除，则撤销
//        return false;
//    }
//    else
//    {
//        // 【1】 获取当前行, 总行数
//        int row       = point_tableView_threeAxis->currentIndex().row();
//        int row_count = c_model_point->model_point_threeAxis->rowCount();

//        // 【2】 差错处理
//        if (!c_model_point->model_point_threeAxis->removeRow(row))
//        {
//            QMessageBox::information(NULL, "Waring", "Delete Faild", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//            return false;
//        }
//        else
//        {
//            c_model_point->model_point_threeAxis->submitAll();

//            // 【3】 将下面的行 ID -1, 节约空间
//            for (int i = row; i < row_count - 1; ++i)
//            {
//                c_model_point->model_point_threeAxis->setData(c_model_point->model_point_threeAxis->index(i, 0), i);
//                c_model_point->model_point_threeAxis->submitAll();
//            }

//            return true;
//        }
//    }
//}

//bool ui_point::point_save()
//{
//    // 【1】 用MyJson保存数据
//    QMyJson my;
//    QJsonObject json;

//    // 【2】 遍历模型
//    for ( int i = 0; i < c_model_point->model_point_threeAxis->rowCount(); ++i)
//    {
//        int point_ID       = c_model_point->model_point_threeAxis->record(i).value("ID").toInt();
//        QString point_name = c_model_point->model_point_threeAxis->record(i).value("Point_name").toString();
//        QString point_disc = c_model_point->model_point_threeAxis->record(i).value("Point_description").toString();
//        double point_X     = c_model_point->model_point_threeAxis->record(i).value("X_axis").toDouble();
//        double point_Y     = c_model_point->model_point_threeAxis->record(i).value("Y_axis").toDouble();
//        double point_Z     = c_model_point->model_point_threeAxis->record(i).value("Z_axis").toDouble();

//        my.MyJson_insert(json, point_ID, point_name, point_disc, point_X, point_Y, point_Z);
//    }

//    // 【3】 保存数据到Json文件
//    my.MyJson_save("../bin/point.json", json);


//    QFile xmlFile("../bin/my.xml");
//    if(!xmlFile.open((QIODevice::WriteOnly)))
//    {
//        QMessageBox::warning(NULL, "Warning", QStringLiteral("保存文件失败"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//        return false;
//    }

//    QXmlStreamWriter stream(&xmlFile);
//    stream.setAutoFormatting(true);
//    stream.writeStartDocument();
//    stream.writeStartElement("point_three_axis");

//    for ( int i = 0; i < c_model_point->model_point_threeAxis->rowCount(); ++i)
//    {
//        int point_ID       = c_model_point->model_point_threeAxis->record(i).value("ID").toInt();
//        QString point_name = c_model_point->model_point_threeAxis->record(i).value("Point_name").toString();
//        QString point_disc = c_model_point->model_point_threeAxis->record(i).value("Point_description").toString();
//        double point_X     = c_model_point->model_point_threeAxis->record(i).value("X_axis").toDouble();
//        double point_Y     = c_model_point->model_point_threeAxis->record(i).value("Y_axis").toDouble();
//        double point_Z     = c_model_point->model_point_threeAxis->record(i).value("Z_axis").toDouble();

//        point_save_xml(stream, point_ID, point_name, point_disc, point_X, point_Y, point_Z);
//    }
//    stream.writeEndElement();
//    stream.writeEndDocument();

//    xmlFile.close();


//    QFile file2("../bin/my.xml");
//    if (!file2.open(QFile::ReadOnly | QFile::Text))
//    {
//        qDebug()<<"Error: cannot open file";
//        return true;
//    }

//    QXmlStreamReader reader;

//    // 设置文件，这时会将流设置为初始状态
//    reader.setDevice(&file2);

//    // 如果没有读到文档结尾，而且没有出现错误
//    while (!reader.atEnd())
//    {
//        // 读取下一个记号，它返回记号的类型
//        QXmlStreamReader::TokenType type = reader.readNext();

//        // 下面便根据记号的类型来进行不同的输出
//        if (type == QXmlStreamReader::StartDocument)
//        {
//            qDebug() << reader.documentEncoding() << reader.documentVersion();
//        }

//        if (type == QXmlStreamReader::StartElement)
//        {
//            qDebug() << "<" << reader.name() << ">";
//            if (reader.attributes().hasAttribute("ID"))
//            {
//                qDebug() << reader.attributes().value("ID");
//            }
//            if (reader.attributes().hasAttribute("Point_name"))
//            {
//                qDebug() << reader.attributes().value("Point_name");
//            }
//            if (reader.attributes().hasAttribute("Point_doc"))
//            {
//                qDebug() << reader.attributes().value("Point_doc");
//            }

//            if (reader.attributes().hasAttribute("X_axis"))
//            {
//                qDebug() << reader.attributes().value("X_axis");
//            }
//            if (reader.attributes().hasAttribute("Y_axis"))
//            {
//                qDebug() << reader.attributes().value("Y_axis");
//            }
//            if (reader.attributes().hasAttribute("Z_axis"))
//            {
//                qDebug() << reader.attributes().value("Z_axis");
//            }

//        }
//        if (type == QXmlStreamReader::Characters && !reader.isWhitespace())
//        {

//            qDebug() << reader.text();
//        }

//        if (type == QXmlStreamReader::EndElement)
//        {
//            qDebug() << "";
//        }
//    }

//    // 如果读取过程中出现错误，那么输出错误信息
//    if (reader.hasError()) {
//        qDebug() << "error: " << reader.errorString();
//    }

//    // 【4】 提交表单
//    if(c_model_point->model_point_threeAxis->submitAll())
//    {
//        return true;
//    }
//    else
//    {
//        QMessageBox::information(NULL, "Waring", "Submit Faild", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//        return false;
//    }
//}

//bool ui_point::point_insert()
//{
//    // 【1】 获取当前行, 总行数
//    int row       = point_tableView_threeAxis->currentIndex().row();
//    int row_count = c_model_point->model_point_threeAxis->rowCount();

//    // 【2】 对当前行,下面的行ID加1, 腾出空间
//    for (int i = row_count - 1; i >= row; --i)
//    {
//        c_model_point->model_point_threeAxis->setData(c_model_point->model_point_threeAxis->index(i, 0), i + 1);
//        c_model_point->model_point_threeAxis->submitAll();
//    }

//    // 【3】 插入一行数据
//    QSqlRecord record_point = c_model_point->model_point_threeAxis->record();
//    record_point.setValue("ID", row);
//    record_point.setValue("Point_name",        QStringLiteral("Point"));
//    record_point.setValue("Point_description", QStringLiteral("..."));
//    record_point.setValue("X_axis", 0.00);
//    record_point.setValue("Y_axis", 0.00);
//    record_point.setValue("Z_axis", 0.00);

//    // 【3】 差错处理
//    if (!c_model_point->model_point_threeAxis->insertRecord(row, record_point))
//    {
//        QMessageBox::information(NULL, "Waring", "Insert Faild", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//        return false;
//    }
//    else
//    {
//        c_model_point->model_point_threeAxis->submitAll();
//        return true;
//    }
//}

//void ui_point::point_save_xml(QXmlStreamWriter &stream, int row,
//                               const QString &point_name, const QString &point_doc,
//                               double X, double Y, double Z)
//{
//    stream.writeStartElement(QString("Point%1").arg(row));
//    stream.writeAttribute("ID", QString("%1").arg(row));
//    stream.writeAttribute("Point_name", point_name);
//    stream.writeAttribute("Point_doc", point_doc);
//    stream.writeAttribute("X_axis", QString("%1").arg(X));
//    stream.writeAttribute("Y_axis", QString("%1").arg(Y));
//    stream.writeAttribute("Z_axis", QString("%1").arg(Z));
//    stream.writeEndElement();
//}





