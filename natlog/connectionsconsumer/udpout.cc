#include "connectionsconsumer.ih"

    // The OUT interface is used to NAT source addresses to the nathost's
    // address. When receiving a known ID packet the via-data can be set
    // and the entry can be removed from d_id, as no information
    // about this connection on the OUT device is used anymore.

void ConnectionsConsumer::udpOut(Record &record)
{
    auto iterID = d_id.find(record.id());

    if (iterID == d_id.end())           // irrelevant UDP packet
        return;                         //  no further actions required.

                                        // find the matching record via 
                                        //  its key
    auto iter = d_udp.find( iterID->second );
    if (iter == d_udp.end())            // not available for some reason
        return;

    auto &accu = iter->second;

    if (accu.sourceIP() != record.sourceIP())
    {
        accu.setViaIP(record.sourceIP());
        accu.setViaPort(record.sourcePort());
    }
    else
    {
        accu.reverse();
        accu.setViaIP(record.destIP());
        accu.setViaPort(record.destPort());
    }

    d_id.erase(iterID);                 // remove the ID information
}
