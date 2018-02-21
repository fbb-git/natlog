#include "udp.ih"

    // received:    src is remote,  dst is local

void UDP::received(Record *next)
{
                                        // src may not be local
    if (not g_nic.mask(Record::IN, next->sourceIP()))
    {
                                        // existing connection: 
                                        // add received bytes
        if (auto iter = find(next->dstKey()); iter != end())
            iter->second->addReceivedBytes(next);
    }

    delete next;
}
