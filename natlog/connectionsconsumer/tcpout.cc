#include "connectionsconsumer.ih"

    // The OUT interface is used to NAT source addresses to the nathost's
    // address. When receiving a SYN packet the via-data can be set
    // and the entry can be removed from d_sequence, as no information
    // about this connection on the OUT device is used anymore.

void ConnectionsConsumer::tcpOut(Record const *record)
try
{
    if (record->flags() != Record::SYN) // ignore unless a mere SYN record
        throw false;                    

                                        // find the matching record
    auto iter = d_tcp.find( record->sequence() );

    if 
    (
        iter == d_tcp.end()             // ignore if unkown record
        or                              // or not coming from the out-device
        g_nic.address(Record::OUT) != record->sourceIP()
    )
        throw false;

                                        // set the via-address and via-port
    iter->second->setViaIP(record->sourceIP());
    iter->second->setViaPort(record->sourcePort());

    d_tcp.insert( value_type{ iter->second->srcKey(), iter->second } );
    d_tcp.erase(iter);

    throw false;
}
catch (...)
{
    delete record;
}



