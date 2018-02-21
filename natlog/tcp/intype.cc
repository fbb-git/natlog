#include "tcp.ih"

TCP::TCP_type TCP::inType(Record const *next)
{
    if (next->flags() == Record::SYN)     // SYN (only) record
        return TCP_SYN;

    if (next->flags() & Record::FIN)       // FIN-flag set
        return TCP_FIN;

    if (find(next->srcKey()) != end())
{
CERR << next->srcKey() << " -- " << next->key() << '\n';
        return TCP_SENT;
}

    if (find(next->dstKey()) != end())
        return TCP_RECVD;

    return TCP_IGNORE;
}
