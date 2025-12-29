#include "RouterWorker.h"

void RouterWorker::routerProcess() {
    Router::routerPtr->createPort(); //port, portName, ifIndex
    emit portThreadStart();

    Router::routerPtr->fetchRouterInfo(); // routerName, cpu, memory, time
    emit routerProgress(Router::routerPtr);
    emit finished();
}





