#include "connectionsconsumer.ih"

void ConnectionsConsumer::icmpOut(Record const *record)
{
    auto iter = d_icmp.find(record->key());

    if (iter == d_icmp.end())           // key not found.
        return;

                                        // 1st time out: 
                                        // NAT has changed the source address
                                        // OK: so set the accumulated data's
                                        // 'via' address.
    if (g_nic.address(Record::OUT) == record->sourceIP())
        iter->second->setViaIP(record->sourceIP());
}
