#include "connectionsconsumer.ih"

void ConnectionsConsumer::icmpDestroy(Record *record)
{
//    auto iter = d_icmp.find(record->key()); // find this record's data
//
//    if (iter == d_icmp.end())            // unknown record: matching NEW 
//        return;                         // not seen during this program's
//                                        // lifetime 
//    iter->second->setEndTime(record);
//    iter->second->addSentBytes(record->sentBytes());
//    iter->second->addReceivedBytes(record->receivedBytes());
//
//    logICMP(iter->second);
//    erase(d_icmp, iter);                // remove the entry
}
