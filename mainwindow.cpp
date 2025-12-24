#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "RouterWorker.h"
#include "DeviceInfoWorker.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // 등록 창
    RegisterDeviceWindow* registerDeviceWindow = new RegisterDeviceWindow(this);
    registerDeviceWindow->setWindowModality(Qt::WindowModal);
    QSize dlgSize = registerDeviceWindow->size();
    QPoint center = this->geometry().center();
    QPoint topLeft = center - QPoint(dlgSize.width()/2, dlgSize.height()/2);
    registerDeviceWindow->move(topLeft);
    registerDeviceWindow->show();
    connect(registerDeviceWindow, &RegisterDeviceWindow::startThreadRequested, this, &MainWindow::startMyThread);

    // arp 테이블
    connect(ui->arpTablePushButton, &QPushButton::clicked, this, [this]() {
        ArpTableWindow* arpTableWindow = new ArpTableWindow(this);
        arpTableWindow->setWindowModality(Qt::WindowModal);
        QSize dlgSize = arpTableWindow->size();
        QPoint center = this->geometry().center();
        QPoint topLeft = center - QPoint(dlgSize.width()/2, dlgSize.height()/2);
        arpTableWindow->move(topLeft);
        arpTableWindow->show();
    });

    // route 테이블
    connect(ui->routeTablePushButton, &QPushButton::clicked, this, [this]() {
        RoutingTableWindow* routeTableWindow = new RoutingTableWindow(this);
        routeTableWindow->setWindowModality(Qt::WindowModal);
        QSize dlgSize = routeTableWindow->size();
        QPoint center = this->geometry().center();
        QPoint topLeft = center - QPoint(dlgSize.width()/2, dlgSize.height()/2);
        routeTableWindow->move(topLeft);
        routeTableWindow->show();
    });
}




MainWindow::~MainWindow() {
    portWorker->portTimerStop(); // 타이머 멈춤
    portThread->quit();
    portThread->wait();
    delete portWorker;
    delete portThread;

    delete Router::routerPtr;
    delete ui;
}




void MainWindow::startMyThread() {
    routerWorker = new RouterWorker();
    routerThread = new QThread;
    routerWorker->moveToThread(routerThread);
    routerThread->start();

    QObject::connect(routerThread, &QThread::started, routerWorker, &RouterWorker::routerProcess);
    QObject::connect(routerWorker, &RouterWorker::routerProgress, this, &MainWindow::showRouterInfo);
    QObject::connect(routerWorker, &RouterWorker::finished, routerThread, &QThread::quit);
    QObject::connect(routerThread, &QThread::finished, routerWorker, &QObject::deleteLater);
    QObject::connect(routerThread, &QThread::finished, routerThread, &QObject::deleteLater);


    portWorker = new PortWorker();
    portThread = new QThread();
    portWorker->moveToThread(portThread);
    QObject::connect(portThread, &QThread::started, portWorker, &PortWorker::portProcess);
    QObject::connect(portWorker, &PortWorker::portViewProgress, this, &MainWindow::showPortView);
    QObject::connect(portWorker, &PortWorker::portInfoProgress, this, &MainWindow::showPortInfo);
    QObject::connect(portWorker, &PortWorker::loadInfoProgress, this, &MainWindow::showLoadInfo);
    QObject::connect(routerWorker, &RouterWorker::portThreadStart, portThread, [=]() {
        portThread->start();
    });
}




void MainWindow::showPortView(Router* router) {
    for(int i = 1; i <= router->ports.size(); i++) {
        QFrame* frame = this->findChild<QFrame*>(QString("port%1Frame").arg(i));

        if(router->ports[i-1].portOperStatus == 1) {
            frame->setStyleSheet("background-color: green;");
        } else {
            frame->setStyleSheet("background-color: gray;");
        }

        QLabel* label = this->findChild<QLabel*>(QString("port%1Text").arg(i));
        label->setText(router->ports[i-1].portName);
    }
}




// 부하 정보
void MainWindow::showLoadInfo(Router* router) {
    int runningCount = 0, normalCount = 0, warningCount = 0, dangerCount = 0;

    for(Port& port : router->ports) {
        if(port.portOperStatus == 1)
            runningCount++;
        if (port.trafficBuffer.last().loadStatus == "warning")
            warningCount++;
        else if(port.trafficBuffer.last().loadStatus == "danger")
            dangerCount++;
    }

    normalCount = runningCount - (warningCount + dangerCount);

    ui->loadTotalText->setText(QString::number(runningCount));
    ui->loadNormalText->setText(QString::number(normalCount));
    ui->loadWarningText->setText(QString::number(warningCount));
    ui->loadDangerText->setText(QString::number(dangerCount));
}




void MainWindow::showRouterInfo(Router* router) {
    enum Column { NameColumn, IPColumn, CPUColumn, MemoryColumn, TimeColumn };

    int seconds = router->runningTime/100;
    QString timeStr = QString("%1일 %2시간").arg(seconds / 86400).arg((seconds % 86400) / 3600);

    ui->routerTable->setRowCount(1);
    int currentRow = 0;
    ui->routerTable->setItem(currentRow, NameColumn,   new QTableWidgetItem(router->routerName));
    ui->routerTable->setItem(currentRow, IPColumn,     new QTableWidgetItem(router->routerIP));
    ui->routerTable->setItem(currentRow, CPUColumn,    new QTableWidgetItem(QString::number(router->cpu) + "%"));
    ui->routerTable->setItem(currentRow, MemoryColumn, new QTableWidgetItem(QString::number(router->memory, 'f', 1) + "%"));
    ui->routerTable->setItem(currentRow, TimeColumn,   new QTableWidgetItem(timeStr));

    QSqlQuery query;
    query.prepare("INSERT INTO Router_State (router_name, ipAddress, cpu, memory, running_time) "
                  "VALUES (:name, :ip, :cpu, :memory, :time)");
    query.bindValue(":name",   router->routerName);
    query.bindValue(":ip",     router->routerIP);
    query.bindValue(":cpu",    router->cpu);
    query.bindValue(":memory", router->memory);
    query.bindValue(":time",   router->runningTime);

    if(!query.exec()) qDebug() << "Insert Failed:" << query.lastError().text();
}










QString MainWindow::formatBps(double bps) {
    static const char* units[] = {"bps", "Kbps", "Mbps", "Gbps"};
    int unitIndex = 0;

    for ( ; bps >= 1000 && unitIndex < (int)std::size(units) - 1; unitIndex++) {
        bps /= 1000;
    }

    return QString::number(bps, 'f', 1) + units[unitIndex];
}

QString MainWindow::getStatusText(int status, QString text) {
    if (text == "admin") {
        if (status == 1) return "On";
        if (status == 2) return "Off";
        if (status == 3) return "Testing";
    } else {
        if (status == 1) return "Running";
        if (status == 2) return "Not Running";
        if (status == 3) return "테스트 중";
    }
    return "unknown";
}



void MainWindow::showPortInfo(Port* port) {
    enum Column { IndexColumn, NameColumn, AdminColumn, OperColumn, MacColumn,
                  InBPSColumn, OutBPSColumn, InPPSColumn, OutPPSColumn };

    static QMap<QString,int> portRows;
    int row = portRows.value(port->portName, -1);
    if(row == -1) {
        row = ui->interfaceTable->rowCount();
        ui->interfaceTable->insertRow(row);
        portRows[port->portName] = row;
    }
    ui->interfaceTable->setItem(row, IndexColumn, new QTableWidgetItem(QString::number(port->ifIndex)));
    ui->interfaceTable->setItem(row, NameColumn,  new QTableWidgetItem(port->portName));
    ui->interfaceTable->setItem(row, AdminColumn, new QTableWidgetItem(getStatusText(port->portAdminStatus, "admin")));
    ui->interfaceTable->setItem(row, OperColumn,  new QTableWidgetItem(getStatusText(port->portOperStatus,  "oper")));
    ui->interfaceTable->setItem(row, MacColumn,   new QTableWidgetItem(port->macAddress));

    Traffic traffic = port->trafficBuffer.last();
    ui->interfaceTable->setItem(row, InBPSColumn,  new QTableWidgetItem(formatBps(traffic.InBPS)));
    ui->interfaceTable->setItem(row, OutBPSColumn, new QTableWidgetItem(formatBps(traffic.OutBps)));
    ui->interfaceTable->setItem(row, InPPSColumn,  new QTableWidgetItem(QString::number(traffic.InPPS)));
    ui->interfaceTable->setItem(row, OutPPSColumn, new QTableWidgetItem(QString::number(traffic.OutPPS)));

    QSqlQuery query;
    query.prepare("INSERT INTO Router_Port "
                "(router_name, port_number, port_name, admin_status, oper_status, mac_address, in_bps, out_bps) "
                "VALUES (:routerName, :portNumber, :portName, :adminStatus, :operStatus, :macAddress, :inBps, :outBps)");
    query.bindValue(":routerName",  Router::routerPtr->routerName);
    query.bindValue(":portNumber",  port->ifIndex);
    query.bindValue(":portName",    port->portName);
    query.bindValue(":adminStatus", port->portAdminStatus);
    query.bindValue(":operStatus",  port->portOperStatus);
    query.bindValue(":macAddress",  port->macAddress);
    query.bindValue(":inBps",       port->trafficBuffer.last().InBPS);
    query.bindValue(":outBps",      port->trafficBuffer.last().OutBps);

    if(!query.exec()) qDebug() << "Insert Failed:" << query.lastError().text();
}








