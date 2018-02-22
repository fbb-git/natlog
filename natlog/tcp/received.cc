#include "tcp.ih"

void TCP::received(Record *next)
{
    find(next->dstKey())->second->addReceivedBytes(next);

    delete next;
}
