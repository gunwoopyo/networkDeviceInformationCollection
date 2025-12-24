#ifndef ROUTINGTABLEWINDOW_H
#define ROUTINGTABLEWINDOW_H
#include <QMainWindow>
#include <QThread>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

class RouteTableWorker;
class RouteTable;

namespace Ui {
class RoutingTableWindow;
}

class RoutingTableWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit RoutingTableWindow(QWidget *parent = nullptr);
    ~RoutingTableWindow();

private:
    RouteTableWorker* routeTableWorker = nullptr;
    QThread* routeTableThread = nullptr;
    Ui::RoutingTableWindow *ui;

public slots:
    void showRouteTableInfo(RouteTable* table);
};

#endif // ROUTINGTABLEWINDOW_H
