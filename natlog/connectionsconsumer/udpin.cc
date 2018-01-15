#include "connectionsconsumer.ih"

void ConnectionsConsumer::udpIn(Record &record)
{
    size_t key = record.setTCPUDPkey();
                                        
    auto iter = d_udp.find(key);        // find this record's accumulated data

    if (iter == d_udp.end())            // new connection
    {                                   // store it
        record.addSentBytes(record.payload());
        d_udp.insert( value_type{ key, record } );

            // d_id: a support map only used for new udp connections
        d_id[record.id()] = key;        // used by OUT

        return;
    }

    // existing connections:

    Record &accu = iter->second;        // the connection's accumulated data

    accu.setEndTime(record);

    if (accu.sourceIP() == record.sourceIP()) // packet was sent to dest.
        accu.addSentBytes(record.payload());
    else                                    // packet was received fm. dest.
        accu.addReceivedBytes(record.payload());
}





