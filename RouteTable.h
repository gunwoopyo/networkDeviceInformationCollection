#ifndef ROUTETABLE_H
#define ROUTETABLE_H

#include <QVector>
#include "RouteTableEntry.h"

class RouteTable {
public:
    QVector<RouteTableEntry> routeTable;

    void fetchRouteTableInfo();
};



#endif // ROUTETABLE_H
