#include "RouterWorker.h"
#include "Port.h"


class Traffic;

void Port::fetchPortInfo() {
    snmp_session* session = Router::openSnmpSession(Router::routerPtr->routerIP, Router::routerPtr->routerCommunity);

    if(!Router::snmpSessionValid(session))
        return;

    oid adminOID[] = {1,3,6,1,2,1,2,2,1,7,(oid)ifIndex};
    oid operOID[] = {1,3,6,1,2,1,2,2,1,8,(oid)ifIndex};
    oid macOID[] = {1,3,6,1,2,1,2,2,1,6,(oid)ifIndex};
    portAdminStatus = Router::getSnmpInteger(session, adminOID, OID_LENGTH(adminOID));
    portOperStatus = Router::getSnmpInteger(session, operOID, OID_LENGTH(operOID));
    macAddress = Router::getSnmpMacAddress(session, macOID, OID_LENGTH(macOID));

    oid inOctetOID[] = {1,3,6,1,2,1,2,2,1,10,(oid)ifIndex};
    oid outOctetOID[] = {1,3,6,1,2,1,2,2,1,16,(oid)ifIndex};
    oid inPacketOID[] = {1,3,6,1,2,1,2,2,1,11,(oid)ifIndex};
    oid outPacketOID[] = {1,3,6,1,2,1,2,2,1,17,(oid)ifIndex};

    Traffic traffic;
    traffic.inOctet = Router::getSnmpInteger(session, inOctetOID, OID_LENGTH(inOctetOID));
    traffic.outOctet = Router::getSnmpInteger(session, outOctetOID, OID_LENGTH(outOctetOID));
    traffic.inPacket = Router::getSnmpInteger(session, inPacketOID, OID_LENGTH(inPacketOID));
    traffic.outPacket = Router::getSnmpInteger(session, outPacketOID, OID_LENGTH(outPacketOID));

    trafficBuffer.append(traffic);
    if(trafficBuffer.size() > 50)
        trafficBuffer.removeFirst();

    snmp_close(session);
    SOCK_CLEANUP;
}





void Port::calculateBPSPPS() {
    Traffic &lastTraffic = trafficBuffer.last();

    quint32 deltaInBytes = lastTraffic.inOctet - trafficBuffer[trafficBuffer.size()-2].inOctet;
    quint32 deltaOutBytes = lastTraffic.outOctet - trafficBuffer[trafficBuffer.size()-2].outOctet;
    quint32 deltaInPackets = lastTraffic.inPacket - trafficBuffer[trafficBuffer.size()-2].inPacket;
    quint32 deltaOutPackets = lastTraffic.outPacket - trafficBuffer[trafficBuffer.size()-2].outPacket;

    lastTraffic.InBPS = (deltaInBytes * 8)  / 5.0;
    lastTraffic.OutBps = (deltaOutBytes * 8) / 5.0;
    lastTraffic.InPPS = deltaInPackets / 5.0;
    lastTraffic.OutPPS = deltaOutPackets / 5.0;

}









void Port::calculateLoadStatus() {
    Traffic &lastTraffic = trafficBuffer.last();
    lastTraffic.loadStatus = "normal";

    quint32 prevInBPS = trafficBuffer[trafficBuffer.size()-2].InBPS;
    quint32 currrentInBPS = lastTraffic.InBPS;

    if (prevInBPS != 0  &&  currrentInBPS != 0) {
        if (currrentInBPS  >  prevInBPS * 2)
                lastTraffic.loadStatus = "danger";

        else if (currrentInBPS  > prevInBPS * 1.5)
            lastTraffic.loadStatus = "warning";
    }
}




















