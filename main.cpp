#include "mainwindow.h"
#include "schetchik.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QSqlQuery>

static bool createConnection() {
    QSqlDatabase db= QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("schet");
    if (!db.open()) {
        qDebug()<<"Cannot open database:"<<db.lastError();
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (!createConnection()){
        return 100;
    }

    MainWindow w;
    w.show();
    if (!w.load()){
        return 101;
    }
    return a.exec();
}
