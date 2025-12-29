#ifndef ROUTER_H
#define ROUTER_H
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include "Port.h"

class Router {
public:
    explicit Router(const QString &routerIPAddress, const QString &community)
        : routerIP(routerIPAddress), routerCommunity(community) { }

    static Router* routerPtr;
    QVector<Port> ports;

    QString routerName = "";
    QString routerIP = "";
    QString routerCommunity = "";
    quint32 cpu = 0;
    quint32 runningTime = 0;
    double memory = 0.0;

    void createPort();
    void fetchRouterInfo();
    static QString getSnmpMacAddress(netsnmp_session* ss, const oid* oidArr, size_t oidLen);
    static QString getSnmpString(netsnmp_session* ss, const oid* oidArr, size_t oidLen);
    static QString snmpIpToVal(netsnmp_variable_list* variables);
    static QString snmpIpToName(netsnmp_variable_list* variables);
    static quint32 getSnmpInteger(netsnmp_session* ss, const oid* oidArr, size_t oidLen);
    static snmp_session* openSnmpSession(QString ip, QString community);
    static bool snmpSessionValid(netsnmp_session *ss);
    static void saveErrorLog(const QString& type, const QString& msg, const QString& oid);


};


#endif // ROUTER_H
