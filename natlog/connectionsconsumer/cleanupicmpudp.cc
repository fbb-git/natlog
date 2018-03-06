#include "connectionsconsumer.ih"

void ConnectionsConsumer::cleanupICMP_UDP(time_t now_ttl)
{
    d_icmp.cleanup(now_ttl);
    d_udp.cleanup(now_ttl);
}
