#include "socketmessage.h"

SocketMessage::SocketMessage () {}
SocketMessage::SocketMessage (QString &message) : _message(message) {}

SocketDataType SocketMessage::type() {
    return SocketDataType::message;
}

QDataStream& SocketMessage::readStream(QDataStream &ds) {
    ds >> _message;
    return ds;
}

QDataStream& SocketMessage::writeStream(QDataStream &ds) {
    ds << _message;
    return ds;
}
