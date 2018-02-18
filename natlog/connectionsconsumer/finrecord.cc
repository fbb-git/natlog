#include "connectionsconsumer.ih"

void ConnectionsConsumer::finRecord(Record *record)
{
    auto iter = d_tcp.find(record->key());

    if (iter != d_tcp.end())
        logTCP_UDP(iter->second, "tcp");    

    delete record;
    erase(d_tcp, iter);                 // remove the entry
}
