#ifndef SOCKETMESSAGE_H
#define SOCKETMESSAGE_H

#include "qdatetime.h"
#include "socketdata.h"

class SocketMessage : public SocketData
{
public:
    SocketMessage();
    SocketMessage(QString &message, QString username = "Username");

    QString getMessage();
    QString getUsername();

    virtual SocketDataType type() override;

    virtual QDataStream& readStream(QDataStream &ds) override;
    virtual QDataStream& writeStream(QDataStream &ds) override;

private:
    QString _username;
    QString _message;
    QDateTime _dateTime;
};

#endif // SOCKETMESSAGE_H
