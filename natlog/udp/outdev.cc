#include "udp.ih"

    // The OUT interface is used to NAT source addresses to the nathost's
    // address. 

    //  nat:nport -> dst:dport,  ID in d_keyMap
    // or
    //  dst:dport -> nat:nport                      (ignored)

    
void UDP::outDev(Record const *next)
try
{
    auto idIter = d_keyMap.find(next->id());    // look for the ID
    if (idIter == d_keyMap.end())               // no such ID
        throw false;

    auto iter = find(idIter->second);           // get the matching record
    if (iter == end())                          // somehow not available
        throw false;

    d_keyMap.erase(idIter);                     // ID no longer needed
    setVia(iter, next);                         // set nat:nport as via
    throw true;
}
catch (...)
{
    delete next;
}

