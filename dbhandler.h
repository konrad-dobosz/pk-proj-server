#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QtSql>

class DbHandler {
public:
    bool openDatabase(QString dbName = "db");
    void closeDatabase();
    bool authenticateUser(const QString& username, const QString& password);

private:
    QSqlDatabase db;
};

#endif // DBHANDLER_H
