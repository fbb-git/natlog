#include "connectionsconsumer.ih"

void ConnectionsConsumer::udp(Record &record)
{
    lock_guard<mutex> lg(d_udpMutex);

    auto iter = d_udp.find(record.id());    // look for this ID

    if (iter == d_udp.end())                // not found: maybe store record 
    {
        switch (record.type())
        {
            case Record::IN:
                record.addSentBytes(record.payload());  // initial payload
                d_udp.insert( value_type{ record.id(), record } );
            [[fallthrough]]

            case Record::OUT:
            return;

            default:                        // CONNTRACK types (NEW, DELETE)
            break;
        }
    }

    switch (record.type())
    {
        case Record::IN:            // 2nd time this connection on the IN dev.
                                    // ends this connection
            iter->second.addReceivedBytes(record.payload());
        break;                      // check timeouts when receviing new IN-
                                    // connections

        case Record::OUT:
            if 
            (
                iter->second.destIP() == record.destIP()
                and
                iter->second.destPort() == record.destPort()
            )
            {
                iter->second.setViaIP(record.sourceIP());
                iter->second.setViaPort(record.sourcePort());
            }
        return;

        case Record::NEW:
           d_udp.insert( value_type{ record.key(), record } );
         return;

        case Record::DESTROY:
            udpDestroy(record);
        return;
    }
}


