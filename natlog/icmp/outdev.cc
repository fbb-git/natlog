#include "icmp.ih"

void ICMP::outDev(Record const *next)
{
    auto iter = find(next->IDKey());

    if (
        iter != end()                   // key found and the NAT-host's 
        and                             // address is the source address
        g_nic.address(Record::OUT) == next->sourceIP()
    )
        iter->second->setViaIP(next->sourceIP()); // then set the via-addr.

                                        // 1st time out: 
                                        // NAT has changed the source address
                                        // OK: so set the accumulated data's
                                        // 'via' address.
    delete next;
}
