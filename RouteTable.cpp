#include "RouteTable.h"
#include "RouterWorker.h"

void RouteTable::fetchRouteTableInfo() {
    Router* router = Router::routerPtr;
    snmp_session *ss = Router::openSnmpSession(router->routerIP, router->routerCommunity);

    if(!Router::snmpSessionValid(ss))
        return;

    oid destOID [] = {1,3,6,1,2,1,4,21,1,1};
    size_t destOIDLength = OID_LENGTH(destOID);
    oid currentDestOID[MAX_OID_LEN];
    size_t currentDestOIDLength = destOIDLength;
    memcpy(currentDestOID, destOID, destOIDLength * sizeof(oid));

    oid ifIndexOID [] = {1,3,6,1,2,1,4,21,1,2};
    size_t ifIndexOIDLength = OID_LENGTH(ifIndexOID);
    oid currentIfIndexOID[MAX_OID_LEN];
    size_t currentIfIndexOIDLength = ifIndexOIDLength;
    memcpy(currentIfIndexOID, ifIndexOID, ifIndexOIDLength * sizeof(oid));

    oid nextHopOID [] = {1,3,6,1,2,1,4,21,1,7};
    size_t nextHopOIDLength = OID_LENGTH(nextHopOID);
    oid currentNextHopOID[MAX_OID_LEN];
    size_t currentNextHopOIDLength = nextHopOIDLength;
    memcpy(currentNextHopOID, nextHopOID, nextHopOIDLength * sizeof(oid));

    oid subnetOID [] = {1,3,6,1,2,1,4,21,1,11};
    size_t subnetOIDLength = OID_LENGTH(subnetOID);
    oid currentSubnetOID[MAX_OID_LEN];
    size_t currentSubnetOIDLength = subnetOIDLength;
    memcpy(currentSubnetOID, subnetOID, subnetOIDLength * sizeof(oid));




    while(true) {
        netsnmp_pdu* ifIndexPDU = snmp_pdu_create(SNMP_MSG_GETNEXT);
        snmp_add_null_var(ifIndexPDU, currentIfIndexOID, currentIfIndexOIDLength);
        netsnmp_pdu* ifIndexResponse = nullptr;
        snmp_synch_response(ss, ifIndexPDU, &ifIndexResponse);

        if (snmp_oid_compare(ifIndexOID, ifIndexOIDLength, ifIndexResponse->variables->name, ifIndexOIDLength) != 0) {
            snmp_free_pdu(ifIndexResponse);
            break;
        }

        netsnmp_pdu* subnetPDU = snmp_pdu_create(SNMP_MSG_GETNEXT);
        snmp_add_null_var(subnetPDU, currentSubnetOID, currentSubnetOIDLength);
        netsnmp_pdu* subnetResponse = nullptr;
        snmp_synch_response(ss, subnetPDU, &subnetResponse);

        netsnmp_pdu* destPDU = snmp_pdu_create(SNMP_MSG_GETNEXT);
        snmp_add_null_var(destPDU, currentDestOID, currentDestOIDLength);
        netsnmp_pdu* destResponse = nullptr;
        snmp_synch_response(ss, destPDU, &destResponse);

        netsnmp_pdu* nextHopPDU = snmp_pdu_create(SNMP_MSG_GETNEXT);
        snmp_add_null_var(nextHopPDU, currentNextHopOID, currentNextHopOIDLength);
        netsnmp_pdu* nextHopResponse = nullptr;
        snmp_synch_response(ss, nextHopPDU, &nextHopResponse);


        RouteTableEntry entry;
        entry.ifIndex = *(ifIndexResponse->variables->val.integer);
        entry.subnetMask = Router::snmpIpToVal(subnetResponse->variables);
        entry.destIPAddress = Router::snmpIpToVal(destResponse->variables);
        entry.nextHop = Router::snmpIpToVal(nextHopResponse->variables);

        routeTable.append(entry);


        memcpy(currentIfIndexOID, ifIndexResponse->variables->name, sizeof(oid)*ifIndexResponse->variables->name_length);
        currentIfIndexOIDLength = ifIndexResponse->variables->name_length;

        memcpy(currentSubnetOID, subnetResponse->variables->name, sizeof(oid)*subnetResponse->variables->name_length);
        currentSubnetOIDLength = subnetResponse->variables->name_length;

        memcpy(currentDestOID, destResponse->variables->name, sizeof(oid)*destResponse->variables->name_length);
        currentDestOIDLength = destResponse->variables->name_length;

        memcpy(currentNextHopOID, nextHopResponse->variables->name, sizeof(oid)*nextHopResponse->variables->name_length);
        currentNextHopOIDLength = nextHopResponse->variables->name_length;
    }

    snmp_close(ss);
    SOCK_CLEANUP;

}
