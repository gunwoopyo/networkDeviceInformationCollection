#ifndef ARPTABLEENTRY_H
#define ARPTABLEENTRY_H
#include <QString>
class ArpTableEntry {
public:
    int ifIndex = 0;
    int type = 0;
    QString IPAddress = "";
    QString macAddress = "";
};

#endif // ARPTABLEENTRY_H




