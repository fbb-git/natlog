#include "tcp.ih"

void TCP::sent(Record *next)
{
    find(next->srcKey())->second->addSentBytes(next);

    delete next;
}
