#include "tcp.ih"

void TCP::sent(RecordPtr &next)
{
    find(next->srcKey())->second->addSentBytes(*next);
}
