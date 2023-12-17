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

bool DbHandler::addFriend(const QString& username, const QString& friendUsername)
{
    QSqlQuery query;
    query.prepare("INSERT INTO friends (user_id, friend_id) "
                  "SELECT u1.id, u2.id "
                  "FROM users u1, users u2 "
                  "WHERE u1.username = :username AND u2.username = :friendUsername");
    query.bindValue(":username", username);
    query.bindValue(":friendUsername", friendUsername);

    return query.exec();
}
