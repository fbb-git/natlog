#include "tcp.ih"

void TCP::syn(Record *next)
{
    if (                                            // package not sent
        not g_nic.mask(Record::IN, next->sourceIP())
        ||
        g_nic.mask(Record::IN, next->destIP())      // or local connection
    )
        delete next;                                // then ignore
    else                                            // else insert
    {
        next->setSrcKey();                  // store the outDev key
        d_keyMap[next->id()] = next->key();
        
        insert(next);
    }
}
