#include "connectionsconsumer.ih"

void ConnectionsConsumer::tcp_udpDestroy(RecordMap &map, Record const *record,
                                         char const *type)
{
                                        // find this record's accumulated data
    auto iter = map.find(record->key());

    if (iter == map.end())              // unknown record: no existing
        return;                         // connection

    auto *accu = iter->second;
    accu->setEndTime(record);

    accu->addSentBytes(record->sentBytes());
    accu->addReceivedBytes(record->receivedBytes());

    logTCP_UDP(iter->second, type);    
    erase(map, iter);                   // remove the entry
}

