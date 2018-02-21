#include "connectionsconsumer.ih"

void ConnectionsConsumer::udpInDev(Record *record)
{
    if (g_nic.mask(Record::IN, record->sourceIP()))     // package is sent
        udpSent(record);

    else if (g_nic.mask(Record::IN, record->destIP()))  // package is received
        udpReceived(record);
}





