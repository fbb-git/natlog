#include "connectionsconsumer.ih"

    // The OUT interface is used to NAT source addresses to the nathost's
    // address. When receiving a known ID packet the via-data can be set
    // and the entry can be removed from d_id, as no information
    // about this connection on the OUT device is used anymore.

void ConnectionsConsumer::udpOut(Record const &record)
{
                                        // previously seen ID?
    auto iterID = d_id.find(record.id());   

    if (iterID == d_id.end())           // no: no further actions required.
        return;
                                        // find the matching record 
    auto iter = d_udp.find( iterID->second );
    if (iter == d_udp.end())            // not available for some reason
        return;
                                        // 1st time out:
                                        // NAT has changed the source address
                                        // OK: so set the accumulated data's
                                        // 'via' address.
    if (g_nic.address(Record::OUT) == record.sourceIP())
    {
        iter->second.setViaIP(record.sourceIP());
        iter->second.setViaPort(record.sourcePort());
    }

    d_id.erase(iterID);                 // remove the ID information
}


