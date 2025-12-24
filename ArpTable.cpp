#include "ArpTable.h"
#include "RouterWorker.h"

void ArpTable::fetchArpTableInfo() {
    Router* router = Router::routerPtr;
    snmp_session *ss = Router::openSnmpSession(router->routerIP, router->routerCommunity);

    if(!Router::snmpSessionValid(ss)) {
        return;
    }

    oid macOID[] = {1,3,6,1,2,1,4,22,1,2};
    size_t macOIDLen = OID_LENGTH(macOID);
    oid currentMacOID[MAX_OID_LEN];
    size_t currentMacOIDLen = macOIDLen;
    memcpy(currentMacOID, macOID, macOIDLen * sizeof(oid));

    oid typeOID[] = {1,3,6,1,2,1,4,22,1,4};
    size_t typeOIDLen = OID_LENGTH(typeOID);
    oid currentTypeOID[MAX_OID_LEN];
    size_t currentTypeOIDLen = typeOIDLen;
    memcpy(currentTypeOID, typeOID, typeOIDLen * sizeof(oid));

    while(true) {
        netsnmp_pdu* typePDU = snmp_pdu_create(SNMP_MSG_GETNEXT);
        snmp_add_null_var(typePDU, currentTypeOID, currentTypeOIDLen);
        netsnmp_pdu* typeResponse = nullptr;
        snmp_synch_response(ss, typePDU, &typeResponse);

        netsnmp_pdu* macPDU = snmp_pdu_create(SNMP_MSG_GETNEXT);
        snmp_add_null_var(macPDU, currentMacOID, currentMacOIDLen);
        netsnmp_pdu* macResponse = nullptr;
        int status = snmp_synch_response(ss, macPDU, &macResponse);

        if (status != STAT_SUCCESS || macResponse == nullptr || macResponse->errstat != SNMP_ERR_NOERROR) {
            if (macResponse != nullptr) {
                snmp_free_pdu(typeResponse);
                snmp_free_pdu(macResponse);
            }
            break;
        }

        if (snmp_oid_compare(macOID, macOIDLen, macResponse->variables->name, macOIDLen) != 0) {
            snmp_free_pdu(typeResponse);
            snmp_free_pdu(macResponse);
            break;
        }

        QStringList macParts;
        if(macResponse->variables->val_len == 6) {
            if (macResponse->variables && macResponse->variables->val.string) {
                for (int i = 0; i < 6; i++) {
                    macParts << QString::asprintf("%02X", (unsigned char)macResponse->variables->val.string[i]);
                }
            }
        }

        ArpTableEntry portEntry;
        portEntry.IPAddress = Router::snmpIpToName(macResponse->variables);
        portEntry.ifIndex = macResponse->variables->name[macResponse->variables->name_length - 5];
        portEntry.type = *(typeResponse->variables->val.integer);
        portEntry.macAddress = macParts.join(":");
        arpTable.append(portEntry);



        memcpy(currentMacOID, macResponse->variables->name, macResponse->variables->name_length * sizeof(oid));
        currentMacOIDLen = macResponse->variables->name_length;

        memcpy(currentTypeOID, typeResponse->variables->name, typeResponse->variables->name_length * sizeof(oid));
        currentTypeOIDLen = typeResponse->variables->name_length;

        snmp_free_pdu(typeResponse);
        snmp_free_pdu(macResponse);
    }

    snmp_close(ss);
    SOCK_CLEANUP;
}






