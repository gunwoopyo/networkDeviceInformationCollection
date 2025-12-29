#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <cstdlib>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    setenv("QT_QPA_PLATFORM", "xcb", 1);
    QApplication a(argc, argv);
    QSqlDatabase DB = QSqlDatabase::addDatabase("QMYSQL");
    DB.setHostName("localhost");
    DB.setDatabaseName("network_db");
    DB.setUserName("gunwoopyo");
    DB.setPassword("rjsdn2939");
    DB.setPort(3306);
    DB.open();

    if (!DB.open()) {
        qDebug() << "Database connection failed!";
        qDebug() << "Error:" << DB.lastError().text();
    } else {
        qDebug() << "Database connected successfully!";
    }

    init_snmp("snmpApp");




    MainWindow w;
    w.show();
    return a.exec();
}
