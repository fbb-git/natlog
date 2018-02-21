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

// CERR << *next << '\n';
                                        // find the matching record
    auto iter = find( next->sequence() );

    if 
    (
        iter != end()                   // known record and
        and                             // src is the out-device
        g_nic.address(Record::OUT) == next->sourceIP()
    )
        newKey(iter, next);                 // use sport srcIP as key

// CERR << "end\n";

    throw false;
}
catch (...)
{
    delete next;
}



