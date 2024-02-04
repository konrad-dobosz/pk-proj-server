#include "socketdata.h"

QDataStream &operator<< (QDataStream &ds, SocketDataType data) {
    return ds << (quint8)data;
}

QDataStream &operator>> (QDataStream &ds, SocketDataType &data) {
    quint8 val;
    ds >> val;
    if (ds.status() == QDataStream::Ok) {
        data = SocketDataType(val);
    }

    return ds;
}

QDataStream &operator<< (QDataStream &ds, SocketData &data) {
    return data.writeStream(ds);;
}

QDataStream &operator>> (QDataStream &ds, SocketData &data) {
    return data.readStream(ds);;
}

SocketData::SocketData() {}
