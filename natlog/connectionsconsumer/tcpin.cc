#include "connectionsconsumer.ih"

void ConnectionsConsumer::tcpIn(Record *record)
{
    size_t key = record->setTCPUDPkey();

    if (record->flags() == Record::SYN)      // syn-flag set
    {
        if (g_nic.mask(Record::IN, record->sourceIP())) // package is sent?
        {
                                            // connecting the local net?
                                            // then ignore the record
            if (g_nic.mask(Record::IN, record->destIP()))
                return;

                                            // store new connection
            d_tcp.insert( value_type{ key, record } );

               // d_sequence: a support map for SYN tcp connections
            d_sequence[record->id()] = key;   // used by OUT at SYN flag
        }

        return;
    }
                                        // find this record's accumulated data
    auto iter = d_tcp.find(record->key()); 

    if (iter == d_tcp.end())            // unknown record: no existing
        return;                         // connection or final ACKs 

    // existing connections:

    Record *accu = iter->second;        // the connection's accumulated data

    accu->setEndTime(record);

    if (accu->sourceIP() == record->sourceIP()) // packet was sent to dest.
        accu->addSentBytes(record->payload());
    else                                    // packet was received fm. dest.
        accu->addReceivedBytes(record->payload());

    if (record->flags() & Record::FIN)       // FIN-flag set
    {
        logTCP_UDP(iter->second, "tcp");    
        erase(d_tcp, iter);                 // remove the entry
    }
}

