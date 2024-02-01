#ifndef SOCKETLOGIN_H
#define SOCKETLOGIN_H

#include "socketdata.h"

class SocketLogin : public SocketData
{
public:
    SocketLogin();
    SocketLogin(QString& username, QString& password);

    QString getUsername();
    QString getPassword();
    void setUsername(QString &username);
    void setPassword(QString &password);
    virtual SocketDataType type();

private:
    QString username;
    QString password;
};

#endif // SOCKETLOGIN_H
