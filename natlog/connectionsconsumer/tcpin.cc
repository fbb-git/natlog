#include "connectionsconsumer.ih"

void ConnectionsConsumer::tcpIn(Record &record)
{
    size_t key = record.setTCPUDPkey();

    if (record.flags() == Record::SYN)      // syn-flag set
    {                                       // store new connection
        d_tcp.insert( value_type{ key, record } );

            // d_sequence: a support map only used for SYN tcp connections
        d_sequence[record.sequenceNr()] = key;   // used by OUT at SYN flag
        return;
    }
                                        // find this record's accumulated data
    auto iter = d_tcp.find(record.key()); 

    if (iter == d_tcp.end())            // unknown record: no existing
        return;                         // connection or final ACKs 

    // existing connections:

    Record &accu = iter->second;        // the connection's accumulated data

    accu.setEndTime(record);

    if (accu.sourceIP() == record.sourceIP()) // packet was sent to dest.
        accu.addSentBytes(record.payload());
    else                                    // packet was received fm. dest.
        accu.addReceivedBytes(record.payload());
}
