#ifndef ROUTERWORKER_H
#define ROUTERWORKER_H
#include <QObject>
#include "Router.h"

class Router;

class RouterWorker : public QObject {
    Q_OBJECT

public:
    explicit RouterWorker(QObject* parent = nullptr)
        : QObject(parent) { }

public slots:
    void routerProcess();

signals:
    void routerProgress(Router* router);
    void portThreadStart();
    void finished();
};


#endif // ROUTERWORKER_H
