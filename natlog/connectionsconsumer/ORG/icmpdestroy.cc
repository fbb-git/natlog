#include "connectionsconsumer.ih"

void ConnectionsConsumer::icmpDestroy(Record *record)
{
    auto iter = d_icmp.find(record->IDKey()); // find this record's data

    if (iter == d_icmp.end())            // unknown record: matching NEW 
        return;                          // not seen during this program's
                                         // lifetime 

    iter->second->addSentBytes(record);
    iter->second->addReceivedBytes(record);

    logICMP(iter->second);
    erase(d_icmp, iter);                // remove the entry
}
