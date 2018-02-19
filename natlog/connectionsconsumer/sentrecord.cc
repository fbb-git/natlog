#include "connectionsconsumer.ih"

void ConnectionsConsumer::sentRecord(Record *record)
{
    auto iter = d_tcp.find(record->srcKey());

    iter->second->addSentBytes(record);
//CERR << "SENT: " << *iter->second << '\n';

    delete record;
}
