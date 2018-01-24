#include "connectionsconsumer.ih"

// static
void ConnectionsConsumer::cleanupWrap(ConnectionsConsumer *const consumer)
{
    // if lastUsed + ttl < now then log and remove the record
    // so: if lastUsed < now - ttl log and remove the record

    while (not consumer->d_storage.empty())
    {
        this_thread::sleep_for(chrono::seconds(3));

        consumer->cleanupICMP_UDP(time(0) - consumer->d_ttl);
    }
}



