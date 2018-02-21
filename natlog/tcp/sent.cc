#include "tcp.ih"

void TCP::sent(Record *next)
{
//CERR << "begin\n";

    find(next->srcKey())->second->addSentBytes(next);

    delete next;

//CERR << "end\n";
}
