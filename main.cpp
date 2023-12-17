#include "mainwindow.h"
#include "dbhandler.h"
#include "socketservice.h"
#include <QDebug>
#include <QApplication>

bool testUserAuthentication(DbHandler& dbHandler) {
    if (dbHandler.openDatabase("db-test")) {
        QSqlQuery createTableQuery;
        createTableQuery.exec("CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)");

        QSqlQuery insertQuery;
        insertQuery.exec("INSERT INTO users (username, password) VALUES ('user', '123')");

        bool isAuthenticated = dbHandler.authenticateUser("user", "123");

        QSqlQuery dropTableQuery;
        dropTableQuery.exec("DROP TABLE users");

        dbHandler.closeDatabase();

        return isAuthenticated;
    } else {
        return false;
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    SocketService socketService = SocketService();
    DbHandler dbHandler = DbHandler();

    if (testUserAuthentication(dbHandler)) {
        qDebug() << "User Authentication - PASS";
    } else {
        qDebug() << "User authentication - FAIL";
    }

    MainWindow w;
    w.show();

    return a.exec();
}
