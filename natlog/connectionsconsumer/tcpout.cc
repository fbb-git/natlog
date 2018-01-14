#include "connectionsconsumer.ih"

    // The OUT interface is used to NAT source addresses to the nathost's
    // address. When receiving a SYN packet the via-data can be set
    // and the entry can be removed from d_sequence, as no information
    // about this connection on the OUT device is used anymore.

void ConnectionsConsumer::tcpOut(Record &record)
{
    if (record.flags() != Record::SYN)  // not a mere SYN record:
        return;                         //  no further actions required.

                                        // find the matching record
    auto iter = d_tcp.find( d_sequence[ record.sequenceNr() ] );

    if (iter == d_tcp.end())            // no data about this connection
        return;

    iter->second.setViaIP(record.sourceIP());
    iter->second.setViaPort(record.sourcePort());

    d_sequence.erase(d_sequence.find(record.sequenceNr()));
}
