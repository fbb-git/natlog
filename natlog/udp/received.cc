#include "udp.ih"

    //  source      destination
    // dst:dport -> src::sport

    // source may not be local
void UDP::received(RecordPtr &next)
{
                                        // source may not be local
    if (not g_nic.mask(Record::IN, next->sourceIP()))
    {
                                        // existing connection: 
                                        // add received bytes
        if (auto iter = find(next->dstKey()); iter != end())
            iter->second->addReceivedBytes(*next);
    }
}
