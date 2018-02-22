#include "tcp.ih"

static size_t count = 0;

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
//CERR << *next << '\n';
        d_keyMap[next->id()] = next->key();
        
        insert(next);
if (count++ % 32 == 0)
CERR << "keymap size: " << d_keyMap.size() << ", map size: " << size() <<
'\n';

    }
}
