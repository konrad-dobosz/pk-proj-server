#include "dbhandler.h"

bool DbHandler::openDatabase(QString dbName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName + ".sqlite");

    return db.open();
}

void DbHandler::closeDatabase() { db.close(); }

bool DbHandler::authenticateUser(const QString& username, const QString& password)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    if (query.exec() && query.next()) {
        return true;
    }
    return false;
}
