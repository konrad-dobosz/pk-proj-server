#include "dbhandler.h"

DbHandler::DbHandler()
{
}

bool DbHandler::openDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("databese1.sqlite");
    QSqlQuery query;

    query.exec("CREATE TABLE IF NOT EXISTS users (user TEXT, password TEXT)");

    return db.open();
}

bool DbHandler::closeDatabase()
{
    db.close();
    return true;
}

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
