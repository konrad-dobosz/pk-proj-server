#include "socketlogin.h"
#include "qdebug.h"

SocketLogin::SocketLogin() {}

SocketLogin::SocketLogin(QString& username, QString& password)
    : username(username),
    password(password)
{}

QString SocketLogin::getUsername() { return username; }
QString SocketLogin::getPassword() { return password; }

void SocketLogin::setUsername(QString &username) {
    this->username = username;
}

void SocketLogin::setPassword(QString &password) {
    this->password = password;
}

SocketDataType SocketLogin::type() {
    return SocketDataType::loginResponse;
}

QDataStream& SocketLogin::readStream(QDataStream &ds) {
    if (ds.status() == QDataStream::Ok) {
        ds >> username;
        ds >> password;
    }
    qDebug() << "Username: " << username << ", password:" << password;

    return ds;
}

QDataStream& SocketLogin::writeStream(QDataStream &ds) {
    ds << username << password;
    qDebug() << username << password;
    return ds;
}
