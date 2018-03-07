#include "tcp.ih"

void TCP::received(RecordPtr &next)
{
    find(next->dstKey())->second->addReceivedBytes(*next);
}
