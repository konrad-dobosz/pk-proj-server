#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QtSql>

class DbHandler
{
public:
    DbHandler();
    bool openDatabase();
    bool closeDatabase();
    bool authenticateUser(const QString& username, const QString& password);

    QSqlDatabase db;
};

#endif // DBHANDLER_H
