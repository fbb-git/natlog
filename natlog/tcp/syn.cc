#include "tcp.ih"

void TCP::syn(RecordPtr &next)
{
    if (                                            // package sent
        g_nic.mask(Record::IN, next->sourceIP())
        &&                                          // and not a local
        g_nic.mask(Record::IN, next->destIP())      // connection
    )
    {
        next->setSrcKey();                  // store the outDev key
        d_keyMap[next->id()] = next->key();
        
        insert(next);
    }
}
