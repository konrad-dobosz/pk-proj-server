#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbhandler.cpp"
#include <QDebug>
#include <QApplication>


bool testUserAuthentication(DbHandler& dbHandler, const QString& username, const QString& password) {
    // Opening the database
    if (dbHandler.openDatabase()) {
        qDebug() << "Database opened successfully.";

        // Checking if the user with the specified credentials exists
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS users (user TEXT, password TEXT)");
        query.prepare("SELECT * FROM users WHERE user = :user AND password = :password");
        query.bindValue(":user", username);
        query.bindValue(":password", password);

        if (query.exec() && query.next()) {
            qDebug() << "User authentication successful.";
            dbHandler.closeDatabase();
            return true;
        } else {
            qDebug() << "User authentication failed.";
            dbHandler.closeDatabase();
            return false;
        }
    } else {
        qDebug() << "Failed to open database. Error:" << dbHandler.db.lastError().text();
        return false;
    }
}


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Creating a DbHandler object
    DbHandler dbHandler;

    // Opening the database
    if (dbHandler.openDatabase()) {
        qDebug() << "Database opened successfully.";

        // Creating an admin user if not already exists
        QSqlQuery checkUserQuery("SELECT * FROM users WHERE user = 'admin5'");

        if (checkUserQuery.exec() && checkUserQuery.next()) {
            qDebug() << "Admin user already exists.";
        } else {
            // Adding the admin user with password "admin123"
            QSqlQuery insertQuery;
            insertQuery.prepare("INSERT INTO users (user, password) VALUES ('admin5', 'admin123')");

            if (insertQuery.exec()) {
                qDebug() << "Admin user added successfully.";
            } else {
                qDebug() << "Failed to add admin user. Error:" << insertQuery.lastError().text();
            }
        }

        // Closing the database
        if (dbHandler.closeDatabase()) {
            qDebug() << "Database closed successfully.";
        } else {
            qDebug() << "Failed to close database.";
        }

    } else {
        qDebug() << "Failed to open database. Error:" << dbHandler.db.lastError().text();
    }

    // Testing user authentication
    if (testUserAuthentication(dbHandler, "admin", "admin123")) {
        qDebug() << "User authentication test passed. The user exists.";
    } else {
        qDebug() << "User authentication test failed. The user does not exist or invalid credentials.";
    }

    // Creating and running the main window
    MainWindow w;
    w.show();

    return a.exec();
}
