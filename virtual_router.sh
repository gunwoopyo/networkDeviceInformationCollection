#!/bin/bash
sudo systemctl stop snmpd 2>/dev/null || true
NETNS_NAME="router"
ip netns del ${NETNS_NAME} 2>/dev/null || true
ip netns add ${NETNS_NAME}
START_SUBNET=101

for i in {1..10}; do
        HOST_PORT="port${i}_host"
        ROUTER_PORT="port${i}"

        HOST_PORT_IP="192.168.${START_SUBNET}.254/24"
        ROUTER_PORT_IP="192.168.${START_SUBNET}.1/24"

        START_SUBNET=$((START_SUBNET + 1))

        ip link add ${HOST_PORT} type veth peer name ${ROUTER_PORT}
        ip link set ${ROUTER_PORT} netns ${NETNS_NAME}

        ip addr add ${HOST_PORT_IP} dev ${HOST_PORT}
        ip link set ${HOST_PORT} up

        ip netns exec ${NETNS_NAME} ip addr add ${ROUTER_PORT_IP} dev ${ROUTER_PORT}
        ip netns exec ${NETNS_NAME} ip link set ${ROUTER_PORT} up
done

ip netns exec ${NETNS_NAME} ip link set lo up
ip netns exec ${NETNS_NAME} sysctl -w net.ipv4.ip_forward=1
ip netns exec ${NETNS_NAME} iptables -F
ip netns exec ${NETNS_NAME} iptables -P FORWARD ACCEPT

sudo ip netns exec ${NETNS_NAME} umount /proc 2>/dev/null || true
sudo ip netns exec ${NETNS_NAME} mount -t proc proc /proc
sudo ip netns exec ${NETNS_NAME} snmpd -u root -f -c /etc/snmp/router.snmpd.conf &

