#include "connectionsconsumer.ih"

void ConnectionsConsumer::icmpOutbound(Record *record)
{
//CERR << '\n';
                                        // when connecting the local net
                                        // ignore the record
    if (not g_nic.mask(Record::IN, record->destIP()))
    {
                                        // existing record: add sent bytes
        if (auto iter = d_icmp.find(record->IDKey()); iter != d_icmp.end())
//{
            iter->second->addSentBytes(record);
//CERR << "SENT: " << *iter->second << '\n';
//}
        else                            
        {                               // or store a new connection
            d_icmp.insert( value_type{ record->IDKey(), record } );
            record->addSentBytes(record);
//CERR << "STORED: " << *record << '\n';
            return;
        }
    }                                   // or ignore the record

    delete record;
}
