#include "tcp.ih"

void TCP::sent(Record *next)
{
//CERR << "key = " << next->srcKey() << '\n';
    find(next->srcKey())->second->addSentBytes(next);

    delete next;
}
