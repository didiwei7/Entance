#include "qmysocket.h"

Client::Client()
{
    this->setupUi();
    this->client_init();
    this->connect_signals_slots();
}

/** Client 初始化 Ui
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-28
 */
void Client::setupUi()
{
    // 【1】 初始化控件
    // Widget
    client_widget = new QWidget();

    // BTN
    btn_client_connect  = new QToolButton();
    btn_client_connect->setText(QStringLiteral("连接"));
    btn_client_abort    = new QToolButton();
    btn_client_abort->setText(QStringLiteral("断开"));

    // TextBrowser
    textBrowser_client  = new QTextBrowser();

    // Edit
    textEdit_client     = new QTextEdit();

    btn_client_sendMsg  = new QToolButton();
    btn_client_clearMsg = new QToolButton();
    btn_client_sendMsg->setText(QStringLiteral("发送"));
    btn_client_clearMsg->setText(QStringLiteral("清空"));

    // ProgressBar
    label_progBar_fileread = new QLabel("...");
    label_progBar_filesend = new QLabel("...");

    progBar_client_fileread = new QProgressBar();
    progBar_client_filesend = new QProgressBar();

    // btn_client_fileread = new QToolButton();
    // btn_client_fileread->setText(QStringLiteral("接收"));
    btn_client_filesend = new QToolButton();
    btn_client_filesend->setText(QStringLiteral("发送"));

    // 【2】 布局
    QVBoxLayout *layout_1 = new QVBoxLayout();
    QGridLayout *layout_2_1 = new QGridLayout();
    QGridLayout *layout_2_2 = new QGridLayout();
    QGridLayout *layout_2_3 = new QGridLayout();

    layout_1->addLayout(layout_2_1);
    layout_1->addWidget(textBrowser_client);
    layout_1->addLayout(layout_2_2);
    layout_1->addLayout(layout_2_3);


    layout_2_1->addWidget(btn_client_connect, 0, 0);
    layout_2_1->addWidget(btn_client_abort,   0, 1);

    layout_2_2->addWidget(textEdit_client,    0, 0, 2, 2);
    layout_2_2->addWidget(btn_client_sendMsg, 0, 3);
    layout_2_2->addWidget(btn_client_clearMsg,1, 3);

    layout_2_3->addWidget(label_progBar_fileread,  0, 0, 1, 2);
    layout_2_3->addWidget(progBar_client_fileread, 1, 0);
    // layout_2_3->addWidget(btn_client_fileread,     1, 1);
    layout_2_3->addWidget(label_progBar_filesend,  2, 0, 1, 2);
    layout_2_3->addWidget(progBar_client_filesend, 3, 0);
    layout_2_3->addWidget(btn_client_filesend,     3, 1);

    client_widget->setLayout(layout_1);

    // 【3】 设置按钮初始状态
    btn_client_connect->setEnabled(false);
    btn_client_abort  ->setEnabled(false);

    btn_client_sendMsg ->setEnabled(false);
    btn_client_clearMsg->setEnabled(false);

    btn_client_filesend->setEnabled(false);

    progBar_client_fileread->reset();
    progBar_client_filesend->reset();
}

/** Client 初始化客户端
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-28
 */
void Client::client_init()
{
    tcpClient = new QTcpSocket();

    tcpClient_file = new QTcpSocket();
    client_read_bytes_total = 0;
    client_read_bytes_readed = 0;
    client_read_fileName_size = 0;
}

/** Client 连接信号槽
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-28
 */
void Client::connect_signals_slots()
{
    // 【1】 连接,断开
    connect(btn_client_connect, &QToolButton::clicked,  this, &Client::client_connect);
    connect(btn_client_abort,   &QToolButton::clicked,  this, &Client::client_abort);

    // 【2】 消息 发送,清空
    connect(btn_client_sendMsg, &QToolButton::clicked,  this, &Client::client_sendMsg);
    connect(btn_client_clearMsg,&QToolButton::clicked,  textEdit_client, &QTextEdit::clear);
    connect(tcpClient,          &QTcpSocket::readyRead, this, &Client::client_readMsg);

    // 【3】 文件 发送/接收
    connect(btn_client_filesend,&QToolButton::clicked,     this, &Client::client_sendFile);
    connect(tcpClient_file,     &QTcpSocket::bytesWritten, this, &Client::update_client_progressBar_send);
    connect(tcpClient_file,     &QTcpSocket::readyRead,    this, &Client::client_readFile);
}

/** Client 连接服务器
 * @brief   开始监听
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-28
 */
void Client::client_connect()
{
    tcpClient->connectToHost(QHostAddress::LocalHost, 7777);

    tcpClient_file->connectToHost(QHostAddress::LocalHost, 8888);

    btn_client_connect->setEnabled(false);
    btn_client_abort  ->setEnabled(true);

    btn_client_sendMsg  ->setEnabled(true);
    btn_client_clearMsg->setEnabled(true);

    btn_client_filesend->setEnabled(true);
}

/** Client 断开服务器
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-29
 */
void Client::client_abort()
{
    tcpClient     ->abort();
    tcpClient_file->abort();

    btn_client_connect->setEnabled(true);
    btn_client_abort  ->setEnabled(false);

    btn_client_sendMsg ->setEnabled(false);
    btn_client_clearMsg->setEnabled(false);

    btn_client_filesend->setEnabled(false);
}

/** Client 接收数据
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-date
 */
void Client::client_readMsg()
{
    // 【1】 声明数据长度， 接收数据字符串
    quint16 buff_size = 0;
    QString msg;

    // 【2】 数据流传输
    QDataStream in(tcpClient);
    in.setVersion(QDataStream::Qt_5_9);     // 设置数据流版本，这里要和服务器端相同

    if(0 == buff_size)
    {
        //判断接收的数据是否大于两字节，也就是文件的大小信息所占的空间
        //如果是则保存到blockSize变量中，否则直接返回，继续接收数据
        if(tcpClient->bytesAvailable() < (int)sizeof(quint16))
        {
            return;  //bytesAvailable()返回字节数
        }
        in >> buff_size;
    }
    // 如果没有得到全部的数据，则返回，继续接收数据
    if(tcpClient->bytesAvailable() < buff_size)
    {
        return;
    }
    // 将接收到的数据存放到变量中
    in >> msg;

    // 【3】 显示数据
    QDateTime currentTime = QDateTime::currentDateTime();
    QString m_currentTime = currentTime.toString(QStringLiteral("yyyy-yy-dd  hh:mm:ss"));
    m_currentTime.insert(0,QStringLiteral("服务器: "));
    textBrowser_client->append(m_currentTime);
    textBrowser_client->append(msg);

    buff_size = 0;
}

/** Client 发送信息
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-29
 */
void Client::client_sendMsg()
{
    // 【1】 获取当前编辑框文本
    QString msg = textEdit_client->document()->toPlainText();

    // 【2】 创建 缓存区
    QByteArray buff;

    // 【3】 数据流传输
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);

    out << (quint16)0;      // 2位， 首先占两位,用于存放数据的大小信息
    out << msg;             // 放入数据
    out.device()->seek(0);
    out << (quint16)(buff.size() - sizeof(quint16));  // 2位： 数据大小

    // 【4】 写入数据
    tcpClient->write(buff);

    // 【5】 当前窗口显示
    QDateTime currentTime = QDateTime::currentDateTime();
    QString m_currentTime = currentTime.toString(QStringLiteral("yyyy-yy-dd  hh:mm:ss"));
    m_currentTime.insert(0,QStringLiteral("客户端: "));
    textBrowser_client->append(m_currentTime);
    textBrowser_client->append(msg);

    // 【6】 清空编辑框
    textEdit_client->clear();
}

/** Client 接收文件
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-31
 */
void Client::client_readFile()
{
    QDataStream readIn(tcpClient_file);
    readIn.setVersion(QDataStream::Qt_5_9);

    // 如果接收到的数据小于16个字节，保存到来的文件头结构
    if (client_read_bytes_readed <= sizeof(qint64)*2)
    {
        if((tcpClient_file->bytesAvailable() >= sizeof(qint64)*2) && (client_read_fileName_size == 0))
        {
            // 接收 数据总大小信息, 文件名大小信息
            readIn >> client_read_bytes_total >> client_read_fileName_size;
            client_read_bytes_readed += sizeof(qint64) * 2;
        }
        if((tcpClient_file->bytesAvailable() >= client_read_fileName_size) && (client_read_fileName_size != 0))
        {
            // 接收文件名，并建立文件
            readIn >> client_read_fileName;
            label_progBar_fileread->setText(QStringLiteral("接收文件: %1").arg(client_read_fileName));
            client_read_bytes_readed += client_read_fileName_size;

            client_read_file = new QFile(client_read_fileName);
            if (!client_read_file->open(QFile::WriteOnly))
            {
                qDebug() << "client: open file error!";
                return;
            }
        }
        else
        {
            return;
        }
    }

    // 如果接收的数据小于总数据，那么写入文件
    if (client_read_bytes_readed < client_read_bytes_total)
    {
        client_read_bytes_readed += tcpClient_file->bytesAvailable();
        client_read_buff = tcpClient_file->readAll();
        client_read_file->write(client_read_buff);
        client_read_buff.resize(0);
    }

    progBar_client_fileread->setMaximum(client_read_bytes_total);
    progBar_client_fileread->setValue(client_read_bytes_readed);

    // 接收数据完成时
    if (client_read_bytes_readed == client_read_bytes_total)
    {
        client_read_file->close();
        client_read_bytes_total = 0;
        client_read_bytes_readed = 0;
        client_read_fileName_size = 0;
        label_progBar_fileread ->setText(QStringLiteral("接收文件 %1 成功").arg(client_read_fileName));
    }
}

/** Client 发送文件
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-31
 */
void Client::client_sendFile()
{
    // 【1】 初始化文件数据参数
    client_send_bytes_send_once = 64*1024; // 64KB
    client_send_bytes_total     = 0;
    client_send_bytes_written   = 0;
    client_send_bytes_toWrite   = 0;
    client_send_filePath        = "";
    client_send_fileName        = "";
    client_send_buff.resize(0);

    // 【2】 打开文件对话框,获取文件路径
    client_send_filePath = QFileDialog::getOpenFileName();

    // 打开文件
    client_send_file = new QFile(client_send_filePath);
    if (!client_send_file->open(QFile::ReadOnly)) {
        qDebug() << "client: open file error!";
        return;
    }

     // 获取文件大小
    client_send_bytes_total = client_send_file->size();

    // 获取文件名
    // client_send_fileName = client_send_filePath.right(client_send_filePath.size() - client_send_filePath.lastIndexOf('/')-1);
    client_send_fileName = client_send_filePath.split("/").last();

    // 【3】 使用数据流传输
    QDataStream sendOut(&client_send_buff, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_9);

    // 保留总大小信息空间、文件名大小信息空间，然后输入文件名
    sendOut << qint64(0) << qint64(0) << client_send_fileName;  // 占位

    // 这里的总大小是总大小信息、文件名大小信息、文件名和实际文件大小的总和
    client_send_bytes_total += client_send_buff.size();
    sendOut.device()->seek(0);

    // 返回outBolock的开始，用实际的大小信息代替两个qint64(0)空间
    sendOut << client_send_bytes_total << qint64((client_send_buff.size() - sizeof(qint64)*2));

    // 发送完文件头结构后剩余数据的大小
    client_send_bytes_toWrite = client_send_bytes_total - tcpClient_file->write(client_send_buff);

    client_send_buff.resize(0);
}

/** Client 发送文件,每次发送64KB
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-31
 */
void Client::update_client_progressBar_send(qint64 numBytes)
{
    // 【1】 已经发送数据的大小
    client_send_bytes_written += (int)numBytes;

    // 【2】 如果已经发送了数据
    if (client_send_bytes_toWrite > 0)
    {
        // 每次发送client_send_bytes_send_once大小的数据，这里设置为64KB，如果剩余的数据不足64KB，
        // 就发送剩余数据的大小
        client_send_buff = client_send_file->read(qMin(client_send_bytes_toWrite, client_send_bytes_send_once));

        // 发送完一次数据后还剩余数据的大小
        client_send_bytes_toWrite -= (int)tcpClient_file->write(client_send_buff);

        // 清空发送缓冲区
        client_send_buff.resize(0);
    }
    else
    { // 如果没有发送任何数据，则关闭文件
        client_send_file->close();
    }

    // 【3】 更新进度条
    progBar_client_filesend->setMaximum(client_send_bytes_total);
    progBar_client_filesend->setValue(client_send_bytes_written);
    label_progBar_filesend ->setText(QStringLiteral("发送文件 %1").arg(client_send_fileName));

    // 【4】 如果发送完毕
    if(client_send_bytes_written == client_send_bytes_total)
    {
        client_send_file->close();
        label_progBar_filesend->setText(QStringLiteral("发送文件 %1 成功").arg(client_send_fileName));
    }
}

/** 通过服务器状态,更新客户端按钮状态
 * @brief   此函数当 Server 发射信号时,触发
 * @arguments
 *      bool b:     b = true, 切换 btn_client_connect 按钮为 "可点击状态".
 *                            此时连接已经断开,但是服务器是开着的.
 *                  b = false,切换 btn_client_connect 按钮为 "不可点击状态".
 *                            此时连接已经断开,服务器处于关闭状态.
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-date
 */
void Client::update_client_status(bool b)
{
    if(b)
    {
        // 此时只有 "连接" 按钮可以点击
        btn_client_connect->setEnabled(true);
        btn_client_abort->setEnabled(false);

        btn_client_sendMsg ->setEnabled(false);
        btn_client_clearMsg->setEnabled(false);

        btn_client_filesend->setEnabled(false);
    }
    else
    {
        // 此时都不可点击
        btn_client_connect->setEnabled(false);
        btn_client_abort  ->setEnabled(false);

        btn_client_sendMsg ->setEnabled(false);
        btn_client_clearMsg->setEnabled(false);

        btn_client_filesend->setEnabled(false);
    }
}


Server::Server()
{
    this->setupUi();
    this->server_init();
    this->connect_signals_slots();
}

/** Server 初始化 Ui
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-28
 */
void Server::setupUi()
{
    // 【1】 初始化控件
    // Widget
    server_widget = new QWidget();

    // BTN
    btn_server_start  = new QToolButton();
    btn_server_start->setText(QStringLiteral("启动"));
    btn_server_abort  = new QToolButton();
    btn_server_abort->setText(QStringLiteral("关闭"));

    // TextBrowser
    textBrowser_server  = new QTextBrowser();
    textEdit_server     = new QTextEdit();
    btn_server_sendMsg  = new QToolButton();
    btn_server_sendMsg->setText(QStringLiteral("发送"));
    btn_server_clearMsg = new QToolButton();
    btn_server_clearMsg->setText(QStringLiteral("清空"));

    // ProgressBar
    label_progBar_fileread = new QLabel("...");
    label_progBar_filesend = new QLabel("...");

    progBar_server_fileread = new QProgressBar();
    progBar_server_filesend = new QProgressBar();

    // btn_server_fileread = new QToolButton();
    // btn_server_fileread->setText(QStringLiteral("接收"));
    btn_server_filesend = new QToolButton();
    btn_server_filesend->setText(QStringLiteral("发送"));

    // 【2】 布局
    // 1表示该窗口的 1级布局，
    // 2_1 表示该窗口的 2级布局的 第1个布局 ...
    QVBoxLayout *layout_1 = new QVBoxLayout();
    QGridLayout *layout_2_1 = new QGridLayout();
    QGridLayout *layout_2_2 = new QGridLayout();
    QGridLayout *layout_2_3 = new QGridLayout();

    layout_1->addLayout(layout_2_1);
    layout_1->addWidget(textBrowser_server);
    layout_1->addLayout(layout_2_2);
    layout_1->addLayout(layout_2_3);


    layout_2_1->addWidget(btn_server_start, 0, 0);
    layout_2_1->addWidget(btn_server_abort,   0, 1);

    layout_2_2->addWidget(textEdit_server,    0, 0, 2, 2);
    layout_2_2->addWidget(btn_server_sendMsg,    0, 3);
    layout_2_2->addWidget(btn_server_clearMsg,   1, 3);

    layout_2_3->addWidget(label_progBar_fileread,  0, 0, 1, 2);
    layout_2_3->addWidget(progBar_server_fileread, 1, 0);
    // layout_2_3->addWidget(btn_server_fileread,     1, 1);
    layout_2_3->addWidget(label_progBar_filesend,  2, 0, 1, 2);
    layout_2_3->addWidget(progBar_server_filesend, 3, 0);
    layout_2_3->addWidget(btn_server_filesend,     3, 1);

    server_widget->setLayout(layout_1);

    // 【3】 初始化按钮状态
    btn_server_abort   ->setEnabled(false);

    btn_server_sendMsg ->setEnabled(false);
    btn_server_clearMsg->setEnabled(false);

    // btn_server_fileread->setEnabled(false);
    btn_server_filesend->setEnabled(false);

    progBar_server_fileread->reset();
    progBar_server_filesend->reset();


    //    // 【3】 绑定 视图/模型
    //    model_list_client   = new QStringListModel();
    //    model_list_client->setStringList(stringList_client);
    //    listView_client->setModel(model_list_client);
}

/** Server 初始化服务器
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-28
 */
void Server::server_init()
{
    // 服务器 消息
    tcpServer = new QTcpServer();
    m_socket  = new QTcpSocket();

    // 服务器 文件
    tcpServer_file = new QTcpServer();
    m_socket_file  = new QTcpSocket();

    // 数据初始化 文件接收
    server_read_bytes_total   = 0;
    server_read_bytes_readed  = 0;
    server_read_fileName_size = 0;
    progBar_server_fileread->reset();
}

/** Server 连接信号槽
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-28
 */
void Server::connect_signals_slots()
{
    // 【1】 开启,关闭,发送,清空
    connect(btn_server_start,   &QToolButton::clicked, this, &Server::server_start);
    connect(btn_server_abort,   &QToolButton::clicked, this, &Server::server_abort);
    connect(btn_server_sendMsg, &QToolButton::clicked, this, &Server::server_sendMsg);
    connect(btn_server_clearMsg,&QToolButton::clicked, textEdit_server, &QTextEdit::clear);

    // 【2】 触发新连接
    connect(tcpServer,      &QTcpServer::newConnection, this, &Server::server_accept);
    connect(tcpServer_file, &QTcpServer::newConnection, this, &Server::server_accept_file);

    connect(btn_server_filesend, &QToolButton::clicked, this, &Server::server_sendFile);
}

/** Server 启动服务器
 * @brief   开始监听
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-28
 */
void Server::server_start()
{
    // 切换按钮状态
    btn_server_start->setEnabled(false);
    btn_server_abort->setEnabled(true);

    // 开始监听
    if (!tcpServer->listen(QHostAddress::Any, 7777))
    {
        // 【1】 错误信息显示
        qDebug() << "tcpServer" << tcpServer->errorString();

        // 【2】 弹出对话框， 警告用户
        QMessageBox::StandardButton ret = QMessageBox::critical(this,
                                                         "Warning",
                                                         QStringLiteral("启动服务器失败\n请检查服务器是否已启动"),
                                                         QMessageBox::Yes | QMessageBox::Cancel);
        if(QMessageBox::Yes == ret)
        {
            // this->close();
            // return;
            // 【3】 消息显示
            textBrowser_server->append(QStringLiteral("服务器已启动,请勿重复操作"));

            // 【4】 设置按钮状态
            btn_server_start->setEnabled(false);
            btn_server_abort->setEnabled(false);
        }
        else
        {
            return;
        }
    }
    else
    {
        // 【4】 设置按钮状态
        textBrowser_server->append(QStringLiteral("启动服务器成功"));

        btn_server_start->setEnabled(false);
        btn_server_abort->setEnabled(true);

        btn_server_sendMsg->setEnabled(true);
        btn_server_clearMsg->setEnabled(true);
    }


    if (!tcpServer_file->listen(QHostAddress::Any, 8888))
    {
        qDebug() << "tcpServer_file" << tcpServer_file->errorString();

    }
    else
    {
        btn_server_filesend->setEnabled(true);
    }

    // 发射信号
    emit server_status_Changed(true);
}

/** Server 关闭服务器
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-29
 */
void Server::server_abort()
{
    // 【1】 关闭服务器
    tcpServer->close();

    // 【2】 断开Tcp连接，关闭
    m_socket ->disconnect();
    m_socket ->abort();

    tcpServer_file->close();
    m_socket_file->disconnect();
    m_socket_file->abort();

    qDebug() << "m_socket:  " << m_socket->state();
    qDebug() << "m_socket_file" << m_socket_file->state();

    // 【3】 设置按钮状态
    btn_server_start->setEnabled(true);
    btn_server_abort->setEnabled(false);

    btn_server_sendMsg ->setEnabled(false);
    btn_server_clearMsg->setEnabled(false);

    btn_server_filesend->setEnabled(false);

    // 【4】 发送信号，服务器切换按钮状态
    emit server_status_Changed(false);
}

/** Server 消息 开始接收连接
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-28
 */
void Server::server_accept()
{
    // 开始连接
    m_socket->abort();
    m_socket = tcpServer->nextPendingConnection();
    qDebug() << "m_socket:" << m_socket->state();
    textBrowser_server->append(QStringLiteral("用户连接成功"));
    connect(m_socket, &QTcpSocket::readyRead,    this,     &Server::server_readMsg);
}

/** Server 文件 开始接收连接
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-28
 */
void Server::server_accept_file()
{
    // 开始连接
    m_socket_file->abort();
    m_socket_file = tcpServer_file->nextPendingConnection();
    qDebug() << "m_socket_file" << m_socket_file->state();

    connect(m_socket_file, &QTcpSocket::readyRead,    this, &Server::server_readFile);
    connect(m_socket_file, &QTcpSocket::bytesWritten, this, &Server::update_server_progressBar_send);
}

/** Server 接收信息
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-29
 */
void Server::server_readMsg()
{
    // 【1】 声明数据长度， 接收数据字符串
    quint16 buff_size = 0;
    QString msg;

    // 【2】 数据流传输
    QDataStream in(m_socket);
    in.setVersion(QDataStream::Qt_5_9);     // 设置数据流版本，这里要和服务器端相同

    if(0 == buff_size)
    {
        //判断接收的数据是否大于两字节，也就是文件的大小信息所占的空间
        //如果是则保存到blockSize变量中，否则直接返回，继续接收数据
        if(m_socket->bytesAvailable() < (int)sizeof(quint16))
        {
            return;  //bytesAvailable()返回字节数
        }
        in >> buff_size;
    }
    // 如果没有得到全部的数据，则返回，继续接收数据
    if(m_socket->bytesAvailable() < buff_size)
    {
        return;
    }
    // 将接收到的数据存放到变量中
    in >> msg;

    // 【3】 显示数据
    QDateTime currentTime = QDateTime::currentDateTime();
    QString m_currentTime = currentTime.toString(QStringLiteral("yyyy-yy-dd  hh:mm:ss"));
    m_currentTime.insert(0,QStringLiteral("客户端: "));
    textBrowser_server->append(m_currentTime);
    textBrowser_server->append(msg);

    buff_size = 0;

    // disconnect(m_socket, &QTcpSocket::readyRead, this, &Server::server_readMsg);
}

/** Server 发送信息
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-29
 */
void Server::server_sendMsg()
{
    // 【1】 获取当前编辑框文本
    QString msg = textEdit_server->document()->toPlainText();

    // 【2】 创建 缓存区
    QByteArray buff;

    // 【3】 数据流传输
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);

    out << (quint16)0;
    out << msg;
    out.device()->seek(0);
    out << (quint16)(buff.size() - sizeof(quint16));

    // 【4】 写入数据
    m_socket->write(buff);

    // 【5】 当前窗口显示
    QDateTime currentTime = QDateTime::currentDateTime();
    QString m_currentTime = currentTime.toString(QStringLiteral("yyyy-yy-dd  hh:mm:ss"));
    m_currentTime.insert(0,QStringLiteral("服务器: "));
    textBrowser_server->append(m_currentTime);
    textBrowser_server->append(msg);

    // 【6】 清空编辑框
    textEdit_server->clear();
}

/** Server 接收文件
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-29
 */
void Server::server_readFile()
{
    QDataStream readIn(m_socket_file);
    readIn.setVersion(QDataStream::Qt_5_9);

    // 如果接收到的数据小于16个字节，保存到来的文件头结构
    if (server_read_bytes_readed <= sizeof(qint64)*2)
    {
        if((m_socket_file->bytesAvailable() >= sizeof(qint64)*2) && (server_read_fileName_size == 0))
        {
            // 接收 数据总大小信息, 文件名大小信息
            readIn >> server_read_bytes_total >> server_read_fileName_size;
            server_read_bytes_readed += sizeof(qint64) * 2;
        }
        if((m_socket_file->bytesAvailable() >= server_read_fileName_size) && (server_read_fileName_size != 0))
        {
            // 接收文件名，并建立文件
            readIn >> server_read_fileName;
            label_progBar_fileread->setText(QStringLiteral("接收文件: %1").arg(server_read_fileName));
            server_read_bytes_readed += server_read_fileName_size;

            server_read_file = new QFile(server_read_fileName);
            if (!server_read_file->open(QFile::WriteOnly))
            {
                qDebug() << "server: open file error!";
                return;
            }
        }
        else
        {
            return;
        }
    }

    // 如果接收的数据小于总数据，那么写入文件
    if (server_read_bytes_readed < server_read_bytes_total)
    {
        server_read_bytes_readed += m_socket_file->bytesAvailable();
        server_read_buff = m_socket_file->readAll();
        server_read_file->write(server_read_buff);
        server_read_buff.resize(0);
    }

    progBar_server_fileread->setMaximum(server_read_bytes_total);
    progBar_server_fileread->setValue(server_read_bytes_readed);

    // 接收数据完成时
    if (server_read_bytes_readed == server_read_bytes_total)
    {
        server_read_file->close();
        server_read_bytes_total = 0;
        server_read_bytes_readed = 0;
        server_read_fileName_size = 0;
        label_progBar_fileread ->setText(QStringLiteral("接收文件 %1 成功").arg(server_read_fileName));
    }
}

/** Server 发送文件
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-29
 */
void Server::server_sendFile()
{
    // 【1】 初始化文件数据参数
    server_send_bytes_send_once = 64*1024; // 64KB
    server_send_bytes_total     = 0;
    server_send_bytes_written   = 0;
    server_send_bytes_toWrite   = 0;
    server_send_filePath        = "";
    server_send_fileName        = "";
    server_send_buff.resize(0);

    // 【2】 打开文件对话框,获取文件路径
    server_send_filePath = QFileDialog::getOpenFileName();

    // 打开文件
    server_send_file = new QFile(server_send_filePath);
    if (!server_send_file->open(QFile::ReadOnly)) {
        qDebug() << "server: open file error!";
        return;
    }

     // 获取文件大小
    server_send_bytes_total = server_send_file->size();

    // 获取文件名
    // server_send_fileName = server_send_filePath.right(server_send_filePath.size() - server_send_filePath.lastIndexOf('/')-1);
    server_send_fileName = server_send_filePath.split("/").last();

    // 【3】 使用数据流传输
    QDataStream sendOut(&server_send_buff, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_9);

    // 保留总大小信息空间、文件名大小信息空间，然后输入文件名
    sendOut << qint64(0) << qint64(0) << server_send_fileName;  // 占位

    // 这里的总大小是总大小信息、文件名大小信息、文件名和实际文件大小的总和
    server_send_bytes_total += server_send_buff.size();
    sendOut.device()->seek(0);

    // 返回outBolock的开始，用实际的大小信息代替两个qint64(0)空间
    sendOut << server_send_bytes_total << qint64((server_send_buff.size() - sizeof(qint64)*2));

    // 发送完文件头结构后剩余数据的大小
    server_send_bytes_toWrite = server_send_bytes_total - m_socket_file->write(server_send_buff);

    server_send_buff.resize(0);

    qDebug() << "123";
}

/** Server 发送文件,每次发送64KB
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-10-31
 */
void Server::update_server_progressBar_send(qint64 numBytes)
{
    // 【1】 已经发送数据的大小
    server_send_bytes_written += (int)numBytes;

    // 【2】 如果已经发送了数据
    if (server_send_bytes_toWrite > 0)
    {
        // 每次发送server_send_bytes_send_once大小的数据，这里设置为64KB，如果剩余的数据不足64KB，
        // 就发送剩余数据的大小
        server_send_buff = server_send_file->read(qMin(server_send_bytes_toWrite, server_send_bytes_send_once));

        // 发送完一次数据后还剩余数据的大小
        server_send_bytes_toWrite -= (int)m_socket_file->write(server_send_buff);

        // 清空发送缓冲区
        server_send_buff.resize(0);
    }
    else
    { // 如果没有发送任何数据，则关闭文件
        server_send_file->close();
    }

    // 【3】 更新进度条
    progBar_server_filesend->setMaximum(server_send_bytes_total);
    progBar_server_filesend->setValue(server_send_bytes_written);
    label_progBar_filesend->setText(QStringLiteral("发送文件 %1").arg(server_send_fileName));

    // 【4】 如果发送完毕
    if(server_send_bytes_written == server_send_bytes_total)
    {
        server_send_file->close();
        label_progBar_filesend->setText(QStringLiteral("发送文件 %1 成功").arg(server_send_fileName));
    }

}



Socket::Socket(QWidget *parent) : QWidget(parent)
{
    this->setupUi();
}

void Socket::setupUi()
{
    // 【2】 载入 Server 窗口
    c_server = new Server();

    // 【3】 载入 Client 窗口
    c_client = new Client();

    // 【4】 连接 Server, Client 状态更新的信号槽
    connect(c_server, &Server::server_status_Changed, c_client, &Client::update_client_status);

    // 【5】 布局
    QVBoxLayout *layout_1 = new QVBoxLayout();
    layout_1->addWidget(c_client->client_widget);
    layout_1->addWidget(c_server->server_widget);

    this->setLayout(layout_1);
}
