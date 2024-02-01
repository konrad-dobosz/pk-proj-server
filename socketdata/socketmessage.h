#ifndef SOCKETMESSAGE_H
#define SOCKETMESSAGE_H

#include "qdatetime.h"
#include "socketdata.h"

class SocketMessage : public SocketData
{
public:
    SocketMessage();

    virtual SocketDataType type();

    void setMessage(QString &msg);
    QString getMessage();

private:
    QString username;
    QString message;
    QDateTime dateTime;
};

#endif // SOCKETMESSAGE_H
