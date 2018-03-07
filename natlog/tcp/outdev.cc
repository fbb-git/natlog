#include "tcp.ih"

    // The OUT device is used to NAT source addresses to the nathost's
    // address. 

    // IN device:   sends SYN src:sport -> dst:dport
    // OUT device:  sends SYN nat:nport -> dst:dport
    // in that case: 
    //  new entry in the map, using a key computed from src::sport

void TCP::outDev(Record const &next)
{
    if (next.flags() != Record::SYN) // ignore unless a mere SYN record
        return;

    auto idIter = d_keyMap.find(next.id());    // look for the ID
    if (idIter == d_keyMap.end())               // no such ID
        return;

    auto iter = find(idIter->second);   // find the matching record
    if (iter == end())                  // somehow not available
        return;

    d_keyMap.erase(idIter);             // key no longer required
    setVia(iter, next);                 // set nat:nport as via
}





