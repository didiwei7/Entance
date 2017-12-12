#include "ui_main.h"

ui_main::ui_main(QWidget *parent)
    : QWidget(parent)
{
    // 【2】 添加StackedWidget
    main_stackedWidget = new QStackedWidget();
    main_stackedWidget->insertWidget(0, new QLabel(QStringLiteral("主界面")));
    main_stackedWidget->insertWidget(1, new ui_motor());
    main_stackedWidget->insertWidget(2, new QLabel(QStringLiteral("I/O")));
    main_stackedWidget->insertWidget(3, new ui_communication());
    main_stackedWidget->insertWidget(4, new QLabel(QStringLiteral("其它")));
    main_stackedWidget->insertWidget(5, new QLabel(QStringLiteral("<font size='+1'><b><p align='center'>敌敌畏Demo系列</p></b></font>"
                                                                  "Tel 15927513928  "
                                                                  "Email 6443569891@qq.com")));

    // 【3】 添加按钮
    c_NavigationBar_main = new QVNavigationBar();
    c_NavigationBar_main->setBackgroundColor   ("#303947");
    c_NavigationBar_main->setPenColorBackground("#E4EBF3");
    c_NavigationBar_main->setPenColorSelected  ("#FFFFFF");
    c_NavigationBar_main->setWidth(80);
    c_NavigationBar_main->setRowHeight(40);
    c_NavigationBar_main->addItem(QStringLiteral("主界面"));
    c_NavigationBar_main->addItem(QStringLiteral("电机"));
    c_NavigationBar_main->addItem(QStringLiteral("I/O"));
    c_NavigationBar_main->addItem(QStringLiteral("通讯"));
    c_NavigationBar_main->addItem(QStringLiteral("其它"));
    c_NavigationBar_main->addItem(QStringLiteral("关于"));

    // 【4】 布局
    QHBoxLayout *layout_1   = new QHBoxLayout();
    layout_1->setContentsMargins(0, 0, 0, 0);
    layout_1->setSpacing(0);

    layout_1->addWidget(c_NavigationBar_main);
    layout_1->addWidget(main_stackedWidget);

    // 【5】 设置布局
    this->setLayout(layout_1);

    // 【6】 连接信号槽
    connect(c_NavigationBar_main, &QVNavigationBar::currentItemChanged,
            main_stackedWidget,   &QStackedWidget::setCurrentIndex);
}

ui_main::~ui_main()
{

}



