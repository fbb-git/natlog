#include "udp.ih"

    // sent: dst may not be in the local net

void UDP::sent(Record *next)
{
                                        // dest may not be in the local net
    if (not g_nic.mask(Record::IN, next->destIP()))
    {
                                        // existing record: add sent bytes
        if (auto iter = find(next->srcKey()); iter != end())
            iter->second->addSentBytes(next);
        else                            
        {                               // or store a new connection
            insert(next);
            next->addSentBytes(next);
            return;
        }
    }                                   

    delete next;
}
