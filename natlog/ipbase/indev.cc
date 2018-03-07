#include "ipbase.ih"

    // sent:        src is local,   dst is remote
    // received:    src is remote,  dst is local

//f: IPbase::inDev(RecordPtr&)
    //c: ICMP::sent(RecordPtr&)
    //c: ICMP:;received(RecordPtr&)
    //c: TCP::sent(RecordPtr&)
    //c: TCP:;received(RecordPtr&)
    //c: UDP::sent(RecordPtr&)
    //c: UDP:;received(RecordPtr&)

void IPbase::inDev(RecordPtr &next)
{
    if (g_nic.mask(Record::IN, next->sourceIP()))   // package is sent
        sent(next);
                                                    // package is received
    else if (g_nic.mask(Record::IN, next->destIP())) 
        received(next);
}

