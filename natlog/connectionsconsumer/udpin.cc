#include "connectionsconsumer.ih"

void ConnectionsConsumer::udpIn(Record *record)
{
//    size_t key = record->setTCPUDPkey();     // find the key
//
//    if (g_nic.mask(Record::IN, record->sourceIP())) // package is sent?
//    {
//                                            // connecting the local net?
//                                            // then ignore the record
//        if (g_nic.mask(Record::IN, record->destIP()))
//            return;
//
//                                            // if accumulated data exist
//                                            // then update #sent
//        if (auto iter = d_udp.find(key); iter != d_udp.end())
//        {
//            iter->second->addSentBytes(record->payload());
//            iter->second->setEndTime(record);
//        }
//        else                                // or it's a new connection
//        {                                   
//            record->addSentBytes(record->payload());      // set #sent
//            d_udp.insert( value_type{ key, record } );  // store the record
//            d_id[record->id()] = key;        // store id -> key, used by udpOut
//        }
//
//        return;
//    }
//
//    auto iter = d_udp.find(key);            // find the accumulated data
//
//    if (iter == d_udp.end())                // not available: done
//        return;
//
//    iter->second->addReceivedBytes(record->payload());    // add #received
//    iter->second->setEndTime(record);
}





