#include "connectionsconsumer.ih"

void ConnectionsConsumer::tcp_udpDestroy(RecordMap &map, Record const *record,
                                         char const *type)
{
                                        // find this record's accumulated data
    auto iter = map.find(record->srcKey());

    if (iter == map.end())              // unknown record: no existing
        return;                         // connection

    auto *accu = iter->second;

    accu->addSentBytes(record);
    accu->addReceivedBytes(record);

    logTCP_UDP(iter->second, type);
    delete record;
    erase(map, iter);                   // remove the entry
}

