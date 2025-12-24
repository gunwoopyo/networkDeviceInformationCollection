#ifndef REGISTERDEVICEWINDOW_H
#define REGISTERDEVICEWINDOW_H
#include <QMainWindow>

namespace Ui {
class RegisterDeviceWindow;
}

class RegisterDeviceWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit RegisterDeviceWindow(QWidget *parent = nullptr);
    ~RegisterDeviceWindow();

public slots:
    void on_startPushButton_clicked();
    void on_deletePushButton_clicked();
    void on_registPushButton_clicked();
    void routerListTable();

private:
    Ui::RegisterDeviceWindow *ui;

signals:
    void startThreadRequested();
};

#endif // REGISTERDEVICEWINDOW_H
