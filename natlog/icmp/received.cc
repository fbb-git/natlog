#include "icmp.ih"

void ICMP::received(RecordPtr &next)
{
                                        // src may not be local
    if (not g_nic.mask(Record::IN, next->sourceIP()))
    {
                                        // existing connection: 
                                        // add received bytes
        if (auto iter = find(next->key()); iter != end())
            iter->second->addReceivedBytes(*next);
    }
}
