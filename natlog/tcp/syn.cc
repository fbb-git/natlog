#include "tcp.ih"

void TCP::syn(Record *next)
{
// CERR << "size: " << size() << '\n';

    if (                                            // package not sent
        not g_nic.mask(Record::IN, next->sourceIP())
        ||
        g_nic.mask(Record::IN, next->destIP())      // or local connection
    )
        delete next;                                // then ignore
    else                                            // else insert
        insert(next->sequenceKey(), next);
            // insertion also means: the record pointer is transferred
            // to the tcp-map.
// CERR << '\n';
}
