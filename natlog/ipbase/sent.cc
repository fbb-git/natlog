#include "ipbase.ih"

void IPbase::sent(Record *next)
{
                                        // when connecting the local net
                                        // ignore the record
    if (not g_nic.mask(Record::IN, next->destIP()))
    {
                                        // existing record: add sent bytes
        if (auto iter = d_map.find(next->IDKey()); iter != d_map.end())
            iter->second->addSentBytes(next);
        else                            
        {                               // or store a new connection
            insert( next->IDKey(), next );
            next->addSentBytes(next);
            return;
        }
    }                                   

    delete next;
}
