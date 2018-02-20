#include "connectionsconsumer.ih"

void ConnectionsConsumer::icmpInDev(Record *record)
{
//CERR << '\n';

    if (g_nic.mask(Record::IN, record->sourceIP())) // package is sent
        icmpSent(record);
                                                    // package is received
    else if (g_nic.mask(Record::IN, record->destIP())) 
        icmpReceived(record);
}

