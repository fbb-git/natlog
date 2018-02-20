#include "connectionsconsumer.ih"

void ConnectionsConsumer::tcpSent(Record *record)
{
    auto iter = d_tcp.find(record->srcKey());

    iter->second->addSentBytes(record);
//CERR << "SENT: " << *iter->second << '\n';

    delete record;
}
