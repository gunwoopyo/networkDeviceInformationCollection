#ifndef ROUTETABLEWORKER_H
#define ROUTETABLEWORKER_H
#include <QObject>

class RouteTable;

class RouteTableWorker : public QObject {
    Q_OBJECT

public:
    explicit RouteTableWorker( QObject* parent = nullptr)
        : QObject(parent)  { }

public slots:
    void routeTableProcess();

signals:
    void routeTableProgress(RouteTable* table);
    void finished();
};




#endif // ROUTETABLEWORKER_H
