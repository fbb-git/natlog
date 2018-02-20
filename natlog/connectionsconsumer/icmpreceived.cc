#include "connectionsconsumer.ih"

void ConnectionsConsumer::icmpReceived(Record *record)
{
//CERR << '\n';
                                        // when inside the local net
                                        // ignore the record
    if (not g_nic.mask(Record::IN, record->sourceIP()))
    {
                                        // existing connection: 
                                        // add received bytes
        if (auto iter = d_icmp.find(record->IDKey()); iter != d_udp.end())
//{
            iter->second->addReceivedBytes(record);
//CERR << "RECEIVED: " << *iter->second << '\n';
//}
//else
//CERR << "NO ID " << record->IDKey() << '\n';

    }
//else
//CERR << "LOCAL CONNECTION\n";

    delete record;
}
