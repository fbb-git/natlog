#include "connectionsconsumer.ih"

void ConnectionsConsumer::cleanupCompleted(time_t now_ttl)
{
        cleanup(now_ttl, d_icmpMutex, d_icmp, &ConnectionsConsumer::logICMP);

        cleanup(now_ttl, d_tcpMutex, d_tcp,
                                    &ConnectionsConsumer::logTCP_UDP, "tcp");

        cleanup(now_ttl, d_udpMutex, d_udp,
                                    &ConnectionsConsumer::logTCP_UDP, "upd");
}
