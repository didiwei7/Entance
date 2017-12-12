#include "ui_motor.h"

ui_motor::ui_motor(QWidget *parent) : QWidget(parent)
{
    motor_stackedWidget   = new QStackedWidget();      // 电机子界面 Stack
    c_NavigationBar_motor = new QVNavigationBar();     // 电机子界面 NavigationBar
    c_NavigationBar_motor->setSelectColor("#FFC0CB");
    c_NavigationBar_motor->setRowHeight(30);
    c_NavigationBar_motor->addItem(QStringLiteral("电机设置"));
    c_NavigationBar_motor->addItem(QStringLiteral("点位调试"));

    QHBoxLayout *layout_1 = new QHBoxLayout();
    layout_1->setContentsMargins(0, 0, 0, 0);
    layout_1->setSpacing(0);

    layout_1->addWidget(c_NavigationBar_motor);
    layout_1->addWidget(motor_stackedWidget);

    motor_stackedWidget->insertWidget(0, new ui_motor_set());
    motor_stackedWidget->insertWidget(1, new ui_motor_point());

    this->setLayout(layout_1);

    connect(c_NavigationBar_motor, &QVNavigationBar::currentItemChanged ,
            motor_stackedWidget,   &QStackedWidget::setCurrentIndex);
}

