#include "tcp.ih"

void TCP::received(Record *next)
{
//CERR << "key = " << next->dstKey() << '\n';
    find(next->dstKey())->second->addReceivedBytes(next);

    delete next;
}
