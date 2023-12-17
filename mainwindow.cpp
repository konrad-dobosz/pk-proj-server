#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QHostAddress>
#include <QAbstractSocket>

QDataStream &operator<< (QDataStream &ds, SocketDataType data) {
    return ds << (quint8)data;
}

QDataStream &operator>> (QDataStream &ds, SocketDataType data) {
    quint32 val;
    ds >> val;
    if (ds.status() == QDataStream::Ok) {
        data = SocketDataType(val);
    }

    return ds;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _server(this)
{
    ui->setupUi(this);
    _server.listen(QHostAddress::Any, 4242);
    connect(&_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewConnection()
{
    QTcpSocket *clientSocket = _server.nextPendingConnection();
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

    _sockets.push_back(clientSocket);
//    for (QTcpSocket* socket : _sockets) {
//        socket->write(QByteArray::fromStdString(clientSocket->peerAddress().toString().toStdString() + " connected to server !\n"));
//    }
}

void MainWindow::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        _sockets.removeOne(sender);
    }
}

void MainWindow::onReadyRead()
{
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());

    QDataStream readStream(sender);

    quint16 sizeRead;
    quint8 type;
    QByteArray msg;

    readStream >> sizeRead;

    if (sender->bytesAvailable() < sizeRead) return;

    readStream >> type;

    readStream >> msg;

    //QByteArray temp = QByteArray::fromStdString(sender->peerAddress().toString().toStdString() + ": " + msg.toStdString());

    switch (SocketDataType(type)) {
    case SocketDataType::loginReqest:
        write(sender, msg, SocketDataType::loginResponse);
        break;
    case SocketDataType::message:
        qDebug() << "Got msg!";

        for (QTcpSocket* socket : _sockets) {
            if (socket != sender)
                write(socket, msg, SocketDataType::message);
        }

        break;
    default:
        qDebug() << "Got someting else?";
        break;
    }
}

void MainWindow::write(QTcpSocket *socket, QByteArray &data, SocketDataType type) {
    QByteArray streamData;
    QDataStream writeStream(&streamData, QIODevice::WriteOnly);
    writeStream <<  quint16(0) << type;
    writeStream << data;
    writeStream.device()->seek(0);
    writeStream << quint16(streamData.size() - sizeof(quint16));

    socket->write(streamData);
    socket->waitForBytesWritten();
}
