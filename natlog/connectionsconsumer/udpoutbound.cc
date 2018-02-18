#include "connectionsconsumer.ih"

void ConnectionsConsumer::udpOutbound(Record *record)
{
                                        // when connecting the local net
                                        // ignore the record
    if (not g_nic.mask(Record::IN, record->destIP()))
    {
                                        // existing record: add sent bytes
        if (auto iter = d_udp.find(record->srcKey()); iter != d_udp.end())
            iter->second->addSentBytes(record);
        else                            
        {                               // or store a new connection
            d_udp.insert( value_type{ record->IDKey(), record } );
            record->addSentBytes(record);
            return;
        }
    }                                   // or ignore the record

    delete record;
}
