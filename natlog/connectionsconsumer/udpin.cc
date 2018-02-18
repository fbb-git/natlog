#include "connectionsconsumer.ih"

void ConnectionsConsumer::udpIn(Record *record)
{
    if (g_nic.mask(Record::IN, record->sourceIP()))     // package is sent
        udpOutbound(record);

    else if (g_nic.mask(Record::IN, record->destIP()))  // package is received
        udpInbound(record);
}





