#include "connectionsconsumer.ih"

// static
ConnectionsConsumer::TCP_type 
        ConnectionsConsumer::tcpInType(Record const *record)
{
    if (record->flags() == Record::SYN)     // SYN (only) record
        return TCP_SYN;

    if (record->flags() & Record::FIN)       // FIN-flag set
        return TCP_FIN;

    if (record->key() == record->srcKey())
        return TCP_SENT;

    if (record->key() == record->dstKey())
        return TCP_RECVD;

    return TCP_IGNORE;
}
