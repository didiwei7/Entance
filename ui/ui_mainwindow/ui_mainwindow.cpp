#include "ui_mainwindow.h"

ui_mainwindow::ui_mainwindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    this->init_all();
}

ui_mainwindow::~ui_mainwindow()
{

}

void ui_mainwindow::init_all()
{
    this->setupUi();
    this->connect_signals_slots();
}

void ui_mainwindow::setupUi()
{
    // 初始化QAction
    this->mainwidow_init_action();

    // 载入QFlex样式.
    qApp->setProperty("window", QVariant::fromValue<QObject*>(this));

    // 载入中心窗口
    this->setCentralWidget(new QtCentral(this));

    // 初始化 位置,大小，标题
    this->setGeometry(QApplication::desktop()->availableGeometry().adjusted(100, 100, -100, -100));
    this->setWindowTitle(QStringLiteral("Entrance"));
}

void ui_mainwindow::connect_signals_slots()
{
    connect(action_view_main,          &QAction::triggered, this, &ui_mainwindow::on_view_main);
    connect(action_view_motor,         &QAction::triggered, this, &ui_mainwindow::on_view_motor);
    connect(action_view_motor_set,     &QAction::triggered, this, &ui_mainwindow::on_view_motor_set);
    connect(action_view_motor_point,   &QAction::triggered, this, &ui_mainwindow::on_view_motor_point);
    connect(action_view_communication, &QAction::triggered, this, &ui_mainwindow::on_view_communication);
    connect(action_view_music,         &QAction::triggered, this, &ui_mainwindow::on_view_music);
    connect(action_view_cv,            &QAction::triggered, this, &ui_mainwindow::on_view_cv);
}

void ui_mainwindow::closeEvent(QCloseEvent* )
{
    QByteArray content = FlexManager::instance()->save();

    QSettings settings("QtFlex5", "QtGuider");

    settings.setValue("Flex", content);

    FlexManager::instance()->close();
}

void ui_mainwindow::mainwidow_init_action()
{
    action_file_new  = new QAction(QStringLiteral("&New"),  this);
    action_file_open = new QAction(QStringLiteral("&Open"), this);
    action_file_save = new QAction(QStringLiteral("&Save"), this);
    action_file_save_all = new QAction(QStringLiteral("&SaveAll"), this);
    action_file_exit = new QAction(QStringLiteral("&Exit"), this);


    action_view_main        = new QAction(QStringLiteral("主界面"), this);

    action_view_motor       = new QAction(QStringLiteral("电机调试"), this);
    action_view_motor_point = new QAction(QStringLiteral("点位设置"), this);
    action_view_motor_set   = new QAction(QStringLiteral("电机设置"), this);

    action_view_communication = new QAction(QStringLiteral("通讯调试"), this);
    action_view_socket        = new QAction(QStringLiteral("Socket"), this);

    action_view_music       = new QAction(QStringLiteral("Music"), this);
    action_view_cv          = new QAction(QStringLiteral("CV"), this);


    QList<QAction*> list_action_file;
    QList<QAction*> list_action_view;

    list_action_file << action_file_new << action_file_open << action_file_save
                     << action_file_save_all << action_file_exit;
    list_action_view << action_view_main
                     << action_view_motor << action_view_motor_set << action_view_motor_point
                     << action_view_communication << action_view_socket
                     << action_view_music << action_view_cv;

    QMenu *menu_file = new QMenu("&File");
    QMenu *menu_view = new QMenu("&View");
    menu_file->addActions(list_action_file);
    menu_view->addActions(list_action_view);

    this->menuBar()->addMenu(menu_file);
    this->menuBar()->addMenu(menu_view);
}

void ui_mainwindow::on_view_main()
{
    QString dockWidgetName = QStringLiteral("主界面");
    DockWidget* widget = nullptr;

    if ((widget = FlexManager::instance()->dockWidget(dockWidgetName)) != nullptr)
    {
        widget->activate();
    }
    else
    {
        if (!FlexManager::instance()->restore(dockWidgetName))
        {
            FlexWidget* flexWidget = FlexManager::instance()->createFlexWidget(Flex::ToolView, Flex::parent(Flex::ToolView), Flex::windowFlags());
            DockWidget* dockWidget = FlexManager::instance()->createDockWidget(Flex::ToolView, flexWidget, Flex::widgetFlags(), dockWidgetName);

            dockWidget->setViewMode(Flex::ToolView);
            dockWidget->setWindowTitle(dockWidgetName);

            flexWidget->addDockWidget(dockWidget);
            flexWidget->show();

            flexWidget->move(geometry().center() - flexWidget->rect().center());
        }
    }
}

void ui_mainwindow::on_view_motor()
{
    QString dockWidgetName = QStringLiteral("电机调试");
    DockWidget* widget = nullptr;

    if ((widget = FlexManager::instance()->dockWidget(dockWidgetName)) != nullptr)
    {
        widget->activate();
    }
    else
    {
        if (!FlexManager::instance()->restore(dockWidgetName))
        {
            FlexWidget* flexWidget = FlexManager::instance()->createFlexWidget(Flex::ToolView, Flex::parent(Flex::ToolView), Flex::windowFlags());
            DockWidget* dockWidget = FlexManager::instance()->createDockWidget(Flex::ToolView, flexWidget, Flex::widgetFlags(), dockWidgetName);

            dockWidget->setViewMode(Flex::ToolView);
            dockWidget->setWindowTitle(dockWidgetName);

            flexWidget->addDockWidget(dockWidget);
            flexWidget->show();
            flexWidget->move(geometry().center() - flexWidget->rect().center());
        }
    }
}

void ui_mainwindow::on_view_motor_set()
{
    QString dockWidgetName = QStringLiteral("电机设置");
    DockWidget* widget = nullptr;

    if ((widget = FlexManager::instance()->dockWidget(dockWidgetName)) != nullptr)
    {
        widget->activate();
    }
    else
    {
        if (!FlexManager::instance()->restore(dockWidgetName))
        {
            FlexWidget* flexWidget = FlexManager::instance()->createFlexWidget(Flex::ToolView, Flex::parent(Flex::ToolView), Flex::windowFlags());
            DockWidget* dockWidget = FlexManager::instance()->createDockWidget(Flex::ToolView, flexWidget, Flex::widgetFlags(), dockWidgetName);

            dockWidget->setViewMode(Flex::ToolView);
            dockWidget->setWindowTitle(dockWidgetName);

            flexWidget->addDockWidget(dockWidget);
            flexWidget->show();
            flexWidget->move(geometry().center() - flexWidget->rect().center());
        }
    }
}

void ui_mainwindow::on_view_motor_point()
{
    QString dockWidgetName = QStringLiteral("点位调试");
    DockWidget* widget = nullptr;

    if ((widget = FlexManager::instance()->dockWidget(dockWidgetName)) != nullptr)
    {
        widget->activate();
    }
    else
    {
        if (!FlexManager::instance()->restore(dockWidgetName))
        {
            FlexWidget* flexWidget = FlexManager::instance()->createFlexWidget(Flex::ToolView, Flex::parent(Flex::ToolView), Flex::windowFlags());
            DockWidget* dockWidget = FlexManager::instance()->createDockWidget(Flex::ToolView, flexWidget, Flex::widgetFlags(), dockWidgetName);

            dockWidget->setViewMode(Flex::ToolView);
            dockWidget->setWindowTitle(dockWidgetName);

            flexWidget->addDockWidget(dockWidget);
            flexWidget->show();
            flexWidget->move(geometry().center() - flexWidget->rect().center());
        }
    }
}

void ui_mainwindow::on_view_communication()
{
    QString dockWidgetName = QStringLiteral("通讯调试");
    DockWidget* widget = nullptr;

    if ((widget = FlexManager::instance()->dockWidget(dockWidgetName)) != nullptr)
    {
        widget->activate();
    }
    else
    {
        if (!FlexManager::instance()->restore(dockWidgetName))
        {
            FlexWidget* flexWidget = FlexManager::instance()->createFlexWidget(Flex::ToolView, Flex::parent(Flex::ToolView), Flex::windowFlags());
            DockWidget* dockWidget = FlexManager::instance()->createDockWidget(Flex::ToolView, flexWidget, Flex::widgetFlags(), dockWidgetName);

            dockWidget->setViewMode(Flex::ToolView);
            dockWidget->setWindowTitle(dockWidgetName);

            flexWidget->addDockWidget(dockWidget);
            flexWidget->show();
            flexWidget->move(geometry().center() - flexWidget->rect().center());
        }
    }
}

void ui_mainwindow::on_view_music()
{
    QString dockWidgetName = QStringLiteral("Music");
    DockWidget* widget = nullptr;

    if ((widget = FlexManager::instance()->dockWidget(dockWidgetName)) != nullptr)
    {
        widget->activate();
    }
    else
    {
        if (!FlexManager::instance()->restore(dockWidgetName))
        {
            FlexWidget* flexWidget = FlexManager::instance()->createFlexWidget(Flex::ToolView, Flex::parent(Flex::ToolView), Flex::windowFlags());
            DockWidget* dockWidget = FlexManager::instance()->createDockWidget(Flex::ToolView, flexWidget, Flex::widgetFlags(), dockWidgetName);

            dockWidget->setViewMode(Flex::ToolView);
            dockWidget->setWindowTitle(dockWidgetName);

            flexWidget->addDockWidget(dockWidget);
            flexWidget->show();
            flexWidget->move(geometry().center() - flexWidget->rect().center());
        }
    }
}

void ui_mainwindow::on_view_cv()
{
    QString dockWidgetName = QStringLiteral("CV");
    DockWidget* widget = nullptr;

    if ((widget = FlexManager::instance()->dockWidget(dockWidgetName)) != nullptr)
    {
        widget->activate();
    }
    else
    {
        if (!FlexManager::instance()->restore(dockWidgetName))
        {
            FlexWidget* flexWidget = FlexManager::instance()->createFlexWidget(Flex::ToolView, Flex::parent(Flex::ToolView), Flex::windowFlags());
            DockWidget* dockWidget = FlexManager::instance()->createDockWidget(Flex::ToolView, flexWidget, Flex::widgetFlags(), dockWidgetName);

            dockWidget->setViewMode(Flex::ToolView);
            dockWidget->setWindowTitle(dockWidgetName);

            flexWidget->addDockWidget(dockWidget);
            flexWidget->show();
            flexWidget->move(geometry().center() - flexWidget->rect().center());
        }
    }
}


QtCentral::QtCentral(QWidget* parent) : QWidget(parent)
{
    // 【0】
    this->init_widget();
    // 【1】 设置窗口
    this->setObjectName("Central");

    // 【2】 开启空布局
    QHBoxLayout* box = new QHBoxLayout(this);
    box->setContentsMargins(0, 0, 0, 0);

    // 【3】 连接信号槽
    connect(FlexManager::instance(), SIGNAL(flexWidgetCreated(FlexWidget*)),    SLOT(on_flexWidgetCreated(FlexWidget*)));
    connect(FlexManager::instance(), SIGNAL(dockWidgetCreated(DockWidget*)),    SLOT(on_dockWidgetCreated(DockWidget*)));
    connect(FlexManager::instance(), SIGNAL(flexWidgetDestroying(FlexWidget*)), SLOT(on_flexWidgetDestroying(FlexWidget*)));
    connect(FlexManager::instance(), SIGNAL(dockWidgetDestroying(DockWidget*)), SLOT(on_dockWidgetDestroying(DockWidget*)));

    // 【4】 载入QSettings
    QSettings  settings("QtFlex5", "QtGuider");
    QByteArray content = settings.value("Flex").toByteArray();
    QMap<QString, QWidget*> parents;
    parents[objectName()] = this;

    if (content.isEmpty())
    {
        createOne();
    }
    else
    {
        FlexManager::instance()->load(content, parents);
    }
}

/** 初始化 Widget
 * @brief   初始化 Widget
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-11-30
 */
void QtCentral::init_widget()
{
    c_dock_main = new ui_main();

    c_dock_motor       = new ui_motor();
    c_dock_motor_set   = new ui_motor_set();
    c_dock_motor_point = new ui_motor_point();

    c_dock_communication = new ui_communication();

    c_dock_music       = new QMyMusic();
    c_dock_cv          = new QMyCV();
}

void QtCentral::createOne()
{
    auto content = FlexManager::instance()->createFlexWidget(Flex::HybridView, this, Flex::widgetFlags(), "M");
    layout()->addWidget(content);
}

void QtCentral::on_flexWidgetCreated(FlexWidget* flexWidget)
{
    if (flexWidget->objectName() == "M")
    {
        layout()->addWidget(flexWidget);
    }
    else
    {
        flexWidget->show();
    }
}

void QtCentral::on_dockWidgetCreated(DockWidget *dockWidget)
{
    if (dockWidget->objectName() == QStringLiteral("主界面"))
    {
        if (dockWidget->widget() != c_dock_main)
        {
            dockWidget->setWidget(c_dock_main);
        }
    }

    if (dockWidget->objectName() == QStringLiteral("电机调试"))
    {
        if (dockWidget->widget() != c_dock_motor)
        {
            dockWidget->setWidget(c_dock_motor);
        }
    }

    if (dockWidget->objectName() == QStringLiteral("电机设置"))
    {
        if (dockWidget->widget() != c_dock_motor_set)
        {
            dockWidget->setWidget(c_dock_motor_set);
        }
    }

    if (dockWidget->objectName() == QStringLiteral("点位调试"))
    {
        if (dockWidget->widget() != c_dock_motor_point)
        {
            dockWidget->setWidget(c_dock_motor_point);
            c_dock_motor_point->update_db();
        }
    }


    if (dockWidget->objectName() == QStringLiteral("通讯调试"))
    {
        if (dockWidget->widget() != c_dock_communication)
        {
            dockWidget->setWidget(c_dock_communication);
        }
    }

    if (dockWidget->objectName() == QStringLiteral("Music"))
    {
        if (dockWidget->widget() != c_dock_music)
        {
            dockWidget->setWidget(c_dock_music);
        }
    }

    if (dockWidget->objectName() == QStringLiteral("CV"))
    {
        if (dockWidget->widget() != c_dock_cv)
        {
            dockWidget->setWidget(c_dock_cv);
        }
    }
}

void QtCentral::on_dockWidgetDestroying(DockWidget *dockWidget)
{
    if (dockWidget->objectName() == QStringLiteral("主界面"))
    {
        if (dockWidget->widget() == c_dock_main)
        {
            dockWidget->detachWidget(c_dock_main);
        }
    }

    if (dockWidget->objectName() == QStringLiteral("电机调试"))
    {
        if (dockWidget->widget() == c_dock_motor)
        {
            dockWidget->detachWidget(c_dock_motor);
        }
    }

    if (dockWidget->objectName() == QStringLiteral("电机设置"))
    {
        if (dockWidget->widget() == c_dock_motor_set)
        {
            dockWidget->detachWidget(c_dock_motor_set);
        }
    }

    if (dockWidget->objectName() == QStringLiteral("点位调试"))
    {
        if (dockWidget->widget() == c_dock_motor_point)
        {
            dockWidget->detachWidget(c_dock_motor_point);
        }
    }


    if (dockWidget->objectName() == QStringLiteral("通讯调试"))
    {
        if (dockWidget->widget() == c_dock_communication)
        {
            dockWidget->detachWidget(c_dock_communication);
        }
    }

    if (dockWidget->objectName() == QStringLiteral("Music"))
    {
        if (dockWidget->widget() == c_dock_music)
        {
            dockWidget->detachWidget(c_dock_music);
        }
    }

    if (dockWidget->objectName() == QStringLiteral("CV"))
    {
        if (dockWidget->widget() == c_dock_cv)
        {
            dockWidget->detachWidget(c_dock_cv);
        }
    }
}

void QtCentral::on_flexWidgetDestroying(FlexWidget*)
{
}
