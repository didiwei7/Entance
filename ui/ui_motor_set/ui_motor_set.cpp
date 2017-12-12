#include "ui_motor_set.h"

ui_motor_set::ui_motor_set(QWidget *parent) : QWidget(parent)
{
    motor_set_stackedWidget   = new QStackedWidget();      // 电机子界面 Stack
    c_NavigationBar_motor_set = new QHNavigationBar();     // 电机子界面 NavigationBar
    c_NavigationBar_motor_set->setColumnWidth(100);
    c_NavigationBar_motor_set->addItem(QStringLiteral("X轴设置"));
    c_NavigationBar_motor_set->addItem(QStringLiteral("Y轴设置"));
    c_NavigationBar_motor_set->addItem(QStringLiteral("Z轴设置"));

    QVBoxLayout *layout_1 = new QVBoxLayout();
    layout_1->setContentsMargins(0, 0, 0, 0);
    layout_1->setSpacing(0);

    layout_1->addWidget(c_NavigationBar_motor_set);
    layout_1->addWidget(motor_set_stackedWidget);

    motor_set_stackedWidget->insertWidget(0, new QLabel(QStringLiteral("开发中")));
    this->setLayout(layout_1);
}
