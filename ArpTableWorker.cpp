#include "ArpTable.h"
#include "ArpTableWorker.h"

class ArpTable;

void ArpTableWorker::arpTableProcess() {
    ArpTable* arpTable = new ArpTable();
    arpTable->fetchArpTableInfo();

    emit arpTableProgress(arpTable);
    emit finished();
}


