#include "tcp.ih"

void TCP::syn(Record *next)
{
CERR << "begin  SYN\n";
    if (                                            // package not sent
        not g_nic.mask(Record::IN, next->sourceIP())
        ||
        g_nic.mask(Record::IN, next->destIP())      // or local connection
    )
        delete next;                                // then ignore
    else                                            // else insert
        insert(next);
}
