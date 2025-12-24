#include "routingtablewindow.h"
#include "ui_routingtablewindow.h"
#include "RouteTableWorker.h"
#include "RouteTable.h"
#include "Router.h"
RoutingTableWindow::~RoutingTableWindow() {
    delete ui;
}

RoutingTableWindow::RoutingTableWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RoutingTableWindow) {
    ui->setupUi(this);

    routeTableWorker = new RouteTableWorker();
    routeTableThread = new QThread();
    routeTableWorker->moveToThread(routeTableThread);
    routeTableThread->start();
    QObject::connect(routeTableThread, &QThread::started, routeTableWorker, &RouteTableWorker::routeTableProcess);
    QObject::connect(routeTableWorker, &RouteTableWorker::routeTableProgress, this, &RoutingTableWindow::showRouteTableInfo);
    QObject::connect(routeTableWorker, &RouteTableWorker::finished, routeTableThread, &QThread::quit);
    QObject::connect(routeTableThread, &QThread::finished, routeTableWorker, &QObject::deleteLater);
    QObject::connect(routeTableThread, &QThread::finished, routeTableThread, &QObject::deleteLater);
}


void RoutingTableWindow::showRouteTableInfo(RouteTable* table) {
    enum Column { DestIPAddColumn, SubnetColumn, IfIndexColumn, NextHopColumn };
    ui->routingTable->setRowCount(0);

    for(RouteTableEntry& entry : table->routeTable) {
        int row = ui->routingTable->rowCount();
        ui->routingTable->insertRow(row);
        ui->routingTable->setItem(row, DestIPAddColumn, new QTableWidgetItem(entry.destIPAddress));
        ui->routingTable->setItem(row, SubnetColumn,    new QTableWidgetItem(entry.subnetMask));
        ui->routingTable->setItem(row, IfIndexColumn,   new QTableWidgetItem(QString::number(entry.ifIndex)));
        ui->routingTable->setItem(row, NextHopColumn,   new QTableWidgetItem(entry.nextHop));

        QSqlQuery query;
        query.prepare("INSERT INTO Route_Table (routerName, destIPAddress, subnetMask, port_number, nextHop) "
                      "VALUES (:name, :ip, :subnet, :number, :nextHop)");
        query.bindValue(":name",    Router::routerPtr->routerName);
        query.bindValue(":ip",      entry.destIPAddress);
        query.bindValue(":subnet",  entry.subnetMask);
        query.bindValue(":number",  entry.ifIndex);
        query.bindValue(":nextHop", entry.nextHop);

        if(!query.exec()) qDebug() << "Insert Failed:" << query.lastError().text();
    }
}










