#include "tcp.ih"

void TCP::received(Record *next)
{
//CERR << "begin\n";
    find(next->dstKey())->second->addReceivedBytes(next);

    delete next;
//CERR << "end\n";
}
