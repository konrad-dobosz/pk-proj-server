#include "socketservice.h"
#include "dbhandler.h"
#include "socketdata/socketmessage.h"
#include "socketdata/socketlogin.h"

SocketService::SocketService(QObject *parent):
    QObject(parent),
    _server(this)
{
    _server.listen(QHostAddress::Any, 4242);
    connect(&_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

void SocketService::onNewConnection()
{
    QTcpSocket *clientSocket = _server.nextPendingConnection();
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

    _sockets.push_back(clientSocket);
}

void SocketService::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        _sockets.removeOne(sender);
    }
}

void SocketService::onReadyRead() {
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
    QDataStream readStream(sender);

    QString test = sender->readAll();
    qDebug() << test;

    quint16 size;
    quint8 type;

    readStream >> size;

    if (sender->bytesAvailable() < size) return;

    readStream >> type;

    if (SocketDataType(type) == SocketDataType::loginRequest) {
        SocketLogin sl;

        readStream >> sl;

        QString username = sl.getUsername();
        QString password = sl.getPassword();

        qDebug() << "LR - U: " << username << ", P: " << password;

        bool isAuthenticated = handleLoginRequest(username, password);

        qDebug() << isAuthenticated;

        write(sender, sl);
    } else if (SocketDataType(type) == SocketDataType::message) {
        SocketMessage sm;

        readStream >> sm;

        for (QTcpSocket* socket : _sockets) {
            if (socket != sender)
                write(socket, sm);
        }
    }
}

bool SocketService::handleLoginRequest(QString &username, QString &password) {
    DbHandler db;
    db.openDatabase();
    return db.authenticateUser(username, password);
}

void SocketService::write(QTcpSocket *socket, SocketData &data) {
    QByteArray streamData;
    QDataStream writeStream(&streamData, QIODevice::WriteOnly);
    writeStream <<  quint16(0) << data.type();
    writeStream << data;
    writeStream.device()->seek(0);
    writeStream << quint16(streamData.size() - sizeof(quint16));

    socket->write(streamData);
    socket->waitForBytesWritten();
}
