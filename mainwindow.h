#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QThread>
#include "Router.h"
#include "PortWorker.h"
#include "registerdevicewindow.h"
#include "arptablewindow.h"
#include "routingtablewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Port;
class RouterWorker;
class DeviceWorker;

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    RouterWorker* routerWorker = nullptr;
    PortWorker* portWorker = nullptr;
    QThread* routerThread = nullptr;
    QThread* portThread = nullptr;
    Ui::MainWindow *ui;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void startThread();
    void showRouterInfo(Router* routerInfo);
    void showLoadInfo(Router* routerInfo);
    void showPortView(Router* routerInfo);
    void showPortInfo(Port* portInfo);   // 포트 정보 UI에 표시

    QString getStatusText(int status, QString text);
    QString formatBps(double bps);
};
#endif // MAINWINDOW_H







