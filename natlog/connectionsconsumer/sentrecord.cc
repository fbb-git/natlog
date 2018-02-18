#include "connectionsconsumer.ih"

void ConnectionsConsumer::sentRecord(Record *record)
{
    auto iter = d_tcp.find(record->key());

    if (iter != d_tcp.end())
        iter->second->addSentBytes(record);

    delete record;
}
