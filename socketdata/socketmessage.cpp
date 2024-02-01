#include "socketmessage.h"

QDataStream &operator<< (QDataStream &ds, SocketMessage &data) {
    return ds << data.getMessage();
}

QDataStream &operator>> (QDataStream &ds, SocketMessage &data) {
    QString msg;
    ds >> msg;

    if (ds.status() == QDataStream::Ok) {
        data.setMessage(msg);
    }

    return ds;
}

SocketMessage::SocketMessage () {}

SocketDataType SocketMessage::type() {
    return SocketDataType::message;
}

QString SocketMessage::getMessage() {
    return message;
}

void SocketMessage::setMessage(QString &msg) {
    this->message = msg;
}
