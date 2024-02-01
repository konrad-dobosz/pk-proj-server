#include "mainwindow.h"
#include "dbhandler.h"
#include "socketservice.h"
#include <QDebug>
#include <QApplication>

bool testUserAuthentication(DbHandler& dbHandler) {
    if (dbHandler.openDatabase("db")) {
        QSqlQuery createTableQuery;
        createTableQuery.exec("CREATE TABLE IF NOT EXISTS users (id INT PRIMARY KEY, username TEXT, password TEXT)");

        QSqlQuery insertQuery;
        insertQuery.exec("INSERT INTO users (username, password) VALUES ('user', '123')");

        bool isAuthenticated = dbHandler.authenticateUser("user", "123");

        //QSqlQuery dropTableQuery;
        //dropTableQuery.exec("DROP TABLE users");

        dbHandler.closeDatabase();

        return isAuthenticated;
    } else {
        return false;
    }
}

bool testFriendsAuthentication(DbHandler& dbHandler) {
    if (dbHandler.openDatabase("db-test")) {
        QSqlQuery createTableQuery;
        createTableQuery.exec("CREATE TABLE IF NOT EXISTS users (id INT PRIMARY KEY, username TEXT, password TEXT)");

        QSqlQuery createTableQueryFriends;
        createTableQueryFriends.exec(
            "CREATE TABLE IF NOT EXISTS friends"
            "(user_id INTEGER, friend_id INTEGER, FOREIGN KEY(user_id)"
            "REFERENCES users(id), FOREIGN KEY(friend_id) REFERENCES users(id))");

        QSqlQuery insertQuery;
        insertQuery.exec("INSERT INTO users (username, password) VALUES ('user', '123')");
        insertQuery.exec("INSERT INTO users (username, password) VALUES ('friend', '456')");


        bool isAuthenticated = dbHandler.authenticateUser("user", "123");

        //QSqlQuery dropTableQuery;
        //dropTableQuery.exec("DROP TABLE users");

        dbHandler.closeDatabase();

        if (isAuthenticated && dbHandler.addFriend("user", "friend")) {
            return true;
        } else {
            return false;
        }

    } else {
        return false;
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    SocketService socketService;
    DbHandler dbHandler;

    if (testUserAuthentication(dbHandler)) {
        qDebug() << "User Authentication - PASS";
    } else {
        qDebug() << "User authentication - FAIL";
    }

    if (testFriendsAuthentication(dbHandler)) {
        qDebug() << "Fiend Authentication - PASS";
    } else {
        qDebug() << "Fiend authentication - FAIL";
    }

    MainWindow w;
    w.show();

    return a.exec();
}
