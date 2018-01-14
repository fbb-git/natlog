#include "connectionsconsumer.ih"

void ConnectionsConsumer::udpIn(Record &record)
{
    size_t key = record.setTCPUDPkey();

                                        // find this record's accumulated data
    auto iter = d_tcp.find(key); 

    if (iter == d_udp.end())            // new connection
    {                                   // store it
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





