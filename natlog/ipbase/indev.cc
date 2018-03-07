#include "ipbase.ih"

    // sent:        src is local,   dst is remote
    // received:    src is remote,  dst is local

//f: IPbase::inDev(Record*)
    //c: ICMP::sent(Record*)
    //c: ICMP:;received(Record*)
    //c: TCP::sent(Record*)
    //c: TCP:;received(Record*)
    //c: UDP::sent(Record*)
    //c: UDP:;received(Record*)

void IPbase::inDev(Record *next)
{
    if (g_nic.mask(Record::IN, next->sourceIP()))   // package is sent
        sent(next);
                                                    // package is received
    else if (g_nic.mask(Record::IN, next->destIP())) 
        received(next);

    else                                            // neither...
        delete next;
}

