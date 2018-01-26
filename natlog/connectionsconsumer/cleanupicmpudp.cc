#include "connectionsconsumer.ih"

void ConnectionsConsumer::cleanupICMP_UDP(time_t now_ttl)
{
    cleanup(now_ttl, d_icmpMutex, d_icmp, 
                                  &ConnectionsConsumer::logICMP, "icmp");

    cleanup(now_ttl, d_udpMutex, d_udp,
                                 &ConnectionsConsumer::logTCP_UDP, "udp");
}
