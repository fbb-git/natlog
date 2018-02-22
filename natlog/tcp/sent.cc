#include "tcp.ih"

void TCP::sent(Record *next)
{
    find(next->key())->second->addSentBytes(next);

    delete next;
}
