#include "ui_arptablewindow.h"
#include "arptablewindow.h"

#include "ArpTableWorker.h"
#include "ArpTable.h"
#include "Router.h"


ArpTableWindow::~ArpTableWindow() {
    delete ui;
}

ArpTableWindow::ArpTableWindow(QWidget *parent) : QMainWindow(parent)
    , ui(new Ui::ArpTableWindow) {
    ui->setupUi(this);

    arpTableWorker = new ArpTableWorker();
    arpTableThread = new QThread();
    arpTableWorker->moveToThread(arpTableThread);
    arpTableThread->start();
    QObject::connect(arpTableThread, &QThread::started, arpTableWorker, &ArpTableWorker::arpTableProcess);
    QObject::connect(arpTableWorker, &ArpTableWorker::arpTableProgress, this, &ArpTableWindow::showArpTable);
    QObject::connect(arpTableWorker, &ArpTableWorker::finished, arpTableThread, &QThread::quit);
    QObject::connect(arpTableThread, &QThread::finished, arpTableWorker, &QObject::deleteLater);
    QObject::connect(arpTableThread, &QThread::finished, arpTableThread, &QObject::deleteLater);
}

// 전체 조회
void ArpTableWindow::on_searchTotalPushButton_clicked() {
    arpTableWorker = new ArpTableWorker();
    arpTableThread = new QThread();
    arpTableWorker->moveToThread(arpTableThread);
    arpTableThread->start();
    QObject::connect(arpTableThread, &QThread::started, arpTableWorker, &ArpTableWorker::arpTableProcess);
    QObject::connect(arpTableWorker, &ArpTableWorker::arpTableProgress, this, &ArpTableWindow::showArpTable);
    QObject::connect(arpTableWorker, &ArpTableWorker::finished, arpTableThread, &QThread::quit);
    QObject::connect(arpTableThread, &QThread::finished, arpTableWorker, &QObject::deleteLater);
    QObject::connect(arpTableThread, &QThread::finished, arpTableThread, &QObject::deleteLater);
}

// 조회
void ArpTableWindow::on_searchPushButton_clicked() {
    arpTableWorker = new ArpTableWorker();
    arpTableThread = new QThread();
    arpTableWorker->moveToThread(arpTableThread);
    arpTableThread->start();
    QObject::connect(arpTableThread, &QThread::started, arpTableWorker, &ArpTableWorker::arpTableProcess);
    QObject::connect(arpTableWorker, &ArpTableWorker::arpTableProgress, this, &ArpTableWindow::showArpTable);
    QObject::connect(arpTableWorker, &ArpTableWorker::finished, arpTableThread, &QThread::quit);
    QObject::connect(arpTableThread, &QThread::finished, arpTableWorker, &QObject::deleteLater);
    QObject::connect(arpTableThread, &QThread::finished, arpTableThread, &QObject::deleteLater);
}

// ArpTable
void ArpTableWindow::showArpTable(ArpTable* table) {
    enum Column { ifIndexColumn, ipAddressColumn, macColumn, typeColumn };
    ui->arpTable->setRowCount(0);
    QString portNumberText = ui->portNumberComboBox->currentText();



    for(ArpTableEntry& entry : table->arpTable) {
        QString index = QString::number(entry.ifIndex);

        if (ui->portNumberComboBox->findText(index) == -1) {  // 콤보박스에 인터페이스 번호 없으면 추가
            ui->portNumberComboBox->addItem(index);
        }

        if(portNumberText.isEmpty() || portNumberText == index) {
            int row = ui->arpTable->rowCount();
            ui->arpTable->insertRow(row);
            ui->arpTable->setItem(row, ifIndexColumn, new QTableWidgetItem(QString::number(entry.ifIndex)));
            ui->arpTable->setItem(row, ipAddressColumn, new QTableWidgetItem(entry.IPAddress));
            ui->arpTable->setItem(row, macColumn, new QTableWidgetItem(entry.macAddress));
            ui->arpTable->setItem(row, typeColumn, new QTableWidgetItem(QString::number(entry.type)));
        }


        QSqlQuery query;
        query.prepare("INSERT INTO ARP_Table (routerName, portNumber, ipAddress, macAddress, type) "
                      "VALUES (:name, :number, :ip, :mac, :type)");
        query.bindValue(":name", Router::routerPtr->routerName);
        query.bindValue(":number", entry.ifIndex);
        query.bindValue(":ip", entry.IPAddress);
        query.bindValue(":mac", entry.macAddress);
        query.bindValue(":type", entry.type);
        if(!query.exec())
            qDebug() << "Insert Failed:" << query.lastError().text();
    }


    ui->portNumberComboBox->setCurrentIndex(0);
    delete table;
}











