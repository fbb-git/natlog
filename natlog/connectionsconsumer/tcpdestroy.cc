#include "connectionsconsumer.ih"

void ConnectionsConsumer::tcpDestroy(Record &record)
{
                                        // find this record's accumulated data
    auto iter = d_tcp.find(record.key());

    if (iter == d_tcp.end())            // unknown record: no existing
        return;                         // connection or final ACKs 

    auto &accu = iter->second;
    accu.setEndTime(record);

    accu.addSentBytes(record.sentBytes());
    accu.addReceivedBytes(record.receivedBytes());

    logTCP_UDP(iter->second, "tcp");    
    d_tcp.erase(iter);                  // remove the entry
}
