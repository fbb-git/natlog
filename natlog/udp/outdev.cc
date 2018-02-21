#include "udp.ih"

    // The OUT interface is used to NAT source addresses to the nathost's
    // address. When receiving a known ID packet the via-data can be set
    // and the entry can be removed from d_id, as no information
    // about this connection on the OUT device is used anymore.

void UDP::outDev(Record const *next)
{
                                        // previously seen ID?
    auto iter = find(next->IDKey());   

    if (
        iter != end()                   // key found and the NAT-host's 
        and                             // address is the source address
        g_nic.address(Record::OUT) == next->sourceIP()
    )
        newKey(iter, next);           // and use sport srcIP as key

    delete next;
}

