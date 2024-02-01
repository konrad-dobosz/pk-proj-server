#include "socketlogin.h"

QDataStream &operator<< (QDataStream &ds, SocketLogin &data) {
    return ds << data.getUsername() << data.getPassword();
}

QDataStream &operator>> (QDataStream &ds, SocketLogin &data) {
    QString username;
    QString password;
    ds >> username;
    ds >> password;
    if (ds.status() == QDataStream::Ok) {
        data.setUsername(username);
        data.setPassword(password);
    }

    return ds;
}

SocketLogin::SocketLogin() {}

SocketLogin::SocketLogin(QString& username, QString& password)
    : username(username),
    password(password)
{

}

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
