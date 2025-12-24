#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include "registerdevicewindow.h"
#include "ui_registerdevicewindow.h"
#include "Router.h"

RegisterDeviceWindow::RegisterDeviceWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegisterDeviceWindow) {
    ui->setupUi(this);
    routerListTable();
}
RegisterDeviceWindow::~RegisterDeviceWindow() {
    delete ui;
}


void RegisterDeviceWindow::on_startPushButton_clicked() {
    enum Column { IpColumn, CommuColumn };
    QTableWidgetItem* selectedItem = ui->routerListTable->currentItem();
    if(!selectedItem) {
        QMessageBox::warning(this, "실패", "장비를 선택해주세요  ");
        return;
    }
    QString ip = ui->routerListTable->item(selectedItem->row(), IpColumn)->text();
    QString community = ui->routerListTable->item(selectedItem->row(), CommuColumn)->text();
    Router* router = new Router(ip, community);
    Router::routerPtr = router;

    emit startThreadRequested();
    this->deleteLater();
}






void RegisterDeviceWindow::on_registPushButton_clicked() {
    QString ipAddress = ui->registIPAddress->text().trimmed();
    QString community = ui->registCommunity->text().trimmed();

    QSqlQuery query;
    query.prepare("INSERT INTO Router_List (ipAddress, community) VALUES (:ip, :commu)");
    query.bindValue(":ip", ipAddress);
    query.bindValue(":commu", community);

    if(query.exec()) {
        QMessageBox::information(this, "등록 완료", "라우터가 등록되었습니다.");
        routerListTable();
    }
    else {
        if(query.lastError().nativeErrorCode() == "1062") {
            QMessageBox::warning(this, "등록 실패", "이미 존재하는 IP 주소입니다.");
        } else {
            qDebug() << "Insert Failed:" << query.lastError().text();
        }
    }
    ui->registIPAddress->clear();
    ui->registCommunity->clear();
}





void RegisterDeviceWindow::on_deletePushButton_clicked() {
    QString ipAddress =  ui->registIPAddress->text().trimmed();

    if(ipAddress.isEmpty()) {
        QMessageBox::warning(this, "입력 오류", "IP 주소를 입력해주세요.  ");
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM Router_List WHERE ipAddress = :ip");
    query.bindValue(":ip", ipAddress);

    if (query.exec() && query.numRowsAffected() > 0) {
        QMessageBox::information(this, "성공", "IP가 삭제되었습니다.");
        routerListTable();
        ui->registIPAddress->clear();
    } else {
        QMessageBox::warning(this, "오류", "해당 IP가 존재하지 않습니다.");
    }
}





void RegisterDeviceWindow::routerListTable() {
    enum Column { IpColumn, CommuColumn };
    ui->routerListTable->setRowCount(0);

    QSqlQuery query("SELECT ipAddress, community FROM Router_List");

    int ip = query.record().indexOf("ipAddress");
    int community = query.record().indexOf("community");

    while(query.next()) {
        int row = ui->routerListTable->rowCount();
        ui->routerListTable->insertRow(row);
        ui->routerListTable->setItem(row, IpColumn, new QTableWidgetItem(query.value(ip).toString()));
        ui->routerListTable->setItem(row, CommuColumn, new QTableWidgetItem(query.value(community).toString()));
    }
}










