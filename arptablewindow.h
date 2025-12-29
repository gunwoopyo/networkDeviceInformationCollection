#ifndef ARPTABLEWINDOW_H
#define ARPTABLEWINDOW_H
#include <QMainWindow>
#include <QThread>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class ArpTableWorker;
class ArpTable;

namespace Ui {
class ArpTableWindow;
}
class ArpTableWindow : public QMainWindow {
    Q_OBJECT

private:
    ArpTableWorker *arpTableWorker = nullptr;
    QThread *arpTableThread = nullptr;
    Ui::ArpTableWindow *ui;

public:
    explicit ArpTableWindow(QWidget *parent = nullptr);
    ~ArpTableWindow();

public slots:
    void on_searchPushButton_clicked();
    void on_searchTotalPushButton_clicked();
    void showArpTable(ArpTable *port);
};

#endif // ARPTABLEWINDOW_H
