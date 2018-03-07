#include "udp.ih"

    // The OUT interface is used to NAT source addresses to the nathost's
    // address. 

    //  nat:nport -> dst:dport,  ID in d_keyMap
    // or
    //  dst:dport -> nat:nport                      (ignored)

    
void UDP::outDev(Record const &next)
{
    auto idIter = d_keyMap.find(next.id());    // look for the ID
    if (idIter == d_keyMap.end())               // no such ID
        return;

    auto iter = find(idIter->second);           // get the matching record
    if (
        iter == end()                           // somehow not available
        ||                                      // or src != OUT device
        g_nic.address(Record::OUT) != next.sourceIP()
    )
        return;

    d_keyMap.erase(idIter);                     // ID no longer needed
    setVia(iter, next);                         // set nat:nport as via
}

