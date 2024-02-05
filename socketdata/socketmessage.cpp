#include "socketmessage.h"

SocketMessage::SocketMessage () {}
SocketMessage::SocketMessage (QHostAddress ip, QString message, QString username)
    : _username(username), _message(message), _ip(ip) {}

SocketDataType SocketMessage::type() {
    return SocketDataType::message;
}

QHostAddress SocketMessage::getIpAddress() { return _ip; }
QString SocketMessage::getMessage() { return _message; }
QString SocketMessage::getUsername() { return _username; }

QDataStream& SocketMessage::readStream(QDataStream &ds) {
    ds >> _ip;
    ds >> _message;
    ds >> _username;
    return ds;
}

QDataStream& SocketMessage::writeStream(QDataStream &ds) {
    ds << _ip;
    ds << _message;
    ds << _username;
    return ds;
}
