#ifndef ARPTABLE_H
#define ARPTABLE_H
#include <QVector>
#include "ArpTableEntry.h"
class ArpTable {
public:
    QVector<ArpTableEntry> arpTable;
    void fetchArpTableInfo();
};

#endif // ARPTABLE_H
