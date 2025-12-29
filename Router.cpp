#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "RouterWorker.h"
#include "Router.h"

Router* Router::routerPtr = nullptr;













QString Router::getSnmpString(netsnmp_session* session, const oid* oidArr, size_t oidLen) {

    netsnmp_pdu* pdu = snmp_pdu_create(SNMP_MSG_GET);
    snmp_add_null_var(pdu, const_cast<oid*>(oidArr), oidLen);
    netsnmp_pdu* response = nullptr;

    int status = snmp_synch_response(session, pdu, &response);
    if (status != STAT_SUCCESS) {
        fprintf(stderr, "SNMP GET (String) failed due to communication error. Status: %d\n", status);
        snmp_sess_perror("snmp_synch_response failed", session);

        if (response) {
            snmp_free_pdu(response);
        }
        return QString();
    }
    if (!response) {
        fprintf(stderr, "SNMP GET (String) failed: Response PDU is NULL.\n");
        return QString();
    }

    if (response->errstat != SNMP_ERR_NOERROR) {
        fprintf(stderr, "SNMP Agent returned error: %s (Index: %ld)\n",
                snmp_errstring(response->errstat), response->errindex);
        snmp_free_pdu(response);
        return QString();
    }
    if (!response->variables) {
        fprintf(stderr, "SNMP GET (String) failed: Response PDU contains no variables.\n");
        snmp_free_pdu(response);
        return QString();
    }
    if (response->variables->type != ASN_OCTET_STR) {
        fprintf(stderr, "SNMP GET (String) failed: Expected OctetString (0x04), but received type 0x%X\n",
                response->variables->type);
        snmp_free_pdu(response);
        return QString();
    }

    if (!response->variables->val.string || response->variables->val_len == 0) {
        fprintf(stderr, "SNMP GET (String) failed: String pointer is NULL or length is zero.");
        snmp_free_pdu(response);
        return QString();
    }

    QString result = QString::fromUtf8((const char*)response->variables->val.string, response->variables->val_len);

    snmp_free_pdu(response);
    return result;
}



bool Router::snmpSessionValid(netsnmp_session* session) {
    if (session == nullptr) {
        qDebug() << "SNMP session open failed!";
        return false;
    }
    return true;
}


snmp_session* Router::openSnmpSession(QString ip, QString community) {
    snmp_session session;
    snmp_sess_init(&session);

    session.peername = strdup(ip.toStdString().c_str());
    session.version = SNMP_VERSION_2c;
    session.community = (u_char*)strdup(community.toStdString().c_str());
    session.community_len = community.length();

    snmp_session *ss = snmp_open(&session);

    if (!ss) {
        snmp_sess_perror("snmp_open failed", ss);
        return nullptr;
    }
    return ss;
}












QString Router::snmpIpToVal(netsnmp_variable_list* variables) {
    return QString("%1.%2.%3.%4")
    .arg(variables->val.string[variables->val_len - 4])
        .arg(variables->val.string[variables->val_len - 3])
        .arg(variables->val.string[variables->val_len - 2])
        .arg(variables->val.string[variables->val_len - 1]);
}


QString Router::snmpIpToName(netsnmp_variable_list* variables) {
    return QString("%1.%2.%3.%4")
    .arg(variables->name[variables->name_length - 4])
        .arg(variables->name[variables->name_length - 3])
        .arg(variables->name[variables->name_length - 2])
        .arg(variables->name[variables->name_length - 1]);
}


QString Router::getSnmpMacAddress(netsnmp_session* ss, const oid* oidArr, size_t oidLen) {
    netsnmp_pdu* pdu = snmp_pdu_create(SNMP_MSG_GET);
    snmp_add_null_var(pdu, const_cast<oid*>(oidArr), oidLen);

    netsnmp_pdu* response = nullptr;


    if (snmp_synch_response(ss, pdu, &response) != STAT_SUCCESS || !response || response->errstat != SNMP_ERR_NOERROR) {
        if (response) snmp_free_pdu(response);
        return QString();
    }

    netsnmp_variable_list* vars = response->variables;

    QStringList macParts;

    if (vars->val.string && vars->val_len == 6) {
        for (int i = 0; i < 6; i++) {
            macParts << QString::asprintf("%02X", (unsigned char)vars->val.string[i]);
        }
    }

    snmp_free_pdu(response);
    return macParts.join(":");
}





quint32 Router::getSnmpInteger(netsnmp_session* ss, const oid* oidArr, size_t oidLen) {
    netsnmp_pdu* pdu = snmp_pdu_create(SNMP_MSG_GET);
    snmp_add_null_var(pdu, const_cast<oid*>(oidArr), oidLen);
    netsnmp_pdu* response = nullptr;

    int status = snmp_synch_response(ss, pdu, &response);

    if (status != STAT_SUCCESS) {
        fprintf(stderr, "SNMP GET failed. Status: %d\n", status);  // 3번째 인자는 두번 째 인수에 대입할 변수 값
        snmp_sess_perror("snmp_synch_response failed", ss);
        if(response) {
            snmp_free_pdu(response);
        }
        return 0;
    }
    if (response->errstat != SNMP_ERR_NOERROR) {
        fprintf(stderr, "SNMP Agent returned error: %s\n", snmp_errstring(response->errstat));
        snmp_free_pdu(response);
        return 0;
    }
    if (response->errindex != 0) {
        fprintf(stderr, "  Error Index: %ld\n", response->errindex);
        snmp_free_pdu(response);
        return 0;
    }
    if (!response->variables) {
        fprintf(stderr, "SNMP GET failed: Response PDU contains no variables.\n");
        snmp_free_pdu(response);
        return 0;
    }
    if (!response->variables->val.integer) {
        fprintf(stderr, "SNMP GET failed: Integer value pointer is NULL.\n");
        snmp_free_pdu(response);
        return 0;
    }
    if (response->variables->type != ASN_INTEGER && response->variables->type != ASN_COUNTER &&
        response->variables->type != ASN_GAUGE && response->variables->type != ASN_TIMETICKS) {

        fprintf(stderr, "SNMP GET failed: Expected Integer type, but received type 0x%X\n", response->variables->type);
        snmp_free_pdu(response);
        return 0;
    }

    quint32 value = (quint32)*(response->variables->val.integer);
    snmp_free_pdu(response);
    return value;
}











void Router::fetchRouterInfo() {
    snmp_session *session = openSnmpSession(routerIP, routerCommunity);

    if(!snmpSessionValid(session))
        return;

    oid sysNameOID[] = {1,3,6,1,2,1,1,5,0};
    oid timeOID[] = {1,3,6,1,2,1,1,3,0};
    oid cpuOID[] = {1,3,6,1,4,1,9,2,1,58,0};
    oid usedMemoryOID[] = {1,3,6,1,4,1,9,9,48,1,1,1,5,1};
    oid freeMemoryOID[] = {1,3,6,1,4,1,9,9,48,1,1,1,6,1};

    routerName = getSnmpString(session, sysNameOID, OID_LENGTH(sysNameOID));
    runningTime = getSnmpInteger(session, timeOID, OID_LENGTH(timeOID));
    cpu = getSnmpInteger(session, cpuOID, OID_LENGTH(cpuOID));
    quint32 usedMemory = getSnmpInteger(session, usedMemoryOID, OID_LENGTH(usedMemoryOID));
    quint32 freeMemory = getSnmpInteger(session, freeMemoryOID, OID_LENGTH(freeMemoryOID));

    if (!(usedMemory + freeMemory) == 0)
        memory = (double)(usedMemory * 100.0) / (double)(usedMemory + freeMemory);

    snmp_close(session);
    SOCK_CLEANUP;
}










void Router::createPort() {
    snmp_session *session = openSnmpSession(routerIP, routerCommunity);

    if(!snmpSessionValid(session)) {
        return;
    }

    oid ifDescrOID[] = {1,3,6,1,2,1,2,2,1,2};
    size_t ifDescrOIDLength = OID_LENGTH(ifDescrOID);
    oid currentOID[MAX_OID_LEN];
    size_t currentOIDLength = ifDescrOIDLength;

    memcpy(currentOID, ifDescrOID, ifDescrOIDLength * sizeof(oid));

    while(true) {
        netsnmp_pdu* pdu = snmp_pdu_create(SNMP_MSG_GETNEXT);
        snmp_add_null_var(pdu, currentOID, currentOIDLength);
        netsnmp_pdu* response = nullptr;

        int status = snmp_synch_response(session, pdu, &response);

        if (status != STAT_SUCCESS || !response || response->errstat != SNMP_ERR_NOERROR) {
            if (response != nullptr) {
                snmp_free_pdu(response);
            }
            break;
        }

        netsnmp_variable_list* vars = response->variables;

        if (snmp_oid_compare(ifDescrOID, ifDescrOIDLength, vars->name, ifDescrOIDLength) != 0) {
            snmp_free_pdu(response);
            break;
        }

        Port port;
        port.portName = QString::fromUtf8((char*)vars->val.string, vars->val_len);
        port.ifIndex = vars->name[vars->name_length - 1];
        ports.append(port);

        memcpy(currentOID, vars->name, sizeof(oid)*vars->name_length);
        currentOIDLength = vars->name_length;

        snmp_free_pdu(response);
    }

    snmp_close(session);
    SOCK_CLEANUP;
}








