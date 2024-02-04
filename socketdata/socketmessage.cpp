#include "socketmessage.h"

SocketMessage::SocketMessage () {}
SocketMessage::SocketMessage (QString &message, QString username) : _message(message), _username(username) {}

SocketDataType SocketMessage::type() {
    return SocketDataType::message;
}

QString SocketMessage::getMessage() { return _message; }
QString SocketMessage::getUsername() { return _username; }


QDataStream& SocketMessage::readStream(QDataStream &ds) {
    ds >> _message;
    ds >> _username;
    return ds;
}

QDataStream& SocketMessage::writeStream(QDataStream &ds) {
    ds << _message;
    ds << _username;
    return ds;
}
