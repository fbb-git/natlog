#include "connectionsconsumer.ih"

void ConnectionsConsumer::udpIn(Record &record)
{
    if (record.id() == 0)                   // ignore invalid IDs
        return;

    size_t key = record.setTCPUDPkey();     // find the key

    if (g_nic.mask(Record::IN, record.sourceIP())) // package being sent?
    {
                                            // connecting the NAT host?
                                            // then ignore the record
        if (g_nic.address(Record::OUT) == record.destIP())   
            return;

                                            // accumulated data exists, then
                                            // update #sent
        if (auto iter = d_udp.find(key); iter != d_udp.end())
            iter->second.addSentBytes(record.payload());
        else                                // or it's a new connection
        {                                   
            record.addSentBytes(record.payload());      // set #sent
            d_udp.insert( value_type{ key, record } );  // store the record
            d_id[record.id()] = key;        // store id -> key, used by udpOut
        }

        return;
    }

    auto iter = d_udp.find(key);            // find the accumulated data

    if (iter != d_udp.end())                // available: 
        iter->second.addReceivedBytes(record.payload());    // add #received
}





