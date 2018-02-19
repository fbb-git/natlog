#include "connectionsconsumer.ih"

void ConnectionsConsumer::receivedRecord(Record *record)
{
    auto iter = d_tcp.find(record->dstKey());

    iter->second->addReceivedBytes(record);
//CERR << "RECEIVED: " << *iter->second << '\n';

    delete record;
}
