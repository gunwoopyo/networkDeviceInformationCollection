#include "RouteTable.h"
#include "RouteTableWorker.h"

class RouteTable;

void RouteTableWorker::routeTableProcess() {
    RouteTable* routeTable = new RouteTable();
    routeTable->fetchRouteTableInfo();


    emit routeTableProgress(routeTable);
    emit finished();

}
