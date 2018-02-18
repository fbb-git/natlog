#include "connectionsconsumer.ih"

    // The OUT interface is used to NAT source addresses to the nathost's
    // address. When receiving a known ID packet the via-data can be set
    // and the entry can be removed from d_id, as no information
    // about this connection on the OUT device is used anymore.

void ConnectionsConsumer::udpOut(Record const *record)
{
                                        // previously seen ID?
    auto iter = d_udp.find(record->IDKey());   

    if (iter != d_udp.end())            // yes: set via-info
    {
                                        // 1st time out:
                                        // NAT has changed the source address
                                        // OK: so set the accumulated data's
                                        // 'via' address.
        iter->second->setViaIP(record->sourceIP());
        iter->second->setViaPort(record->sourcePort());

        d_udp.insert( value_type{ iter->second->srcKey(), iter->second } );
        d_udp.erase(iter);
    }

    delete record;
}

