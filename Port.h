#ifndef PORT_H
#define PORT_H
#include "Traffic.h"
class Port {
public:
    int ifIndex = 0;
    int portAdminStatus = 0;
    int portOperStatus = 0;
    QString portName = "";
    QString macAddress = "";

    QVector<Traffic> trafficBuffer;

    void fetchPortInfo();
    void calculateBPSPPS();
    void calculateLoadStatus();
};

#endif // PORT_H











