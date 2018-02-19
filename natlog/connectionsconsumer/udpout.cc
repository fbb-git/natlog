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
        newKey(d_udp, iter, record);    // and use sport srcIP as key

    delete record;
}

