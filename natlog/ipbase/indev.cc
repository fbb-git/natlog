#include "ipbase.ih"

    // sent:        src is local,   dst is remote
    // received:    src is remote,  dst is local

void IPbase::inDev(Record *next)
{
    if (g_nic.mask(Record::IN, next->sourceIP())) // package is sent
        sent(next);
                                                    // package is received
    else if (g_nic.mask(Record::IN, next->destIP())) 
        received(next);
}

