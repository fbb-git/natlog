#include "udp.ih"

    // source         destination
    // src:sport  ->  dst::dport,   ID
    //
    // sent: dst may not be in the local net

void UDP::sent(Record *next)
{
                                        // dest may not be in the local net
    if (not g_nic.mask(Record::IN, next->destIP()))
    {
                                        // existing record: add sent bytes
        if (auto iter = find(next->key()); iter != end())
            iter->second->addSentBytes(next);
        else                            
        {                               // or store a new connection
            next->setSrcKey();                  // store the outDev key
            d_keyMap[next->id()] = next->key();

            insert(next);                       // store the record

            next->addSentBytes(next);
//CERR << "insert: " << *next << '\n';
            return;
        }
    }                                   

    delete next;
}



