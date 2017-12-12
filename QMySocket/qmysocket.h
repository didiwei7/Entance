#ifndef SOCKET_H
#define SOCKET_H

#include <QtWidgets>
#include <QObject>
#include <QFile>
#include <QtNetwork>
#include <QDebug>
#include <QDataStream>

#include "socket_global.h"

class Client;
class Server;

class SOCKETSHARED_EXPORT Socket : public QWidget
{
    Q_OBJECT
public:
    Socket(QWidget *parent = 0);

public:
    void setupUi();

private:
    Client   *c_client;
    Server   *c_server;
};


class SOCKETSHARED_EXPORT Client : public QWidget
{
    Q_OBJECT
public:
    Client();

public:
    // 初始化
    void setupUi();
    void client_init();
    void connect_signals_slots();

public:
    QWidget      *client_widget;

private:
    // BTN 启动，关闭
    QToolButton  *btn_client_connect;
    QToolButton  *btn_client_abort;

    // TextBrowser    显示消息
    QTextBrowser *textBrowser_client;

    // TextEdit, BTN  发送消息
    QTextEdit    *textEdit_client;
    QToolButton  *btn_client_sendMsg;
    QToolButton  *btn_client_clearMsg;

    // ProgressBar   发送/接收 文件
    QLabel       *label_progBar_filesend;
    QProgressBar *progBar_client_filesend;
    QToolButton  *btn_client_filesend;

    QLabel       *label_progBar_fileread;
    QProgressBar *progBar_client_fileread;
    // QToolButton  *btn_client_fileread;

private:
    // 客户端 连接/断开
    void client_connect();
    void client_abort();

    // 文本信息传输
    void client_readMsg();
    void client_sendMsg();

    // 文件传输
    void client_readFile();
    void client_sendFile();
    void update_client_progressBar_send(qint64 numBytes);

public slots:

    // Qt5的信号槽,初次使用
    // 控制 Client 窗口的按钮状态
    void update_client_status(bool b);

private:
    QTcpSocket       *tcpClient;
    QTcpSocket       *tcpClient_file;

    // 发送文件
    QFile   *client_send_file;                 // 发送文件的对象
    QString client_send_filePath;              // 文件的路径
    QString client_send_fileName;              // 文件名, 发送
    qint64  client_send_bytes_total;           // 发送数据的总大小 = 文件大小信息(2) + 文件名() + 文件数据
    qint64  client_send_bytes_written;         // 已发送数据大小
    qint64  client_send_bytes_toWrite;         // 未发送数据大小
    qint64  client_send_bytes_send_once;       // 每次发送数据的大小
    QByteArray client_send_buff;               // 数据发送缓冲区, 存放每次发送的数据块

    // 接收文件
    QFile   *client_read_file;                 // 接收文件的对象
    QString client_read_fileName;              // 文件名， 存放
    qint64  client_read_fileName_size;         // 文件名的大小信息
    qint64  client_read_bytes_total;           // 接收数据的总大小 = 文件大小信息(2) + 文件名() + 文件数据
    qint64  client_read_bytes_readed;          // 已接收的数据大小
    qint64  client_read_bytes_toRead;          // 未接收数据大小
    qint64  client_read_bytes_read_once;       // 每次发送数据的大小
    QByteArray client_read_buff;               // 数据接收缓冲区
};


class SOCKETSHARED_EXPORT Server : public QWidget
{
    Q_OBJECT
public:
    Server();

public:
    // 初始化
    void setupUi();
    void server_init();
    void connect_signals_slots();

public:
    QWidget      *server_widget;

private:
    // BTN 启动，关闭
    QToolButton  *btn_server_start;
    QToolButton  *btn_server_abort;

    // TextBrowser    显示消息
    QTextBrowser *textBrowser_server;

    // TextEdit, BTN  发送消息
    QTextEdit    *textEdit_server;
    QToolButton  *btn_server_sendMsg;
    QToolButton  *btn_server_clearMsg;

    // ProgressBar   发送/接收 文件
    QLabel       *label_progBar_filesend;
    QProgressBar *progBar_server_filesend;
    QToolButton  *btn_server_filesend;

    QLabel       *label_progBar_fileread;
    QProgressBar *progBar_server_fileread;

private:
    // 服务器 启动/关闭
    void server_start();
    void server_abort();

    // 连接套接字通讯
    void server_accept();
    void server_accept_file();

    // 文本消息 发送/接收
    void server_readMsg();
    void server_sendMsg();

    // 文件 发送/接收
    void server_sendFile();
    void update_server_progressBar_send(qint64 numBytes);
    void server_readFile();

signals:
    // Qt5的信号槽,初次使用
    // 控制 Client 窗口的按钮状态
    void server_status_Changed(bool b);

private:
    QTcpServer *tcpServer;
    QTcpSocket *m_socket;

    QTcpServer *tcpServer_file;
    QTcpSocket *m_socket_file;

    // 发送文件
    QFile  *server_send_file;                  // 发送文件的对象
    QString server_send_filePath;              // 文件的路径
    QString server_send_fileName;              // 文件名, 发送
    qint64  server_send_bytes_total;           // 发送数据的总大小 = 文件大小信息(2) + 文件名() + 文件数据
    qint64  server_send_bytes_written;         // 已发送数据大小
    qint64  server_send_bytes_toWrite;         // 未发送数据大小
    qint64  server_send_bytes_send_once;       // 每次发送数据的大小
    QByteArray server_send_buff;               // 数据发送缓冲区, 存放每次发送的数据块

    // 接收文件
    QFile  *server_read_file;                  // 接收文件的对象
    QString server_read_fileName;              // 文件名， 存放
    qint64  server_read_fileName_size;         // 文件名的大小信息
    qint64  server_read_bytes_total;           // 接收数据的总大小 = 文件大小信息(2) + 文件名() + 文件数据
    qint64  server_read_bytes_readed;            // 已接收的数据大小
    qint64  server_read_bytes_toRead;          // 未接收数据大小
    qint64  server_read_bytes_read_once;       // 每次发送数据的大小
    QByteArray server_read_buff;               // 数据接收缓冲区
};


#endif // SOCKET_H
