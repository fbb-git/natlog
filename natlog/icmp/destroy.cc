#include "icmp.ih"

void ICMP::destroy(Record const *next)
{
    auto iter = find(next->IDKey());    // find this next's data

    if (iter == end())                  // unknown next: matching NEW 
        return;                         // not seen during this program's
                                        // lifetime 

    iter->second->addSentBytes(next);
    iter->second->addReceivedBytes(next);

    log(iter->second);
    erase(iter);                        // remove the entry
}
