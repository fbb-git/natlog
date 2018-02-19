#include "connectionsconsumer.ih"

void ConnectionsConsumer::icmpOut(Record const *record)
{
//CERR << '\n';

    auto iter = d_icmp.find(record->IDKey());

    if (
        iter != d_icmp.end()            // key found and the NAT-host's 
        and                             // address is the source address
        g_nic.address(Record::OUT) == record->sourceIP()
    )
//{
        iter->second->setViaIP(record->sourceIP()); // then set the via-addr.
//CERR << "VIA: " << *iter->second << '\n';
//}
                                        // 1st time out: 
                                        // NAT has changed the source address
                                        // OK: so set the accumulated data's
                                        // 'via' address.
    delete record;
}
