#ifndef SOCKETSERVICE_H
#define SOCKETSERVICE_H

#include <QObject>
#include <QWidget>

#include <QTcpServer>
#include <QTcpSocket>

enum class SocketDataType: quint8 {
    loginReqest,
    loginResponse,
    message
};

Q_DECLARE_METATYPE(SocketDataType);

class SocketService : QObject
{
    Q_OBJECT
public:
    SocketService(QObject *parent = nullptr);

    void write(QTcpSocket *socket, QByteArray &data, SocketDataType type);
    bool handleLoginRequest(QString &username, QString &password);

public slots:
    void onNewConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onReadyRead();

private:
    QTcpServer _server;
    QList<QTcpSocket*> _sockets;

};

#endif // SOCKETSERVICE_H
