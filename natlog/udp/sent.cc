#include "udp.ih"

    // source         destination
    // src:sport  ->  dst::dport,   ID
    //
    // sent: dst may not be in the local net

void UDP::sent(RecordPtr &next)
{
                                        // dest may not be in the local net
    if (not g_nic.mask(Record::IN, next->destIP()))
    {
                                        // existing record: add sent bytes
        if (auto iter = find(next->key()); iter != end())
            iter->second->addSentBytes(*next);
        else                            
        {                               // or store a new connection

            auto idIter = d_keyMap.find(next->id());    // look for the ID
            if (idIter == d_keyMap.end())               // ID not yet seen
            {
                next->setSrcKey();                  // store the key for outDev
                d_keyMap[next->id()] = { true, next->key() };
            }
            else
            {
                next->setVia(idIter->second.key);
                idIter->second.expired = true;
            }

            next->addSentBytes(*next);
            insert(next);                       // store the record
        }
    }                                   
}



