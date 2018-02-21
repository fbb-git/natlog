#include "tcp.ih"

TCP::TCP_type TCP::inType(Record *next)
{
    if (next->flags() == Record::SYN)     // SYN (only) record
        return TCP_SYN;

    if (next->flags() & Record::FIN)       // FIN-flag set
        return TCP_FIN;

    if (find(next->srcKey()) != end())
        return TCP_SENT;

    if (find(next->dstKey()) != end())
        return TCP_RECVD;

    return TCP_IGNORE;
}
