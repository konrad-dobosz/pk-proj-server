#ifndef SOCKETDATA_H
#define SOCKETDATA_H

#include <QObject>

enum class SocketDataType: quint8 {
    loginRequest,
    loginResponse,
    message
};

Q_DECLARE_METATYPE(SocketDataType);

class SocketData
{
public:
    SocketData();

    virtual SocketDataType type() = 0;
};

QDataStream &operator<< (QDataStream &ds, SocketData &data);
QDataStream &operator>> (QDataStream &ds, SocketData &data);

#endif // SOCKETDATA_H
