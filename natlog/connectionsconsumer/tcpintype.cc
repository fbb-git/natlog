#include "connectionsconsumer.ih"

ConnectionsConsumer::TCP_type 
        ConnectionsConsumer::tcpInType(Record const *record)
{
    if (record->flags() == Record::SYN)     // SYN (only) record
        return TCP_SYN;

    if (record->flags() & Record::FIN)       // FIN-flag set
        return TCP_FIN;

    if (d_tcp.find(record->srcKey()) != d_tcp.end())
        return TCP_SENT;

    if (d_tcp.find(record->dstKey()) != d_tcp.end())
        return TCP_RECVD;

    return TCP_IGNORE;
}
