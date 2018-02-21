#include "ipbase.ih"

void IPbase::received(Record *next)
{
                                        // when remaining inside the local net
                                        // ignore the record
    if (not g_nic.mask(Record::IN, next->sourceIP()))
    {
                                        // existing connection: 
                                        // add received bytes
        if (auto iter = d_map.find(next->dstKey()); iter != d_map.end())
            iter->second->addReceivedBytes(next);
    }

    delete next;
}
