#ifndef ROUTETABLEENTRY_H
#define ROUTETABLEENTRY_H
#include <QString>

class RouteTableEntry {
public:
    int ifIndex = 0;
    QString destIPAddress = "";
    QString subnetMask = "";
    QString nextHop = "";
};


#endif // ROUTETABLEENTRY_H


