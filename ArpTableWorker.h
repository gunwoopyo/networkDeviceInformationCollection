#ifndef ARPTABLEWORKER_H
#define ARPTABLEWORKER_H
#include <QObject>
class ArpTable;
class ArpTableWorker : public QObject {
    Q_OBJECT
public:
    explicit ArpTableWorker(QObject* parent = nullptr)
        : QObject(parent) { }

public slots:
    void arpTableProcess();

signals:
    void arpTableProgress(ArpTable* table);
    void finished();
};


#endif // ARPTABLEWORKER_H
