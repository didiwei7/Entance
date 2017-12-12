#include "ui_communication.h"

ui_communication::ui_communication(QWidget *parent) : QWidget(parent)
{
    communication_stackedWidget   = new QStackedWidget();    // 电机主界面 Stack
    c_NavigationBar_communication = new QHNavigationBar();   // 电机主界面 NavigationBar
    c_NavigationBar_communication->setSelectColor("#FFC0CB");
    c_NavigationBar_communication->setColumnWidth(100);
    c_NavigationBar_communication->addItem(QStringLiteral("Socket1"));
    c_NavigationBar_communication->addItem(QStringLiteral("Socket2"));
    c_NavigationBar_communication->addItem(QStringLiteral("串口通讯"));

    // 【2】 初始化布局
    QVBoxLayout *layout_1 = new QVBoxLayout();
    layout_1->setContentsMargins(0, 0, 0, 0);
    layout_1->setSpacing(0);

    // 【3】 1 级布局
    layout_1->addWidget(c_NavigationBar_communication);
    layout_1->addWidget(communication_stackedWidget);

    communication_stackedWidget->insertWidget(0, new QLabel(QStringLiteral("开发中")));
    communication_stackedWidget->insertWidget(1, new Socket());

    this->setLayout(layout_1);

    connect(c_NavigationBar_communication, &QHNavigationBar::currentItemChanged,
            communication_stackedWidget,   &QStackedWidget::setCurrentIndex);
}
