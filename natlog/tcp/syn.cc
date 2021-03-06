#include "tcp.ih"

void TCP::syn(RecordPtr &next)
{
    if (                                            // package sent
        g_nic.mask(Record::IN, next->sourceIP())
        &&                                          // and not a local
        not g_nic.mask(Record::IN, next->destIP())  // connection
    )
    {
        auto idIter = d_keyMap.find(next->id());    // look for the ID
        if (idIter == d_keyMap.end())               // ID not yet seen
        {
            next->setSrcKey();                  // store the key for outDev
            d_keyMap[next->id()] = { true, next->key() };
        }
        else                                    // ID already set by outDev
        {
            next->setVia(idIter->second.key);
            d_keyMap.erase(idIter);             // so not needed anymore
        }

        insert(next);
    }
}
