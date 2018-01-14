#include "connectionsconsumer.ih"

// static
void ConnectionsConsumer::cleanupWrap(ConnectionsConsumer *const consumer)
{
    // if lastUsed + ttl < now then log and remove the record
    // so: if lastUsed < now - ttl log and remove the record

    while (not consumer->d_storage.empty())
    {
        this_thread::sleep_for(chrono::seconds(3));

        time_t now_ttl = time(0) - consumer->d_ttl;

        consumer->cleanup(now_ttl, consumer->d_icmpMutex, consumer->d_icmp,
                &ConnectionsConsumer::logICMP);

        consumer->cleanup(now_ttl, consumer->d_tcpMutex, consumer->d_tcp,
                &ConnectionsConsumer::logTCP_UDP, "tcp");
    }
}



