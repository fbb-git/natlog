#include "connectionsconsumer.ih"

void ConnectionsConsumer::udpReceived(Record *record)
{
                                        // when remaining inside the local net
                                        // ignore the record
    if (not g_nic.mask(Record::IN, record->sourceIP()))
    {
                                        // existing connection: 
                                        // add received bytes
        if (auto iter = d_udp.find(record->dstKey()); iter != d_udp.end())
            iter->second->addReceivedBytes(record);
    }

    delete record;
}
