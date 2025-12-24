#ifndef PORTWORKER_H
#define PORTWORKER_H
#include <QObject>
#include <QTimer>
class Port;
class Router;
class PortWorker : public QObject {
    Q_OBJECT
private:
    bool secondRead = false;
    bool thirdRead = false;
public:
    QTimer* timer;
    explicit PortWorker( QObject* parent = nullptr)
        : QObject(parent) {
        timer = new QTimer(this);
    }
public slots:
    void portProcess();

    void portTimerStop() {
        timer->stop();
    }
signals:
    void loadInfoProgress(Router* router);
    void portInfoProgress(Port* port);
    void portViewProgress(Router* router);
};
#endif
