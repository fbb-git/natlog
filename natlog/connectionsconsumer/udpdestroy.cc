#include "connectionsconsumer.ih"

void ConnectionsConsumer::udpDestroy(Record &record)
{
                                        // find this record's accumulated data
    auto iter = d_udp.find(record.key());

    if (iter == d_udp.end())            // unknown record: no existing
        return;                         // connection

    auto &accu = iter->second;
    accu.setEndTime(record);

    accu.addSentBytes(record.sentBytes());
    accu.addReceivedBytes(record.receivedBytes());

    logTCP_UDP(iter->second, "udp");    
    d_udp.erase(iter);                  // remove the entry
}

