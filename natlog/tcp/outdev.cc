#include "tcp.ih"

    // The OUT device is used to NAT source addresses to the nathost's
    // address. 

    // IN device:   sends SYN src:sport -> dst:dport
    // OUT device:  sends SYN nat:nport -> dst:dport
    // in that case: 
    //  new entry in the map, using a key computed from src::sport

void TCP::outDev(Record const *next)
try
{
    if (next->flags() != Record::SYN) // ignore unless a mere SYN record
        throw false;                    

                                        // find the matching record
    auto iter = find( next->key() );

    if 
    (
        iter != end()                   // known record and
        and                             // src is the out-device
        g_nic.address(Record::OUT) == next->sourceIP()
    )
        viaAndSrcKey(iter, next);       // use sport srcIP as key

    throw false;
}
catch (...)
{
    delete next;
}





