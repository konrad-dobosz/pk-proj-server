#ifndef SOCKETMESSAGE_H
#define SOCKETMESSAGE_H

#include "qhostaddress.h"
#include "socketdata.h"

class SocketMessage : public SocketData
{
public:
    SocketMessage();
    SocketMessage(QHostAddress ip, QString message, QString username = "Username");

    QHostAddress getIpAddress();
    QString getMessage();
    QString getUsername();

    virtual SocketDataType type() override;

    virtual QDataStream& readStream(QDataStream &ds) override;
    virtual QDataStream& writeStream(QDataStream &ds) override;

private:
    QString _username;
    QString _message;
    QHostAddress _ip;
};

#endif // SOCKETMESSAGE_H
