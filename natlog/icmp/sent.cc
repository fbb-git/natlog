#include "icmp.ih"

    // sent: dst may not be in the local net

void ICMP::sent(RecordPtr &next)
{
                                        // dest may not be in the local net
    if (not g_nic.mask(Record::IN, next->destIP()))
    {
                                        // existing record: add sent bytes
        if (auto iter = find(next->key()); iter != end())
            iter->second->addSentBytes(*next);
        else                            
        {                               // or store a new connection
            next->addSentBytes(*next);
            insert(next);
            return;
        }
    }                                   
}
