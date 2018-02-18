#include "connectionsconsumer.ih"

void ConnectionsConsumer::icmpIn(Record *record)
{
    if (g_nic.mask(Record::IN, record->sourceIP())) // package being sent?
    {
                                            // connecting the local net?
                                            // then ignore the record
        if (g_nic.mask(Record::IN, record->destIP()))
            return;
                                            // key is the record's ID
                                            // existing entry:
        if (auto iter = d_icmp.find(record->key()); iter != d_icmp.end())
        {
            iter->second->addSentBytes(record->payload());
            iter->second->setEndTime(record);
        }
        else                                // new entry:
        {
            record->addSentBytes(record->payload());  // initial payload
            d_icmp.insert( value_type{ record->key(), record } );
        }

        return;                        
    }

    // source is not the local computer. This must be an answer, and the
    // record must therefore exist:

    auto iter = d_icmp.find(record->key());  // find the accumulated data

    if (iter == d_icmp.end())               // not available: done
        return;

    iter->second->addReceivedBytes(record->payload());    // add #received
    iter->second->setEndTime(record);
}

