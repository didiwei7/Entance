#include "ui_motor_point.h"

ui_motor_point::ui_motor_point(QWidget *parent) : QWidget(parent)
{
    c_ui_point_workStation1 = new ui_point_workStation1();
    c_ui_point_workStation2 = new ui_point_workStation2();
    c_ui_point_workStation3 = new ui_point_workStation3();
    c_ui_point_workStation4 = new ui_point_workStation4();

    motor_point_stackedWidget   = new QStackedWidget();      // 电机子界面 Stack
    c_NavigationBar_motor_point = new QHNavigationBar();     // 电机子界面 NavigationBar
    c_NavigationBar_motor_point->setColumnWidth(100);
    c_NavigationBar_motor_point->addItem(QStringLiteral("工站1点位"));
    c_NavigationBar_motor_point->addItem(QStringLiteral("工站2点位"));
    c_NavigationBar_motor_point->addItem(QStringLiteral("工站3点位"));
    c_NavigationBar_motor_point->addItem(QStringLiteral("工站4点位"));

    QVBoxLayout *layout_1 = new QVBoxLayout();
    layout_1->setContentsMargins(0, 0, 0, 0);
    layout_1->setSpacing(0);

    layout_1->addWidget(c_NavigationBar_motor_point);
    layout_1->addWidget(motor_point_stackedWidget);

    motor_point_stackedWidget->insertWidget(0, c_ui_point_workStation1);
    motor_point_stackedWidget->insertWidget(1, c_ui_point_workStation2);
    motor_point_stackedWidget->insertWidget(2, c_ui_point_workStation3);
    motor_point_stackedWidget->insertWidget(3, c_ui_point_workStation4);

    this->setLayout(layout_1);

    connect(c_NavigationBar_motor_point, &QHNavigationBar::currentItemChanged ,
            motor_point_stackedWidget,   &QStackedWidget::setCurrentIndex);
}



void ui_motor_point::update_db()
{
    c_ui_point_workStation1->c_model_point->model_point_workStation1->select();
    c_ui_point_workStation2->c_model_point->model_point_workStation2->select();
    c_ui_point_workStation3->c_model_point->model_point_workStation3->select();
    c_ui_point_workStation4->c_model_point->model_point_workStation4->select();
}
