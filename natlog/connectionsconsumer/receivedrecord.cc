#include "connectionsconsumer.ih"

void ConnectionsConsumer::receivedRecord(Record *record)
{
    auto iter = d_tcp.find(record->key());

    if (iter != d_tcp.end())
        iter->second->addReceivedBytes(record);

    delete record;
}
